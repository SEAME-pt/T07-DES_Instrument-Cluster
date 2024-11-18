# **DES Project - Instrument Cluster**

- [**DES Project - Instrument Cluster**](#des-project---instrument-cluster)
  - [Introduction](#introduction)
  - [Background Information](#background-information)
  - [Project Goals and Objectives](#project-goals-and-objectives)
  - [Technical Requirements](#technical-requirements)
  - [Software Design](#software-design)
  - [Implementation](#implementation)
  - [Project Timeline](#project-timeline)
  - [Collaboration and Teamwork](#collaboration-and-teamwork)
  - [Results](#results)
  - [Submission](#submission)
  - [Evaluation](#evaluation)
  - [References](#references)

## Introduction

The PiRacer instrument cluster Qt application project is aimed at creating a real-time speedometer for a PiRacer car. The application will run on a Raspberry Pi and receive speed data from a speed sensor via the in-vehicle communication using Controller Area Network (CAN) protocol. This project will provide an opportunity for students to gain practical experience in software engineering, specifically in the areas of embedded systems, software architecture, and communication protocols. The project will also allow students to gain knowledge of the GUI frameworks (eg. Qt), that are widely used in the automotive industry for developing many embedded applications. The successful completion of this project will demonstrate the students' ability to design and implement a real-world software solution, and their ability to effectively communicate their results.  
</br>


## Background Information

This section would provide background information on the technologies and tools used in the project, including the Raspberry Pi, in-vehicle communication using CAN (Controller Area Network) protocol and Qt framework.

The Raspberry Pi is a small, low-cost computer that is commonly used for hobbyist and educational projects. It provides a versatile platform for developing a wide range of applications, including those in the automotive industry. The Qt framework is a popular cross-platform application development framework that is widely used in the automotive industry for developing embedded applications, such as instrument clusters and infotainment systems. The CAN protocol is a communication standard that is widely used in the automotive industry for interconnecting different ECUs (Electronic Control Units) in a vehicle.
</br>


## Project Goals and Objectives

The main goal of the PiRacer Instrument Cluster Qt Application project is to create a functioning instrument cluster for a PiRacer car that displays real-time speed data from a speed sensor via CAN bus.

The following are the specific objectives of the project:

1. To design and implement a Qt-based graphical user interface (GUI) for the instrument cluster.
2. To integrate an arduino based speed sensor system with the Raspberry Pi using the CAN bus protocol.
3. To display real-time speed data on the instrument cluster GUI.
4. To test the functionality of the instrument cluster using realistic driving scenarios.
5. To document the project in a comprehensive manner, including a detailed explanation of the system architecture, software design, implementation, results, and conclusions.
6. BONUS Part:
   1. To display battery level of PiRacer on Instrument Cluster.
</br>


## Technical Requirements

1. Raspberry Pi: The Raspberry Pi is a small, low-cost, single-board computer that is ideal for developing and testing embedded applications. A Raspberry Pi 3 Model B or later is recommended for this project, as it provides sufficient processing power and memory for running the instrument cluster application and receiving data from the speed sensor via CAN.
2. Qt (Open Source version): Qt Creator is a powerful, cross-platform integrated development environment (IDE) for developing applications with the Qt framework. The Qt libraries for Raspberry Pi include all of the necessary components for building Qt applications for the Raspberry Pi.
3. CAN bus interface: A CAN bus interface is required for connecting the Raspberry Pi to the vehicle's CAN bus and receiving speed data from the speed sensor. Suitable CAN bus interfaces for the Raspberry Pi include the MCP2515 and the TJA1050.
4. Speed sensor: A speed sensor capable of transmitting speed data via CAN is required for this project. The type of speed sensor required will depend on the vehicle being used for testing.
5. OBD-II cable: An OBD-II cable is required for connecting the Raspberry Pi and the speed sensor to the vehicle's CAN bus. This cable provides a convenient and reliable way to tap into the vehicle's CAN bus and receive data from the speed sensor.
6. Voltage regulator: A 12V to 5V voltage regulator is required for powering the Raspberry Pi from the vehicle's electrical system. The voltage regulator ensures that the Raspberry Pi receives a stable, regulated power supply, even when the vehicle's electrical system voltage fluctuates.
7. Display: A display is required for the instrument cluster application. Suitable displays include LCD and OLED displays, and the size and resolution of the display will depend on the specific requirements of the instrument cluster application.
8. Mounting hardware: A suitable method of mounting the display and Raspberry Pi in the vehicle is required. This may involve mounting brackets, enclosures, or other hardware, depending on the specific requirements of the instrument cluster application.
9. Vehicle for testing: Access to a PiRacer for testing the instrument cluster application is required. The PiRacer should have a CAN bus system and should be compatible with the speed sensor and other hardware components.

The students will be responsible for sourcing all of the required hardware components and ensuring that the hardware is compatible with the Raspberry Pi and the CAN bus interface. They will also be responsible for installing and configuring the operating system, the Qt framework, and any necessary drivers or libraries. The students will need to write and test the instrument cluster speedometer application, including the user interface, data processing, and CAN communication code. They will need to integrate the application with the hardware components and test the instrument cluster in a PiRacer. Finally, the students will be expected to document their work and demonstrate the instrument cluster application in a final presentation. This project delivers a solid understanding of software development and embedded systems, as well as the ability to work effectively in a team and to solve complex technical problems.  
</br>


## Software Design

The software design of the PiRacer instrument cluster application is based on the Qt framework, which is a popular cross-platform application development framework. Qt provides a wide range of tools and libraries that make it easy to create user-friendly graphical user interfaces (GUIs) and communicate with hardware devices.

The software design of the PiRacer instrument cluster consists of several key components, including the main application, the CAN communication module, and the data display module.

The main application is responsible for managing the overall functionality of the instrument cluster. It creates the GUI, manages the communication with the speed sensor via the CAN bus, and displays the speed data on the screen.

The CAN communication module is responsible for communicating with the speed sensor via the CAN bus. It receives speed data from the speed sensor and passes it on to the main application for display. This module uses the CAN library provided by Qt to communicate with the speed sensor.

The display module is responsible for displaying the speed data on the screen. It receives speed data from the main application and displays it in an easy-to-read format on the screen. This module can be customized to display the speed data in various ways, such as using a speedometer or a numerical display.

The software design of the PiRacer instrument cluster application is designed to be flexible and scalable, allowing for future modifications and additions. The use of the Qt framework and modular design also makes it easy to maintain and update the application. 
</br>


## Implementation

The implementation of the PiRacer instrument cluster application involves several key steps, including writing the code for the various components, testing the code, and deploying the application on the Raspberry Pi.

1. Writing the code: The first step in the implementation process is writing the code for the various components of the application. This includes writing the code for the main application, the CAN communication module, and the display module. The code should be written in a clear and organized manner, making use of best practices in software engineering.
2. Testing the code: After writing the code, it is important to test it to ensure that it works correctly and meets the technical requirements. This can be done by running the code on the Raspberry Pi and verifying that it correctly receives speed data from the speed sensor and displays it on the screen.
3. Deploying the application: Once the code has been tested and verified, the application can be deployed on the Raspberry Pi. This involves copying the code to the Raspberry Pi and executing it. The Raspberry Pi should be configured to boot up and run the application automatically upon startup.

The implementation process should be carefully planned and executed to ensure that the final product meets the technical requirements and provides a user-friendly interface for monitoring the speed of the vehicle. The implementation process should also be carefully documented, so that any future modifications or updates to the application can be made easily.
</br>


## Project Timeline

The PiRacer Instrument Cluster Qt Application project is expected to take approximately 6-8 weeks to complete, with the following estimated timeline:

* Week 1-2:
  * Research and familiarization with the CAN bus protocol, speed sensors, and Qt.
  * Design of the system architecture and software design.

* Week 3-4:
  * Implementation of the Qt-based GUI for the instrument cluster.
  * Integration of the speed sensor with the Raspberry Pi using the CAN bus protocol.

* Week 5-6:
  * Testing and debugging of the instrument cluster.
  * Verification of real-time speed data display on the instrument cluster GUI.

* Week 7-8:
  * Final documentation and report writing, including a detailed explanation of the system architecture, software design, implementation, results, and conclusions.
  * Preparation for final presentation and demonstration.
</br>


## Collaboration and Teamwork

Students will be working in teams of maximum four to complete this project. Each team member will be assigned specific tasks and responsibilities, and will be expected to contribute to the overall success of the project. Teams will be required to do check-ins on regular progress reports and feedback.  
</br>


## Results

The results of the PiRacer instrument cluster application can be evaluated based on the following factors:

1. Functionality: The most important factor in evaluating the results of the project is the functionality of the application. Does the application receive speed data from the speed sensor via CAN and display it on the screen in a user-friendly manner? If the answer is yes, then the application can be considered a success.
2. Usability: Another important factor in evaluating the results of the project is the usability of the application. Is the application user-friendly and easy to use? Does it provide a clear and intuitive interface for monitoring the speed of the vehicle? If the answer is yes, then the application can be considered a success.
3. Reliability: The reliability of the application is another important factor in evaluating the results of the project. Does the application run smoothly and consistently without any errors or crashes? If the answer is yes, then the application can be considered a success.
4. Maintainability: The maintainability of the application is another important factor in evaluating the results of the project. Is the code well-organized and easy to modify? Can future updates and modifications be made easily? If the answer is yes, then the application can be considered a success.

</br>


## Submission

Turn in a github repository with following information:

1. Code and relevant configuration files.
2. Detailed descriptions of algorithms and data structures used in the implementation.
3. Screenshots and diagrams of the instrument cluster user interface.
4. Detailed test plans, test cases, and results of software testing and debugging.
5. Detailed descriptions of the hardware components used in the project, including the Raspberry Pi and the speed sensor.
6. A list of online resources and tutorials used in the project.
7. Any additional material that supports the understanding of the project and provides context to the reader.  

</br>

## Evaluation
In this project, every team must host ONE final submission demo & presentation (max. 30 mins) in front of all the other teams. Each team must find a way to organize this presentation making sure that all the other teams can be present and participate actively (Please work out what date/time works the best for every team). The date and time of each team's presentation must be communicated to staff well in advance (at least a week in advance). It is presenting team's responsibility to make sure that all the forms are filled in **immediately** after the presentation.

This project has two evaluation forms:
1. For evaluators (the audience) - Fill in [this form](https://docs.google.com/forms/d/e/1FAIpQLSePixvxR1Bk-camL9IMAn8xDPxVNl3TAjwX7Z9ceruHsp9spA/viewform?usp=sf_link) to evaluate the presenting team's final project submission
2. For evaluatee (the presentor) - Fill in [this form](https://docs.google.com/forms/d/e/1FAIpQLSdnnoSJPRx1OrrhPhs-bLlVrBM1-n_cYO_QLZ7_ntLIuCL0Qw/viewform?usp=sf_link) for general feedback on your workings on this project.



## References

1. Embedded Systems Design with the Raspberry Pi, by Muhammed Ali, Packt Publishing (2017)
2. The Qt Company (2021). Qt 5.15.0 Reference Documentation. Available at: https://doc.qt.io/qt-5/index.html
3. Bosch, R. (2016). Automotive Handbook (9th edition). Springer.
4. SAE International (2018). J1939 Digital Annex Document, Society of Automotive Engineers, Warrendale, PA.
5. CAN in Automation (CiA) e.V. (2017). CAN FD Specification Version 1.0.
6. K. Mäntylä, T. Mäntylä (2008). “Requirements Engineering Processes in the Automotive Domain.” Journal of Systems and Software, vol. 81, no. 11, pp. 19-29.
7. H. Elmqvist, B. Englund (2010). “Qt Quick and QML for N950”. Available at: https://www.slideshare.net/QtDevelopment/qt-quick-and-qml-for-n950
8. Raspberry Pi Foundation (2021). Raspberry Pi Hardware Reference. Available at: https://www.raspberrypi.org/documentation/hardware/raspberrypi/
9. R. Davis (2016). “Agile Estimating and Planning”. Prentice Hall.
10. I. Sommerville (2011). “Software Engineering”. Addison-Wesley.  

</br>
