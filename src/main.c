/*
 * main.c
 * Projeto: Arduino | Python | HTML | Websocket
 * Criado por Guilherme Rodrigues em 28/03/2020
 *
*/

/** Inclusoes de arquivos **/
#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"

/** Definicoes Gerais **/
#define LED13           PB5

/** Definicoes de Macro Funcoes **/
#define CONF_PORT()     DDRB = _BV(LED13);
#define LED13_ON()      (PORTB |= _BV(LED13))  // Coloca 1 no PB5
#define LED13_OFF()     (PORTB &= ~_BV(LED13)) // Coloca 0 no PB5
#define LED13_WRITE(level) (level ? LED13_ON() : LED13_OFF()); // Coloca um nivel logico no PB5

/** Declaracao de variaveis Globais **/
unsigned char ledStatus = 0;

/** Corpo da funcao main **/
int main(void){
  CONF_PORT();
  USART_Init();

  for(;;)
  {
    LED13_WRITE(ledStatus);
    transmitByte(ledStatus);
    _delay_ms(1000);
    ledStatus = !ledStatus;
  }
}
