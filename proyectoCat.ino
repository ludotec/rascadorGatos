
#define sw1                 13
#define sw2                 11
#define pinMotor            6
#define in3                 4
#define in4                 3
#define tiempoGiro          5000
#define readSwitch(x)       digitalRead(x)
#define encenderMotor       digitalWrite(pinMotor, HIGH)
#define apagarMotor         digitalWrite(pinMotor, LOW)
#define giroHorarioHIGH     digitalWrite(in3, HIGH)
#define giroHorarioLOW      digitalWrite(in4, LOW)
#define giroAntiHorarioHIGH digitalWrite(in4, HIGH)
#define giroAntiHorarioLOW  digitalWrite(in3, LOW)

const int EchoPin    = 9;
const int TriggerPin = 10;

void setup() {
  Serial.begin(9600);
  pinMode(sw1, INPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(sw2, INPUT);
  pinMode(pinMotor, OUTPUT);
  pinMode(TriggerPin, OUTPUT);
   pinMode(EchoPin, INPUT);
}

void loop() {
 int cm = ping(TriggerPin, EchoPin);
 static unsigned long antMillis=0;
 static bool giro = 0;

Serial.print("detenido...");
Serial.println(cm);

//controlo el tiempo de giro
 
 
   if (cm <= 7 && readSwitch(sw2) == 0 && giro){
      Serial.print("girandoSW2... ");
      Serial.println(cm);
      encenderMotor;
      giroHorarioHIGH;
      giroHorarioLOW;
   }
   if (cm <= 7 && readSwitch(sw1) == 0 && !giro){
      Serial.print("girandoSW1... ");
      Serial.println(cm);
      encenderMotor;
      giroAntiHorarioHIGH;
      giroAntiHorarioLOW;
    }
   if((millis() - antMillis) < tiempoGiro) return;
   antMillis = millis(); 
   apagarMotor;
   giro = !giro;    
   Serial.println(giro);
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
