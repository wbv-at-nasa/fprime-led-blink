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

  void LED ::
    BLINKING_ON_OFF_cmdHandler(
      FwOpcodeType opCode,
      U32 cmdSeq,
      Fw::On on_off
    )
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
  }

}
