#include <SoftwareSerial.h>
int leitura = 0;
int estadoled = 0;
int estadoled2 = 0;
SoftwareSerial rs485(10,11);
char c=0;
int set =100;
byte d;

char t = 'T';
void setup() {


  pinMode(6, OUTPUT);       //pino de controle
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);       //led de saida
  digitalWrite(6,LOW);      //inicia em modo recepção
  Serial.begin(9600);       //inicia serial
  rs485.begin(9600);        //inicia comunicacao rs485
  delay(60);
}
 
void loop() {

            leitura = analogRead(0);
            leitura = map(leitura,0,1023,0,99);
  digitalWrite(6,LOW);
             if ( leitura >= set){
                delay(60);
                digitalWrite(12,HIGH);
                Serial.print("alarme    ->");
                Serial.println(leitura);
             }
             else{
             digitalWrite(12,LOW);    
            }
              
   //Ve se tem sinal na porta do rs485
  while (rs485.available()){
                   //habilita transmissao
            c = rs485.read();

            if( c=='4'){ // comando de requisicao da temperatura
              Serial.println(c);
              digitalWrite(6,HIGH);  
              delay(60);

              
              
              rs485.write(leitura);
              Serial.println(leitura);

               //delay(60);
               rs485.flush();
              digitalWrite(6,LOW); 
             
            }

            if( c == '3'){ // comando para alterar o estado do led neste escravo
              
              Serial.println(c); 
              delay(60);
//altera o estado do led o led
              estadoled = !estadoled; 
              if (estadoled == 0) {
                digitalWrite(13,LOW);
                Serial.println("Led Desligado");
              }
              else {
                digitalWrite(13,HIGH);
                Serial.println("Led Ligado");
              }
                            
               delay(60);
               rs485.flush();
             // digitalWrite(6,LOW); 
            }

            if ( c == '6'){
              Serial.println(c);
              digitalWrite(6,HIGH);  
              delay(60);
              
              rs485.write('6');
              d = rs485.read(); 
              rs485.flush();
              
              digitalWrite(6,LOW); 
              delay(1000);
             
              set = rs485.parseInt();
              Serial.println(set);
            }

          
               delay(60);
               rs485.flush();
             // digitalWrite(6,LOW); 

             }

                  
}                 
