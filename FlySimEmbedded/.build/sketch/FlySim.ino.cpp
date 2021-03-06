#include <Arduino.h>
#line 1 "C:\\Users\\codes\\Documents\\Arduino\\generated_examples\\FlySim\\FlySim.ino"
#line 1 "C:\\Users\\codes\\Documents\\Arduino\\generated_examples\\FlySim\\FlySim.ino"
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. 
// To get started please visit https://microsoft.github.io/azure-iot-developer-kit/docs/projects/connect-iot-hub?utm_source=ArduinoExtension&utm_medium=ReleaseNote&utm_campaign=VSCode
#include "AzureIotHub.h"
#include "AZ3166WiFi.h"
#include "config.h"
#include "utility.h"
#include "iothub_client_sample_mqtt.h"
#include "Telemetry.h"

static bool hasWifi = false;
int messageCount = 1;

#line 14 "C:\\Users\\codes\\Documents\\Arduino\\generated_examples\\FlySim\\FlySim.ino"
void initWifi();
#line 31 "C:\\Users\\codes\\Documents\\Arduino\\generated_examples\\FlySim\\FlySim.ino"
void setup();
#line 50 "C:\\Users\\codes\\Documents\\Arduino\\generated_examples\\FlySim\\FlySim.ino"
void loop();
#line 14 "C:\\Users\\codes\\Documents\\Arduino\\generated_examples\\FlySim\\FlySim.ino"
void initWifi()
{
     Screen.print("IoT DevKit\r\n \r\nConnecting...\r\n");

    if (WiFi.begin() == WL_CONNECTED)
    {
        IPAddress ip = WiFi.localIP();
        Screen.print(1, ip.get_address());
        hasWifi = true;
        Screen.print(2, "Running... \r\n");
    }
    else
    {
        Screen.print(1, "No Wi-Fi\r\n ");
    }
}

void setup()
{
    hasWifi = false;
    initWifi();
    if (!hasWifi)
    {
        LogInfo("Please make sure the wifi connected!");
        return;
    }
    
    // Microsoft collects data to operate effectively and provide you the best experiences with our products. 
    // We collect data about the features you use, how often you use them, and how you use them.
    send_telemetry_data_async("", "HappyPathSetup", "");

    Serial.begin(115200);
    sensorInit();
    iothubInit();
}

void loop()
{
    char messagePayload[MESSAGE_MAX_LEN];
    bool temperatureAlert = readMessage(messageCount, messagePayload);
    iothubSendMessage((const unsigned char *)messagePayload, temperatureAlert);
    iothubLoop();
    delay(50);
}

