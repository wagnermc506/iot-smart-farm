
#include <ESP8266WiFi.h> // Importa a Biblioteca ESP8266WiFi
#include <PubSubClient.h> // Importa a Biblioteca PubSubClient
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11


const int buttonPin = 2;     // the number of the pushbutton pi
const int irigandoPin =  15;
const int naoirrigandoPin =  13;


#define dht_dpin 0 //pino D3 (O pino do sensor de temperatura e umidade)
#define pinSensorA A0 //Pino A0 do sensor de umidade de solo
#define ID_MQTT  "Smart_Farm"     //id mqtt (para identificação de sessão)
//defines de id mqtt e tópicos para publicação e subscribe
#define TOPICO_SUBSCRIBE "MQTTSmartFarmEnvia"     //tópico MQTT de escuta
#define TOPICO_PUBLISH   "MQTTSmartFarmRecebe"    //tópico MQTT de envio de informações para Broker
DHT dht(dht_dpin, DHTTYPE); 
const int oneWireBus = 5; //pino D1 (O pino do sensor de temperatura do solo)


// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);


// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);


// WIFI
const char* SSID = "SSID"; // SSID / nome da rede WI-FI que deseja se conectar
const char* PASSWORD = "SENHA"; // Senha da rede WI-FI que deseja se conectar
 
  
// MQTT
const char* BROKER_MQTT = "iot.eclipse.org"; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883; // Porta do Broker MQTT
 
 
//Variáveis e objetos globais
WiFiClient espClient; // Cria o objeto espClient
PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient


char EstadoSaida = '0';  //variável que armazena o estado atual da saída
int buttonState = 0;



//parameros
void initWiFi();
void initMQTT();
void reconectWiFi(); 
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void VerificaConexoesWiFIEMQTT(void);
void InitOutput(void);


//Função: inicializa e conecta-se na rede WI-FI desejada
//Parâmetros: nenhum
//Retorno: nenhum
void initWiFi() 
{
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(SSID);
    Serial.println("Aguarde");
     
    reconectWiFi();
}


//Função: inicializa parâmetros de conexão MQTT(endereço do 
//        broker, porta e seta função de callback)
//Parâmetros: nenhum
//Retorno: nenhum
void initMQTT() 
{
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);   //informa qual broker e porta deve ser conectado
    MQTT.setCallback(mqtt_callback);            //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
}


//Função: função de callback 
//        esta função é chamada toda vez que uma informação de 
//        um dos tópicos subescritos chega)
//Parâmetros: nenhum
//Retorno: nenhum
void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    String msg;
 
    //obtem a string do payload recebido
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }
   
   
    //toma ação dependendo da string recebida:
    //verifica se deve colocar nivel alto de tensão na saída D0:
    //IMPORTANTE: o Led já contido na placa é acionado com lógica invertida (ou seja,
    //enviar HIGH para o output faz o Led apagar / enviar LOW faz o Led acender)
    /*if (msg.equals("L"))
    {
        digitalWrite(D0, LOW);
        EstadoSaida = '1';
    }
 
    //verifica se deve colocar nivel alto de tensão na saída D0:
    if (msg.equals("D"))
    {
        digitalWrite(D0, HIGH);
        EstadoSaida = '0';
    }*/
     
}
  
  
//Função: reconecta-se ao broker MQTT (caso ainda não esteja conectado ou em caso de a conexão cair)
//        em caso de sucesso na conexão ou reconexão, o subscribe dos tópicos é refeito.
//Parâmetros: nenhum
//Retorno: nenhum
void reconnectMQTT() 
{
    while (!MQTT.connected()) 
    {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) 
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(TOPICO_SUBSCRIBE); 
        } 
        else
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentatica de conexao em 2s");
            delay(2000);
        }
    }
}
 
  
//Função: reconecta-se ao WiFi
//Parâmetros: nenhum
//Retorno: nenhum
void reconectWiFi() 
{
    //se já está conectado a rede WI-FI, nada é feito. 
    //Caso contrário, são efetuadas tentativas de conexão
    if (WiFi.status() == WL_CONNECTED)
        return;
         
    WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
     
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(100);
        Serial.print(".");
    }
   
    Serial.println();
    Serial.print("Conectado com sucesso na rede ");
    Serial.print(SSID);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
}

void InitOutput(void)
{
    dht.begin(); // iniciar o sensor dht
    sensors.begin();  // iniciar o sensor DS18B20
    Serial.begin(9600);
    pinMode(irigandoPin, OUTPUT);
    pinMode(naoirrigandoPin, OUTPUT);
    pinMode(buttonPin, INPUT);         
}


//............................................
void setup() {
  // put your setup code here, to run once:
  //inicializações:
    InitOutput();
    initWiFi();
    initMQTT();

 
}



void loop() {
  // put your main code here, to run repeatedly:
  sensors.requestTemperatures(); 
  float temperatureSolo = sensors.getTempCByIndex(0);
  int umidadeSolo =  analogRead(pinSensorA);
  float humidadeAmbiente = dht.readHumidity();
  float temperaturaAmbiente = dht.readTemperature();
  Serial.print("Temperatura Atual do Ambiente = ");
  Serial.print(temperaturaAmbiente); 
  Serial.println("ºC");
  
  Serial.print("Temperatura Atual do Solo = ");
  Serial.print(temperatureSolo);
  Serial.println("ºC");
  
  Serial.print("Umidade Atual do Ambiente  = ");
  Serial.print(humidadeAmbiente);
  Serial.println("%");
    
  Serial.print("Umidade Atual do Solo  = ");
  Serial.print(umidadeSolo);
  Serial.println("%");
  
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(irigandoPin, HIGH);
    digitalWrite(naoirrigandoPin, LOW);}
  else if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(naoirrigandoPin, HIGH);
    digitalWrite(irigandoPin, LOW);}

  delay(5000);
}
