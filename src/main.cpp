#include <Arduino.h>

#define on_value_alarms 1
#define alarm1 3
#define alarm2 4
#define alarm3 5
#define alarm4 6
#define duration_of_alarm 500

bool alarms_states[] = {false,false,false,false};

void set_alarm(int duration_alarms, bool alarms[]);
void choose_alarms(int alarm_number);



void setup(){
  Serial.begin(9600);
  pinMode(alarm1,OUTPUT);
  pinMode(alarm2,OUTPUT);
  pinMode(alarm3,OUTPUT);
  pinMode(alarm4,OUTPUT);
}

void loop(){
  
  choose_alarms(2);
  choose_alarms(3);
  set_alarm(duration_of_alarm, alarms_states);
  choose_alarms(4);
  set_alarm(duration_of_alarm, alarms_states);
}

// FUNCIONES
void set_alarm(int duration_alarms, bool alarms_enabled[]){
  digitalWrite(alarm1, alarms_enabled[0]);
  digitalWrite(alarm2, alarms_enabled[1]);
  digitalWrite(alarm3, alarms_enabled[2]);
  digitalWrite(alarm4, alarms_enabled[3]);
  delay(duration_alarms);
  digitalWrite(alarm1,false);
  digitalWrite(alarm2,false);
  digitalWrite(alarm3,false);
  digitalWrite(alarm4,false);
  delay(duration_alarms);
  for(int i=0; i<=3;i++){
    alarms_states[i] = false;
  }
  }

  void choose_alarms(int alarm_number){
    if( 1<=alarm_number && alarm_number<=4 ){
      alarms_states[alarm_number-1]=true;
    }else{
      Serial.println("The alarm number does not exist");
    }
    
  }

