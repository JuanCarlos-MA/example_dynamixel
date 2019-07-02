#include "ros/ros.h"
#include "dynamixel_sdk/dynamixel_sdk.h"     // Uses Dynamixel SDK library
#include "usefull_functions.cpp"             // Extra functions: getch()  &  kbhit()

// 1.- Global variables
#define DXL_ID                          1    // Dynamixel ID
#define DXL_MOVING_STATUS_THRESHOLD     10   // Dynamixel moving status threshold

dynamixel::PortHandler *portHandler;         // Port handler
dynamixel::PacketHandler *packetHandler;     // Packet handler

int indexs = 0;
int dxl_goal_position[2] = {100, 4000};      // Goal position
int dxl_comm_result = COMM_TX_FAIL;          // Communication result
uint8_t dxl_error = 0;                       // Dynamixel error
uint16_t dxl_present_position;               // Present position



// User-functions that utilize global variables

void read(void) {            // Read present position
	// Sending Instruction Packet
    dxl_comm_result = packetHandler->read2ByteTxRx(portHandler, DXL_ID, 36, &dxl_present_position, &dxl_error);
    
    // Analizing received Status Packet
    if (dxl_comm_result != COMM_SUCCESS)
        printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
    else if (dxl_error != 0)
        printf("%s\n", packetHandler->getRxPacketError(dxl_error));
}

void write(void) {        // Write goal position
	// Sending Instruction Packet
    dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, DXL_ID, 30, dxl_goal_position[indexs], &dxl_error);
        
    // Analizing received Status Packet
    if (dxl_comm_result != COMM_SUCCESS)
        printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
    else if (dxl_error != 0)
        printf("%s\n", packetHandler->getRxPacketError(dxl_error));
}

void torque_on(void) {     // Enable Dynamixel Torque
	// Sending Instruction Packet
    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_ID, 24, 1, &dxl_error);
    
    // Analizing received Status Packet
    if (dxl_comm_result != COMM_SUCCESS) 
        printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
    else if (dxl_error != 0)
        printf("%s\n", packetHandler->getRxPacketError(dxl_error));
    else
        printf("Torque successfully enabled \n");
}

void torque_off(void) {    // Disable Dynamixel Torque
	// Sending Instruction Packet
    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_ID, 24, 0, &dxl_error);
    
    // Analizing received Status Packet
    if (dxl_comm_result != COMM_SUCCESS)
        printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
    else if (dxl_error != 0)
        printf("%s\n", packetHandler->getRxPacketError(dxl_error));
    else
        printf("Torque successfully disabled \n");
}



int main(int argc, char **argv) {
    ros::init(argc, argv, "read_write");
    ros::NodeHandle n;

    // ---------------------------------- INICIA CODIGO DE DINAMIXELSDK ---------------------------------------------  
    portHandler = dynamixel::PortHandler::getPortHandler("/dev/ttyUSB0"); // Linux: "/dev/ttyUSB0" 
    packetHandler = dynamixel::PacketHandler::getPacketHandler(1.0);      // Protocol version

    portHandler->openPort();                 // 2.- Open port
    portHandler->setBaudRate(1000000);       // 3.- Set baudrate (Ex. 9600, 57600, 1000000)
    
    torque_on();                             // 4.- Torque ON command
    while(true) {
        printf("Press any key to continue! (or press ESC to quit!)\n");
        if (getch() == ESC_ASCII_VALUE)    break;
        write();                             // 4.- Write goal position command
        do {
            read();                          // 4.- Read present position command
            printf("[ID:%03d] GoalPos:%03d  PresPos:%03d\n", DXL_ID, dxl_goal_position[indexs], dxl_present_position);
        } while(abs(dxl_goal_position[indexs] - dxl_present_position) > DXL_MOVING_STATUS_THRESHOLD);
        // Change goal position
        if (indexs == 0)   indexs = 1;
        else               indexs = 0;
    }
    torque_off();                            // 4.- Torque OFF command
 
    // Close port
    portHandler->closePort();                // 5.- Close port
  
    // ---------------------------------- TERMINA CODIGO DE DINAMIXELSDK ---------------------------------------------
    ros::spinOnce();
    return 0;
}
