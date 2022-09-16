import mqtt from 'mqtt'
import EspData from './types'

interface PublishI {
    topic: string,
    message: string,
    qos: mqtt.QoS
}

export default function mqtt_publish(client: mqtt.MqttClient, props: PublishI) {
    if (!client.connected) return;
    client.publish(props.topic, props.message, {qos: props.qos})
}

export function handleMessage(topic: string, message: string, data: EspData): EspData {
    const msgData = JSON.parse(message)
    if (msgData.sender == 'server') return {...data};
    
    const context = topic.split('/').at(-1)

    if (context == 'temperatura') {
        return handle_temperature(msgData, data)
    }

    if (context == 'umidade') {
        return handle_humidity(msgData, data)
    }

    if (context == 'bomba') {
        return handle_pump(msgData, data)
    }

    return data
}

function handle_register() {};

function handle_temperature(msg: any, data: EspData) {
    const dataCopy = {...data}
    if (msg.type == 'ground') {
        dataCopy.data.temp.ground = msg.data
    }
    if (msg.type == 'env') {
        dataCopy.data.temp.environment = msg.data
    }
    return {...dataCopy}
}

function handle_humidity(msg: any, data: EspData) {
    const dataCopy = {...data}
    if (msg.type == 'ground') {
        dataCopy.data.hum.ground = msg.data
    }
    if (msg.type == 'env') {
        dataCopy.data.hum.environment = msg.data
    }
    return {...dataCopy}
}

function handle_pump(msg: any, data: EspData) {
    const dataCopy = {...data}
    dataCopy.data.pump.status = msg.data
    return {...dataCopy}
}