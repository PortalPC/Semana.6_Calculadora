#include <avr/.io.h>
#include <util/delat.h>

char signo = 0;
char operación = 0;
int valor_displat = 0;
int valor_numero = 0;
int valor_previo = 0;
char cantidad_cifras = 0;
char cifra 1 = 0;
char cifra 2 = 0;
char cifra 3 = 0;
 char enter = 0;

 uitn8_t scanear_matriz(void){
  static uint8_t a =0;
  for (uint8_t row = 0; row <4; row++){
    PORTB = ~(1 << row) | 0xF0;
    _delay_ms(1);

    for (uint8_t col = 0; col < 4; col++){
      if (!(PIND & (1 << (col + 4)))){
        _delay_ms(50);
        if (a == 0){
          a= 1; return ((row*4) + col) + 1;
        }
        return 0xFF;
      }

    }
  }
  a = 0;
  return 0xFF;
 }

 void display_triple (int numero){
  if (valor_numero < 0){
    PORTC |= 0x10;
  }else {
    PORTC &= ~(0x100);
  }
  int num = numero;
  if (numero < 0){
    num = -numero;
  }

  int unidades = num % 10;
  int decenas = (num /10) % 10;
  int centenas = (num / 100);

  PORTF &= ~(0x08);
  PORTD &= ~(0x04);
  PORTD |= 0x02;

  PORTC |= (unidades | 0x00);
  PORTC &= (unidades | 0xF0);

  _delay_ms(5);

  PORTD &= ~(0x08);
  PORD |= 0x04;
  PORTD &= ~(0x02);

  PORTC |= (decenas | 0x00);
  PORTC &= (decenas | 0xF0);

  _delay_ms(5);
 }