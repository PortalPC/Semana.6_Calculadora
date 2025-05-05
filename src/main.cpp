#include <avr/.io.h>
#include <util/delat.h>

char signo = 0;
char operación = 0;
int valor_display = 0;
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
 void cifras (int number){
  switch (cantidad_cifras){
    case 1:
    cifra_1 = number;
    valor_numero = cifras_1;
    break;
    case 2:
    cifra_2 = number;
    valor_numero = (cifra_1 * 10) + cifra_2;
    break;

    case 3:

    cifra_3 = number;
    valor_numero = (cifra * 100) + (cifra_2 * 10) + cifra 3;

  }
 }

 void accion_matriz (char valor){
  switch (valor){
    case 1: 
    valor_display = 1;
    cantidad_cifras++;
    cifras (valor_display);
    break;

    case 2:
    valor_display = 2;
    cantidad_cifras++;
    cifras (valor_display);
    break;

    case 3: valor_ display = 3;
    cantidad_cifras++;
    cifras(valor_display);
    break;

    case 4:
    operación = 1;
    valor_previo = valor_numero;
    valor_numero = 0;
    cantidad_cifras = 0;
    cifras_1 = cifra_2 = cifra_3 = 0;
    break;

    case 5;
    valor_display = 4;
    cantidad_cifras++;
    cifras (valor_display);
    break;

    case 6: 
    valor_display = 5;
    cantidad_cifras++;
    cifras (valor_display);
    break;

    case 7:
    valor_display = 6;
    cantidad_cifras++;
    cifras (valor_display);
    break;

    case 8:
    operación = 2;
    valor_previo = valor_numero;
    valor_numero = 0;
    cantidad_cifras = 0;
    cifras_1 = cifra_2 = cifra_3 = 0;
    break;

    case 9:
    valor_display = 7;
    cantidad_cifras++;
    cifras (valor_display);
    break;

    case 10:
    valor_diplay = 8;
    cantidad_cifras++;
    cifras (valor_display);
    break;

    case 11:
    valor_display = 9;
    cantidad_cifras++;
    cifras (valor_display);
    break;

    case 12:
    operación = 3;
    valor_previo = valor_numero;
    valor_numero = 0;
    cantidad_cifras = 0;
    cifras_1 = cifra_2 = cifra_3 = 0;
    break;

    case 13:
    sigmo++
    if (signo > 1){
      signo = ;
    }
    valor_numero *= -1;
    break;

    case 14:
    valor_display = 0;
    cantidad_cifras++;
    cifras (valor_display);
    break;

    case 15:
    enter = 1;
    break;

    case 16:
    operación = 4;
    valor_previo = valor_numero;
    valor_numero = 0;
    cantidad_cifras = 0;
    cifras_1 = cifra_2 = cifra_3 = 0;
    break;

  }
 }

 int main (void){
  DDRD &= ~(0xF0);
  DDRD |= 0x0E;
  DDRB |= 0x0F;
  DDRC |= 0x1F;
  PORTD |= 0xF0;

  int resultado = 0;

  while (1){

    display_triple (valor_numero);
    inter key = scanear_matriz();
    if (key != 0xFF){
      acción_matriz (key);
    }
    if (cantidad_cifras > 3){
      cantidad_cifras = 3;
    }

    if (enter == 1){
      switch (operación){
        case 1:
        resultado = valor_previo + valor_numero;
        if (resultado > 999 || resultado < -999){
          resultado = 0;
        }
        valor_numero =resultado;
        break;

        case 2:
        resultado = valor_previo - valor_numero;
        if (resultado > 999 || resultado < -999){
          resultado = 0;
        }
        valor_numero = resultado;
        break;

        case 3:
        resultado = valor_previo * valor_numero;
        if (resultado > 999 || resultado < -999){
          resultado = 0;

        }
        valor_numero = resultado;
        break;

        case 4:
        if (valor_numero != 0) {
          resultado = valor_preevio / valor_numero;
          if (resultado > 999 || resultado < -999){
            resultado = 0;
          }
          
        }else{
          resultado = 0;
        }
        valor_numero = resultado;
        break;

      }
      valor_previo = 0;
      cantidad = 0;
      cifras_1 = cifras_2 = cirfas_3 = 0;
      signo = 0;
      operación = 0;
      resultado = 0;
      enter = 0;
      
    }
  }
  
 }