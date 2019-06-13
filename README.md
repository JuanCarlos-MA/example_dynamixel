# example_dynamixel ROS package

## Descripción general
Tutorial de como instalar y usar los servomotores Dynamixel de Robotis dentro de ROS con la intensión de facilitar el trabajo a los nuevos programadores.

## Pre-requisitos
Se considera que la computadora del usuario ya tiene correctamente instalado ROS, GIT y que ya tiene la carpeta de `catkin_ws` correctamente inicializada.

Deberá contar cos los siguientes componentes (o similares):
* Un servomotor [Dynamixel](http://www.robotis.us/dynamixel/) (ejemplo: Mx-28 Mx-106, etc.)
* Un [usb2dynamixel](http://emanual.robotis.com/docs/en/parts/interface/usb2dynamixel/)
* Una Switched Modulated Power Supplier SMPS de 12v @ 4A
* Un [U2D2 Power Hub Board](http://emanual.robotis.com/docs/en/parts/interface/u2d2_power_hub/)
* Al menos dos cables con conectores Dynamixel

El primer paso es asegurarse de que se instaló el driver del USB2Dynamixel para Linux (Ubuntu) adecuadamente. Para ello se ejecuta el comando:

```$ ls /dev/tty* ```

Posteriormente se desplegará una lista de dispositivos. El USB2Dynamixel aparecerá como `/dev/ttyUSB0`. Sin embargo el número del puerto podría llegar a cambiar. En caso de contar con una máquina virtual, deberá habilitarse previamente el dispositivo USB en la sección de dispositivos.

Las últimas versiones de linux incluyen el kernel que contiene los drivers para usados para el USB2Dynamixel. Por lo tanto la mayoría de los usuarios no necesitarán instalar el driver manualmente. En caso contrario, consultar esta referencia: https://www.ftdichip.com/Drivers/VCP.htm

Por último es necesario habilitar el puerto para que se utilizado, para ello se emplea:

```$ sudo chmod a+rw /dev/ttyUSB0 ```

## Proceso de instalación
En una Terminal ejecutar las siguientes instrucciones:
```
Follow these guidelines:
http://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_sdk/library_setup/cpp_linux/#cpp-linux

$ cd ~/catkin_ws/src
$ git clone https://github.com/aaceves/example_dynamixel.git
$ cd ~/catkin_ws
$ catkin build
$ source devel/setup.bash
```
El proceso de compilación debe terminar sin errores. El paquete descargado, es una subconjunto del paquete dynamixel_sdk, del cual se extrajo únicamente la carpeta de ROS, ya que dicho el GIT contiene librerías para MATLAB, LabVIEW, Python, C#, etc. El paquete completo se puede obtener de 




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

