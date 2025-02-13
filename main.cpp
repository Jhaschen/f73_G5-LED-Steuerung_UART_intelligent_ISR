#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "f73-rncontrol-lib/uart.h"
#include "f73-rncontrol-lib/adc.h"
#include "f73-rncontrol-lib/button.h"
#include "f73-rncontrol-lib/led.h"

volatile uint8_t data = 0;

int main()
{
  // init uart
  uartInit(9600, 8, 'N', 1);
  // UART RX Interrupt
  UCSRB |= (1 << RXCIE); // RX Interrupt einschalten
  sei();

  // init LED
  ledInit();

  uint8_t data_old = 0;

  printf("LED-Steuerung\n\r0=LED0 (an/aus) .... 7 = LED7\n\r "); //  String senden

  while (1)
  {

    // data=uartGetc(); // Zeichen von Tastatur einlesen
    if (data != data_old)
    {
      data_old = data;
      if ((data >= '0') && (data <= '7'))
      { // Nur Tasten 1-7
        ledToggle((data - '0'));
      }
      else
      {

        printf("\n\rNur die Tasten 0 bis 7 druecken !\n\r "); //  String senden
      }
    }

    _delay_ms(50);
  }

  return 0;
}

ISR(USART_RXC_vect)
{

  data = UDR;

  printf("\n\r USART ISR RX\n\r ");
}
