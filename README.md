# STM - LPT Print Queue System (LPQS)

# Overview
LPQS is a queue system for offices such as dean's office with simple workflow. It's a nice tool to make waiting
in queue process more tolerable by petitioners.

# Description
This project consists of three different layers for different purpouses connected together by several interfaces.
## STM32 Layer
STM32 microcontroller is used for controlling user display for selecting visit's case. This also have
LPT printer support to print in-queue number for petitioner. This device is connected with the rest of the system
by UART connection.
## Aggregate
This layer is handled by Raspberry Pi computer. Main task of it is to be a bridge between STM32 and web-based
application available for officers. Another important function is displaying current and upcomming
petitioners' numbers. The communication is provided by standard Ethernet network for officers and UART connection
for STM32 microcontroller.
## Web system
WebSys is an application available for officers, which allows to call for next petitioner and perform some
administrative tasks, like defining users or case categories.

# How to run
This section will be expanded when project will be in more mature stage.

# How to compile
STM32 software is compileable without any hacks or tricks. You must only connect PC10 pin with GPIO15 on RPi and
PC11 with GPIO14.

Aggregate layer is written in Python, so no compilation is needed, you need just run script using
Python 2.7 interpreter.

Web system needs some configuration. More details will be added soon.

# Future Improvements

# Attributions
This project is using Symfony 3 Framework standard distribution for web system layer.

# License
MIT - more information on LICENSE file.

# Credits
+ Norbert Langner
+ Jan Śmigielski

The project was conducted during the Microprocessor Lab course held by the Institute of Control and
Information Engineering, Poznan University of Technology.

Supervisor: Michał Fularz
