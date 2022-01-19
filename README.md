# Autonomous Can-Collecting Robot

Source code for an autonomous can collecting/stacking robot. This robot was fabricated over 6 weeks as a part of a UBC Engineering Physics project course called ENPH 253.

# Paths to Notable Directories

### Main Module: [/src/main.cpp][8]

- Master control loop responsible for scheduling robot tasks. Achieves multi-threaded, interrupt-driven control.

### Tasks Modules: [/src/robot-tasks/][1]
- Directory containing robot task modules. this project's firmware architecture was designed off of a task-paradigm, 
where all of the robot's desired functionality was split up into self contained tasks. These tasks access driver-level 
functions through different robot controller modules to achieve a specific behavior (for example, line following), and are scheduled for execution in a master
control loop.

- A `robot_task_t` struct was created to hold all data specific to tasks, like their mutex that controls 
when they should execute in the control loop, the time of last execution, and an unique identifier.

### Core Modules: [/src/robot-core/][2], [/src/robot-controllers/][3]

- These two directories contain methods that both interpret the raw signals entering the microcontroller, and drive the actuators that make the robot move.
Together they act as a hardware abstraction layer/controller library that can be used by task modules.

- Both the controller and core modules contain configuration structs that keep track of parameters important for achieving predictable robot behavior on boot 
and during each competition run. For example, the `line_following_controller_config_t` and `line_following_controller_state_t` structs in the 
[line-following-controller][4] module keep track of essential driving parameters like PID tuning values, max/min speed clamping values, and robot target velocity.

### Custom CLI: [/src/robot-cli/][5], [/src/robot-cli/command.cpp][6]

- The `robot-cli` directory contains all the modules relevant to the custom CLI (Command Line Interface) written specifically for this robot. Each CLI module
contains functions that can be called by the `robot-core/command` module after it parses messages sent over the robot's serial port. This means that the CLI can
be used for real time data collection/bug diagnosis without the need to constantly re-flash the microcontroller with updated firmware. 

- The CLI can also be used to change configuration values after the robot's firmware has been flashed. This cut our time spent tuning PID parameters by 
nearly 50% and also allowed for further PID tuning optimization. The [line-following-diagnostics][7] directory holds python scripts that run on a laptop
connected sharing a serial connection with the robot. This script can pull data from the robot at run time to evaluate performance.

[1]: https://github.com/graysonk546/enph-253-2021/tree/master/src/robot-tasks "/src/robot-tasks/"
[2]: https://github.com/graysonk546/enph-253-2021/tree/master/src/robot-core "/src/robot-core/"
[3]: https://github.com/graysonk546/enph-253-2021/tree/master/src/robot-control "/src/robot-control/"
[4]: https://github.com/graysonk546/enph-253-2021/blob/master/src/robot-control/line-following-controller.cpp "line-following-controller"
[5]: https://github.com/graysonk546/enph-253-2021/tree/master/src/robot-cli "/src/robot-cli/"
[6]: https://github.com/graysonk546/enph-253-2021/blob/master/src/robot-core/command.cpp "/src/robot-core/command.cpp"
[7]: https://github.com/graysonk546/enph-253-2021/tree/master/src/scripts/line-following-diagnostics "src/scripts/line-following-diagnostics/"
[8]: https://github.com/graysonk546/enph-253-2021/blob/master/src/main.cpp "/src/main.cpp"


