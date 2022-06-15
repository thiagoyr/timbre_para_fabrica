#include <Arduino.h>

#define on_value_alarms 1
#define alarm1 3
#define alarm2 4
#define alarm3 5
#define alarm4 6
#define duration_of_alarm 500

bool alarms_states[] = {false,false,false,false};

void set_enabled_alarms(int duration_alarms, bool alarms[]);
void choose_alarms(int alarm_number);



void setup(){
  Serial.begin(9600);
  pinMode(alarm1,OUTPUT);
  pinMode(alarm2,OUTPUT);
  pinMode(alarm3,OUTPUT);
  pinMode(alarm4,OUTPUT);
}

void loop(){
  //one alarm
  bool first_ring_one_alarm = true;
  bool second_ring_one_alarm = true;
  bool third_ring_one_alarm = true;
  bool fourth_ring_one_alarm = true;
  //two alarms
  bool first_ring_two_alarm = true;
  bool second_ring_two_alarm = true;
  //four alarms
  bool first_ring_four_alarm = true;

  if(first_ring_one_alarm){
    choose_alarms(1);
    set_enabled_alarms(duration_of_alarm, alarms_states);
  }
  if(second_ring_one_alarm){
    choose_alarms(2);
    set_enabled_alarms(duration_of_alarm, alarms_states);
  }
  if(third_ring_one_alarm){
    choose_alarms(3);
    set_enabled_alarms(duration_of_alarm, alarms_states);
  }
  if(fourth_ring_one_alarm){
    choose_alarms(4);
    set_enabled_alarms(duration_of_alarm, alarms_states);
  }


  if(first_ring_two_alarm){
    choose_alarms(2);
    choose_alarms(4);
    set_enabled_alarms(duration_of_alarm, alarms_states);
  }
  if(second_ring_two_alarm){
    choose_alarms(1);
    choose_alarms(3);
    set_enabled_alarms(duration_of_alarm, alarms_states);
  }


  if(first_ring_four_alarm){
    choose_alarms(1);
    choose_alarms(2);
    choose_alarms(3);
    choose_alarms(4);
    set_enabled_alarms(duration_of_alarm, alarms_states);
  }
}

// FUNCIONES
void set_enabled_alarms(int duration_alarms, bool alarms_enabled[]){
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

