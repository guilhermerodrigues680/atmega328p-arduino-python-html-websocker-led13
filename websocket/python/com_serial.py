################################################
## com_serial.py
## - Modulo que realiza a leitura da porta serial
## Projeto: Arduino | Python | HTML | Websocket
## Criado por Guilherme Rodrigues em 28/03/2020
##
################################################


import serial


PORTA_SERIAL = '/dev/cu.usbmodem14201' # Mac
# PORTA_SERIAL = 'COM3' # Ex Porta Windows

SER = None

def init():
    # Inicia a comunicacao serial (Configuracao padrao: “9600,8,N,1”, sem timeout)
    global SER
    SER = serial.Serial(PORTA_SERIAL) 


def read_status_led():
    # Loop eterno para leitura continua da serial
    global SER
    byte = None

    # Fica presso no loop até receber um byte na porta serial
    while not(byte):
        byte = SER.read(1)
    
    # Transforma o byte em inteiro (O Atmega328P usa Little-endian e o ledStauts é um 'unsigned char')
    led_status = int.from_bytes(byte, byteorder='little', signed=False)
    # print("Leitura: ", led_status) # Le 1 byte da serial

    return led_status
