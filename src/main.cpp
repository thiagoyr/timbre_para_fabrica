#include <Arduino.h>

#define on_value_alarms 1
#define alarm1 3
#define alarm2 4
#define alarm3 5
#define alarm4 6
#define duration_of_alarm 500

void set_one_alarm_on(int pin_alarm1, int duration_alarms);
void set_two_alarm_on(int pin_alarma1, int pin_alarma2, int duration_alarms);
void set_four_alarm_on(int pin_alarma1,int pin_alarma2,int pin_alarma3,int pin_alarma4, int duration_alarms);


void setup(){
  Serial.begin(9600);
  pinMode(alarm1,OUTPUT);
  pinMode(alarm2,OUTPUT);
  pinMode(alarm3,OUTPUT);
  pinMode(alarm4,OUTPUT);
}

void loop(){
    
    set_one_alarm_on(duration_of_alarm, alarm1);
    set_one_alarm_on(duration_of_alarm, alarm2);
    set_one_alarm_on(duration_of_alarm, alarm3);
    set_one_alarm_on(duration_of_alarm, alarm4);

    set_two_alarm_on(duration_of_alarm, alarm1, alarm2);
    set_two_alarm_on(duration_of_alarm, alarm3, alarm4);

    set_four_alarm_on(duration_of_alarm, alarm1, alarm2, alarm3, alarm4);
}

// FUNCIONES
void set_one_alarm_on(int duration_alarms, int pin_alarm1){
  digitalWrite(pin_alarm1, on_value_alarms);
  delay(duration_alarms);
  digitalWrite(pin_alarm1, !on_value_alarms);
  delay(duration_alarms);
}

void set_two_alarm_on(int duration_alarms, int pin_alarma1, int pin_alarma2){
  digitalWrite(pin_alarma1, on_value_alarms);
  digitalWrite(pin_alarma2, on_value_alarms);
  delay(duration_alarms);
  digitalWrite(pin_alarma1, !on_value_alarms);
  digitalWrite(pin_alarma2, !on_value_alarms);
  delay(duration_alarms);
}

void set_four_alarm_on(int duration_alarms, int pin_alarma1,int pin_alarma2,int pin_alarma3,int pin_alarma4){
  digitalWrite(pin_alarma1, on_value_alarms);
  digitalWrite(pin_alarma2, on_value_alarms);
  digitalWrite(pin_alarma3, on_value_alarms);
  digitalWrite(pin_alarma4, on_value_alarms);
  delay(duration_alarms);
  digitalWrite(pin_alarma1, !on_value_alarms);
  digitalWrite(pin_alarma2, !on_value_alarms);
  digitalWrite(pin_alarma3, !on_value_alarms);
  digitalWrite(pin_alarma4, !on_value_alarms);
  delay(duration_alarms);
  }