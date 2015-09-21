// #############################################################################
// #                --- Borsti: Remote controlled vibrobot ---                 #
// #############################################################################
// # bluetooth.c - HC-05 bluetooth module functions                            #
// #############################################################################
// #              Version: 1.1 - Compiler: AVR-GCC 4.5.3 (Linux)               #
// #     (c) 2013 by Malte Pöggel - www.MALTEPOEGGEL.de - malte@poeggel.de     #
// #############################################################################
// #  This program is free software; you can redistribute it and/or modify it  #
// #   under the terms of the GNU General Public License as published by the   #
// #        Free Software Foundation; either version 3 of the License,         #
// #                  or (at your option) any later version.                   #
// #                                                                           #
// #      This program is distributed in the hope that it will be useful,      #
// #      but WITHOUT ANY WARRANTY; without even the implied warranty of       #
// #           MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.            #
// #           See the GNU General Public License for more details.            #
// #                                                                           #
// #  You should have received a copy of the GNU General Public License along  #
// #      with this program; if not, see <http://www.gnu.org/licenses/>.       #
// #############################################################################

 #include <avr/io.h>
 #include <util/delay.h>
 #include "uart.h"
 #include "eeprom.h"
 #include "bluetooth.h"


 // ***** Initialize BT module if PD4 high on startup *****
 void bluetooth_init( void )
  {
   uint8_t i, chr;

   // Setup HC5 bluetooth module
   DDRD &= ~(1<<PD4); // Key pin

   if(!(PIND&(1<<PD4))) return;

   // Status LEDs
   PORTB |= (1<<PB0);
   PORTB |= (1<<PB1);

   // Check module ready
   while(1)
    {
     uart_putstring("AT\r\n");
     bluetooth_delay();
     bluetooth_delay();
     bluetooth_delay();
     bluetooth_delay();
     if(buffer_cmp("OK\r", 3)) break;
    }
   uart_reset();

   // Restore defaults
   uart_putstring("AT+ORGL\r\n");
   bluetooth_wait();

   // Set role
   uart_putstring("AT+ROLE=0\r\n");
   bluetooth_wait();

   // Set baudrate
   uart_putstring("AT+UART=38400,0,0\r\n");
   bluetooth_wait();

   // Set name
   uart_putstring("AT+NAME=Borsti");
   for(i=EE_BT_NAME_0;i<=EE_BT_NAME_5;i++)
    {
     chr = ee_getval(i);
     if(chr<=0x20) break;
     if(i==EE_BT_NAME_0) uart_putchar('-'); // Add - before first character
     uart_putchar(chr);
    }
   uart_putstring("\r\n");
   bluetooth_wait();

   // Finished
   PORTB &= ~(1<<PB1);
   while(1)
    {
     bluetooth_delay();
     bluetooth_delay();
     PORTB ^= (1<<PB0);
     PORTB ^= (1<<PB1);
    }
  }


 // ***** Wait for OK from module *****
 void bluetooth_wait( void )
  {
   while(1)
    {
     bluetooth_delay();
     if(buffer_cmp("OK\r", 3)) break;
    }
   uart_reset();
  }


 // ***** Delay function *****
 void bluetooth_delay( void )
  {
   _delay_ms(50);
  }
