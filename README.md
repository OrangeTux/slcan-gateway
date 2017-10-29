# sclan-gateway

This sketch transforms an Arduino Uno with a CAN bus shield into a CAN232
ASCII/sclan gateway. It works with shields that use the [Michrochip MCP2515
CAN tranceiver][mcp2515]. The code has been tested with this [CAN bus
shield][tinytronics].

With this code one communicate with the Arduino using the CAN232 ASCII
protocol, also known as slcan. The sketch 'translates' the slcan messages into
native CAN frames and vice verca.

This sketch was inspired by [kahiroka/slcanuino][kahiroka/slcanuino].

## Dependencies

This project requires the [CAN Bus Arduino Library from Sparkfun][sparkfun].

## Supported commands

* tiiildd... - read a standard (11 bit) can frame

## License

slcan-gateway is licensed under the [MIT License](LICENCE).


[kahiroka/slcanuino]: https://github.com/kahiroka/slcanuino
[mcp2515]: http://ww1.microchip.com/downloads/en/DeviceDoc/21667E.pdf
[sparkfun]: https://github.com/sparkfun/SparkFun_CAN-Bus_Arduino_Library
[tinytronics]: https://www.tinytronics.nl/shop/nl/arduino/shields/can-bus-shield-mcp2515?search=can
