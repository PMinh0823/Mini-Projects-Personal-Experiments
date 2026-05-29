const int ledPins[] = {3, 4, 5, 6, 7};
const int buttonPin = 2;
const int buzzerPin = 8;

int currentButtonState;
int lastButtonState = HIGH;

int mode = -1;

void setup(){
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  for (int i=0; i<5; i++){
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buzzerPin, OUTPUT);
}

void loop(){
  currentButtonState = digitalRead(buttonPin);
  if (currentButtonState == LOW && lastButtonState == HIGH){ //chi chay dung mot lan duy nhat luc nhan nut
    delay(50);
    if(digitalRead(buttonPin) == LOW) mode ++;
    if (mode > 2) mode = 0; 
  }
  if (currentButtonState == LOW) {
    showPattern(mode); 
    digitalWrite(buzzerPin, HIGH);
  }
  else {
    turnOffAll();
    digitalWrite(buzzerPin, LOW);
  }
  lastButtonState = currentButtonState;
}

void showPattern (int pattern){
  if (pattern == 0) {
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[2], HIGH);
    digitalWrite(ledPins[4], HIGH);
  }

  if (pattern == 1){
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[3], HIGH);
  }

  if (pattern == 2){
    for (int i = 0; i<5; i++){
      digitalWrite(ledPins[i], HIGH);
    }
  }
}

void turnOffAll(){
  for (int i = 0; i < 5; i++){
    digitalWrite(ledPins[i], LOW);
  }
}