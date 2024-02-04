

// DS3231 Pin   -    Arduino Pin
// SCL          -     A5 = SCL
// SDA          -     A4 = SDA
// SQW          -     D2 = INT0 - Used for Alarm Only.

#include <RTClib.h>
#include <Servo.h>
RTC_DS3231 rtc;
Servo myservo;
int pos;
int temp=0; 
int light=0; 
bool light_state=0;
bool temp_state=0;
bool state=0;

// the pin that is connected to SQW
#define CLOCK_INTERRUPT_PIN 2

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  myservo.attach(9);  
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
    Serial.begin(19200);

    if(!rtc.begin()) 
    {
        Serial.println("Couldn't find RTC!");
        Serial.flush();
        abort();
    }
    
    if(rtc.lostPower()) 
    {
        Serial.println("RTC lost power, set the time!");
    }
    
    //we don't need the 32K Pin, so disable it
    rtc.disable32K();
    
    // Making it so, that the alarm will trigger an interrupt
    pinMode(CLOCK_INTERRUPT_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(CLOCK_INTERRUPT_PIN), onAlarm, FALLING);
    
    // set alarm 1, 2 flag to false (so alarm 1, 2 didn't happen so far)
    // if not done, this easily leads to problems, as both register aren't reset on reboot/recompile
    rtc.clearAlarm(1);
    rtc.clearAlarm(2);
    
    // stop oscillating signals at SQW Pin
    // otherwise setAlarm1 will fail
    rtc.writeSqwPinMode(DS3231_OFF);
    
    // turn off alarm 2 (in case it isn't off already)
    // again, this isn't done at reboot, so a previously set alarm could easily go overlooked
    rtc.disableAlarm(2);

    
    DateTime now = rtc.now();
    // future alarm time is now + timespan given.
    DateTime future (now + TimeSpan(0,0,0,15)); //total seconds or // days,hrs,mins,secs
    
    // schedule an alarm 15 seconds in the future
    // Alarm when hours, minutes and seconds match 
    rtc.setAlarm1(future,DS3231_A1_Second);
}

void loop() {
  temp= analogRead(0);
light= analogRead(1);
   /* // print current time
    char timeNow[10] = "hh:mm:ss";
    rtc.now().toString(timeNow);
   Serial.print("Present Time = ");
    Serial.print(timeNow);
    
    // the value at SQW-Pin (because of pullup 1 means no alarm)
    Serial.print(" SQW: ");
    Serial.print(digitalRead(CLOCK_INTERRUPT_PIN));
    // whether a alarm happened happened
    Serial.print(" Alarm1: ");
    Serial.println(rtc.alarmFired(1)? "Yes. " : "No. ");
    */
    Serial.print("Temperature: ");
    Serial.println(temp);
    Serial.print("Light intensity: ");
    Serial.println(light);
if(light<275)
light_state=1;
else 
light_state=0;

if(temp<450)
temp_state=1;
else
temp_state=0;

if(temp_state==1){
if(state==1){
  state=0;
}
else state=1;
digitalWrite(3, state);
//Serial.println("1");
}
else if(light_state==1){
digitalWrite(3, 1);
}
else{
  digitalWrite(3, 0);
}
    delay(100);

   if(rtc.alarmFired(1)){
Serial.println("Alarm fired");
char timeNow[10] = "hh:mm:ss";
    rtc.now().toString(timeNow);
   Serial.print("Present Time = ");
    Serial.println(timeNow);
      for(pos=180; pos>=65; pos--){
    myservo.write(pos);
    delay(25);
    }
  delay(5000);

  for(pos=65; pos<=180; pos++){
    myservo.write(pos);
    delay(25);

    rtc.clearAlarm(1);
    DateTime now = rtc.now();
    // future alarm time is now + timespan given.
    DateTime future (now + TimeSpan(0,0,0,30)); //total seconds or // days,hrs,mins,secs
    // schedule an alarm 15 seconds in the future
    // Alarm when hours, minutes and seconds match 
    rtc.setAlarm1(future,DS3231_A1_Hour);
   }
}
}

void onAlarm() {

  }
