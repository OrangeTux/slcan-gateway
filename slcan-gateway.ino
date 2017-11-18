#include <mcp2515.h>
#include <defaults.h>
#include <global.h>
#include <Canbus.h>
#include <mcp2515_defs.h>

//********************************Setup Loop*********************************//
void setup() {
  Serial.begin(1000000); // For debug use
  delay(1000);

  Canbus.init(CANSPEED_500);  //Initialise MCP2515 CAN controller at the specified speed
  delay(1000);
}

//********************************Main Loop*********************************//

void loop() {
  ReadCanMessage();
  WriteCanMessage();
}


void ReadCanMessage() {
  tCAN message;

  if (mcp2515_check_message())
  {
    if (mcp2515_get_message(&message)) {
      Serial.print("t");

      Serial.print(message.id, HEX);
      Serial.print(message.header.length, HEX);

      for (int i = 0; i < message.header.length; i++)
      {
        if (message.data[i] < 255) {
          Serial.print(0, HEX);
        }
        Serial.print(message.data[i], HEX);
      }
      Serial.print('\r');
    }
  }
}

void WriteCanMessage() {
  tCAN message;
  static char buf[80];
  if (readline(Serial.read(), buf, 80) > 0) {

    switch (buf[0]) {
      case 't':
        // Assume the following message t10021133.

        // 0x100 is message id.
        sscanf(&buf[1], "%03x", &message.id);

        // 0x2 is length.
        int length;
        sscanf(&buf[4], "%01x", &length);
        message.header.length = length;

        // 0x11 and 0x33 are the 2 bytes of data.
        for (int i = 0; i < message.header.length; i++) {
          int val;
          sscanf(&buf[5 + (i * 2)], "%02x", &val);
          message.data[i] = val;
        }

        // Serial.print("send message\n");
        mcp2515_bit_modify(CANCTRL, (1 << REQOP2) | (1 << REQOP1) | (1 << REQOP0), 0);
        mcp2515_send_message(&message);
        break;
    }
  }
}

int readline(int readch, char *buffer, int len)
{
  static int pos = 0;
  int rpos;

  if (readch > 0) {
    switch (readch) {
      case '\r': // Return on CR
        rpos = pos;
        pos = 0;  // Reset position index ready for next time
        return rpos;
      default:
        if (pos < len - 1) {
          buffer[pos++] = readch;
          buffer[pos] = 0;
        }
    }
  }

  // No end of line has been found, so return -1.
  return -1;
}

