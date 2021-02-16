#include "Light.h"
#include "KorrySwitch.h"
#include "AnalogSwitch.h"

// Aqui defimos os Pinos dos Botões e Controladoras de Led
// Controladora de Leds 01
#define PINLATCH_1 51
#define PINCLOCK_1 53
#define PINDATA_1 49

// Controladora de Leds 02
#define PINLATCH_2 50
#define PINCLOCK_2 48
#define PINDATA_2 52

// Korry Switches Pins
#define BTN_PIN_01 A5;

// Switches Analógicos
AnalogSwitch LDG_ELEV;
AnalogSwitch PACK_FLOW;
AnalogSwitch COCKPIT;
AnalogSwitch FWD_CABIN;

// Light Controllers
LightController LModule01;
LightController LModule02;

// Korry Switches
KorrySwitch ENG_1_FIRE;

void setup()
{
  Serial.begin(9600);

  // Modulo 01 que controla os quatro primeiros 74HC595
  LModule01.latchPin = PINLATCH_1;
  LModule01.clockPin = PINCLOCK_1;
  LModule01.dataPin = PINDATA_1;
  LModule01.setup();
  LModule01.CheckData(0, 1);
  LModule01.CheckData(0, 2);
  LModule01.CheckData(0, 3);
  LModule01.CheckData(0, 4);

  // Modulo 02 que controla demais 74HC595
  LModule02.latchPin = PINLATCH_2;
  LModule02.clockPin = PINCLOCK_2;
  LModule02.dataPin = PINDATA_2;
  LModule02.setup();
  LModule02.CheckData(0, 1);
  LModule02.CheckData(0, 2);
  LModule02.CheckData(0, 3);
  LModule02.CheckData(0, 4);

  // Analog Buttons
  // LDG_ELEV - Board - A04
  LDG_ELEV.Pin = A2;

  // PACK_FLOW Board - A02
  PACK_FLOW.Pin = A0;

  // COCKPIT Board - A01
  COCKPIT.Pin = A1;

  // FWD_CABIN - Board - A03
  FWD_CABIN.Pin = A3;

  // Korry Buttons
  ENG_1_FIRE.Pin = BTN_PIN_01;
  ENG_1_FIRE.setup();
}

void loop()
{
  // Já testado
  //LDG_ELEV.check();
  //PACK_FLOW.check();
  //COCKPIT.check();
  //FWD_CABIN.check();
  //LModule01.SelfTest(1);
  //LModule01.SelfTest(0);

  ENG_1_FIRE.check();
}
