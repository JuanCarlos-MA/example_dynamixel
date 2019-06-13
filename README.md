# example_dynamixel ROS package

## Descripción general
Tutorial de como instalar y usar los servomotores Dynamixel de Robotis dentro de ROS con la intensión de facilitar el trabajo a los nuevos programadores.

## Pre-requisitos
Se considera que la computadora del usuario ya tiene correctamente instalado ROS, GIT y que ya tiene la carpeta de `catkin_ws` correctamente inicializada.

Deberá contar con los siguientes componentes (o similares):
* Un servomotor [Dynamixel](http://www.robotis.us/dynamixel/) (ejemplo: Mx-28 Mx-106, etc.)
* Un [usb2dynamixel](http://emanual.robotis.com/docs/en/parts/interface/usb2dynamixel/)
* Una Switched Modulated Power Supplier SMPS de 12v @ 4A
* Un [U2D2 Power Hub Board](http://emanual.robotis.com/docs/en/parts/interface/u2d2_power_hub/)
* Al menos dos cables con conectores Dynamixel

El primer paso es asegurarse de que el driver del USB2Dynamixel para Linux (Ubuntu) se encuentra instalado adecuadamente. Para ello se ejecuta el comando:

```$ ls /dev/tty* ```

Posteriormente se desplegará una lista de dispositivos. El USB2Dynamixel aparecerá como `/dev/ttyUSB0`. Sin embargo el número del puerto podría llegar a cambiar. En caso de contar con una máquina virtual, deberá habilitarse previamente el dispositivo USB en la sección de dispositivos.

Las últimas versiones de linux ya incluyen el kernel que contiene los drivers para el USB2Dynamixel. Por lo tanto la mayoría de los usuarios no necesitarán instalar el driver manualmente. En caso contrario, consultar esta referencia: https://www.ftdichip.com/Drivers/VCP.htm

Por último es necesario habilitar el puerto para que sea utilizado, para ello se emplea:

```$ sudo chmod a+rw /dev/ttyUSB0 ```

Este comando le asigna permisos de read y write al dispositivo.

## Proceso de instalación
En una Terminal ejecutar las siguientes instrucciones:
```
Follow these guidelines:
http://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_sdk/library_setup/cpp_linux/#cpp-linux

$ cd ~
$ git clone https://github.com/ROBOTIS-GIT/DynamixelSDK.git
```

Esto descargará el repositorio en nuestra carpeta personal. Dicho paquete descargado, es en realidad un conjunto de librerías diseñadas para diversos lenguajes de programación como JAVA, MATLAB, LabVIEW, C#, etc. y además contiene los archivos necesarios para diversos sistemas operativos. Realmente sólo las carpetas  `ros` y `c++` tienen utilidad. En la primera se encuentra el paquete a utilizar como librería y el segundo contiene códigos de ejemplo para mover los motores. La manera más rápida de proceder con la instalación es utilizar el gestor (explorador) de archivos de  Ubuntu y copiar sólo la carpeta `ros` dentro de la carpeta `~/catkin_ws/src/`. Cambiar el nombre de la carpeta `ros`a "DynamixelSDK".

Posteriormente se procede a compilar el paquete:

```
$ cd ~/catkin_ws
$ catkin build
$ source devel/setup.bash
```

El proceso de compilación debe terminar sin errores. Para proceder con el ejemplo, se creó un paquete basado en el código read_write.cpp encontrado en la carpeta de ejemplos para linux en c++. A este código se le agregaron líneas para lanzar un nodo y utilizar la librería de dynamixel previamente creada. 

Para instalarlo, ejecutar las siguientes instrucciones: 

```
$ cd ~/catkin_ws/src
$ git clone https://github.com/aaceves/example_dynamixel.git
$ cd ~/catkin_ws
$ catkin build
$ source devel/setup.bash
```


## Ejemplo de ejecución


En dos Terminales diferentes ejecutar cada una de las siguientes lineas:

```
$ roscore
$ rosrun example_dynamixel read_write
```

Este programa moverá al motor a una posición específica. Se debe tener cuidado de que el baudrate del dynamixel sea `34)   57600` y que el ID del motor sea `1`.

## Autores y colaboradores
Este paquete fue desarrollado a partir de programas de OpenCV disponibles en Internet, pero ajustados ligeramente por el Dr. Alejandro Aceves-López, xxxx, yyyyy,   zzzzz  para que sean más comprensibles a los programadores nuevos de ROS.

## Referencias

1. Anónimo, "Dynamixel SDK ", [Online]. Available: http://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_sdk/overview/, [Accessed: 05-Jun-2019].

