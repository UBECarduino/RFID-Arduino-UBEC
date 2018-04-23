#if 1
  #include <PN532_HSU.h>
  #include <PN532.h>
      
  PN532_HSU pn532hsu(Serial);
  PN532 nfc(pn532hsu);
#endif
  
void setup(void) {
  pinMode (13, OUTPUT);

//  Serial.println("Hello!");

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
//    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  
  nfc.setPassiveActivationRetries(0xFF);
  
  nfc.SAMConfig();
    
//  Serial.println("請感應票卡");
}

void loop(void) {

  digitalWrite(13, HIGH);
  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  
  uint8_t uidLength;                        
  
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
  
  if (success) {
//    Serial.print("卡號 UID：");
//    for (uint8_t i=0; i < uidLength; i++) 
//    {
//      Serial.print(" ");Serial.print(uid[i], HEX); 
//    }
//    Serial.println("");

    if (uid[0] == 174)
      digitalWrite(13, LOW);
      //Serial.print("亮燈");Serial.println("");
      
    if (uid[0] == 4)
      digitalWrite(13, LOW);

    if (uid[0] == 190) //HP's UID
      digitalWrite(13, LOW);
      
    delay(1000);
  }
  else
  {
    // Serial.println("請感應票卡");
  }
}
