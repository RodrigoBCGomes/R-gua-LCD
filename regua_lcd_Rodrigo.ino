#include <HCSR04.h>                    // Inclui a biblioteca do módulo HC-SR04
#include <LiquidCrystal_I2C.h>         // Inclui a biblioteca LCD com I2C

                                       // Define pinos de entrada e saída do Arduino
const byte pinTrig = 8;                // Pino usado para disparar os pulsos do sensor
const byte pinEcho = 9;                // Pino usado para ler a saida do sensor
const byte pinBut = 2;                 // Pino usado para o push button

#define col 16                         // Define o número de colunas do display utilizado
#define lin 2                          // Define o número de linhas do display utilizado
#define ende 0x27                      // Define o endereço do display
                                       // Instancia objetos das bibliotecas
LiquidCrystal_I2C lcd(ende, col, lin); // Cria o objeto lcd passando como parâmetros o endereço, o nº de colunas e o nº de linhas

// define variáveis globais
byte state = 1;                        // Estado do menu
byte decimal = 0;                      // Número de casas decimais
String unity = "cm";                   // Descrição das unidades
double *result;                        // Uso do ponteiro para um double (obrigatório)

void setup() {
  pinMode(pinBut,INPUT_PULLUP);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Loading ruler...");
  lcd.setCursor(0,1);
  lcd.print("By: Rojao");
  HCSR04.begin(pinTrig,pinEcho);
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop() {
  readPushButton();
  showDisplay();
  delay(150);
}

void readPushButton(){
  if(!digitalRead(pinBut)){
    state >= 3 ? state = 0 : state = state;
    state++;
    while(!digitalRead(pinBut)){}
    lcd.clear();
    delay(150);
  }
}

void showDisplay(){
  switch(state){
    case 1:
      result = HCSR04.measureDistanceCm();
      decimal = 0;
      unity = "cm";
      break;
    case 2:
      result = HCSR04.measureDistanceMm();
      decimal = 0;
      unity = "mm";
      break;
    case 3:
      result = HCSR04.measureDistanceIn();
      decimal = 0;
      unity = "pol";
      break;    
  }  
  lcd.setCursor(0,0);
  lcd.print("       ");
  lcd.print(result[0],decimal);
  lcd.print(unity);
  lcd.print("       ");
  lcd.setCursor(1,1);
  lcd.print("The ruler worked!!");
}
