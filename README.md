# STM - LPT Print Queue System (LPQS)

# Overview
LPQS is a queue system for offices such as dean's office with simple workflow. It's a nice tool to make waiting
in queue process more tolerable by petitioners.

# Description
This project consists of three different layers for different purpouses connected together by several interfaces.
## STM32 Layer
STM32 microcontroller is used for controlling user display for selecting visit's case. This also have
LPT printer support to print in-queue number for petitioner. This device is connected with the rest of the system
by WiFi (ESP8266) module. 
## Aggregate and Web systsem
WebSys is an application available for officers, which allows to call for next petitioner and perform some
administrative tasks, like defining users or case categories. It also provides a web interface for STM32 board to request and receive next petitioner numbers.

# How to run
WebSys should be installed on Web Server, which provides PHP Interpreter and MySQL Database. Project has been tested on Apache2 server, but other ones should work too. Server needs to work on IP: 192.168.0.107 and Port 8000.

STM layer requires: LPT Printer, 2 buttons and ESP8266 WiFi module to work properly. Connection schema is presented below:

STM <-> Printer (LPT)
GPIOA - Pin 0..7 (Data lines)
GPIOB - Pin 6 (Button 1), Pin 7 (Button 2), Pin 8 (LPT ACK)
GPIOD - Pin 9 (LPT Busy)
GPIOE - Pin 10 (LPT Strobe)

STM <-> ESP8266 (UART4)
GPIOC - Pin 10 (Tx on STM, Rx on ESP), Pin 11 (Rx on STM, Tx on ESP)

Other connections are internal on STM32 Discovery boards.

# How to compile
STM32 software is compileable without any hacks or tricks.
WebSys requires working PHP instance on computer, MySQL database and Composer. The minimal install looks like following:
composer install  // please ignore errors at this step for the first time
php bin/console doctrine:database:create
php bin/console doctrine:schema:update --force
php bin/console fos:user:create username user@email.com password
php bin/console fos:user:promote username ROLE_SUPER_ADMIN
php bin/console cache:clear

# Future Improvements
- Printing images
- USB printing instead of obsolete LPT
- LCD Display for user
- Configuration without reflashing
- A lot more...

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
