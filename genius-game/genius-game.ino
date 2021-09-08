int greenLed = 2;
int yellowLed = 3;
int redLed = 4;
int ledsPorts[] = {greenLed, yellowLed, redLed};

int greenButton = 6;
int yellowButton = 7;
int redButton = 8;
int btnsPorts[] = {greenButton, yellowButton, redButton};

int maxLevel = 5;
bool ledStatus = 0;


void customDigitalWrite(int arr[], int arrLength, uint8_t value, int dlay) {
  for(int i = 0; i < arrLength; i++) {
    digitalWrite(arr[i], value);
  }
  delay(dlay);
}

void customDigitalWrite(int port, uint8_t value, int dlay) {
  digitalWrite(port, value);
  delay(dlay);
}

void customPinMode(int arr[], int arrLength, uint8_t mode) {
  for(int i = 0; i < arrLength; i++) {
    pinMode(arr[i], mode);
  }
}

void setup() {
  Serial.begin(9600);

  customPinMode(ledsPorts, sizeof(ledsPorts) / sizeof(ledsPorts[0]), OUTPUT);
  customPinMode(btnsPorts, sizeof(btnsPorts) / sizeof(btnsPorts[0]), INPUT_PULLUP);
}

void loop() {
  for(int i = 3; i <= maxLevel;) {
    bool flag = true;
    int ledSequence[i];
    int buttonSequence[i];
    
    for(int j = 0; j < i; j++) {
      int randomPort = random(2,5);

      customDigitalWrite(randomPort, HIGH, 1000);
      customDigitalWrite(randomPort, LOW, 1000);
      ledSequence[j] = randomPort;
    }
    
    for(int j = 0; j < i;) {
      if(digitalRead(greenButton) == LOW) {
        delay(500);
        buttonSequence[j] = greenLed;
        j++;
      }
      else if(digitalRead(yellowButton) == LOW) {
        delay(500);
        buttonSequence[j] = yellowLed;
        j++;
      }
      else if(digitalRead(redButton) == LOW) {
        delay(500);
        buttonSequence[j] = redLed;
        j++;
      }
    }
    
    for(int j = 0; j < i; j++) {
      if(ledSequence[j] != buttonSequence[j]) {
        flag = false;
        break;
      }
    }
    if(flag) {
      for(int j = 0; j < i; j++) {
        customDigitalWrite(ledSequence[j], HIGH, 250);
        customDigitalWrite(ledSequence[j], LOW, 250);
      }
      i++;
    }
    else {
      for(int j = 0; j < 2; j++) {
        customDigitalWrite(ledsPorts, sizeof(ledsPorts) / sizeof(ledsPorts[0]), HIGH, 500);
        customDigitalWrite(ledsPorts, sizeof(ledsPorts) / sizeof(ledsPorts[0]), LOW, 500);
      }
      i = 3;
    }
    delay(2000);
  }
}
