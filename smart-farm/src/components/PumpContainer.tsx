import { useState } from 'react'
import './DataContainer.css'
import { PumpData } from './types';

export function PumpContainer(props: PumpData) {

  // console.log(props)
  const state = props.status ? 'on' : 'off';
  // console.log(state)
  const buttonTxt = props.status ? 'Desligar' : 'Ligar'

  return (
    <div className='Container'>
      <div>{state}</div>
      {/* <button onClick={() => props.callback()}>{buttonTxt}</button> */}
    </div>
  );
}