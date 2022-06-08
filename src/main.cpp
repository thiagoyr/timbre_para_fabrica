#include <Arduino.h>

#define on_value_alarms 0

void setup() {
  
}



void loop() {

}


void set_one_alarm_on(int pin_alarm, int duration_alarms){
  digitalWrite(pin_alarm, on_value_alarms);
  delay(duration_alarms);
  digitalWrite(pin_alarm, !on_value_alarms);
}

void set_two_alarm_on(int pin_alarma1, int pin_alarma2, int duration_alarms){
  digitalWrite(pin_alarma1, on_value_alarms);
  digitalWrite(pin_alarma2, on_value_alarms);
  delay(duration_alarms);
  digitalWrite(pin_alarma1, !on_value_alarms);
  digitalWrite(pin_alarma2, !on_value_alarms);
}

void set_four_alarm_on(int pin_alarma1,int pin_alarma2,int pin_alarma3,int pin_alarma4, int duration_alarms){
  digitalWrite(pin_alarma1, on_value_alarms);
  digitalWrite(pin_alarma2, on_value_alarms);
  digitalWrite(pin_alarma3, on_value_alarms);
  digitalWrite(pin_alarma4, on_value_alarms);
  delay(duration_alarms);
  digitalWrite(pin_alarma1, !on_value_alarms);
  digitalWrite(pin_alarma2, !on_value_alarms);
  digitalWrite(pin_alarma3, !on_value_alarms);
  digitalWrite(pin_alarma4, !on_value_alarms);
}