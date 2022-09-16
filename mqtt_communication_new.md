## ESP spec

A esp deve ter um `device_id` criado e salvo em sua configuração de build.

### Envio de temperatura

- tópico: `IOT2022-1/<device_id>/temperatura`
- modo: publish

```json
{
    "sender": "esp",
    "type": "ground|env",
    "data": Number
}
```

### Envio de umidade

- tópico: `IOT2022-1/<device_id>/umidade`
- modo: publisher

```json
{
    "sender": "esp",
    "type": "ground|env",
    "data": Number
}
```

### Envio do estado da bomba

- tópico: `IOT2022-1/<device_id>/bomba`
- modo: publisher

```json
{
    "sender": "esp",
    "data": 1|0
}
```

### Recebimento de estado da bomba

- tópico: `IOT2022-1/<device_id>/bomba`
- modo: subscriber

```json
{
    "sender": "front",
    "data": 1|0
}
```

## Front spec

### Recebimento de temperatura

- tópico: `IOT2022-1/+/temperatura`
- modo: subscriber

```json
{
    "sender": "esp",
    "type": "ground|env",
    "data": Number
}
```

### Recebimento de umidade

- tópico: `IOT2022-1/+/umidade`
- modo: subscriber

```json
{
    "sender": "esp",
    "type": "ground|env",
    "data": Number
}
```

## Recebimento de estado da bomba

- tópico: `IOT2022-1/+/bomba`
- modo: subscriber

```json
{
    "sender": "esp",
    "data": 1|0
}
```

## Envio de estado da bomba

- tópico: `IOT2022-1/+/bomba`
- modo: publisher

```json
{
    "sender": "front",
    "data": 1|0
}
```

## MQTT Listener spec

### Recebimento de temperatura

- tópico: `IOT2022-1/+/temperatura`
- modo: subscriber

```json
{
    "sender": "esp",
    "type": "ground|env",
    "data": Number
}
```

### Recebimento de umidade

- tópico: `IOT2022-1/+/umidade`
- modo: subscriber

```json
{
    "sender": "esp",
    "type": "ground|env",
    "data": Number
}
```

## Recebimento de estado da bomba

- tópico: `IOT2022-1/+/bomba`
- modo: subscriber

```json
{
    "sender": "esp",
    "data": 1|0
}
```