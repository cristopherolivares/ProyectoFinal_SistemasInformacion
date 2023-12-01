#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "M33RK4T 1226"; //SSID red wifi 
const char *password = "chocokrispi"; //password red wifi
String servidor = "http://192.168.100.73/html/"; //Servidro al que se conectará
//Cliente wifi
WiFiClient client;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println("Conectado a: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) //Esperar a concetar WiFi
  {
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.println("¡WiFi conectado!");

}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0;i<=10;i++)
  {
    HTTPClient http;
    Serial.print("Numero actual: ");
    Serial.println(i);
    //Valor a enviar a servidor
    String sEnviado = "valor=" + String(i);
    Serial.println("Enviar a servidor");
    Serial.println("<- "+sEnviado);

    //Inicializacion de servicio de envio
    http.begin(client,servidor);
    http.addHeader("Content_Type", "application/x-www-form-urlencoded"); //Header de texto plano
    //Envio de post con espera de código respuesta
    int iCodigoRespuesta = http.POST(sEnviado);
    //Validar codigo respuesta
    if (iCodigoRespuesta>0)
    {
      Serial.println("Codigo de respuesta "+ String(iCodigoRespuesta));
      //Respuesta satisfactoria
      if(iCodigoRespuesta == 200)
      {
        String sRecibido = http.getString();
        Serial.println("Respuesta servidor: ");
        Serial.println("-> +sRecibido");
        }
      }
      else
      {
        Serial.print("Error en envio de post: ");
        Serial.println(iCodigoRespuesta);
        }
        //Finalizacion de servicio de envio
        http.end();
        //client.stop();
        Serial.println("Espera ...");
        delay(5000); //Retardo entre envios de servidor
    }

}
