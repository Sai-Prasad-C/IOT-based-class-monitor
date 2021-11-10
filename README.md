Overview
RFID tags being used by few institutions, but with minimal applications. For example, our own college Reva uses RFIDs in ID cards which are as of now being used only in libraries. Which can further meet more applications for Saving Institution’s Energy. 

Goals
1. Electricity Supply: Allowing power supply to a room only when a teacher or students with RFIDs in their ID  card enters in and Discontinuing Power Supply as soon as the last student or teacher leaves the room, with no ID with RFIDs in the room. 
2. Energy Density Management: Bulbs detecting movements and allowing only the Bulbs above to glow and Bulbs below whom no student occupies aren’t allow to glow. 

Scope of the Project
This model can be easily implemented with most the institutions around having WIFI connections and firewalls. Saving a lot of energy for the institution and reducing the electricity demands for the city. Demonstrating & Promoting this model to all the institutions that already use RFIDS or have a WIFI connections installed. 

Working Methodology
A room has to be installed with a RFID sensor at the entry which needs to be connected to a Microcontroller which has instructions to collect data from RFID tags of students and teachers and send it to cloud to store the details of people entering the room. 
When at least 1 person is in the room the power supply to the room is allowed and similarly if no person is in the room, the power supply is discontinued. 
Motion sensors are used to monitor the movements below so as to allow that particular Blub or Any light source to Glow.

System requirements:
1. Arduino IDE
2. Arduino Drivers
3. Python 3+
4. Python IDE(any)
5. Pyfirmata package
6. Mysql-Connector
7. MySQL or WAMP Server

Components Required for Prototype:
1. Arduino
2. MFRC RFID sensor
3. LEDs
5. Wires
6. Ultrasonic Sensors
