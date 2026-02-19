//
// Created by loogze on 2026/2/19.
//

#ifndef UNTITLED_INIT_H
#define UNTITLED_INIT_H

#define NTP1  "ntp1.aliyun.com"
#define NTP2  "ntp2.aliyun.com"
#define NTP3  "ntp3.aliyun.com"
#define FONT u8g2_font_wqy12_t_chinese2
#define ON_BOARD_LED 48

constexpr auto ssid = "TP-link_A67A";
constexpr auto passwd = "0852wppu,.";

inline void Init_System() {
    Serial.begin(9600);
    pinMode(ON_BOARD_LED,OUTPUT);
}

inline void Init_Senser() {
    if (bmp.begin()) {
        Serial.printf("Fail to start BMP20");
    }
    if (! aht.begin()) {
        Serial.println("Could not find AHT? Check wiring");
    }
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL, /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2, /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16, /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16, /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500);
}

inline void Init_Wifi() {
    WiFiClass::mode(WIFI_STA);
    WiFi.begin(ssid, passwd);
    Serial.printf("Connecting");
    while (WiFiClass::status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected.");
    Serial.println(WiFi.localIP());
}

inline void Init_Display() {
    u8g2.begin();
    u8g2.enableUTF8Print();
    u8g2.setFont(FONT);
}

inline void Init_Time() {
    time_t now;
    char strftime_buf[64];
    struct tm timeinfo{};

    time(&now);
    // 将时区设置为中国标准时间
    setenv("TZ", "CST-8", 1);
    tzset();

    localtime_r(&now, &timeinfo);
    strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
    ESP_LOGI(TAG, "The current date/time in Shanghai is: %s", strftime_buf);  //时间的分辨率为 1S
}
#endif //UNTITLED_INIT_H