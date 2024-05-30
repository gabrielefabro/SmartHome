# Smart Home Project

## Introduction

The Smart Home project was developed during a university course with the aim of creating a centralized system for managing the components of an intelligent home. The system is capable of generating random scenarios and saving them in a database for future analysis and optimizations.

## System Architecture

### Central Hub

The central hub is the core of the Smart Home system. It is responsible for communicating with all the home components, generating scenarios, and saving data in the database. The main functionalities of the hub include:

- **Device Management**: Connecting and controlling various home devices (lights, thermostats, cameras, etc.).
- **Scenario Generation**: Random creation of home usage scenarios.
- **Data Storage**: Recording the generated scenarios and usage data in the database.

### Home Components

The home components include various smart devices that can be controlled by the central hub. Each component initializes its own process, allowing for parallel and independent operation. Communication between these processes is facilitated via Redis, ensuring efficient data exchange and coordination. Some examples of components include:

- **Smart Lights**: Can be turned on, off, or adjusted according to scenarios.
- **Smart Thermostats**: Can regulate the home temperature based on scenarios.
- **Smart Camera**: Can record different parts of the house.
- **Smart Device**: represent the simple household appliances in common use and can be turned on, off or programmed.
- **Smat Sensor**: Can detect the temperature and humidity of the garden

### Database

The database is used to store the generated scenarios and usage data. This allows for data analysis to improve system efficiency and identify usage patterns.

## System Operation

### Device Connection

The central hub manages all connections and ensures smooth communication between the devices through Redis, which facilitates efficient data exchange and coordination.

### Scenario Generation

The central hub generates random scenarios based on predefined parameters. An example scenario might include:

- At 7:00 AM, turn on the living room lights.
- At 7:30 AM, set the thermostat to 22°C.
- At 8:00 AM, check temperature and humidity.

### Data Storage

Once a scenario is generated, the central hub saves the scenario details in the database. Each record in the database includes:

- **Timestamp**: The moment the scenario was generated.
- **Scenario Details**: The specific actions that are part of the scenario.
- **Action Outcomes**: The results of the actions performed on the devices.

## Conclusion

The Smart Home project represents a practical example of how technology can be used to create intelligent solutions for home management. The central hub, with its ability to generate random scenarios and save data in the database, offers a flexible and scalable platform for future extensions and improvements. Each home component initializing its own process ensures efficient and independent operation, with Redis facilitating effective communication between these processes, contributing to the overall robustness of the system.
