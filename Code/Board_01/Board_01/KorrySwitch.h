#ifndef KORRYSWITCH_H
#define KORRYSWITCH_H

#include <Arduino.h>

class KorrySwitch
{
private:
    // Variável que Controla se o botão já havia sido pressionado antes
    int ButtonState = 0;

    // Variável que controla o estado atual do Botão (HIGH ou LOW)
    int State = 0;

    // Variável que controla se o botão continua pressionado
    int IsPressed = 0;

    // Atualiza o Novo Valor do Botão para a Controladora CAN
    void KorrySwitchUpdate(int Value);

public:
    //Pino conectado ao botão
    int Pin;

    // Seta os Pinos de Comunicação como OUTPUT
    void setup();

    // Verifica se o Botão foi pressionado
    void check();

    //
};

#endif
