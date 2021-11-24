#include <Arduino.h>

// Pins

const int button = 2;
const int buzzor = 3;
const int sensor = 4;
const int green = 12;
const int red = 13;

// Constants and Variables

bool door_open;
bool key_status;
bool previously_open = false;

const int blink_time = 375;
const int check_time = 100;
const int alarm_time = blink_time / 1.3;
const int alarm_wait = 30;
bool alarm_confirm = true;

// Functions

void check_key() {
  if (digitalRead(button) == HIGH) {key_status = true;}
  else {key_status = false;}
}

void check_door() {
  if (digitalRead(sensor) == HIGH) {door_open = true;}
  else {door_open = false;}
}

void lightWrite(int p1, int p2) {
  digitalWrite(green, p1); // Green Light
  digitalWrite(red, p2); // Red Light
}

void greenLight() {lightWrite(HIGH, LOW);}

void redLight() {lightWrite(LOW, HIGH);}

void openingTune() {
  Serial.println("Opening Tune");
  tone(buzzor, 523, 250); // C5 4th
  delay(325);
  tone(buzzor, 587, 250); // D5 4th
  delay(325);
}

void closingTune() {
  Serial.println("Closing Tune");
  tone(buzzor, 262, 250); // C4 4th
  delay(325);
  tone(buzzor, 220, 250); // A3 4th
  delay(325);
}

void alarmTune() {
  Serial.println("Alarm Tune");
  while (key_status == false) {
    redLight();
    
    tone(buzzor, 988, alarm_time); // B5
    delay(blink_time);
    Serial.print("Wee-");
    
    greenLight();
    
    tone(buzzor, 1047, alarm_time); // C6
    delay(blink_time);
    Serial.print("Woo-");
    
    check_key();
  }
}

void alarm_prompt() {
  Serial.println("Alarm prompting");
  for (int i = 0; i < alarm_wait; i++) {
    Serial.print("Waiting-");
    tone(buzzor, 523, 500); // C5 4th
    delay(1000);
    check_key();
    if (key_status == true) {
      Serial.println("Alarm disabled");
      alarm_confirm = false;
      tone(buzzor, 523, 250); // C5 4th
      delay(325);
      tone(buzzor, 587, 250); // D5 4th
      delay(325);
      break;
    }
  }
  if (alarm_confirm == true) {alarmTune();}
  else {alarm_confirm = true;}
}

void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT);
  pinMode(buzzor, INPUT);
  pinMode(buzzor, OUTPUT);
  pinMode(sensor, INPUT_PULLUP);
  pinMode(sensor, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  check_door();
  check_key();
  if (key_status == true) {greenLight();
    if (door_open == true) {
      if (previously_open == true) {}
      else {openingTune();previously_open = true;}
    }
    else {
      if (previously_open == true) {redLight();closingTune();previously_open = false;}
    }
  }
  else {redLight();
    if (door_open == true) {
      if (previously_open == true) {greenLight();}
      else {alarm_prompt();previously_open = true;}
    }
    else {
      if (previously_open == true) {closingTune();previously_open = false;}
    }
  }
  delay(check_time);
}