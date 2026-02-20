//
// Created by loogze on 2026/2/19.
//

#ifndef UNTITLED_INIT_H
#define UNTITLED_INIT_H

#define NTP1  "ntp1.aliyun.com"
#define NTP2  "ntp2.aliyun.com"
#define NTP3  "ntp3.aliyun.com"
#define ON_BOARD_LED 48

const char ssid[] = "TP-LINK_A67A";
const char passwd[] = "0852wppu,.";
const int rxPin = 16;
const int txPin = 17;

inline void Init_System() {
    Serial.begin(9600);
    Serial2.begin(9600,SERIAL_8N1,rxPin,txPin);
    pinMode(ON_BOARD_LED,OUTPUT);
    Serial2.println("Sys OK");
}

inline void Init_Senser() {
    if (!bmp.begin()) {
        Serial2.printf("Fail to start BMP20");
    }
    if (! aht.begin()) {
        Serial2.println("Could not find AHT? Check wiring");
    }
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL, /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2, /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16, /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16, /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500);
    Serial2.println("Senser OK");
}

inline void Init_Wifi() {
    WiFiClass::mode(WIFI_STA);
    WiFi.begin(ssid, passwd);
    Serial2.printf("Connecting");
    while (WiFiClass::status() != WL_CONNECTED) {
        delay(150);
        digitalWrite(ON_BOARD_LED,HIGH);
        delay(150);
        digitalWrite(ON_BOARD_LED,LOW);
    }
    Serial2.println("");
    Serial2.print("WiFi connected IP:");
    Serial2.print(WiFi.localIP());
    Serial2.println("");
}

inline void Init_Display() {
    u8g2.begin();
    u8g2.enableUTF8Print();
    Serial2.println("U8G2 OK");
}
#endif //UNTITLED_INIT_H