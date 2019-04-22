#include<SoftwareSerial.h>
SoftwareSerial esp(2,3);
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
 int i;

void setup(){ 
  Serial.begin(9600);
  esp.begin(115200);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  scom("AT+RST",5,"OK");
  scom("AT+CWMODE=2",5,"OK");
  scom("AT+CIFSR",5,"WIFI GOT IP");
  scom("AT+CIPMUX=1",5,"OK");
  scom("AT+CIPSERVER=1,80",5,"OK");
}
void loop(){
   String str = "";
   Serial.print(".");
   i+=1;
    if(esp.find("+IPD,")){
    str += esp.readString();
    Serial.print("["+str+"]");
    Serial.print(str.length());
//    Serial.print(strlen(str));
     if(str.length() ==8){
      digitalWrite(11, !digitalRead(11));
      Serial.print("Lights Toggled!");
      
      }
      if(str.length() == 10 ){
        digitalWrite(12, !digitalRead(12));
        Serial.print("Fans Toggled!");
      }
    }
    if(i >= 20){
      Serial.println(" ");
      i = 0;
    }
    //Now str has the output, simply put str == +IPD 0,4:11 for pin 11 and +IPD 0,4:12 for pin 12
    //Henceforth we will be modifying this bit as well. 
   
    
  }



void scom(String command, int maxTime, char readReplay[]) { 
  Serial.print("  [[AT command]]: ");
  Serial.print(command);
  Serial.print(" ");
  esp.println(command);
  while(countTimeCommand < (maxTime*1))
  {
    esp.println(command);                //at+cipsend
    if(esp.find(readReplay))              //ok
    {
      found = true;
      break;
    }
    countTimeCommand++;
  }
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  found = false;
 }
