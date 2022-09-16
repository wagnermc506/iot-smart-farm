import { MqttClient } from "mqtt"

export interface TempData {
    environment: Number,
    ground: Number
}

export interface HumData {
    environment: Number,
    ground: Number
}

export interface PumpData {
    status: Boolean
}

export interface DataContainerI {
    temp: TempData,
    hum: HumData,
    pump: PumpData
}

export default interface EspData {
    id: string,
    client: MqttClient,
    data: DataContainerI
}