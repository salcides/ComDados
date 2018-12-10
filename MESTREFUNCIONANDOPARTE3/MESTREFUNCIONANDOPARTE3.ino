#include <SoftwareSerial.h>
#include <ESP8266WiFi.h> //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO CÓDIGO
 
const char* ssid = "Salcides"; //VARIÁVEL QUE ARMAZENA O NOME DA REDE SEM FIO EM QUE VAI CONECTAR
const char* password = "072727201430"; //VARIÁVEL QUE ARMAZENA A SENHA DA REDE SEM FIO EM QUE VAI CONECTAR
 
WiFiServer server(80);


SoftwareSerial rs485(14, 12, false, 256);
int x=-1;
char c=0;
char d=0;
int set = -1;
int cont = 0;
int estadoled1 = 0;
int estadoled2 = 0;
int temperatura1 = -1;
int temperatura2 = -1;
void setup() {
// Inicializa a comunicaÃ§Ã£o serial com uma taxa de 9600 bauds.
pinMode(D7,OUTPUT);
Serial.begin(9600);
Serial.println("");
Serial.print("Conectando a ");
Serial.print(ssid);
WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) { //ENQUANTO STATUS FOR DIFERENTE DE CONECTADO
  delay(500);
  Serial.print(".");
}
Serial.print("Conectado a rede sem fio ");
Serial.println(ssid);
server.begin();
Serial.println(WiFi.localIP()); //Mostra o IP do servidor criado

rs485.begin(9600);
delay(50); 

}


void loop(){
WiFiClient client = server.available();

String request = client.readStringUntil('\r'); //Le o pedido do client
client.flush();

if (request.indexOf("/LED1") != -1)  {
  digitalWrite(D7, HIGH);
  delay(200);
  rs485.write('1');
  Serial.print("                 Comando executado:");
  Serial.println('1');
  Serial.print("\n");
  digitalWrite(D7, LOW);
  delay(150);
  estadoled1 = !estadoled1;
}
if (request.indexOf("/LED2") != -1)  {
  digitalWrite(D7, HIGH);
  delay(200);
  rs485.write('3');
  Serial.print("                 Comando executado:");
  Serial.println('3');
  Serial.print("\n");
  digitalWrite(D7, LOW);
  delay(150);
  estadoled2 = !estadoled2;
}
if (request.indexOf("/TMP1") != -1)  {
  digitalWrite(D7, HIGH);
  delay(200);
  rs485.write('2');
  Serial.print("                 Comando executado:");
  Serial.println('2');
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
           temperatura1 = x;
         }
}
if (request.indexOf("/TMP2") != -1)  {
  digitalWrite(D7, HIGH);
  delay(200);
  rs485.write('4');
  Serial.print("                 Comando executado:");
  Serial.println('4');
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
           temperatura2 = x;
         }
}

while(Serial.available())
{
  cont = 0;
  c = Serial.read(); // LÃª byte do buffer serial;

  if (c == '2' || c == '1'|| c == '3'|| c == '4'){
     Serial.println("digite um comando: (1) Acionar o atuador escravo 1 \n (2) Temperatura escravo 1 \n (3) Acionar o atuador escravo 2 \n (4) Temperatura escravo 2 \n (5) Definir Setpoint escravo 1 \n (6) Definir Setpoint escravo 2 \n\n");  
    digitalWrite(D7, HIGH);
    delay(200);
    rs485.write(c);
    Serial.print("                 Comando executado:");
    Serial.println(c);
    Serial.print("\n");
    digitalWrite(D7, LOW);
    delay(150);
    if(c == '1') estadoled1 = !estadoled1;
    if(c == '3') estadoled2 = !estadoled2;


           while(rs485.available()){
           x = rs485.read(); 
           d = rs485.read();
           rs485.flush();
           Serial.print("                 Temperatura:"); 
           Serial.println(x);
           d = rs485.read(); 
           delay(400);
           if (c == '2') temperatura1 = x;
           if (c == '4') temperatura2 = x;
    }

  }

  if ( c == '5' || c == '6') { //passar setpoint
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

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  //client.println("<meta http-equiv=""refresh"" content=""5"">");
  client.println("<style>body {background-color: #d24dff;}</style>");
  client.println("<h1><center><font color=""red"">Trabalho de Comunica&ccedil&atildeo</font></center></h1>");

  if (set != -1){
    client.print("<center> Valor do Setpoint: ");client.print(set);client.println("</center><br>");
  }
  client.print("<center>");
  
  if (estadoled1) client.println("Led 1 Ligado");
  else client.println("Led 1 Desligado");
  client.println("<br>");
  if (estadoled2) client.println("Led 2 Ligado");
  else client.println("Led 2 Desligado");
  client.print("<br>");

  if (temperatura1 > -1) {
    client.print("Temperatura 1: ");
    client.print(temperatura1);
  }
  client.println("<br>");
  if (temperatura2 > -1) {
    client.print("Temperatura 2: ");
    client.print(temperatura2);
  }
  client.print("<br>");
  
  client.print("</center>");
  client.println("<a href=\"/LED1\"\"><button>LED 1 </button></a>");//
  client.println("<a href=\"/LED2\"\"><button>LED 2 </button></a><br />");//
  client.println("<a href=\"/TMP1\"\"><button>TMP 1 </button></a>");
  client.println("<a href=\"/TMP2\"\"><button>TMP 2 </button></a><br />");
  client.println("<a href=\"/\"\"><button>Refresh </button></a><br />");
  
  client.println("</html>");
}

  

    
