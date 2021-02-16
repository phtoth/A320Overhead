#include "AnalogSwitch.h"

// Funcão que verifica se o valor do switch foi alterado ou não
// Checar também a possibilidade de uso de IRQ aqui
void AnalogSwitch::check()
{
  // Lê o valor atual do switch
  int NewValue = analogRead(this->Pin);

  // Compara o valor atual com o valor antigo.
  // Caso haja mudança, sumente o valor para a função que atualiza o estado do switch
  // A condição considera que o valor seja até 2 valores para cima ou para baixo, considerando pequenas flutuações do sensor
  if (this->SwitchValue != NewValue && this->SwitchValue != this->SwitchValue + 2 && this->SwitchValue != this->SwitchValue - 2)
  {
    this->SwitchValue = NewValue;
    this->AnalogSwitchUpdate(this->SwitchValue);
  }
}

//Função que atualiza o novo valor do Analog Switch
void AnalogSwitch::AnalogSwitchUpdate(int Value)
{
  Serial.println(Value); // imprime o valor na porta serial
  // TO DO - Implementar Código do CANBUS Aqui
}
