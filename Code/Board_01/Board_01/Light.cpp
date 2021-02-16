#include "Light.h"

//Seta os Pinos de Comunicação como OUTPUT
void LightController::setup()
{
   pinMode(this->latchPin, OUTPUT);
   pinMode(this->clockPin, OUTPUT);
   pinMode(this->dataPin, OUTPUT);
}

//Função que verifica se o estado dos Leds foi alterado
//Como Parametro são enviados o módulo do Led e o valor atual, que será comparado com o anterior
//Caso o valor seja alterado, é chamada a função que atualiza os Leds Acesos
void LightController::CheckData(int Value, int Module)
{
   //Se Value é 256, indica que o modulo está em Self Test
   if (Value == 256)
   {
      this->SelfTest(1);
   }
   else
   {
      switch (Module)
      {
      case '1':
         if (Value != this->LastData01)
         {
            this->LastData01 = Value;
            this->UpdateLights();
         }
         break;
      case '2':
         if (Value != this->LastData02)
         {
            this->LastData02 = Value;
            this->UpdateLights();
         }
         break;
      case '3':
         if (Value != this->LastData03)
         {
            this->LastData03 = Value;
            this->UpdateLights();
         }
         break;
      case '4':
         if (Value != this->LastData04)
         {
            this->LastData04 = Value;
            this->UpdateLights();
         }
         break;
      }
   }
}

// Função que atualiza quais Leds estão acesos e quais apagados
// A sequencia envia primeiro os leds do quarto banco, depois do terceiro, até o primeiro
void LightController::UpdateLights()
{
   //Mudamos o pino de latch para LOW, assim o controlador não muda de estado enquanto atualizamos os valores
   digitalWrite(latchPin, LOW);

   //Atualiza o Quarto Modulo 74HC595
   shiftOut(dataPin, clockPin, MSBFIRST, this->LastData04);

   //Atualiza o Terceiro Modulo 74HC595
   shiftOut(dataPin, clockPin, MSBFIRST, this->LastData03);

   //Atualiza o Segundo Modulo 74HC595
   shiftOut(dataPin, clockPin, MSBFIRST, this->LastData02);

   //Atualiza o Primeiro Modulo 74HC595
   shiftOut(dataPin, clockPin, MSBFIRST, this->LastData01);

   //Mudamos o pino de latch para HIGH, atualizando os Leds Acesos / Apagados
   digitalWrite(latchPin, HIGH);
}

//Função que acende todos os Leds para Teste de Funcionamento
// O valor passado como parametro pode ser 1 para Ligado ou 0 para Desligado
void LightController::SelfTest(int Value)
{
   if (Value == 1)
   {
      //Mudamos o pino de latch para LOW, assim o controlador não muda de estado enquanto atualizamos os valores
      digitalWrite(latchPin, LOW);

      //Atualiza o Quarto Modulo 74HC595
      shiftOut(dataPin, clockPin, MSBFIRST, 255);

      //Atualiza o Terceiro Modulo 74HC595
      shiftOut(dataPin, clockPin, MSBFIRST, 255);

      //Atualiza o Segundo Modulo 74HC595
      shiftOut(dataPin, clockPin, MSBFIRST, 255);

      //Atualiza o Primeiro Modulo 74HC595
      shiftOut(dataPin, clockPin, MSBFIRST, 255);

      //Mudamos o pino de latch para HIGH, atualizando os Leds Acesos / Apagados
      digitalWrite(latchPin, HIGH);
   }
   else if (Value == 0)
   {
      //Como o Valor dos Leds fica dentro das variaveis LastDataXX, basta executar a função UpdateLights para que o seu Estado Original Volte
      UpdateLights();
   }
}
