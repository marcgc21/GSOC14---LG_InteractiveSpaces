/*
 * WebServerParsing
 * Respond to requests in the URL to change digital output ports
 * For example:
 *   sending http://192.168.1.40/?POID2=1 turns digital pin 2 on
 *   sending http://192.168.1.40/?POID2=0 turns pin 2 off. 
 *   sending http://192.168.1.40/?POID2=0&POID3=0 turns pin 2 and pin 3 off. 
 * This sketch demonstrates text parsing using the 1.0 Stream class.
 * Moreover you can see which pings are open using the web http://192.168.1.40
 */

#include <SPI.h>        
#include <Ethernet.h>

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 
  192, 168, 1,40 };

EthernetServer server(80);

void setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.println("ready");
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
}

void loop()
{
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        int digitalRequests = 0;  
        int analogRequests = 0;
        if( client.find("GET /") ) {  // search for 'GET'
          // find tokens starting with "pin" and stop on the first blank line
          // search to the end of line for 'pin'
          Serial.println("hola");


          while(client.findUntil("POI", "\n\r")){  
            char type = client.read(); // D or A
            // the next ascii integer value in the stream is the pin
            int pin = client.parseInt(); 
            int val = client.parseInt(); // the integer after that is the value
            if( type == 'D') {
              Serial.print("Digital pin ");

              pinMode(pin, OUTPUT);
              digitalWrite(pin, val);
              digitalRequests++;
            }

            else {
              Serial.print("Unexpected type ");
              Serial.print(type);
            }
            Serial.print(pin);
            Serial.print("=");
            Serial.println(val);
          }

        }
        Serial.println();

        //Serves a standard http response header with pins information
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println();

        //Output the number of pins handled by the request
        client.print(digitalRequests);
        client.print(" digital pin(s) written");
        client.println("<br />");


        //Output the value of each analog input pin
        for (int i = 1; i < 9; i++) {
          client.print("Digital input ");
          client.print(i);
          client.print(" is ");
          client.print(digitalRead(i));
          client.println("<br />");
        }

        break;
      }
    }
    //Give the web browser time to receive the data
    delay(1);
    client.stop();
  }
}

