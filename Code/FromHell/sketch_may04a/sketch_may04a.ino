#include <oacsp.h>
int pressed = 0;
void setup() {
  OACSP.begin("MyCockpit");
  //OACSP.observeLVar("AB_MPL_FD");
  OACSP.observeLVar("AB_OVH_ELECGENL_FAULT");
  //OACSP.observeLVar("AB_OVH_ELECGENL");
  //OACSP.observeLVar("AB_OVH_ELECGENR");
  // OACSP.observeOffset(0x56CB, OAC::OFFSET_UINT8);
  //OACSP.observeOffset(0x56CC, OAC::OFFSET_UINT8);


  pinMode(13, OUTPUT);
  // pinMode(2, INPUT);


}


void loop() {
  OACSP.pollEvent();
  
  /*
  if (OAC::OffsetUpdateEvent* ev = OACSP.offsetUpdateEvent(0x56CB)) {
    if (ev->value == 1) {
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
    }
  }

  /*  if (OAC::OffsetUpdateEvent* ev = OACSP.offsetUpdateEvent(0x56CC)) {
    if(ev->value==1) {
     digitalWrite(13, HIGH);
          delay(500);
          digitalWrite(13,LOW);
          delay(500);
          digitalWrite(13, HIGH);
          delay(500);
          digitalWrite(13,LOW);
          delay(500);
          digitalWrite(13, HIGH);
          delay(500);
          digitalWrite(13,LOW);
          delay(500);
    }
    }


    */
    if (OAC::LVarUpdateEvent* ev = OACSP.lvarUpdateEvent("AB_OVH_ELECGENL_FAULT")) {

        if(ev->value==1) {
          digitalWrite(13, HIGH);
        }
        else {
          digitalWrite(13,LOW);
        }
        }
/*
        if (OAC::LVarUpdateEvent* ev = OACSP.lvarUpdateEvent("AB_OVH_PNEUBLEEDAPU")) {

        if(ev->value==1) {
          digitalWrite(13, HIGH);
          delay(500);
          digitalWrite(13,LOW);
          delay(500);
          digitalWrite(13, HIGH);
          delay(500);
          digitalWrite(13,LOW);
          delay(500);
          digitalWrite(13, HIGH);
          delay(500);
          digitalWrite(13,LOW);
          delay(500);
          digitalWrite(13, HIGH);
          delay(500);
          digitalWrite(13,LOW);
          delay(500);
          digitalWrite(13, HIGH);
          delay(500);
          digitalWrite(13,LOW);
          delay(500);

        }
        else {
          digitalWrite(13,LOW);
        }
        }

    int wasPressed = pressed;
    pressed = digitalRead(2);
    if (wasPressed != pressed) {
        OACSP.writeLVar("AB_MPL_FD", pressed);
    }

  */
}
