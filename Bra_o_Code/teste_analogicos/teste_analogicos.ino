const int pinX = A0; // Pino analógico para o eixo X do joystick
const int pinY = A1; // Pino analógico para o eixo Y do joystick

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
}

void loop() {
  int xAxisValue = analogRead(pinX); // Lê o valor do eixo X
  int yAxisValue = analogRead(pinY); // Lê o valor do eixo Y

  // Imprime os valores no Monitor Serial
  Serial.print("Eixo X: ");
  Serial.print(xAxisValue);
  Serial.print("\tEixo Y: ");
  Serial.println(yAxisValue);

  delay(100); // Pequena pausa para evitar leituras muito rápidas
}
