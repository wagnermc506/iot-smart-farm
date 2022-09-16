import './DataContainer.css'
import { HumData } from './types'

export function HumidityContainer(props: HumData) {
  return (
    <div className='Container'>
      <div>{props.environment.toString() + ' RH'}</div>
      <div>Ambiente</div>
      <div>{props.ground.toString() + ' RH'}</div>
      <div>Solo</div>
    </div>
  );
}