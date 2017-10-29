#include <mcp2515.h>
#include <defaults.h>
#include <global.h>
#include <Canbus.h>
#include <mcp2515_defs.h>

//********************************Setup Loop*********************************//

void setup() {
  Serial.begin(1000000); // For debug use
  //Serial.println("CAN Read - Testing receival of CAN Bus message");
  delay(1000);

  Canbus.init(CANSPEED_500);  //Initialise MCP2515 CAN controller at the specified speed
   // Serial.println("CAN Init ok");
 // else
   // Serial.println("Can't init CAN");

  delay(1000);
}

//********************************Main Loop*********************************//

void loop(){

  tCAN message;
  //message.id = 1059;
  //message.header.length = 6;
  //message.data[0] = 0;
  //message.data[1] = 0;
  //message.data[2] = 2;
  //message.data[3] = 8;
  //message.data[4] = 13;
  //message.data[5] = 190;
  //message.data[6] = 0x00;
  //message.data[7] = 0x00;


if (mcp2515_check_message())
  {
    if (mcp2515_get_message(&message)) {
               Serial.print("t");

               Serial.print(message.id,HEX);
               Serial.print(message.header.length,HEX);

               for(int i=0;i<message.header.length;i++)
                {
                  if (message.data[i] < 255){
                    Serial.print(0,HEX);
                  }

                  Serial.print(message.data[i],HEX);
                }
              Serial.print('\r');
           }
     }
}
