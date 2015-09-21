// #############################################################################
// #                --- Borsti: Remote controlled vibrobot ---                 #
// #############################################################################
// # ir.c - IR functions                                                       #
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
 #include "libnecdecoder.h"
 #include "io.h"
 #include "eeprom.h"
 #include "ir.h"
 
 uint8_t ir_addr_l;
 uint8_t ir_addr_h;
 uint8_t ir_toggle_front;
 uint8_t ir_beep;
 uint8_t ir_blink_l;
 uint8_t ir_blink_r;
 uint8_t ir_blink_n;
 uint8_t ir_blink_w;
 uint8_t ir_blink_a;
 uint8_t ir_flash_f;
 uint8_t ir_flash_o;
 uint8_t ir_motor_r;
 uint8_t ir_motor_s;
 uint8_t ir_motor_l;
 uint8_t mo_bal_l;
 uint8_t mo_bal_r;


 // ***** Restore IR data *****
 void ir_restore( void )
  {
   ir_addr_l = ee_getval(EE_IR_ADDR_L);
   ir_addr_h = ee_getval(EE_IR_ADDR_H);
   ir_toggle_front = ee_getval(EE_IR_TOGGLE_FRONT);
   ir_beep = ee_getval(EE_IR_BEEP);
   ir_blink_l = ee_getval(EE_IR_BLINK_L);
   ir_blink_r = ee_getval(EE_IR_BLINK_R);
   ir_blink_n = ee_getval(EE_IR_BLINK_N);
   ir_blink_w = ee_getval(EE_IR_BLINK_W);
   ir_blink_a = ee_getval(EE_IR_BLINK_A);
   ir_flash_f = ee_getval(EE_IR_FLASH_F);
   ir_flash_o = ee_getval(EE_IR_FLASH_O);
   ir_motor_r = ee_getval(EE_IR_MOTOR_R);
   ir_motor_s = ee_getval(EE_IR_MOTOR_S);
   ir_motor_l = ee_getval(EE_IR_MOTOR_L);
   mo_bal_l = ee_getval(EE_MO_BAL_L);
   mo_bal_r = ee_getval(EE_MO_BAL_R);
  }


 // ***** Poll IR code *****
 void ir_poll( const uint8_t controlmode )
  {
   // Switch between bluetooth and IR control
   switch(controlmode)
    {
     case 0:
      // ** Infrared **
      // Check IR command
      if(ir.status & (1<<IR_RECEIVED))
       {
        if(ir.address_l==ir_addr_l&&ir.address_h==ir_addr_h)
         {
          // Reset active values
          io_reset_vals();
          if(ir.command==ir_toggle_front) // Toggle front light
           {
            io_toggle_led_front();
           }
          if(ir.command==ir_beep) // Activate beep
           {
            io_set_beep(1);
           }
          if(ir.command==ir_blink_l) // Blink left
           {
            if(io_get_blink()==1) io_set_blink(0); else io_set_blink(1);
           }
          if(ir.command==ir_blink_r) // Blink right
           {
            if(io_get_blink()==2) io_set_blink(0); else io_set_blink(2);
           }
          if(ir.command==ir_blink_n) // Both lit
           {
            if(io_get_blink()==4) io_set_blink(0); else io_set_blink(4);
           }
          if(ir.command==ir_blink_w) // Both blink
           {
            if(io_get_blink()==3) io_set_blink(0); else io_set_blink(3);
           }
          if(ir.command==ir_blink_a) // Auto blink
           {
            if(io_get_blink()==5) io_set_blink(0); else io_set_blink(5);
           }
          if(ir.command==ir_flash_f) // Flashlight flashing
           {
            if(io_get_flash()==1) io_set_flash(0); else io_set_flash(1);
           }
          if(ir.command==ir_flash_o) // Flashlight on
           {
            if(io_get_flash()==2) io_set_flash(0); else io_set_flash(2);
           }
          if(ir.command==ir_motor_l) // Move left (right motor)
           {
            io_set_speed_a(mo_bal_r);
           }
          if(ir.command==ir_motor_s) // Move straight
           {
            io_set_speed_a(mo_bal_r);
            io_set_speed_b(mo_bal_l);
           }
          if(ir.command==ir_motor_r) // Motor right (left motor)
           {
            io_set_speed_b(mo_bal_l);
           }
         }
        // Reset state
        ir.status &= ~(1<<IR_RECEIVED);
       }
      // If signal invalid
      if(!(ir.status & (1<<IR_SIGVALID)))
       {
        io_reset_vals();
       }
      break;
     case 1:
      // ** Bluetooth ** 
      // Ignore IR
      if(ir.status & (1<<IR_RECEIVED))
       {
        // Reset state
        ir.status &= ~(1<<IR_RECEIVED);
       }
      break;
     case 2:
      // ** Setup **
      break;
    } 
  }
