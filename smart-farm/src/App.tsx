// import React from 'react';
import logo from './logo.svg';
import './App.css';
import './fixImport';
import { Header } from './components/Header'
import { EspContainer } from './components/EspContainer'
import { useEffect, useState } from 'react';
import mqtt from 'mqtt';
import EspData from './components/types';
import { handleMessage } from './components/mqtt_publish';

const client = mqtt.connect('mqtt://localhost:8080')

function App() {

  const [connectionStatus, setConnectionStatus] = useState(false);
  // const [messages, setMessages] = useState([])

  const [esp, setEsp] = useState({
    id: '1',
    client: client,
    data: {
      temp: {
        environment: 0,
        ground: 0
      },
      hum: {
        environment: 0,
        ground: 0
      },
      pump: {
        status: false
      }
    }
  } as EspData)  

  useEffect(() => {
    client.on('connect', () => {
      console.log('connected!')
      client.subscribe('iot2022/temperatura', console.log)
      client.subscribe('iot2022/umidade', console.log)
      client.subscribe('iot2022/bomba', console.log)
      setConnectionStatus(true)
    })

    client.on('message', (topic, message) => {
      console.log(`Mensagem recebida de: ${topic}`)
      console.log(`Content: ${message}`)

      // const data = JSON.parse(message.toString());
      const data = handleMessage(topic, message.toString(), esp)
      console.log(data)
      setEsp({...data})
    })

    return () => {
      client.removeAllListeners();
    }
  }, [])

  return (
      <div>
        <Header/>
        <EspContainer {...esp}></EspContainer>
        {/* <EspContainer id='uuid2' temp={temperature}></EspContainer> */}
      </div>
  );
}

export default App;