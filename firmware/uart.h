// #############################################################################
// #                --- Borsti: Remote controlled vibrobot ---                 #
// #############################################################################
// # uart.c - UART functions                                                   #
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

 #ifndef UART_H
  #define UART_H

  #include <avr/io.h>

  // Crystal
  #ifndef F_CPU 
   #warning "F_CPU undefined, set to 4,9152MHz"
   #define F_CPU 4915200UL
  #endif 

  // Baudrate
  #define BAUD 38400UL

  // Calculations
  #define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)
  #define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))
  #define BAUD_ERROR ((BAUD_REAL*1000)/BAUD)

  #if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
   #error Baudrate error higher than 1%! 
  #endif

  #define UART_BUFFERSIZE 8

  void uart_init( void );
  void uart_putchar( char x );
  void uart_putstring( char* s );
  void uart_put8int( uint8_t i );
  uint8_t buffer_cmp( const char* cmp, uint8_t len );
  uint8_t buffer_ncmp( const char* cmp, uint8_t len, uint8_t* val );
  uint8_t hcheck( const char val );
  uint8_t buffer_hcmp( const char* cmp, uint8_t len, uint8_t* val_a, uint8_t* val_b );
  void uart_poll( uint8_t* controlmode );
  void uart_reset( void );

 #endif
