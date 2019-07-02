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

Esto descargará el repositorio `DynamixelSDK` en la carpeta personal de usuario. Dicho paquete descargado es en realidad un conjunto de librerías diseñadas para diversos lenguajes de programación como JAVA, MATLAB, LabVIEW, C#, etc. y además contiene los archivos necesarios para diversos sistemas operativos. Leer referencia [1] para mayores detalles. Realmente sólo las carpetas  `ros` y `c++` tienen utilidad. En la primera se encuentra el paquete a utilizar como librería y la segunda contiene códigos de ejemplo para mover los motores. La manera más rápida de proceder con la instalación es utilizar el gestor (explorador) de archivos de  Ubuntu y copiar sólo la carpeta `ros` dentro de la carpeta `~/catkin_ws/src/`. Cambiar el nombre de la carpeta `ros`  por  `DynamixelSDK`.

Compilar el nuevo paquete `DynamixelSDK` para que pueda ser utilizado posteriormente por otros paquetes. Para ello, ejecute los siguientes comandos:
```
cd ~/catkin_ws
catkin build
source devel/setup.bash
```

El proceso de compilación debe terminar sin errores. Ya puede borrar el repositorio original (generado por el comando `clone`) `DynamixelSDK` de la carpeta personal. Para ello use el gestor (explorador) de archivos de Ubuntu. ¡No borre nada más!.

Para conocer que servomotores están conectados, se puede usar el nodo `find_dynamixel` del paquete `dynamixel_workbench_controllers`. Siga el siguiente procedimiento para instalarlo y usarlo. Para más detalles leer referencia [6].

```
cd ~/catkin_ws/src
git clone https://github.com/ROBOTIS-GIT/dynamixel-workbench.git
git clone https://github.com/ROBOTIS-GIT/dynamixel-workbench-msgs.git
cd ~/catkin_ws
catkin build
source devel/setup.bash
```
Podrían aparecer Warnings sobre `No relevant classes found. No output generated` en ese caso ignórelo. El proceso de compilación debe terminar sin errores. El nodo `find_dynamixel` busca en los Baudrate (9600, 57600, 115200, 1000000, 2000000, 3000000, 4000000) y muestra los servomotores dynamixels encontrados. En dos Terminales diferentes ejecutar cada una de las siguientes lineas:
```
roscore
rosrun dynamixel_workbench_controllers find_dynamixel /dev/ttyUSB0
```
Si hay errores, el programa mostrará avisos como los siguientes:
```
[PortHandlerLinux::SetupPort] Error opening serial port!
[ WARN] [1562033264.693982660]: [DynamixelDriver] Failed to open the port!
[ WARN] [1562033264.694007892]: Failed to init
[ INFO] [1562033264.694017542]: Wait for scanning...
[ INFO] [1562033264.694418720]: Find 0 Dynamixels
 ```
Si este es el caso, repita la instrucción para otorgar permisos de lectura y escritura al dispositivo USB: ` sudo chmod a+rw /dev/ttyUSB0 `. Si todo está correcto, los mensajes serán del tipo:
```
[ INFO] [1562033454.445125756]: Succeed to init(1000000)
[ INFO] [1562033454.445174751]: Wait for scanning...
[ INFO] [1562033463.086145622]: Find 3 Dynamixels
[ INFO] [1562033463.086188124]: id : 1, model name : MX-28
[ INFO] [1562033463.086197548]: id : 2, model name : MX-106
[ INFO] [1562033463.086206021]: id : 3, model name : AX-12A

```

## Ejemplos de programas de usuario en ROS
Se creó un paquete llamada `example_dynamixel` con algunos programas basados en los ejemplos presentados en sitio de ROBOTIS GIT - Dinamixel SDK [7] en la carpeta `linux` en `c++`. Dichos programas utilizan la librería `dynamixel_sdk` previamente creada. 

Para instalar el paquete `example_dynamixel` ejecutar las siguientes instrucciones: 
```
cd ~/catkin_ws/src
git clone https://github.com/aaceves/example_dynamixel.git
cd ~/catkin_ws
catkin build
source devel/setup.bash
```
Se habrán dado de alta los siguientes nodos:

| <node_name> | Descripción | ./src/file |
| --- | --- | --- |
| read_write | Mueve el servo 1 de un lado al otro. El baudrate del servomotor debe ser 57600. | read_write.cpp | 
| ping | Ejecuta el comando ping a los ID = 1, 2 y 3 en un baudrate de 1000000 | ping.cpp | 

En dos Terminales diferentes ejecutar cada una de las siguientes lineas:
```
roscore
rosrun example_dynamixel <node_name>
```
El protocolo de comunicación usado es el `1.0`. Estos programas se pueden usar como base para programas más complejos, pero eso requiere de mayor conocimiento del uso de los servomotores. Se sugiere leer las referencias [2-5] para mayores detalles.

## Autores y colaboradores
Ese paquete fue originalmente desarrollado por Robotis y se encuentra disponibles en Internet [1], pero fue ajustado ligeramente por Marco, Sarai, Bryan y el Dr. Alejandro Aceves-López para que sean más comprensibles a los programadores nuevos de ROS.

## Referencias

1. Anónimo, "Dynamixel SDK ", [Online]. Available: http://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_sdk/overview/, [Accessed: 05-Jun-2019].
2. Anónimo, "Mx-28", [Online]. Available: http://emanual.robotis.com/docs/en/dxl/mx/mx-28/, [Accessed: 05-Jun-2019].
3. Anónimo, "Mx-106 ", [Online]. Available: http://emanual.robotis.com/docs/en/dxl/mx/mx-106/, [Accessed: 05-Jun-2019].
4. Anónimo, "Robotis Dynamixel RX-28 User Manual", [Online]. Available: http://www.hizook.com/files/users/3/RX-28_Robotis_Dynamixel_Servo_UserGuide.pdf, and https://www.manualslib.com/manual/141478/Robotis-Dynamixel-Rx-28.html, [Accessed: 05-Jun-2019].
5. Anónimo, "Robotis Dynamixel RX-64 User Manual", [Online]. Available: https://www.robotshop.com/media/files/pdf/robotis-bioloid-dynamixel-rx-64-manual.pdf, [Accessed: 05-Jun-2019].
6. Anónimo, "Dynamixel Workbench", [Online]. Available: http://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_workbench/, [Accessed: 05-Jun-2019].
7. Kei OpusK, et. al., " ROBOTIS GIT - Dynamixel SDK ", Available: https://github.com/ROBOTIS-GIT/DynamixelSDK, [Accessed: 05-Jun-2019].
