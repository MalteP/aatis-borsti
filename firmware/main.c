// #############################################################################
// #                --- Borsti: Remote controlled vibrobot ---                 #
// #############################################################################
// # main.c - Main program                                                     #
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
 #include <avr/wdt.h>
 #include "io.h"
 #include "libnecdecoder.h"
 #include "ir.h"
 #include "bluetooth.h"
 #include "uart.h"
 #include "main.h"


 // ***** Main loop *****
 int main( void )
  {
   uint8_t controlmode = 0;

   // Make sure WDT is disabled here
   wdt_disable();

   // Init IO
   io_init();

   // Init UART
   uart_init();

   // Init Bluetooth
   bluetooth_init();

   // Initialize IR lib
   ir_init();
   ir_restore();

   // Set lights
   io_set_led_front();
   io_set_blink(5);

   // Enable WDT
   wdt_enable(WDTO_500MS);

   // Poll functions
   while(1)
    {
     io_poll();
     uart_poll(&controlmode);
     ir_poll(controlmode);
     wdt_reset();
    }
  }
