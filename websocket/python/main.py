################################################
## main.py
## - Servidor websocket
## Projeto: Arduino | Python | HTML | Websocket
## Criado por Guilherme Rodrigues em 28/03/2020
##
################################################


import asyncio
import json
import websockets
import datetime

# Modulos locais
import com_serial


com_serial.init()


def status_led_event(status_led):
    return json.dumps({
        "status_led": status_led
    })


async def sync_status_led(websocket, path):
    print('-> Nova conexão - ', datetime.datetime.now().strftime("%X"))
    while True:
        status = com_serial.read_status_led()

        try:
            await websocket.send(status_led_event(status))

        except websockets.exceptions.ConnectionClosedError:
            print('-> Conexao fechada - ', datetime.datetime.now().strftime("%X"))
            break


# Inicia o servidor websocket na porta '6789' com loop eterno na função 'sync_status_led'
start_server = websockets.serve(sync_status_led, "0.0.0.0", 6789)
print("Servidor Em Execução")

asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()
