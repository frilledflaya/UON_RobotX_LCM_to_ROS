# UON_RobotX_LCM_to_ROS
This repo should be cloned into ~/vmrc_ws/src/

which should've been created following the setup and installation of vmrc

https://bitbucket.org/osrf/vmrc/wiki/tutorials/SystemSetupInstall

## Mapping

At the moment this is only configured for the differential thrust config. VMRC haven't yet implemented the actuated thrust configuration.

| ROS Topic 	   | Data Type | Values     | LCM Channel          | LCM Message       | Field           | Values        |
| ---------------- |:---------:|:----------:| -------------------- | ----------------- | --------------- | ------------- |
| left_thrust_cmd  | Float32   |-1.0 to 1.0 | STM_CONTROL_RESPONSE | STM/control_msg_t | port_motor      | -1000 to 1000 |
| right_thrust_cmd | Float32   |-1.0 to 1.0 | STM_CONTROL_RESPONSE | STM/control_msg_t | starboard_motor | -1000 to 1000 |
