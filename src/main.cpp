#include <Arduino.h>

#define on_value_alarms 1 //value used to turn on alarms
#define alarm1 3 //alarm pins
#define alarm2 4
#define alarm3 5
#define alarm4 6
#define duration_of_alarm 500
#define number_of_alarms 4 //number of alarms used

bool alarms_states[number_of_alarms] = {false,false,false,false};
int alarm_pin[number_of_alarms] = {alarm1, alarm2, alarm3, alarm4};

void set_enabled_alarms(int duration_alarms, bool alarms[]);
void choose_alarm(int alarm_number);
void choose_alarms2(int alarm_number1, int alarm_number2);
void choose_alarms4(int alarm_number1, int alarm_number2, int alarm_number3, int alarm_number4);


void setup(){
  Serial.begin(9600);
  for(int i=0; i<number_of_alarms;i++){
    pinMode(alarm_pin[i],OUTPUT);
  }
  Serial.println("Ready!");
}

void loop(){
  
  int alarm_scenario = 1;
  /*
   * List of scenarios
   * 1 = turn on alarm 1 
   * 2 = turn on alarm 2
   * 3 = turn on alarm 3
   * 4 = turn on alarm 4
   * 5 = turn on alarm 1 and 2
   * 6 = turn on alarm 3 and 4
   * 7 = turn on alarm 1, 2 , 3 and 4
  */ 
  while(!Serial.available()){

  }
  alarm_scenario = Serial.read()-48;
  Serial.println(alarm_scenario);
  switch(alarm_scenario){
    case 1:
      choose_alarm(1);
      break;
    case 2:
      choose_alarm(2);
      break;
    case 3:
      choose_alarm(3);
      break;
    case 4:
      choose_alarm(4);
      break;
    case 5:
      choose_alarms2(1,2);
      break;
    case 6:
      choose_alarms2(3,4);
      break;
    case 7:
      choose_alarms4(1,2,3,4);
      break;
    default:
      Serial.println("The selected scenario does not exist.");
  }
  
  set_enabled_alarms(duration_of_alarm, alarms_states);
}

// FUNCIONES
/*Enables alarms. First parameter uses a delay (in milliseconds) to determine how long they will ring, and must use a global bool vector called "alarm_states" as a second parameter to ensure working of the function. Sets all positions of global vector to 0 when finished. Has a delay at the end because it may be needed when using Leds.*/
void set_enabled_alarms(int duration_alarms, bool alarms_enabled[]){
  for(int i=0;i<number_of_alarms;i++){
    digitalWrite(alarm_pin[i], alarms_enabled[i]);
  }
  delay(duration_alarms);
  for(int i=0; i< number_of_alarms;i++){
    alarms_states[i] = false;
  }
  delay(duration_alarms);
}

  /*Chooses which alarms to enable in a global bool vector called "alarm_states". Number of alarms starts at 1, and if the number isn't in the defined range of alarms it prints that the desired alarm does not exist.*/
  void choose_alarm(int alarm_number){
    if( 1<=alarm_number && alarm_number<=number_of_alarms ){
      alarms_states[alarm_number-1]=true;
    }else{
      Serial.println("The alarm number does not exist");
    }
  }

  /*Chooses 2 alarms at the same time. Must have 2 parameters, the position of both alarms in the alarms_states vector.*/
  void choose_alarms2(int alarm_number1, int alarm_number2){
    choose_alarm(alarm_number1);
    choose_alarm(alarm_number2);
  }

  /*Chooses 4 alarms at the same time. Must have 4 parameters, the position of the alarms in the alarms_states vector.*/
  void choose_alarms4(int alarm_number1, int alarm_number2,int alarm_number3, int alarm_number4){
    choose_alarm(alarm_number1);
    choose_alarm(alarm_number2);
    choose_alarm(alarm_number3);
    choose_alarm(alarm_number4);
  }
