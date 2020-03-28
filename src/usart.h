/*
 * usart.h
 * Criado por Guilherme Rodrigues em 28/03/2020
 *
*/

/* USART */

#ifndef USART_H
#define USART_H

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR ((FOSC / 16) / BAUD) - 1

void USART_Init(void);
void transmitByte(unsigned char byte);
void transmit2Bytes(unsigned int int16);
void printString(const char string[]);
void printByte(char byte);
void print2Bytes(int int16);

#endif /* USART_H */
