// #############################################################################
// #                --- Borsti: Remote controlled vibrobot ---                 #
// #############################################################################
// # io.h - IO functions                                                       #
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
 #include <avr/interrupt.h>
 #include "io.h"

 uint8_t io_pre_a;
 uint8_t io_pre_b;
 uint8_t io_pre_c;
 uint8_t io_pre_d;
 uint8_t io_flag;
 uint8_t io_beep;
 uint8_t io_blink;
 uint8_t io_blink_auto;
 uint8_t io_flash;
 uint8_t io_mot_timeout;
 uint8_t io_mot_counter;


 // ***** Setup ports and timers *****
 void io_init( void )
  {
   // Initialize LED ports
   DDRB |= (1<<PB0) | (1<<PB1) | (1<<PB2);
   DDRD |= (1<<PD5);
   // Initialize motor PWM
   DDRB |= (1<<PB3) | (1<<PB4);
   TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);
   TCCR1B = (1<<CS10);
   OCR0A = 0;
   // Initialize buzzer port
   DDRD |= (1<<PD6);
   // Initialize blink timer
   TIMSK |= (1<<TOV1);
   io_pre_a = 0;
   io_pre_b = 0;
   io_pre_c = 0;
   io_pre_d = 16;
   io_beep = 0;
   io_blink = 0;
   io_blink_auto = 0;
   io_flash = 0;
   io_mot_timeout = 0;
   io_mot_counter = 0;
  }


 // ***** Poll IO timers *****
 void io_poll( void )
  {
   if(io_flag!=0)
    {
     if(++io_pre_b==0)
      {
       if(io_pre_d==16) io_pre_d=8; else io_pre_d=16;
       if(io_mot_counter>0)
        {
         if(io_mot_counter==1)
          {
           OCR1A = 0;
           OCR1B = 0;
           io_beep = 0;
          }
         --io_mot_counter;
        }
      }
     if(io_blink==0)
      {
       PORTB &= ~((1<<PB0) | (1<<PB1));
      } else {
       if(io_blink&0x04)
        {
         PORTB |= (1<<PB0) | (1<<PB1);
        } else {
         if(io_pre_b==0)
          {
           if(io_blink&0x02) PORTB ^= (1<<PB0); else PORTB &= ~(1<<PB0);
           if(io_blink&0x01) PORTB ^= (1<<PB1); else PORTB &= ~(1<<PB1);
          }
        }
      }
     if(io_flash==0)
      {
       PORTD &= ~(1<<PD5);
      } else {
       if(io_flash==1)
        {
         if(io_pre_b<=25) PORTD |= (1<<PD5); else PORTD &= ~(1<<PD5);
        } else {
         PORTD |= (1<<PD5);
        }
      }
     io_flag = 0;
    }
  }


 // ***** Toggle front LED *****
 void io_toggle_led_front( void )
  {
   PORTB ^= (1<<PB2);
  }


 // ***** Set front LED *****
 void io_set_led_front( void )
  {
   PORTB |= (1<<PB2);
  }


 // ***** Reset front LED *****
 void io_reset_led_front( void )
  {
   PORTB &= ~(1<<PB2);
  }


 // ***** Get front LED *****
 uint8_t io_get_led_front( void )
  {
   return ((PORTB&(1<<PB2))==0?0:1);
  }


 // ***** Set buzzer value *****
 void io_set_beep( uint8_t val )
  {
   if(io_beep!=val)
    {
     if(val!=0)
      {
       io_pre_b = 0xFF;
       io_pre_d = 8;
      }
     io_beep = val;
    }
   if(io_mot_timeout!=0) io_mot_counter = IO_MOTOR_TIMEOUT;
  }


 // ***** Get buzzer value *****
 uint8_t io_get_beep( void )
  {
   return io_beep;
  }


 // ***** Set blinker value *****
 void io_set_blink( uint8_t val )
  {
   if(val>=5)
    {
     io_blink_auto = 1;
     io_blink_auto_calc();
    } else {
     io_blink_auto = 0;
     if(io_blink==0)
      {
       io_pre_b = 0xFF;
      }
     PORTB &= ~((1<<PB0) | (1<<PB1));
     io_blink = val;
    }
  }


 // ***** Get blinker value *****
 uint8_t io_get_blink( void )
  {
   if(io_blink_auto==1) return 5; else return io_blink;
  }


 // ***** Set top LED flash value *****
 void io_set_flash( uint8_t val )
  {
   io_flash = val;
  }


 // ***** Get top LED flash value *****
 uint8_t io_get_flash( void )
  {
   return io_flash;
  }


 // ***** Set speed for motor A *****
 void io_set_speed_a( uint8_t pwm )
  {
   OCR1A = pwm;
   if(io_mot_timeout!=0) io_mot_counter = IO_MOTOR_TIMEOUT;
   io_blink_auto_calc();
  }


 // ***** Get speed for motor A *****
 uint8_t io_get_speed_a( void )
  {
   return OCR1A;
  }


 // ***** Set speed for motor B *****
 void io_set_speed_b( uint8_t pwm )
  {
   OCR1B = pwm;
   if(io_mot_timeout!=0) io_mot_counter = IO_MOTOR_TIMEOUT;
   io_blink_auto_calc();
  }


 // ***** Get speed for motor B *****
 uint8_t io_get_speed_b( void )
  {
   return OCR1B;
  }


 // ***** Set motor timeout *****
 void io_set_motor_timeout( uint8_t val )
  {
   io_mot_timeout = val;
   if(io_mot_timeout!=0) io_mot_counter = IO_MOTOR_TIMEOUT;
  }


 // ***** Get motor timeout *****
 uint8_t io_get_motor_timeout( void )
  {
   return io_mot_timeout;
  }


 // ***** Reset values ****
 void io_reset_vals( void )
  {
   io_set_beep(0);
   io_set_speed_a(0);
   io_set_speed_b(0);
  }

 
 // ***** Auto blink *****
 void io_blink_auto_calc( void )
  {
   uint8_t a, b;
   if(io_blink_auto!=1) return;
   a = OCR1A;
   b = OCR1B;
   if(a>=b)
    {
     a-=b;
     if(a>=64)
      {
       io_blink = 0x01;
      } else {
       io_blink = 0x04;
      }
    } else {
     b-=a;
     if(b>=64)
      {
       io_blink = 0x02;
      } else {
       io_blink = 0x04;
      }
    }
  }


 // ***** Timer interrupt *****
 ISR( TIMER1_OVF_vect )
  {
   if(++io_pre_a==16)
    {
     io_pre_a = 0; 
     io_flag = 1;
    }
   if(++io_pre_c>=io_pre_d)
    {
     io_pre_c = 0;
     if(io_beep!=0) PORTD ^= (1<<PD6); else PORTD &= ~(1<<PD6);
    }
  }
