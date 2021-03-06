// Libraries
#include <Arduino.h>
#include <RTClib.h>
#include <SPI.h>
#include <wire.h>

// Defines
#define on_value_alarms 1 // value used to turn on alarms
#define alarm1 3          // alarm pins
#define alarm2 4
#define alarm3 5
#define alarm4 6
#define duration_of_alarm 500
#define number_of_alarms 4 // number of alarms used.
#define time 1500

// Global Variables
bool alarms_states[number_of_alarms] = {false, false, false, false};
int alarm_pin[number_of_alarms] = {alarm1, alarm2, alarm3, alarm4};
uint8_t hhour;
uint8_t mminute;
uint8_t ssecond;
uint8_t dday;
uint8_t mmonth;
uint16_t yyear;
uint8_t index = 0;

// RTC
RTC_DS3231 rtc;
DateTime now = rtc.now();
DateTime alarms[12] = {{yyear, mmonth, dday, 9, 0, 0},   // 0inicio primer recreo
                       {yyear, mmonth, dday, 9, 15, 0},  // 1fin del primer recreo
                       {yyear, mmonth, dday, 9, 20, 0},  // 2inicio segundo recreo
                       {yyear, mmonth, dday, 9, 35, 0},  // 3fin del segundi recreo
                       {yyear, mmonth, dday, 9, 40, 0},  // 4inicio tercer recreo
                       {yyear, mmonth, dday, 9, 55, 0},  // 5fin del tercer recreo
                       {yyear, mmonth, dday, 10, 0, 0},  // 6inicio cuarto recreo
                       {yyear, mmonth, dday, 10, 15, 0}, // 7fin del cuarto recreo
                       {yyear, mmonth, dday, 13, 0, 0},  // 8inicio del almuerzo
                       {yyear, mmonth, dday, 14, 0, 0},  // 9fin del almuerzo
                       {yyear, mmonth, dday, 16, 0, 0},  // 10fin de jornada laboral 1
                       {yyear, mmonth, dday, 18, 0, 0}}; // 11fin de jornada laboral 2

uint8_t tiempo[3] = {now.hour(), now.minute(), now.second()};

// Functions
void set_enabled_alarms(int duration_alarms, bool alarms[]);
void choose_alarm(int alarm_number);
void choose_alarms2(int alarm_number1, int alarm_number2);
void choose_alarms4(int alarm_number1, int alarm_number2, int alarm_number3, int alarm_number4);
void get_index_number();

// es una forma de hacer sonar las alarmas(forma1)
/* uint8_t alarm1[3] = {11, 10, 00};
uint8_t hourAlarm = 9;
uint8_t minuteAlarm = 0;
uint8_t secondAlarm = 0;
uint8_t changeAlarm = 0;
DateTime alarma1 (yyear, mmonth, dday, hourAlarm, minuteAlarm, secondAlarm); */

void setup()
{
    Serial.begin(9600);
    Serial.setTimeout(time);
    delay(500);
    while (Serial.available() == 0)
    {
    }
    Serial.println(F("ENTER HOUR"));
    hhour = (Serial.parseInt());
    Serial.println(F("ENTER MINUTE"));
    mminute = (Serial.parseInt());
    Serial.println(F("ENTER SECOND"));
    ssecond = (Serial.parseInt());
    Serial.println(F("ENTER DAY"));
    dday = (Serial.parseInt());
    Serial.println(F("ENTER MONTH"));
    mmonth = (Serial.parseInt());
    Serial.println(F("ENTER YEAR ultimas dos cifras"));
    yyear = (Serial.parseInt()); // ver despues, no permite cuatro cifras
    Serial.println(F("ya finalizo la configuracion"));

    Serial.print(hhour);
    Serial.print(":");
    Serial.print(mminute);
    Serial.print(":");
    Serial.println(ssecond);
    Serial.print(dday);
    Serial.print("/");
    Serial.print(mmonth);
    Serial.print("/");
    Serial.println(yyear);

    Serial.println(F("empieza configuracion del rtc"));
    rtc.begin();
    rtc.adjust(DateTime(yyear, mmonth, dday, hhour, mminute, ssecond));

    rtc.disableAlarm(1);
    rtc.clearAlarm(1);
    
    get_index_number();
    
    for (int i = 0; i < number_of_alarms; i++)
    {
        pinMode(alarm_pin[i], OUTPUT);
    }
    // rtc.setAlarm1(alarma1, DS3231_A1_Minute);
}

void loop()
{
    // forma 1
    /* if (alarm1[0] == tiempo[0] && alarm1[1] == tiempo[1] && alarm1[2] == tiempo[2])
    {
      Serial.println("Comparo alarma con el tiempo");
    }
    else
    Serial.println("Fin de la comparacion de alarma con el tiempo");
    Serial.print("NOW: ");Serial.print(now.hour());Serial.print(":");Serial.print(now.minute());Serial.print(':');Serial.println(now.second());
    Serial.print("ALARM: ");Serial.print(alarma1.hour());Serial.print(":");Serial.print(alarma1.minute());Serial.print(':');Serial.println(alarma1.second());
    */
    rtc.setAlarm1(alarms[index], DS3231_A1_Hour);
    Serial.print("ALARM: ");
    Serial.print(alarms[index].hour());
    Serial.print(":");
    Serial.print(alarms[index].minute());
    Serial.print(':');
    Serial.println(alarms[index].second());

    if (rtc.alarmFired(1))
    {
        Serial.println(F("Comparo alarma con el tiempo"));

        // int i=(index == 0 || index == 1)?1:0+(index == 2 || index == 3)?2:0;

        switch (index){
            case 0: case 1:
                choose_alarm(1);
            break; case 2: case 3:
                choose_alarm(2);
            break; case 4: case 5:
                choose_alarm(3);
            break; case 6: case 7:
                choose_alarm(4);
            break; case 8: case 9:
                choose_alarms4(1,2,3,4);
            break; case 10:
                choose_alarms2(1,2);
            break; case 11:
                choose_alarms2(3,4);
        }
        set_enabled_alarms(duration_of_alarm, alarms_states);

        /* if (index == 0 || index == 1) 
        {
            choose_alarm(1);
            set_enabled_alarms(duration_of_alarm, alarms_states);
        }
        else if (index == 2 || index == 3)
        {
            choose_alarm(2);
            set_enabled_alarms(duration_of_alarm, alarms_states);
        }
        else if (index == 4 || index == 5)
        {
            choose_alarm(3);
            set_enabled_alarms(duration_of_alarm, alarms_states);
        }
        else if (index == 6 || index == 7)
        {
            choose_alarm(4);
            set_enabled_alarms(duration_of_alarm, alarms_states);
        }
        else if (index == 8 || index == 9)
        {
            choose_alarms4(1, 2, 3, 4);
            set_enabled_alarms(duration_of_alarm, alarms_states);
        }
        else if (index == 10)
        {
            choose_alarms2(1, 2);
            set_enabled_alarms(duration_of_alarm, alarms_states);
        }
        else if (index == 11)
        {
            choose_alarms2(3, 4);
            set_enabled_alarms(duration_of_alarm, alarms_states);
        }
        else if (index >= 12)
            index = 0; */

        rtc.disableAlarm(1);
        rtc.clearAlarm(1);
        index++;
        if(index>11)
            index = 0;
    }
    delay(1000);
}

// FUNCTIONS
/*Enables alarms. First parameter uses a delay (in milliseconds) to determine how long they will ring, and must use a global bool vector called "alarm_states" as a second parameter to ensure working of the function. Sets all positions of global vector to 0 when finished. Has a delay at the end because it may be needed when using Leds.*/
void set_enabled_alarms(int duration_alarms, bool alarms_enabled[])
{
    for (int i = 0; i < number_of_alarms; i++)
    {
        digitalWrite(alarm_pin[i], alarms_enabled[i]);
    }
    delay(duration_alarms);
    for (int i = 0; i < number_of_alarms; i++)
    {
        alarms_states[i] = false;
    }
    delay(duration_alarms);
}

/*Chooses which alarms to enable in a global bool vector called "alarm_states". Number of alarms starts at 1, and if the number isn't in the defined range of alarms it prints that the desired alarm does not exist.*/
void choose_alarm(int alarm_number)
{
    if (1 <= alarm_number && alarm_number <= number_of_alarms)
    {
        alarms_states[alarm_number - 1] = true;
    }
    else
    {
        Serial.println("The alarm number does not exist");
    }
}

/*Chooses 2 alarms at the same time. Must have 2 parameters, the position of both alarms in the alarms_states vector.*/
void choose_alarms2(int alarm_number1, int alarm_number2)
{
    choose_alarm(alarm_number1);
    choose_alarm(alarm_number2);
}

/*Chooses 4 alarms at the same time. Must have 4 parameters, the position of the alarms in the alarms_states vector.*/
void choose_alarms4(int alarm_number1, int alarm_number2, int alarm_number3, int alarm_number4)
{
    choose_alarm(alarm_number1);
    choose_alarm(alarm_number2);
    choose_alarm(alarm_number3);
    choose_alarm(alarm_number4);
}

void get_index_number()
{
    switch(now.hour()){
        case 9:
            for (uint8_t indexConfiguration = 0; indexConfiguration <= 8; indexConfiguration++)
            {
                if (now.minute() > alarms[indexConfiguration].minute())
                {
                    continue;
                }
                else
                {
                    index = indexConfiguration;
                }
            }
            
        break; case 10:
            if (now.minute() < alarms[7].minute())
            {
                index = 7;
            }
            else
                index = 8;

        break; case 11: case 12:
            index = 8;

        break; case 13:
            index = 9;

        break; case 14: case 15:
            index = 10;

        break; case 16: case 17:
            index = 11;

        break; default:
            index = 0;

    }

    /* if (now.hour() == 9)
    {
        for (uint8_t indexConfiguration = 0; indexConfiguration <= 5; indexConfiguration++)
        {
            if (now.minute() > alarms[indexConfiguration].minute())
            {
                continue;
            }
            else
            {
                index = indexConfiguration + 1;
            }
        }
    }
    else if (now.hour() == 10)
    {
        if (now.minute() < alarms[7].minute())
        {
            index = 7;
        }
        else
            index = 8;
    }
    else if (now.hour() == 11 || now.hour() == 12)
    {
        index = 8;
    }
    else if (now.hour() == 13)
    {
        index = 9;
    }
    else if (now.hour() == 14 || now.hour() == 15)
    {
        index = 10;
    }
    else if (now.hour() == 16 || now.hour() == 17)
    {
        index = 11;
    }
    else
        index = 0; */
}