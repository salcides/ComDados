#include <SoftwareSerial.h>


SoftwareSerial rs485(14, 12, false, 256);
int x=0;
char c=0;
char d=0;
int set = 0;
int cont = 0;
void setup() {
// Inicializa a comunicaÃ§Ã£o serial com uma taxa de 9600 bauds.
pinMode(D7,OUTPUT);
Serial.begin(9600);
rs485.begin(9600);
delay(50); 

}

void loop(){

while(Serial.available())
{
  cont = 0;
  c = Serial.read(); // LÃª byte do buffer serial;

  if (c == '2' || c == '1'){
      
    digitalWrite(D7, HIGH);
    rs485.write(c);
    digitalWrite(D7, LOW);
    delay(100);
 
    d = rs485.read(); 

  }

  if ( c == '6') { 

    digitalWrite(D7, HIGH);
    rs485.write(c);
    digitalWrite(D7, LOW);
    d = rs485.read(); 
    delay(1000);

    if(Serial.available()){
      set = Serial.parseInt();
      Serial.println(set);
    
          digitalWrite(D7, HIGH);
          rs485.print(set);
          digitalWrite(D7, LOW);
          d = rs485.read(); 
          delay(100);
    }

    
    }
  
while(rs485.available()){
    x = rs485.read(); 
    d = rs485.read();
    rs485.flush(); 
    if(cont=1){
    Serial.println(x);
    cont++;}
    d = rs485.read(); 
    delay(400);
    }
    
    
     
}
  }
  

    
