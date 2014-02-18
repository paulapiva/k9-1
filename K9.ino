/**
 * Programa do K9
 *
 *
 * Autor: Mauricio de O. Pena
 * Data: 30/01/2014
 *
 */
#include <Ultrasonic.h>
#include <Servo.h> 

// Indica constantes
#define PWM_MD 10            // PWM MOTOR DIREITO
#define PWM_ME 9             // PWM MOTOR ESQUERDO
#define DIR_MD 4             // DIRECAO MOTOR DIREITO
#define DIR_ME 8             // DIRECAO MOTOR ESQUERDO

// Seta variaveis globais
Ultrasonic ultrasonic(2, 5); // indica
Servo myservoD;              // inica objeto do servo da direita do cão
Servo myservoE;              // inica objeto do servo da esquerda do cão
int pos1 = 0;                // variável para armazenar a posição de servo da direita 
int pos2 = 180;              // variável para armazenar a posição de servo da esquerda 
int dir1 = 1;                // variable to store the servo position 
int dir2 = 0;                // variable to store the servo position 
long distancia = 100000000L; // variavel que recebe valor da distancia

void setup() {
    
    // Seta os pinos dos PWM dos motores como saidas
    pinMode(PWM_ME, OUTPUT);
    pinMode(PWM_MD, OUTPUT);
    
    // Seta os 2 pinos de controle dos motores
    pinMode(DIR_ME, OUTPUT);
    pinMode(DIR_MD, OUTPUT);
    
    // Aciona ambos os motores em 100%
    analogWrite(PWM_ME, 255);
    analogWrite(PWM_MD, 255);
  
    // Define direcao dos 2 motores
    digitalWrite(DIR_ME, LOW);
    digitalWrite(DIR_MD, LOW);  
    
    // Configuracao da porta serial, para exibir as leituras do sonar
    Serial.begin( 9600 );
    
    // Configura servos
    myservoD.attach(11);  // atribui o servo no pino 11 para o objeto servo da direita do cão
    myservoE.attach(12);  // atribui o servo no pino 12 para o objeto servo da esquerda do cão
}
 
void loop() {
      
    // Obtem valor do sonar
    distancia = ultrasonic.Ranging(CM);
    
    // Checa se o robo colidiu com algo
    if (distancia <= 45)
    {
      // Movimenta para tras, circulando
      digitalWrite(DIR_ME, HIGH);
      digitalWrite(DIR_MD, LOW); 
      
      // Aguarda 0,3 segundo
      delay(300);
      
      // Movimenta para frente
      digitalWrite(DIR_ME, LOW);
      digitalWrite(DIR_MD, LOW);      
    }
        
    // Exibe leitura do sonar
    Serial.print(distancia);
    Serial.println( "cm" );    
    delay(200);      // tempo necessario para uma nova leitura do sonar

    // Movimenta os servos
    myservoD.write(pos1);
    myservoE.write(pos2);
    delay(15);

    if (dir1 == 1)
    { 
      pos1 += 10;
      if (pos1 == 180)
      {
        dir1 = 0;
      }
    }  
    else
    {
      pos1 -= 10; 
      if (pos1 == 110)
      {
        dir1 = 1;
      }
    }
  
    if (dir2 == 1)
    { 
      pos2 += 10;
      if (pos2 == 140)
      {
        dir2 = 0;
      }
    }  
    else
    {
      pos2 -=10; 
      if (pos2 == 50)
      {
        dir2 = 1;
      }
    }    

    //Serial.println(pos1);    
    //Serial.println(pos2);
}

