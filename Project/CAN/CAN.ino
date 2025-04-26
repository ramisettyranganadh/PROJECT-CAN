; PlatformIO Project Configuration File
;
;   Build options: build flags, source filter
;   Upload options: custom upload port, speed and extra flags
;   Library options: dependencies, extra library storages
;   Advanced options: extra scripting
;
; Please visit documentation for the other options and examples
; https://docs.platformio.org/page/projectconf.html

[env:uno]
platform = atmelavr
board = uno
framework = arduino
lib_deps = 
    autowp/MCP2515@^1.2.1
    arduino-libraries/SPI

#include <mcp2515.h>
#include <SPI.h>

#define CHIPSELECT      10

struct can_frame Message1;
struct can_frame Message2;

MCP2515 CAN2515(CHIPSELECT);

void setup(void) 
{
  // put your setup code here, to run once:
  Message1.can_id  = 0x1FEDCBA1 | CAN_EFF_FLAG;
  Message1.can_dlc = 8;
  Message1.data[0] = 0xF1;
  Message1.data[1] = 0xF1;
  Message1.data[2] = 0xF1;
  Message1.data[3] = 0xF1;
  Message1.data[4] = 0xF1;
  Message1.data[5] = 0xF1;
  Message1.data[6] = 0xF1;
  Message1.data[7] = 0xF1;
  
  Message2.can_id  = 0x1FEDCBA2 | CAN_EFF_FLAG;
  Message2.can_dlc = 8;
  Message2.data[0] = 0xF2;
  Message2.data[1] = 0xF2;
  Message2.data[2] = 0xF2;
  Message2.data[3] = 0xF2;
  Message2.data[4] = 0xF2;
  Message2.data[5] = 0xF2;
  Message2.data[6] = 0xF2;
  Message2.data[7] = 0xF2;

  while(!Serial);
  Serial.begin(115200);
  
  CAN2515.reset();
  CAN2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  //CAN2515.setLoopbackMode();
  CAN2515.setNormalMode();

  Serial.println("Example: Write to CAN");
  
  return;
}

void loop(void) 
{
  // put your main code here, to run repeatedly:
  
  if (CAN2515.readMessage(&Message1) == MCP2515::ERROR_OK) 
  {
      // frame contains received message
  }
  
  /* send out the message to the bus using second TX buffer and
  tell other devices this is a extended frame from 0x12345678. */
  CAN2515.sendMessage(MCP2515::TXB1, &Message2);
  
  Serial.println("MESSAGE 2 SENT");
  
  return;
}
