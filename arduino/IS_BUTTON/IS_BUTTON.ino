/*
 ----------------------------------- 
 Encender LED con un pulsador
 -----------------------------------
 
 Oprimir un pulsador y mientras este se mantenga accionado 
 un LED se enciende
 
 Cosas de Mecatrónica y Tienda de Robótica
 
 */

//------------------------------------
//Declara puertos de entradas y salidas
//------------------------------------
int pulsador=8;        //Pin donde se encuentra el pulsador, entrada
int led=13;            //Pin donde se encuentra el LED, salida

//------------------------------------
//Funcion principal
//------------------------------------
void setup() // Se ejecuta cada vez que el Arduino se inicia
{
  pinMode(pulsador, OUTPUT); //Configurar el pulsador como una entrada
  pinMode(led,OUTPUT);      //Configurar el LED como una salida
  Serial.begin(9600);
}

//------------------------------------
//Funcion ciclicla
//------------------------------------
void loop() // Esta funcion se mantiene ejecutando
{           //  cuando este energizado el Arduino

  //Condicional para saber estado del pulsador
  if (digitalRead(pulsador)==LOW)
  {
    //Pulsador oprimido
    
    Serial.println("Hola");
    digitalWrite(led,LOW); //Enciende el LED
  }
  else
  {
    //Pulsador NO oprimido
    Serial.println("Adeu");
    digitalWrite(led,HIGH);  //Apaga el LED
  }

  delay(1000);

}

//Fin programa

