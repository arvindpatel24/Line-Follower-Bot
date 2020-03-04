# Line-Follower-Bot
A Line Follower Bot for simple line path tracing.It can be used for 2-IR,3-IR,4-IR,5-IR or more.

 A Line Follower Robot, as the name suggests, is an automated guided vehicle, which follow a visual line embedded on the floor. Usually, the visual line is the path in which the line follower robot goes and it will be a black line on a white suface. Large line follower robots are usually used in industries for assisting the automated production process. They are also used in military applications, human assisiting purpose, delivery services, etc.

## Components used for line follower:

1. Arduino UNO
2. Motor Driver(L298n)
3. Bo Motors x 2
4. Chassis
5. IR Sensor array
6. Black Tape (Electrical Insulation Tape)
7. Connecting Wires
8. Power Supply
9. Battery Connector
10. Wheels


## Mechanical Design:

  In this project we have used acrylic material as our chassis, in which two BO motors are connected with the help of clamps nuts and bolts. Three wheels are connected, one of them is a caster wheel. The chassis is fitted with the help of bolting. To insert the motor driver, we have made a rack so as it can be more space and looks more presentable.

## Working of the robot :

  In this project, we have designed an Arduino based Line Follower Robot. The working of the project is pretty simple it detects the black line on the surface and move along that line. The detailed working is explained here. We need sensor to detect the line. For line detection logic, we used IR Sensor array, which consists of IR LED and Photodiode. It is placed in centre, so that whenever they come in to proximity of a reflective surface, the light emitted by IR LED will be detected by Photo diode.
  
The following is the working of an IR Sensor:
   In front of a light-coloured surface is high, the infrared light emitted by IR LED will be maximum reflected and will be detected by the Photdiode. In case of black surface, which has a low reflectance, the light gets completely absorbed by the black surface and doesn't reach the photodiode. Using the same principle, we have setup the IR Sensor array on the Line Follower Robot such that the IR Sensors are on the floor each. The motion of the line follower robot according to the sensor output is as shown in the following table:

  For example, if the right or left IR Sensor detects the black line, it means that there is a right or left curve (or turn) ahead. Arduino UNO detects this change and sends signal to motor driver accordingly. In order to turn right, the motor on the right side of the robot is slowed down using PWM, while the motor on the left side is run at normal speed. Arduino UNO continuously monitors the data from the sensor and turns the robot as per the line detected by them.

