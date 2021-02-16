#include "KorrySwitch.h"

//Seta os Pinos de Comunicação como OUTPUT
void KorrySwitch::setup()
{
  pinMode(this->Pin, OUTPUT);
}

//verificamos se o botão está sendo precionado ou não
// Checar também a possibilidade de uso de IRQ aqui
void KorrySwitch::check()
{
  this->State = digitalRead(this->Pin);

  if (this->State == HIGH && this->IsPressed == 0)
  {
    this->IsPressed = 1;
    // Aqui verificamos o estado anterior do Botão
    // Se era LOW, agora será HIGH, e vice-versa
    if (this->ButtonState == 0)
    {
      this->ButtonState = 1;
      this->KorrySwitchUpdate(1);
    }
    else
    {
      this->ButtonState = 0;
      this->KorrySwitchUpdate(0);
    }
  }
  else if (this->State == LOW && this->IsPressed == 1)
  {
    this->IsPressed = 0;
  }
}

// Função que atualiza o estado do botão para a
void KorrySwitch::KorrySwitchUpdate(int Value)
{
  Serial.println(Value); // imprime o valor na porta serial
  // TO DO - Implementar Código do CANBUS Aqui
}
