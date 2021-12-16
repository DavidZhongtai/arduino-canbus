#include <mcp_can.h>
#include <SPI.h>

const int SPI_CS_PIN = 10;
MCP_CAN CAN(SPI_CS_PIN);   

unsigned char canMsgAlt[8] = {0, 0, 0, 0, 0, 0, 0, 0};

int32_t altData = 1800025;

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

    canMsgAlt[0] = altData;
    canMsgAlt[1] = altData >> 8;
    canMsgAlt[2] = altData >> 16;
    CAN.sendMsgBuf(321, 0, 3, canMsgAlt);

    Serial.println(altData);//Print for debug

}
