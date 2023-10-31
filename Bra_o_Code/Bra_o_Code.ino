

#include <Servo.h>

Servo servo1;

int joyX;          // Valor do eixo X do joystick (0-1023)
int angle = 90;    // Posição inicial do servo
bool servoLocked = false;    // Variável para controlar o bloqueio do servo (começa desbloqueado)
unsigned long lastButtonPressTime = 0; // Armazena o tempo do último pressionamento do botão
const unsigned long autoLockDelay = 1000; // Tempo em milissegundos para auto-travar o servo (5 segundos)
int buttonPin = 2; // Pino do botão para bloquear e destravar o servo
int servoStep = 10; // Incremento de ângulo em graus a cada passo

void setup() {
  servo1.attach(9);      // Conecte o servo ao pino 9
  servo1.write(angle);   // Inicialize o servo na posição inicial
  Serial.begin(9600);    // Inicialize a comunicação serial
  pinMode(buttonPin, INPUT_PULLUP); // Configure o pino do botão como entrada com resistor de pull-up interno
}

void loop() {
  // Ler os valores analógicos do joystick
  joyX = analogRead(A0);  // Conecte o eixo X do joystick ao pino A0

  // Mapear os valores do joystick (0-1023) para o ângulo do servo (0-180)
  angle = map(joyX, 0, 950, 0, 180);

  // Limitar o ângulo do servo entre 0 e 180 graus
  angle = constrain(angle, 0, 180);

  // Controlar o servo com o ângulo calculado, apenas se o servo não estiver bloqueado
  if (!servoLocked) {
    int currentAngle = servo1.read();
    if (angle > currentAngle) {
      for (int i = currentAngle; i <= angle; i += servoStep) {
        servo1.write(i);
        delay(80); // Atraso entre cada passo (ajuste para 80 ms)
      }
    } else if (angle < currentAngle) {
      for (int i = currentAngle; i >= angle; i -= servoStep) {
        servo1.write(i);
        delay(80); // Atraso entre cada passo (ajuste para 80 ms)
      }
    }
  }

  // Verificar o estado do botão para bloquear e destravar o servo
  if (digitalRead(buttonPin) == LOW) { // Se o botão for pressionado (LOW)
    lastButtonPressTime = millis(); // Registra o tempo do último pressionamento do botão
    servoLocked = !servoLocked; // Inverte o estado de bloqueio do servo
  }

  // Verificar o tempo decorrido desde o último pressionamento do botão e auto-travar o servo se necessário
  /*if (servoLocked && (millis() - lastButtonPressTime >= autoLockDelay)) {
    servoLocked = false; // Auto-destrava o servo após o tempo especificado
  }*/

  // Aguardar um breve intervalo para evitar leituras rápidas do joystick
  delay(50);
}
