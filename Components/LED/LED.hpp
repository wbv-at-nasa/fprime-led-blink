// ======================================================================
// \title  LED.hpp
// \author wbv
// \brief  hpp file for LED component implementation class
// ======================================================================

#ifndef Components_LED_HPP
#define Components_LED_HPP

#include <Os/Mutex.hpp>
#include <Fw/Types/OnEnumAc.hpp>

#include "Components/LED/LEDComponentAc.hpp"

namespace Components {

  class LED :
    public LEDComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct LED object
      LED(
          const char* const compName //!< The component name
      );

      //! Destroy LED object
      ~LED();

    PRIVATE:

      //! Handler for the blink-toggle command, `BLINKING_ON_OFF`
      void BLINKING_ON_OFF_cmdHandler(
          FwOpcodeType opCode, //!< The opcode
          U32 cmdSeq,          //!< The command sequence number
          Fw::On on_off        //!< Controls whether LED should blink
      );

      //! TODO
      void parameterUpdated(
          FwPrmIdType id //!< ID of the (updated) parameter
      );

      //! TODO
      void run_handler(
        const NATIVE_INT_TYPE portNum, //!< Port number
        NATIVE_UINT_TYPE context       //!< The call order
      );

      Os::Mutex lock;  //!< Used to allow thread-safe control
      Fw::On state;    //!< Tracks whether LED state is on or off
      U64 transitions; //!< Number of LED on-off transitions that have occurred
      U32 count;       //!< Number of ticks the LED has been `On` for.
      bool blinking;   //!< Flag: whether blinking should be occurring

  };

}

#endif
