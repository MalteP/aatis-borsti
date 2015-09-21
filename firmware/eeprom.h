// #############################################################################
// #                --- Borsti: Remote controlled vibrobot ---                 #
// #############################################################################
// # eeprom.h - EEPROM definitions                                             #
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

 #ifndef EEPROM_H
  #define EEPROM_H

  #include <avr/io.h>

  #define EE_NUM_VALUES                 22   // No. of values without dummy
  #define EE_DUMMY                      0xFF
  #define EE_IR_ADDR_L                  0
  #define EE_IR_ADDR_L_VAL              0x02
  #define EE_IR_ADDR_H                  1
  #define EE_IR_ADDR_H_VAL              0xBD
  #define EE_IR_TOGGLE_FRONT            2
  #define EE_IR_TOGGLE_FRONT_VAL        0x00
  #define EE_IR_BEEP                    3
  #define EE_IR_BEEP_VAL                0x15
  #define EE_IR_BLINK_L                 4
  #define EE_IR_BLINK_L_VAL             0x06
  #define EE_IR_BLINK_R                 5
  #define EE_IR_BLINK_R_VAL             0x08
  #define EE_IR_BLINK_N                 6
  #define EE_IR_BLINK_N_VAL             0x07
  #define EE_IR_BLINK_W                 7
  #define EE_IR_BLINK_W_VAL             0x1C
  #define EE_IR_BLINK_A                 8
  #define EE_IR_BLINK_A_VAL             0x09
  #define EE_IR_FLASH_F                 9
  #define EE_IR_FLASH_F_VAL             0x01
  #define EE_IR_FLASH_O                 10
  #define EE_IR_FLASH_O_VAL             0x02
  #define EE_IR_MOTOR_L                 11
  #define EE_IR_MOTOR_L_VAL             0x11
  #define EE_IR_MOTOR_S                 12
  #define EE_IR_MOTOR_S_VAL             0x12
  #define EE_IR_MOTOR_R                 13
  #define EE_IR_MOTOR_R_VAL             0x10
  #define EE_MO_BAL_R                   14
  #define EE_MO_BAL_R_VAL               0xFF
  #define EE_MO_BAL_L                   15
  #define EE_MO_BAL_L_VAL               0xFF
  #define EE_BT_NAME_0                  16
  #define EE_BT_NAME_0_VAL              0x00
  #define EE_BT_NAME_1                  17
  #define EE_BT_NAME_1_VAL              0x00
  #define EE_BT_NAME_2                  18
  #define EE_BT_NAME_2_VAL              0x00
  #define EE_BT_NAME_3                  19
  #define EE_BT_NAME_3_VAL              0x00
  #define EE_BT_NAME_4                  20
  #define EE_BT_NAME_4_VAL              0x00
  #define EE_BT_NAME_5                  21
  #define EE_BT_NAME_5_VAL              0x00

  uint8_t ee_getval( uint8_t pos );
  void ee_setval( uint8_t pos, uint8_t val );

 #endif
