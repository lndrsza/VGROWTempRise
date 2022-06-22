String _dataOut = "";
String _dataIn = "";

int _readValues[36];
int _sensorPins[35] = {11,12,13,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53};

int _getValuesDelay = 5000;
int _delayToStart = 1000;
int _delayBetweenMeasurement = 250;

bool _performingTest = false;

void setup() {
  Serial.begin(9600);
  delay(_delayToStart);
}

void loop() {
  // ---------------------------------------------------------------
  // ---------------------------------------------------------------
  while(Serial.available()){
    char c = Serial.read();
    if (c == 'R'){
      _performingTest = true;
    }
    if (c == 'S'){
      _performingTest = false;
    }
    if (c == 'O'){
      Serial.println("OK");
    }
  }

  if (_performingTest == true){
    GetValues();
    _dataOut = _dataIn;
    Serial.println(_dataOut);
    delay(_getValuesDelay);
  }
}

void GetValues(){
  _dataIn = "";
  for (int i = 0; i < 36; i++){
    _readValues[i] = random(0,200);
    if (i < 35){
      _dataIn.concat(_readValues[i]);
      _dataIn.concat(";");
    } else {
      _dataIn.concat(_readValues[i]);
    }
    delay(_delayBetweenMeasurement);
  }
}
