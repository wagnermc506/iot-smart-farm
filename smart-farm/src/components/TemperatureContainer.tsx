import './DataContainer.css'
import { TempData } from './types'

export function TemperatureContainer(props: TempData) {
  return (
    <div className='Container'>
      <div>{props.environment.toString() + '°C'}</div>
      <div>Ambiente</div>
      <div>{props.ground.toString() + '°C'}</div>
      <div>Solo</div>
    </div>
  );
}