#include <SPI.h>
#include "mcp_can.h"

const int SPI_CS_PIN = 10;

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void setup() {
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_500KBPS)) {            // init can bus : baudrate = 500k
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(100);
    }
    Serial.println("CAN BUS Shield init ok!");
}


void loop() {
    unsigned char len = 0;
    unsigned char buf[8];
    
    if (CAN_MSGAVAIL == CAN.checkReceive()) {         // check if data coming
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        if (CAN.getCanId()== 321){
            int32_t altitude = buf[2];
            altitude = (altitude<<8)|buf[1];
            altitude = (altitude<<8)|buf[0];
            Serial.print("number: ");
            Serial.println(altitude); 
            Serial.println(len);
            delay(1000);
        }

       
    }
}
