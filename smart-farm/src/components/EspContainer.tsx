import { DataContainer } from './DataContainer'
import './EspContainer.css'
import { Client } from 'mqtt'
import EspData from './types'

export function EspContainer(props: EspData) {
  return (
    <div className='EspContainer'>
      <h2 className='Header'>{props.id}</h2>
      <DataContainer {...props.data}/>
    </div>
  );
}