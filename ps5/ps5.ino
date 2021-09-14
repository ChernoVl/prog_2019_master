#include "lcd_wrapper.h"
#include "mastermind.h"

void setup()
{
  Serial.begin(9600); // send and receive at 9600 baud
  
  pinMode(LED_BLUE_1, OUTPUT);
  pinMode(LED_RED_1, OUTPUT);
  pinMode(LED_BLUE_2, OUTPUT);
  pinMode(LED_RED_2, OUTPUT);
  pinMode(LED_BLUE_3, OUTPUT);
  pinMode(LED_RED_3, OUTPUT);
  pinMode(LED_BLUE_4, OUTPUT);
  pinMode(LED_RED_4, OUTPUT);

  pinMode(BTN_1_PIN, INPUT);
  pinMode(BTN_2_PIN, INPUT);
  pinMode(BTN_3_PIN, INPUT);
  pinMode(BTN_4_PIN, INPUT);
  pinMode(BTN_ENTER_PIN, INPUT_PULLUP);

  lcd_init();
  
  randomSeed(analogRead(0));
}

void loop() 
{
    char* code = generate_code(false, 4);
    play_game(code);
    free(code);
}