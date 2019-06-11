# example_dynamixel ROS package

## Descripción general
Tutorial de como instalar y usar los servomotores Dynamixel de Robotis dentro de ROS con la intensión de facilitar el trabajo a los nuevos programadores.

## Pre-requisitos
Se considera que la computadora del usuario ya tiene correctamente instalado ROS, GIT y que ya tiene la carpeta de `catkin_ws` correctamente inicializada.

Deberá contar cos los siguientes componentes (o similares):
* Un servomotor Dynamixel (ejemplo: Mx-28 Mx-106, etc.)
* Un usb2dynamixel (http://emanual.robotis.com/docs/en/parts/interface/usb2dynamixel/)
* Una Switched Modulated Power Supplier SMPS de 12v @ 4A
* Un U2D2 Power Hub Board
* Al menos dos cables con canectores Dynamixel

Primero asegurarse que se instaló adecuadamente el driver del USB2Dynamicel para Linux (Ubuntu) adecuadamente. LN101, FT232R USB UART, FTDI Chip https://www.ftdichip.com/Drivers/VCP.htm. In Linux VCP drivers are integrated into the kernel. Recent Linux releases include the kernel which contains the FT232RL driver for the FTDI driver used by USB2Dynamixel. Hence, most users won’t need to install the driver manually.

## Proceso de instalación
En una Terminal ejecutar las siguientes instrucciones:
```
Follow these guidelines:
http://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_sdk/library_setup/cpp_linux/#cpp-linux

$ cd ~/catkin_ws/src
$ git clone https://github.com/ROBOTIS-GIT/DynamixelSDK.git    (NO ESTOY SEGURO)
$ cd ~/catkin_ws
$ catkin build
$ source devel/setup.bash
```
El proceso de compilación debe terminar sin errores. 


## Ejemplo de ejecución

En dos Terminales diferentes ejecutar cada una de las siguientes lineas:
```
$ roscore
$ rosrun 
```


## Autores y colaboradores
Este paquete fue desarrollado a partir de programas de OpenCV disponibles en Internet, pero ajustados ligeramente por el Dr. Alejandro Aceves-López, xxxx, yyyyy,   zzzzz  para que sean más comprensibles a los programadores nuevos de ROS.

## Referencias

1. Anónimo, "Dynamixel SDK ", [Online]. Available: http://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_sdk/overview/, [Accessed: 05-Jun-2019].

