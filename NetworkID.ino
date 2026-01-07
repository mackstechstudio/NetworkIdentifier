#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include <TFT_eSPI.h> // Hardware-specific library

#define PIN_ETH_SS 10

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

byte ip[4]={ 0xc0, 0xa8, 0x7a, 0x7b };
byte mac[]={ 0x1E, 0xE8, 0x09, 0xE7, 0x56, 0xD8 };

void setup() {
  Serial.begin(115200);
  tft.init(); // Initialize the TFT display
  tft.setRotation(1); // Set display rotation (adjust as needed)
  tft.fillScreen(TFT_BLACK); // Fill the screen with black
  tft.setTextFont(2); // Set font (e.g., 2 for a system font)
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // Set text color (white) and background color (black)  Serial.begin(9600);
  tft.setTextSize(1);
  tft.setCursor(0, 0); // Set cursor to top-left corner
  Serial.println("Starting ...");
  tft.println("Starting ...");
  Ethernet.init(PIN_ETH_SS);
  Serial.println("Initializing NIC");
  tft.println("Initializing NIC");

  Ethernet.begin(mac,ip);
  if(Ethernet.hardwareStatus()==EthernetNoHardware) {
    Serial.println("Ethernet-Interface not found!");
    tft.println("Ethernet-Interface not found!");
  } else {
    bool DHCPsuccess = false;

    while (!DHCPsuccess) {
      if (Ethernet.begin(mac)) {
        Serial.print("IP: ");
        Serial.println(Ethernet.localIP());
        tft.print("IP: ");
        tft.println(Ethernet.localIP());
        Serial.print("Subnet Mask: ");
        Serial.println(Ethernet.subnetMask());
        tft.print("Subnet Mask: ");
        tft.println(Ethernet.subnetMask());
        Serial.print("Gateway: ");
        Serial.println(Ethernet.gatewayIP());
        tft.print("Gateway: ");
        tft.println(Ethernet.gatewayIP());
        Serial.print("DNS Server: ");
        Serial.println(Ethernet.dnsServerIP());
        tft.print("DNS Server: ");
        tft.println(Ethernet.dnsServerIP());
        DHCPsuccess = true;
      } else {
        //timed out 60 secs.
        Serial.println(F("Timeout."));
        Serial.println(F("Check Ethernet cable."));
        Serial.println(F("Retring DHCP..."));
      }
    }
  }
}

void loop() {
  delay(100);
}
