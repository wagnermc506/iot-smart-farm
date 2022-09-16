### Registro de uma ESP

tópico: `IOT2022-1/register`

- publisher: ESP
- subscriber: MQTT Listener

```json
{
    "sender": "esp"
}
```

### Registro de uma ESP (resposta)

tópico: `IOT2022-1/register`

- publisher: MQTT Listener
- subscriber: ESP

```json
{
    "sender": "server",
    "uuid": "<uuid>"
}
```

### Envio de temperatura e umidade

tópico: `IOT2022-1/<device_id>/temperatura|umidade`

- publisher: ESP
- subscriber: MQTT Listener e Front

```json
{
    "sender": "esp",
    "type": "ground|env",
    "data": Number
}
```

### Envio do estado da bomba (via esp)

tópico: `IOT2022-1/<device_id>/bomba`

- publisher: ESP
- subscriber: MQTT Listener e Front

```json
{
    "sender": "esp",
    "data": Number
}
```

### Envio do estado da bomba (controle do servidor)

tópico: `IOT2022-1/<device_id>/bomba`

publisher: Front
subscriber: ESP

```json
{
    "sender": "server"
}
```