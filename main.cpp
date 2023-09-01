// Cabeçalho somente para platformIO
// Remove no arduino IDE
#include <Arduino.h>

// Controle de LED
#define FPDIM 2    // Frequencia PDIM
#define FADIM 4    // Frequencia ADIM
#define DADIM 5    // DutyCycle ADIM
#define DREFF 7    // DutyCycle REF

// Entradas
#define ANALOG_IN A0
#define BTN 8

// Saidas PWM
#define PDIM_PWM 6
#define ADIM_PWM 9
#define REFF_PWM 3

// Variaveis globais
int funcao = 0;
int sensorValue;
int frequenciaPDIM = 100;
int frequenciaADIM = 2500;
int dutyCycleADIM = 1200;
int dutyCycleREF = 100;

int ultimo_valor_lido = 0;

int controleTrimpot(void);
void _delay(int ms);

void setup() {
  // Leds
  pinMode(FPDIM, OUTPUT);
  pinMode(FADIM, OUTPUT);
  pinMode(DADIM, OUTPUT);
  pinMode(DREFF, OUTPUT);

  // BTN
  pinMode(BTN, INPUT);

  // PWM
  pinMode(PDIM_PWM, OUTPUT);
  pinMode(ADIM_PWM, OUTPUT);
  pinMode(REFF_PWM, OUTPUT);

  // Timers para os PWMs
  TCCR0A = 0b01000010; // PDIM -> MODO CTC para configurar frequencia
  TCCR0B = 5;          // Prescaler 1024;

  TCCR2A = 0xA3;       // REF -> Modo FastPWM com 60Hz
  TCCR2B = 7;          // Aumente a frequência decrementando este valor

  TCCR1A = 0xA2;       // ADIM -> 100Hz
  TCCR1B = 0x1b;       // Prescaler 64;

  funcao = 0;
}

void loop() {
  // Reseta os LEDS
  digitalWrite(FPDIM, LOW);
  digitalWrite(FADIM, LOW);
  digitalWrite(DADIM, LOW);
  digitalWrite(DREFF, LOW);

  // Botao
  if(digitalRead(BTN) == LOW){
    funcao++;
    while(digitalRead(BTN) == LOW) _delay(30);
  }
  if(funcao == 4){
    funcao = 0;
  }

  switch(funcao){
    case 0:
      // Ajuste de frequencia do PDIM
      digitalWrite(FPDIM, HIGH);
      if (controleTrimpot()==1) break;
      frequenciaPDIM = sensorValue* (156. / 1023.);
      if(frequenciaPDIM < 30) frequenciaPDIM = 30;
      break;
    case 1:
      // Ajuste de frequencia do ADIM
      digitalWrite(FADIM, HIGH);
      if (controleTrimpot()==1) break;;
      frequenciaADIM = sensorValue *(5000./1023.); 
      if(frequenciaADIM<999) frequenciaADIM = 999;
      break;
    case 2:
      // Ajuste DutyCycle do ADIM
      digitalWrite(DADIM, HIGH);
      if (controleTrimpot()==1) break;
      dutyCycleADIM = sensorValue* ((float)frequenciaADIM / 1023.);
      break;
    case 3:
      // Ajuste DutyCycle do REFF
      digitalWrite(DREFF, HIGH);
      if (controleTrimpot()==1) break;
      dutyCycleREF = sensorValue * (255. / 1023.);
      break;
  }

  // Atuação
  OCR0A = frequenciaPDIM;  // Pino 6
  ICR1  = frequenciaADIM;  // Pino 9
  OCR1A = dutyCycleADIM;   // Pino 9
  OCR2B = dutyCycleREF;    // Pino 3
}

/* Esta função retorna 1 se o trimpot for alterado
 * no intervalo de tempo que ela for chamada */
int controleTrimpot(void){
  sensorValue = analogRead(ANALOG_IN);
  ultimo_valor_lido = sensorValue;
  _delay(60);
  sensorValue = analogRead(ANALOG_IN);
  if(ultimo_valor_lido <= sensorValue+5 && 
      ultimo_valor_lido >= sensorValue-5) 
        return 1;
  return 0;
}

void _delay(int ms){
  for(double i=0; i<20000*ms; i++){
    asm("nop");
  }
}
