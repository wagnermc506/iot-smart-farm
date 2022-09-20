from paho.mqtt import client as mqtt_client
from influxdb_conn import DEFAULTS, InfluxClient
import json

broker = 'localhost'
port = 1883
client_id = 'mqtt_listener'

influx_client = InfluxClient(**DEFAULTS)

def msg_handle(client, userdata, msg):
    prefix, device_id, context = msg.topic.split('/')
    data = json.loads(msg.payload.decode())
    if data['sender'] != 'esp':
        return
    influx_client.write(context, 'device_id', device_id, [(data['type'], data['data'])])

def connect_mqtt():
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)
    client = mqtt_client.Client(client_id)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client

def subscribe(client: mqtt_client, topic: str):
    # def on_message(client, userdata, msg):
    #     print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")

    client.subscribe(topic)

def run():
    client = connect_mqtt()
    client.on_message = msg_handle
    subscribe(client, 'IOT2022-1/+/temperatura')
    subscribe(client, 'IOT2022-1/+/umidade')
    subscribe(client, 'IOT2022-1/+/bomba')
    client.loop_forever()


if __name__ == '__main__':
    run()
