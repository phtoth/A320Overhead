#ifndef LIGHT_H
#define LIGHT_H

#include "Arduino.h"

class LightController
{

private:
  //Ultimo valor de dadps da Variavel LastData01
  int LastData01 = 0;

  //Ultimo valor de dadps da Variavel LastData02
  int LastData02 = 0;

  //Ultimo valor de dadps da Variavel LastData03
  int LastData03 = 0;

  //Ultimo valor de dadps da Variavel LastData04
  int LastData04 = 0;

public:
  //Pino conectado a porta ST_SP do 74HC595
  int latchPin;

  //Pino conectado a porta SH_CP do 74HC595
  int clockPin;

  //Pino conectado a porta DS do 74HC595
  int dataPin;

  //Seta os Pinos de Comunicação como OUTPUT
  void setup();

  //Função que verifica se o estado dos Leds foi alterado
  void CheckData(int Value, int Module);

  //Função que Atualiza os Leds Ligados e Desligados
  void UpdateLights();

  //Função que acende todos os Leds para Teste de Funcionamento
  // O valor passado como parametro pode ser 1 para Ligado ou 0 para Desligado
  void SelfTest(int Value);
};

#endif
