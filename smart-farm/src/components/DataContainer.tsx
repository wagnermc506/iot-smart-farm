import { TemperatureContainer } from "./TemperatureContainer";
import { HumidityContainer } from "./HumidityContainer";
import { PumpContainer } from "./PumpContainer";
import './DataContainer.css'
import { useState } from 'react';
import { DataContainerI } from './types'

export function DataContainer(props: DataContainerI) {

  // const [temp, setTemp] = useState(props.temp)
  // const [hum, setHum] = useState({environment: 10, ground: 30})
  // const [pump, setPump] = useState(true)

  // const change_pump_status = () => {
  //   setPump(!pump);
  // }

  // console.log(props)

  return (
    <div className="DataContainer">
      <TemperatureContainer {...props.temp}/>
      <HumidityContainer {...props.hum}/>
      <PumpContainer {...props.pump}/>
    </div>
  );
}