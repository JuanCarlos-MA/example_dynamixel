# example_dynamixel ROS package

## Descripción general
Tutorial de como instalar y usar los servomotores Dynamixel de Robotis dentro de ROS con la intensión de facilitar el trabajo a los nuevos programadores.

## Pre-requisitos
Se considera que la computadora del usuario ya tiene correctamente instalado ROS, GIT y que ya tiene la carpeta de `catkin_ws` correctamente inicializada.

Deberá contar con los siguientes componentes (o similares):
* Un servomotor [Dynamixel](http://www.robotis.us/dynamixel/) (ejemplo: Mx-28 Mx-106, etc.)
* Una Switched Modulated Power Supplier [SMPS](https://www.trossenrobotics.com/p/power-supply-12vdc-5a.aspx) de 12v @ 1A (El amperaje dependerá del número de servomotores simultáneamente conectados)
* Un [U2D2-PowerHubBoard](http://emanual.robotis.com/docs/en/parts/interface/u2d2_power_hub/) o la pareja [USB2Dynamixel](http://emanual.robotis.com/docs/en/parts/interface/usb2dynamixel/) + [SMPS2Dynamixel-Adapter](https://www.trossenrobotics.com/store/p/5886-SMPS2Dynamixel-Adapter.aspx)
* Al menos dos cables con conectores Dynamixel [3pins-TTL-comm](https://www.trossenrobotics.com/bioloid-servo-sensor-cables.aspx) o [4pins-RS485-comm](https://www.trossenrobotics.com/store/p/6264-Dynamixel-240mm-4-Pin-Cable-10-Pack.aspx)

<p align="center">
  <img width="460" height="300" src="https://images-na.ssl-images-amazon.com/images/I/712FNMH9KPL._SL1280_.jpg">
</p>

El primer paso es asegurarse de que el driver del USB2Dynamixel para Linux (Ubuntu) se encuentra instalado adecuadamente. Para ello, conectar el USB2Dynamixel al puerto USB y después ejecutar el siguiente comando en una Terminal:
```
ls /dev/tty* 
```

Se desplegará una lista de dispositivos. El USB2Dynamixel aparecerá como `/dev/ttyUSB0`. Sin embargo el número del puerto podría llegar a cambiar. En caso de contar con una máquina virtual, deberá habilitarse previamente el dispositivo USB en la sección de dispositivos. Para conocer el nombre exacto del dispositivo habilitado para el USB2Dynamixel, compare la lista de dispositivos cuando éste está conectado y cuando está desconectado.

Las últimas versiones de Linux ya contiene los drivers para el USB2Dynamixel. Por lo tanto la mayoría de los usuarios no necesitarán instalar el driver manualmente. En caso contrario, consultar esta referencia: https://www.ftdichip.com/Drivers/VCP.htm

Por último es necesario habilitar los permisos de lectura y escritura al nuevo dispositivo, para ello se emplea:
```
sudo chmod a+rw /dev/ttyUSB0 
```
   

## Proceso de instalación
En una Terminal ejecutar las siguientes instrucciones:
```
cd ~
git clone https://github.com/ROBOTIS-GIT/DynamixelSDK.git
```

Esto descargará el repositorio `DynamixelSDK` en nuestra carpeta personal. Dicho paquete descargado, es en realidad un conjunto de librerías diseñadas para diversos lenguajes de programación como JAVA, MATLAB, LabVIEW, C#, etc. y además contiene los archivos necesarios para diversos sistemas operativos. Leer referencia [1] para mayores detalles. Realmente sólo las carpetas  `ros` y `c++` tienen utilidad. En la primera se encuentra el paquete a utilizar como librería y la segunda contiene códigos de ejemplo para mover los motores. La manera más rápida de proceder con la instalación es utilizar el gestor (explorador) de archivos de  Ubuntu y copiar sólo la carpeta `ros` dentro de la carpeta `~/catkin_ws/src/`. Cambiar el nombre de la carpeta `ros`  por  `DynamixelSDK`.

Compilar el nuevo paquete `DynamixelSDK` para que pueda ser utilizado posteriormente por otros paquetes:
```
cd ~/catkin_ws
catkin build
source devel/setup.bash
```

El proceso de compilación debe terminar sin errores. Para verificar que funciona correctamente, se creó un ejemplo basado en el código `read_write.cpp` encontrado en la carpeta de ejemplos para `linux` en `c++`. A este código se le agregaron líneas para lanzar el nodo `read_write` y utilizar la librería `dynamixel_sdk` previamente creada. 

Para instalarlo, ejecutar las siguientes instrucciones: 
```
cd ~/catkin_ws/src
git clone https://github.com/aaceves/example_dynamixel.git
cd ~/catkin_ws
catkin build
source devel/setup.bash
```

## Ejemplo de ejecución
En dos Terminales diferentes ejecutar cada una de las siguientes lineas:
```
roscore
rosrun example_dynamixel read_write
```

Este programa moverá al motor a una posición específica. Se debe tener cuidado de que el baudrate del servomotor dynamixel sea `(34) 57600` y que su ID sea `1`. El protocolo de comunicación usado es el `1.0`. Estos valores se pueden cambiar, pero eso requiere de mayor conocimiento del uso de los servomotores. Se sugiere leer las referencias [2-5] para mayores detalles.

## Autores y colaboradores
Ese paquete fue originalmente desarrollado por Robotis y se encuentra disponibles en Internet [1], pero fue ajustado ligeramente por Marco, Sarai, Bryan y el Dr. Alejandro Aceves-López para que sean más comprensibles a los programadores nuevos de ROS.

## Referencias

1. Anónimo, "Dynamixel SDK ", [Online]. Available: http://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_sdk/overview/, [Accessed: 05-Jun-2019].
2. Anónimo, "Mx-28", [Online]. Available: http://emanual.robotis.com/docs/en/dxl/mx/mx-28/, [Accessed: 05-Jun-2019].
3. Anónimo, "Mx-106 ", [Online]. Available: http://emanual.robotis.com/docs/en/dxl/mx/mx-106/, [Accessed: 05-Jun-2019].
4. Anónimo, "Robotis Dynamixel RX-28 User Manual", [Online]. Available: http://www.hizook.com/files/users/3/RX-28_Robotis_Dynamixel_Servo_UserGuide.pdf, and https://www.manualslib.com/manual/141478/Robotis-Dynamixel-Rx-28.html, [Accessed: 05-Jun-2019].
5. Anónimo, "Robotis Dynamixel RX-64 User Manual", [Online]. Available: https://www.robotshop.com/media/files/pdf/robotis-bioloid-dynamixel-rx-64-manual.pdf, [Accessed: 05-Jun-2019].
