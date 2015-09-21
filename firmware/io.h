// #############################################################################
// #                --- Borsti: Remote controlled vibrobot ---                 #
// #############################################################################
// # io.h - Header for IO functions                                            #
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

 #ifndef IO_H
  #define IO_H

  #include <avr/io.h>

  #define IO_MOTOR_TIMEOUT 10;

  void io_init( void );
  void io_poll( void );
  void io_toggle_led_front( void );
  void io_set_led_front( void );
  void io_reset_led_front( void );
  uint8_t io_get_led_front( void );
  void io_set_beep( uint8_t val );
  uint8_t io_get_beep( void );
  void io_set_blink( uint8_t val );
  uint8_t io_get_blink( void );
  void io_set_flash( uint8_t val );
  uint8_t io_get_flash( void );
  void io_set_speed_a( uint8_t pwm );
  void io_set_speed_b( uint8_t pwm );
  uint8_t io_get_speed_a( void );
  uint8_t io_get_speed_b( void );
  void io_set_motor_timeout( uint8_t val );
  void io_reset_vals( void );
  uint8_t io_get_motor_timeout( void );
  void io_blink_auto_calc( void );

 #endif
