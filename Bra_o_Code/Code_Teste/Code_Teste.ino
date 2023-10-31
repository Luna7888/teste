#include <VarSpeedServo.h> //biblioteca para controle da velocidade e da posição dos servos

#define servoBase   3  // Porta Digital do Servo da Base
#define servoAltura 4  // Porta Digital do Servo da Altura do Braço
#define servoAngulo 5  // Porta Digital do Servo do Ângulo do Braço
#define servoGarra  6  // Porta Digital do Servo da Garra

#define potBase    A0  // Porta Analógica do Potenciometro para Controle da base
#define potAltura  A1  // Porta Analógica do Potenciometro para Controle da altura do braço
#define potAngulo  A2  // Porta Analógica do Potenciometro para Controle do ângulo do braço
#define potGarra   A3  // Porta Analógica do Potenciometro para Controle da garra

#define botao_trava     8  // Porta Digital do Botao trava
#define botao_destrava  9  // Porta Digital do Botao trava
 
//Instanciação dos Objetos de Controle dos Servos

VarSpeedServo base; 
VarSpeedServo altura;
VarSpeedServo angulo;
VarSpeedServo garra;

//Variaveis para cálculo dos angulos
int leitura_Base;
int valor_Base;
int leitura_altura;
int valor_altura;
int leitura_angulo;
int valor_angulo;
int leitura_garra;
int valor_garra;

//Variaveis para controle dos botões
int estado_trava, estado_destrava;
int anterior_trava = HIGH;
int anterior_destrava = HIGH;
boolean travado = false;

void setup(){
  pinMode(botao_trava, INPUT_PULLUP);
  pinMode(botao_destrava, INPUT_PULLUP);

  //Usa o LED do Arduino para informar estado de congelado
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
    
  //Configuração das Portas dos Servos
  base.attach(servoBase);
  altura.attach(servoAltura);
  angulo.attach(servoAngulo);
  garra.attach(servoGarra); 
}


void loop() {
 
  if (!travado) {
    leitura_Base = analogRead(potBase); //Leitura do Angulo do Potenciometro
    valor_Base = map(leitura_Base, 0, 1024, 0,180 ); //Conversão do valor do potenciometro (de 0 até 1024) para o angulo (de 0 até 180)
    base.slowmove(valor_Base, 30); //envio do ângulo para o servo
                          
  
    leitura_altura = analogRead(potAltura);           //Leitura do Angulo do Potenciometro
    valor_altura = map(leitura_altura, 0, 950, 180, 0); //Conversão do valor do potenciometro (de 0 até 1024) para o angulo (de 0 até 180) 
    altura.slowmove(valor_altura, 40); //envio do ângulo para o servo
    
    leitura_angulo = analogRead(potAngulo);           //Leitura do Angulo do Potenciometro
    valor_angulo = map(leitura_angulo, 0, 1024, 180, 0); //Conversão do valor do potenciometro (de 0 até 1024) para o angulo (de 0 até 180)
    angulo.slowmove(valor_angulo,40ij);                          //Envio do angulo para o Servo 
    
    leitura_garra = analogRead(potGarra);               //Leitura do Angulo do Potenciometro
    valor_garra = map(leitura_garra, 0, 1000, 0, 100); //Conversão do valor do potenciometro (de 0 até 1024) para o angulo (de 0 até 180)
    garra.slowmove(valor_garra, 80); //envio do ângulo para o servo                    
  }

  //Se o botao de congelar foi apertado
  estado_trava = digitalRead(botao_trava); 
  if (estado_trava != anterior_trava) {
     travado = true;
     digitalWrite(13, HIGH); //Informa o estado de congelado no LED interno do Arduino
  }
  anterior_trava = estado_trava;

  //Se o botao de descongelar foi apertado
  estado_destrava = digitalRead(botao_destrava); 
  if (estado_destrava != anterior_destrava) {
     travado = false;
     digitalWrite(13, LOW); //Informa o estado de congelado no LED interno do Arduino
  }
  estado_destrava = anterior_destrava;

}
