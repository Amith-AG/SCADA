Title: Design and Implementation of a Miniature SCADA System for Industrial Parameter Monitoring and Control

Abstract:
This abstract presents a mini model Supervisory Control and Data Acquisition (SCADA) project consisting of eight interconnected block units. The project aims to develop a compact SCADA system that monitors critical parameters in a factory environment, such as temperature, humidity, and gas leakage, while providing control capabilities and warnings for enhanced safety and efficiency.

The microcontroller unit serves as the central processing unit, continuously monitoring the factory's critical parameters and controlling them. In the event of a gas leakage, it provides warnings and connects to the internet for remote monitoring and control. The project utilizes the NodeMCU ESP8266 development board, equipped with the ESP8266 chip, supporting a 32-bit LX106 RISC microprocessor with adjustable clock frequency.

The display unit presents real-time data of the monitored parameters, including temperature and humidity, providing operators with an overview of the factory conditions. The power supply unit ensures a stable 5V input voltage for the microcontroller and other components, utilizing a 9V battery and a 7805 IC voltage regulator.

The gas sensing unit employs the MQ4 gas sensor, which detects gas leakage and sends a high input signal to the NodeMCU for appropriate actions. The temperature and humidity sensing unit utilizes the DHT22 sensor to collect relevant data for precise environmental monitoring.

The heating system, comprising an incandescent light bulb, provides supplementary heat if the temperature falls below a user-defined critical range. Similarly, the cooling system, utilizing a 12V DC fan, offers cooling support if the temperature rises above the critical range.

Furthermore, the project includes a warning system that combines a buzzer and an LED to provide audible and visual alerts in the event of a gas leak, ensuring prompt response and enhanced safety measures.

The successful implementation of this mini SCADA project offers a cost-effective solution for real-time monitoring and control of critical parameters in a factory environment. It showcases the utilization of microcontrollers, sensors, and actuators to enable efficient decision-making and rapid response to abnormal conditions. This abstract sets the stage for a detailed exploration of the project's methodology, results, and potential future enhancements.
