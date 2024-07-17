module Components {
    @ Manages the LED to be blinked.
    active component LED {

        #==========#
        # Commands #
        #==========#

        @ Command to enable or disable the LED blinking.
        async command BLINKING_ON_OFF(
            on_off: Fw.On @< Controls whether LED should blink
        )


        #===========#
        # Telemetry #
        #===========#

        @ Telemetry for reporting blink state.
        telemetry BlinkState: Fw.On

        @ Telemetry for number of transitions (blinks) the LED has made.
        telemetry LEDTransitions: U64


        #========#
        # Events #
        #========#

        @ Indicates bad argument for LED blinking.
        event InvalidBlinkArg(badArg: Fw.On) \
            severity warning low \
            format "Invalid Blink Arg: {}"

        @ Reports blinking state.
        event SetBlinkState(state: Fw.On) \
            severity activity high \
            format "Blinking state set to: {}"

        @ Controls the Blinking Interval (in ticks).
        event BlinkIntervalSet(interval: U32) \
            severity activity high \
            format "Blinking interval set to: {}"

        @ Reports the LED state.
        event LedState(on_off: Fw.On) \
            severity activity low \
            format "LED state is now: {}"


        #========#
        # Params #
        #========#

        @ Blinking interval (in ticks).
        param BLINK_INTERVAL: U32


        #=======#
        # Ports #
        #=======#

        @ Recieves calls from the rate group.
        sync input port run: Svc.Sched

        @ Sends calls to the GPIO Driver.
        output port gpioSet: Drv.GpioWrite


        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Port for sending command registrations
        command reg port cmdRegOut

        @ Port for receiving commands
        command recv port cmdIn

        @ Port for sending command responses
        command resp port cmdResponseOut

        @ Port for sending textual representation of events
        text event port logTextOut

        @ Port for sending events to downlink
        event port logOut

        @ Port for sending telemetry channels to downlink
        telemetry port tlmOut

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

    }
}
