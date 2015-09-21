// #############################################################################
// #                --- Borsti: Remote controlled vibrobot ---                 #
// #############################################################################
// # eeprom.c - EEPROM definitions                                             #
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
 #include <avr/eeprom.h>
 #include "eeprom.h"

 uint8_t EEMEM ee_values[EE_NUM_VALUES+1] = { EE_DUMMY, EE_IR_ADDR_L_VAL, EE_IR_ADDR_H_VAL, EE_IR_TOGGLE_FRONT_VAL, EE_IR_BEEP_VAL, EE_IR_BLINK_L_VAL, EE_IR_BLINK_R_VAL, EE_IR_BLINK_N_VAL, EE_IR_BLINK_W_VAL, EE_IR_BLINK_A_VAL, EE_IR_FLASH_F_VAL, EE_IR_FLASH_O_VAL, EE_IR_MOTOR_L_VAL, EE_IR_MOTOR_S_VAL, EE_IR_MOTOR_R_VAL, EE_MO_BAL_R_VAL, EE_MO_BAL_L_VAL, EE_BT_NAME_0_VAL, EE_BT_NAME_1_VAL, EE_BT_NAME_2_VAL, EE_BT_NAME_3_VAL, EE_BT_NAME_4_VAL, EE_BT_NAME_5_VAL };


 // ***** Load value from EEPROM *****
 uint8_t ee_getval( uint8_t pos )
  {
   if(pos>=EE_NUM_VALUES) return 0;
   ++pos; // Don't read out dummy
   return eeprom_read_byte(&ee_values[pos]);
  }


 // ***** Write value to EEPROM *****
 void ee_setval( uint8_t pos, uint8_t val )
  {
   if(pos>=EE_NUM_VALUES) return;
   ++pos; // Don't write to dummy
   eeprom_write_byte(&ee_values[pos], val);
  }
