/*
 * usart.c
 * Criado por Guilherme Rodrigues em 28/03/2020
 *
*/

/* USART */

#include <avr/io.h>
#include "usart.h"

void USART_Init()
{
	unsigned int ubrr = MYUBRR;
	UBRR0H = (unsigned char)(ubrr >> 8); //Set baud rate
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = ( 0<< RXEN0) | (1 << TXEN0); // Disable receiver and enable transmitter
	UCSR0C = (0 << USBS0) | (0b11 << UCSZ00); // 8 bits de dados, sem paridade e 1 stop bit.
}

/**Transmite 8bits - 1 Byte - char*/
void transmitByte(unsigned char byte)
{
	while (!(UCSR0A & (1 << UDRE0))); /* Wait for empty transmit buffer */
	UDR0 = byte; /* Put data into buffer, sends the data */
}

/**Transmite 16bits - 2 Bytes - int*/
void transmit2Bytes(unsigned int int16)
{
	// Um numero inteiro possui 16 bits = 2 bytes
	// Assim para transmiti-lo, é necessário enviar primeiro 
	// os bits mais significativos e depois os bits menos significativos

    transmitByte(int16 >> 8); // send most significan't byte
    transmitByte(int16); // send least significant byte
}

/**Imprime na serial uma sequencia de caracteres*/
void printString(const char string[])
{
    unsigned char i = 0;
    
    while (string[i])
    {
        transmitByte(string[i]);
        i++;
    }
}

/**Imprime na serial um numero de 8bits - 1 Byte - char*/
void printByte(char byte)
{
    // 1 Byte possui tamanho máximo de 3 bits
    // Se for negativo adiciona o charactere '-'
    // Pega o codigo do '0'(48, 0x30) e soma para obter o codigo do numero

    if (byte < 0){
        transmitByte('-');
        byte = -byte;
    }
    
    transmitByte(48 + (byte / 100)); // Centenas
    transmitByte(48 + ((byte / 10) % 10)); // Dezenas
    transmitByte(48 + (byte % 10)); // Unidade
}

/**Imprime na serial um numero de 16bits - 2 Bytes - int*/
void print2Bytes(int int16)
{
    // 1 Byte possui tamanho máximo de 3 bits
    // Se for negativo adiciona o charactere '-'
    // Pega o codigo do '0'(48, 0x30) e soma para obter o codigo do numero

    if (int16 < 0){
        transmitByte('-');
        int16 = -int16;
    }

    transmitByte(48 + (int16 / 10000)); // Dezenas de milhar
    transmitByte(48 + ((int16 / 1000) % 10)); // Unidades de milhar
    transmitByte(48 + ((int16 / 100) % 10)); // Centenas
    transmitByte(48 + ((int16 / 10) % 10)); // Dezenas
    transmitByte(48 + (int16 % 10)); // Unidade
}
