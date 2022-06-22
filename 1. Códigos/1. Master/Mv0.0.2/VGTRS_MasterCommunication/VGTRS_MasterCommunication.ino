// #########################################################
// VGTRS - ARDUINO MASTER COMMUNICATION
// By VGROW Comércio e Representação LTDA
// #########################################################
// Bibliotecas
#include <Wire.h>

// Variáveis
// Dados recebidos do computador
String _dataPC = "";

// Dados de medição de cada dispositivo
String _dataIn_D1 = "000;000;000;000;000";   // D1z
String _dataIn_D3 = "R;000;000;000;000;000;000;000";   // D3

// Dados de saída para o computador
String _dataOut = "";

// Delay entre atualizações de temperatura
int _getValuesDelay = 5000;

int _delayToStart = 1000;

// #########################################################
// Função para reiniciar o arduino
// #########################################################
void (* resetFunc) (void) = 0;

// #########################################################
// Função de configuração
// #########################################################
void setup() {
  // Inicia o procotolo serial
  Serial.begin(9600);

  // Inicia o protocolo I2C
  Wire.begin();
  // put your setup code here, to run once:

  delay(_delayToStart);
}

// #########################################################
// Função de repetição
// #########################################################
void loop() {
  while(Serial.available()){
    char c = Serial.read();
    if (c == 'R'){
      resetDevices(8);
      resetDevices(9);
      resetFunc();
    }
  }
  
  _dataIn_D1 = getTemp(8,21);
  if (_dataIn_D1.length() < 9){
    _dataIn_D1 = "000;000;000;000;000";
  }

  _dataIn_D3 = getTemp(9,29);
  if (_dataIn_D3.length() < 9){
    _dataIn_D3 = "R;000;000;000;000;000;000;000";
  }

  String toSend = _dataIn_D1 + "@" + _dataIn_D3;
  Serial.println(toSend);
  delay(_getValuesDelay);
}

// #########################################################
// Função de atualização dos dados de temperatura
// #########################################################
String getTemp(int deviceAdress, int bytesNumber){
  // Pede os dados do dispositivo e a quantidade de bytes a serem recebidos
  Wire.requestFrom(deviceAdress, bytesNumber);
  
  // Zera a string
  String receivedData = "";
  
  // Laço de repetição de leitura
  while(Wire.available()){
    char c = Wire.read();
    // Concatena o char a string completa
    receivedData.concat(c);
  }
  // Verifica se há o caractere X e o remove
  char d;
  for (int i = 0; i < receivedData.length(); i++){
    d = receivedData.charAt(i);
    if (d== 'X'){
      receivedData.remove(i);
    }
  }

  // Retorna o valor obtido
  return receivedData;
}

// #########################################################
// Reseta os leitores de temperatura do endereço adress
// #########################################################
void resetDevices(int adress){
  Wire.beginTransmission(adress);
  Wire.write("R");
  Wire.endTransmission();
}
