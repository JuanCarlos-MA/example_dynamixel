#include "ros/ros.h"
#include "dynamixel_sdk/dynamixel_sdk.h"     // Dynamixel SDK library


// 1.- Global variables
dynamixel::PortHandler *portHandler;         // Port handler
dynamixel::PacketHandler *packetHandler;     // Packet handler
int dxl_comm_result = COMM_TX_FAIL;          // Communication result
uint8_t dxl_error = 0;                       // Dynamixel error
uint16_t dxl_model_number;                   // Dynamixel model number


// User-function that utilize global variables
void ping(void) {
    for (int dxl_id = 1; dxl_id <= 3; ++dxl_id) {
	
    // Sending Instruction Packet
    dxl_comm_result = packetHandler -> ping(portHandler, dxl_id, &dxl_model_number, &dxl_error);
		
    // Analizing received Status Packet
    if (dxl_comm_result != COMM_SUCCESS) // If comm is not succesful
        printf("%s\n", packetHandler -> getTxRxResult(dxl_comm_result));
    else if (dxl_error != 0)             // If dynamixel got an error
        printf("%s\n", packetHandler -> getRxPacketError(dxl_error));
    else                                 // If everything is ok
        printf("Dynamixel %i has been successfully connected \n", dxl_id);
    }
}


int main(int argc, char **argv) {
    ros::init(argc, argv, "ping");
    ros::NodeHandle n;

    // -------------------------- INICIA CODIGO DE DINAMIXELSDK ------------------------------------  
    portHandler = dynamixel::PortHandler::getPortHandler("/dev/ttyUSB0"); // Linux: "/dev/ttyUSB0" 
    packetHandler = dynamixel::PacketHandler::getPacketHandler(1.0);      // Protocol version
    
    portHandler->openPort();                 // 2.- Open port
    portHandler->setBaudRate(1000000);       // 3.- Set baudrate (Ex. 9600, 57600, 1000000)

    ping();                                  // 4.- Execute a Command
        
    portHandler->closePort();                // 5.- Close port
  
    // -------------------------- TERMINA CODIGO DE DINAMIXELSDK -----------------------------------
    ros::spinOnce();
    return 0;
}
