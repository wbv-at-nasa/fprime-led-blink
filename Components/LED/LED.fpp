module Components {
    @ Manages the LED to be blinked.
    active component LED {

        @ Command to enable or disable the LED blinking.
        async command BLINKING_ON_OFF(
            on_off: Fw.On @< Controls whether LED should blink
        )

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

        ##############################################################################
        #### Uncomment the following examples to start customizing your component ####
        ##############################################################################

        # @ Example async command
        # async command COMMAND_NAME(param_name: U32)

        # @ Example telemetry counter
        # telemetry ExampleCounter: U64

        # @ Example event
        # event ExampleStateEvent(example_state: Fw.On) severity activity high id 0 format "State set to {}"

        # @ Example port: receiving calls from the rate group
        # sync input port run: Svc.Sched

        # @ Example parameter
        # param PARAMETER_NAME: U32

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
