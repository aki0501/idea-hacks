//-----------------------------------------------------------
//ESP-NOW: Receiver
//Ref: Random Nerd Tutorials https://randomnerdtutorials.com
//-----------------------------------------------------------
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>

#include <SPIFFS.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
//-------------------------------------------------------------------------------------
// Adafruit_SSD1306 display(128, 64, &Wire, -1);
//-------------------------------------------------------------------------------------
//FUNCTION TO SAVE STRING TO TEXT FILE

String filename = "/matchUserData.txt";

void saveStringToFile(const String& data, const char* filename) {
  File file = SPIFFS.open(filename, "w");
  if (!file) {
    Serial.println("Error opening file for writing");
    return;
  }
  if (file) {
    file.print(data);
    file.close();
    Serial.println("File saved successfully.");
  } else {
    Serial.println("Error saving file.");
  }
}

typedef struct RxStruct
{
  char contents[1024];
}RxStruct;
RxStruct receivedData;
//-------------------------------------------------------------------------------------
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len)
{
  memcpy(&receivedData, incomingData, sizeof(receivedData));
}
//======================================================================================
void setup()
{
  Serial.begin(9600);
  // if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  // {
  //   Serial.println(F("SSD1306 allocation failed"));
  //   for (;;); // Don't proceed, loop forever
  // }
  // display.clearDisplay();
  //-------------------------------------------------------------------------------------
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  else{
    Serial.println("ESP Now successful init");
  }
  int ret = esp_now_register_recv_cb(OnDataRecv);
  if (ret == ESP_NOW_SEND_SUCCESS){
    Serial.println("ESP_NOW_SEND_SUCCESS");
  }
  else{
    Serial.println("ESP_NOW_SEND_FAIL");
  }
}
//======================================================================================
void loop()
{
  Serial.println(receivedData.contents);
  saveStringToFile(receivedData.contents, filename);
  // display.setTextColor(WHITE); display.clearDisplay();
  // display.setTextSize(2); display.setCursor(20,0); display.print("ESP-NOW");
  // display.setCursor(10,18); display.print("POT Value");
  // display.setTextSize(3); display.setCursor(25,42); display.print(receivedData.potVal);
  // display.display();
}
