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
     Serial.println("digite um comando: (1) Acionar o atuador escravo 1 \n (2) Temperatura escravo 1 \n (3) Acionar o atuador escravo 2 \n (4) Temperatura escravo 2 \n (5) Definir Setpoint escravo 1 \n (6) Definir Setpoint escravo 2 \n\n");  
    digitalWrite(D7, HIGH);
    delay(200);
    rs485.write(c);
    Serial.print("                 Comando executado:");
    Serial.println(c);
    Serial.print("\n");
    digitalWrite(D7, LOW);
    delay(150);
 


           while(rs485.available()){
           x = rs485.read(); 
           d = rs485.read();
           rs485.flush();
           Serial.print("                 Temperatura:"); 
           Serial.println(x);
           d = rs485.read(); 
           delay(400);
    }

  }

  if ( c == '5') { //passar setpoint
    Serial.println("digite um comando: (1) Acionar o atuador escravo 1 \n (2) Temperatura escravo 1 \n (3) Acionar o atuador escravo 2 \n (4) Temperatura escravo 2 \n (5) Definir Setpoint escravo 1 \n (6) Definir Setpoint escravo 2 \n\n");  
    delay(200);
    digitalWrite(D7, HIGH);
    rs485.write(c);
    Serial.print("                   Comando executado:");
    Serial.println(c);
    Serial.print("\n");
    Serial.print("   Digite um Setpoint: \n`");
    delay(50);
    digitalWrite(D7, LOW);
    d = rs485.read(); 
    delay(1000);

    if(Serial.available()){
      set = Serial.parseInt();
    Serial.print("                    Setpoint:");

    
          digitalWrite(D7, HIGH);
          rs485.print(set);
          digitalWrite(D7, LOW);
          d = rs485.read(); 
          delay(100);
         
          
            Serial.println(set);
            Serial.print("\n");}
    }
    }    
}

  

    
