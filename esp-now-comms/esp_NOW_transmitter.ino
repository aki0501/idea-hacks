//-----------------------------------------------------------
//ESP-NOW: Transmitter
//Ref: Random Nerd Tutorials https://randomnerdtutorials.com
//-----------------------------------------------------------
#include <esp_now.h>
#include <WiFi.h>
//-------------------------------------------------------------------------------------
uint8_t RxMACaddress[] = {0x08, 0xD1, 0xF9, 0x28, 0x90, 0x54};
//-------------------------------------------------------------------------------------
typedef struct TxStruct
{
  int potVal;
}TxStruct;
TxStruct sentData;
//-------------------------------------------------------------------------------------
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) //callback function
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
//======================================================================================
void setup()
{
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  //------------------------------------------------------------------------------------
  if(esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  else{
    Serial.println("Success: initialized ESP-NOW");
  }
  //-------------------------------------------------------------------------------------
  int ret = esp_now_register_send_cb(OnDataSent);
  if (ret == ESP_NOW_SEND_SUCCESS){
    Serial.println("SUCCESS: esp_now_register_send_cb");
  }
  else{
    Serial.println("FAIL: esp_now_register_send_cb");
  }
  //-------------------------------------------------------------------------------------
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, RxMACaddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  //-------------------------------------------------------------------------------------
  if(esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  } else {
    Serial.println("MacAddress Registered OK");
  }
}
//======================================================================================
void loop()
{
  sentData.potVal = 2;
  //-------------------------------------------------------------------------------------
  esp_err_t result = esp_now_send(RxMACaddress, (uint8_t *) &sentData, sizeof(sentData));
  Serial.println(result);
  Serial.println(ESP_OK);
  //-------------------------------------------------------------------------------------
  if (result == ESP_OK) Serial.println("Sent with success");
  else Serial.println("Error sending the data");
  //-------------------------------------------------------------------------------------
  delay(500);
}
