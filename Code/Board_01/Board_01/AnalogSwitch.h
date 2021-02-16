#ifndef ANALOGSWITCH_H
#define ANALOGSWITCH_H

#include <Arduino.h>

class AnalogSwitch
{
private:
    // Variavel que Verifica o estado do botão no momento do teste
    int SwitchValue = 0;

    // Atualiza o Novo Valor do Botão para a Controladora CAN
    void AnalogSwitchUpdate(int Value);

public:
    // Pino conectado ao botão
    int Pin;

    // Verifica se o valor do Botão foi alterado
    void check();
};

#endif
