// ======================================================================
// \title  LED.cpp
// \author wbv
// \brief  cpp file for LED component implementation class
// ======================================================================

#include "Components/LED/LED.hpp"
#include "FpConfig.hpp"

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  LED ::
    LED(const char* const compName)
      : LEDComponentBase(compName)
      , state(Fw::On::OFF)
      , transitions(0)
      , count(0)
      , blinking(false)
  {

  }

  LED ::
    ~LED()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void LED::BLINKING_ON_OFF_cmdHandler(
      FwOpcodeType opCode,
      U32 cmdSeq,
      Fw::On on_off)
  {
    auto response = Fw::CmdResponse::VALIDATION_ERROR;

    if (on_off.isValid())
    {
      response = Fw::CmdResponse::OK;
      this->count = 0; // reset the count for this state change
      this->lock.lock();
      this->blinking = (on_off == Fw::On::ON);
      this->lock.unlock();
      this->log_ACTIVITY_HI_SetBlinkState(on_off);
    }
    else
    {
      this->log_WARNING_LO_InvalidBlinkArg(on_off);
    }

    this->cmdResponse_out(opCode, cmdSeq, response);
    this->tlmWrite_BlinkState(on_off);
  }

  void LED::parameterUpdated(FwPrmIdType id)
  {
    Fw::ParamValid valid = Fw::ParamValid::DEFAULT;
    auto interval = this->paramGet_BLINK_INTERVAL(valid);

    FW_ASSERT(valid == Fw::ParamValid::VALID, valid);

    if (id == PARAMID_BLINK_INTERVAL)
    {
      // TODO
    }

    log_ACTIVITY_HI_BlinkIntervalSet(interval);
  }

  void LED::run_handler(
    const NATIVE_INT_TYPE portNum,
    NATIVE_UINT_TYPE context
  )
  {
    Fw::ParamValid valid;
    U32 interval = paramGet_BLINK_INTERVAL(valid);

    // clamp `interval` to 0 if the param is bad
    if ((valid == Fw::ParamValid::INVALID) || (valid == Fw::ParamValid::UNINIT))
    {
      interval = 0;
    }

    this->lock.lock();
    bool is_blinking = this->blinking;
    this->lock.unlock();

    if (is_blinking)
    {
      auto next_state = state;
      if ((count == 0) && (state == Fw::On::OFF))
      {
        next_state = Fw::On::ON;
      }
      else if ((count == (interval / 2)) && (state == Fw::On::ON))
      {
        next_state = Fw::On::OFF;
      }

      // if state changes, then update the LED
      if (state != next_state)
      {
        transitions++;
        tlmWrite_LEDTransitions(transitions);

        // only set the actual gpio if we're connected
        if (isConnected_gpioSet_OutputPort(0))
        {
          Fw::Logic level = (next_state == Fw::On::ON) ? Fw::Logic::HIGH : Fw::Logic::LOW;
          gpioSet_out(0, level);
        }

        state = next_state;
        tlmWrite_BlinkState(state);
      }
      
      // increment `count`, wrapping around to 0 at `interval`
      if (++count >= interval)
      {
        count = 0;
      }
    }
    else // if not `is_blinking`, force the LED off
    {
      if (state == Fw::On::ON)
      {
        // only set the gpio if we're actually connected
        if (isConnected_gpioSet_OutputPort(0))
        {
          gpioSet_out(0, Fw::Logic::LOW);
        }

        state = Fw::On::OFF;
        // TODO: report LED state-change via event
      }
    }
  }
}
