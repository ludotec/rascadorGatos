/***************  Configuración  *****************************/
/*
 * Autor: Fuentes Claudio
 * Año 2022
 * Materia: Micrcontroladores II
 * Profesor: Alejo Giles
 * Carrera: Técnico Superior en Desarrollo de Software
 * Instituto: Ites (Instituto Tecnológico de Educación Superior)
 * 
 * Descripción: El código es para el proyecto que se realizón en la maateria de 
 * Robótica y Automatización Industrial dictada por el Profesor Gonzalez Nicolas.
 * El proyecto consta de un rodillo que debe actuar al detectar un elemento cercano
 * a una determinada distancia y detenerse al alejarse. A su vez el sensor de movimiento
 * tiene que hacer un barrido de 180° en ambas direcciones a partir de su punto medio. 
 * Además debe tener una señal lumínica que indique la presencia del objeto en distintas direcciones.
 * 
 * Actuadores: Motor cc, Servomotor, Led RGB, Sensor ultasónico.
 * 
 */

#include <Servo.h>

Servo servo;

#define PIN_SERVO          11 
#define PIN_LED_RED        6
#define PIN_LED_BLUE       7
#define PIN_LED_GREEN      8
#define PIN_MOTOR_ENABLE   5  //Pin 1 "Enable 1" L293D
#define PIN_IN_1           3  //Pin 2 "INPUT 1" L293D
#define PIN_IN_2           4  //Pin 9 "INPUT 2" L293D
#define TIEMPO_GIRO        5000  // tiempo de giro del motor en ms.
#define TIEMPO_INACTIVO    10000 // tiempo en que el motor se encuentra inactivo en ms.
#define DISTANCIA_SENSOR   15 
//#define ANT_MILLIS_SERVO   0
//#define DELAY_SERVO        ((millis() -  ANT_MILLIS_SERVO) < 15)
#define ENCENDER_MOTOR(x)  digitalWrite(PIN_MOTOR_ENABLE, x)
#define SENTIDO_GIRO(a,b)  digitalWrite(PIN_IN_1, a);digitalWrite(PIN_IN_2, b);
#define LED_SERVO_OFF      digitalWrite(PIN_LED_GREEN, 0);digitalWrite(PIN_LED_BLUE, 0);
#define LED_SENSOR(x)      digitalWrite(PIN_LED_RED, x);
#define DEBUG(x)           Serial.println(x)           

const int  EchoPin    = 9;
const int  TriggerPin = 10;
      int  posServo   = 90;
      bool detenido   = 0;
      bool estadoMotor = 1;
      bool estadoMotorAnt = 0;
      unsigned long antMillisGlobal = 0;
      bool estadoGiro = 0;
      int giroServo = 3;
      char a = 0;
      char b = 1;
      char led = 1;
 

void setup() {
  Serial.begin(9600);
  servo.attach(PIN_SERVO);
  pinMode(PIN_IN_1, OUTPUT);
  pinMode(PIN_IN_2, OUTPUT);
  pinMode(PIN_MOTOR_ENABLE, OUTPUT);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  servo.writeMicroseconds(1500);
  servo.write(posServo);
}

/******************************** Funciones ************************************/

 void CtrlServo(void)
  {
  static unsigned char posServo_ant=0;
  
  if(posServo==posServo_ant) return;
  posServo_ant=posServo;

  servo.write(posServo);
 }
  
void EncenderMotor(){
 int cm = ping(TriggerPin, EchoPin);
 static unsigned long antMillisMotor =0;
 if((cm < DISTANCIA_SENSOR)&& estadoMotor && (millis() - antMillisMotor) > 150){
  antMillisMotor = millis();
  estadoMotor = 0;
  giroServo = 3;
  LED_SENSOR(1);
  estadoGiro = !estadoGiro;
  ENCENDER_MOTOR(1);
  DEBUG("Motor Encendido");  
 }
}
void CtrlTiempo() 
{
  if(!estadoMotor) return;
  
  if((millis() - antMillisGlobal) < TIEMPO_INACTIVO) return;
  antMillisGlobal = millis();
  DEBUG("GirarServo");
  giroServo = 0;
  led = 0;
}

void CtrlGiro(){
 static char estadoGiroAnt = 0;
 static unsigned long antMillis =0;
 
 if(estadoMotor) return;
 
 if((millis() - antMillis) < 500) return;
 antMillis = millis();
 
 
 if(estadoGiro == estadoGiroAnt) return;
 estadoGiro = estadoGiroAnt;
 DEBUG("entro");
 
 a=!a;
 b=!b;
 SENTIDO_GIRO(a,b);
}

void ApagarMotor(){
  int cm = ping(TriggerPin, EchoPin);
  static unsigned long antMillis =0;
  
  if(estadoMotor) return;
  
  if(cm < DISTANCIA_SENSOR)   antMillis=millis();

  if((millis() - antMillis) < TIEMPO_GIRO) return;
  antMillis = millis();
  DEBUG("apagarMotor");
  ENCENDER_MOTOR(0);
  estadoMotor = 1;
  LED_SENSOR(0);
}

int ping(int TriggerPin, int EchoPin) {
   long duration, distanceCm;
   
   digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(TriggerPin, LOW);
   
   duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
   
   distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
   return distanceCm;
}


void BarridoServo(){
  static unsigned long antMillis=0;
  
  if ((millis() - antMillis) < 15) return;
  antMillis = millis();

  switch(giroServo){
    case 0      :  posServo--;  //de 90 a 0
                   if(posServo) return;
                   giroServo++;
    case 1      :  posServo++; //de 0 a 180
                   if(posServo<180) return;
                   giroServo++;
    case 2      :  posServo--; //de 180 a 90
                   if(posServo>90) return;
                   giroServo++;
                   break;
    case 3      :  posServo = 90; 
                   antMillisGlobal = millis();
                   giroServo++;
                   LED_SERVO_OFF
                   led = 1;   
                   break; 
  }
}

void LedTest()
  {
  #define INTERVALO 250
  static int ledState=0;
  static unsigned long antMillis = 0;
  if(led) return;
  //Si no se cumple tal condicion, retorna
  if(millis() - antMillis < INTERVALO) return;
  antMillis = millis();

  ledState = !ledState;
  
  digitalWrite(PIN_LED_GREEN, !ledState);  
  digitalWrite(PIN_LED_BLUE, ledState);
  }

/***************************** Main *************************************************/


void loop()
{
  EncenderMotor();
  ApagarMotor();
  BarridoServo();
  CtrlServo();
  CtrlGiro();
  CtrlTiempo();
  LedTest();
}
