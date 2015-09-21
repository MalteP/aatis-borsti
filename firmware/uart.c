// #############################################################################
// #                --- Borsti: Remote controlled vibrobot ---                 #
// #############################################################################
// # uart.c - Header for UART functions                                        #
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
 #include "eeprom.h"
 #include "libnecdecoder.h"
 #include "ir.h"
 #include "uart.h"


 // ***** UART init *****
 void uart_init( void )
  {
   // Setup serial communication
   UBRRH  = (uint8_t) (UBRR_VAL>>8);
   UBRRL  = (uint8_t)  UBRR_VAL;
   UCSRB |= (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
   UCSRC  = (1<<UCSZ1)|(1<<UCSZ0);

   // Flush receive-buffer
   do { UDR; } while ( UCSRA & (1 << RXC) ); 
   
   uart_ptr = 0;
   uart_state = 0;
   
   // Global interrupt enable
   sei();
  }


 // ***** Send single character via UART *****
 void uart_putchar( char x )
  {
   while (!(UCSRA & (1<<UDRE)))
    {
    }
   UDR = x;
  }


 // ***** Send string via UART *****
 void uart_putstring( char* s )
  {
   while (*s) // while not \0
    {
     uart_putchar(*s);
     s++;
    }
  }


 // ***** Send 8bit as hex int via UART *****
 void uart_puthex( uint8_t i )
  {
   uint8_t tmp;
   tmp = ((i>>4)&0x0F);
   if(tmp>=10) tmp+=7;
   uart_putchar('0'+tmp);
   tmp = (i&0x0F);
   if(tmp>=10) tmp+=7;
   uart_putchar('0'+tmp);
  }


 // ***** Send 8bit int via UART *****
 void uart_putdec( uint8_t i )
  {
   uart_putchar('0'+i);
   uart_putchar('\n');
  }


 // ***** Compare string in buffer *****
 uint8_t buffer_cmp( const char* cmp, uint8_t len )
  {
   uint8_t tmp = 0;
   if(uart_ptr!=len) return 0;
   while(tmp<len)
    {
     if(cmp[tmp]!=uart_buffer[tmp]) return 0;
     tmp++;
    }
   return 1;
  }


 // ***** Compare string and number *****
 uint8_t buffer_ncmp( const char* cmp, uint8_t len, uint8_t* val )
  {
   uint8_t tmp = 0;
   if(uart_ptr!=len+1) return 0;
   while(tmp<len)
    {
     if(cmp[tmp]!=uart_buffer[tmp]) return 0;
     tmp++;
    }
   if(!hcheck(uart_buffer[len])) return 0;
   tmp = uart_buffer[len]-'0';
   if(tmp>9) tmp-=7;
   *val = tmp;
   return 1;
  }


 // ***** Check for valid hex char *****
 uint8_t hcheck( const char val )
  {
   if(val<'0') return 0;
   if(val>'F') return 0;
   if(val>'9'&&val<'A') return 0;
   return 1;
  }


 // ***** Compare string and parse two hex values *****
 uint8_t buffer_hcmp( const char* cmp, uint8_t len, uint8_t* val_a, uint8_t* val_b )
  {
   uint8_t tmp = 0;
   uint8_t ret = 0;
   if(uart_ptr!=len+4) return 0;
   while(tmp<len)
    {
     if(cmp[tmp]!=uart_buffer[tmp]) return 0;
     tmp++;
    }
   if(!hcheck(uart_buffer[len])) return 0;
   if(!hcheck(uart_buffer[len+1])) return 0;
   if(!hcheck(uart_buffer[len+2])) return 0;
   if(!hcheck(uart_buffer[len+3])) return 0;
   tmp = uart_buffer[len]-'0';
   if(tmp>9) tmp-=7;
   ret = tmp<<4;
   tmp = uart_buffer[len+1]-'0';
   if(tmp>9) tmp-=7;
   ret += tmp;
   *val_a = ret;
   tmp = uart_buffer[len+2]-'0';
   if(tmp>9) tmp-=7;
   ret = tmp<<4;
   tmp = uart_buffer[len+3]-'0';
   if(tmp>9) tmp-=7;
   ret += tmp;
   *val_b = ret;
   return 1;
  }


 // ***** Poll UART buffer for valid command *****
 void uart_poll( uint8_t* controlmode )
  {
   uint8_t tmpval;
   uint8_t tmpval2;
   uint8_t ret = 0;
   if(uart_state!=0)
    {
     // ** Extended commands **
     switch(*controlmode)
      {
       case 1:
        // ** BT mode **
        if(buffer_hcmp("SP", 2, &tmpval, &tmpval2))
         {
          io_set_speed_a(tmpval);
          io_set_speed_b(tmpval2);
          ret=1;
         } else 
        if(buffer_ncmp("BE", 2, &tmpval))
         {
          if(tmpval<=1)
           {
            io_set_beep(tmpval);
            ret=1;
           }
         } else
        if(buffer_ncmp("FR\0", 2, &tmpval))
         {
          if(tmpval==0)
           {
            io_reset_led_front();
            ret=1;
           } else {
            if(tmpval==1)
             {
              io_set_led_front();
              ret=1;
             }
           }
         } else
        if(buffer_ncmp("RE\0", 2, &tmpval))
         {
          if(tmpval<=5)
           {
            io_set_blink(tmpval);
            ret=1;
           }
         } else
        if(buffer_ncmp("FL\0", 2, &tmpval))
         {
          if(tmpval<=2)
           {
            io_set_flash(tmpval);
            ret=1;
           }
         } else
        if(buffer_ncmp("TO\0", 2, &tmpval))
         {
          if(tmpval<=1)
           {
            io_set_motor_timeout(tmpval);
            ret=1;
           }
         }
        break;
       case 2:
        // ** Setup mode **
        if(buffer_ncmp("EE?0", 4, &tmpval)) // Get EEP value 0...15
         {
          uart_puthex(ee_getval(tmpval));
          uart_putchar('\n');
          ret=2;
         } else
        if(buffer_ncmp("EE?1", 4, &tmpval)) // Get EEP value 16...21
         {
          if(tmpval<=EE_NUM_VALUES-17)
           {
            tmpval+=16;
            uart_puthex(ee_getval(tmpval));
            uart_putchar('\n');
            ret=2;
           }
         } else
        if(buffer_hcmp("EE", 2, &tmpval, &tmpval2))
         {
          if(tmpval<=EE_NUM_VALUES-1)
           {
            ee_setval(tmpval, tmpval2);
            ir_restore(); // Refresh values in memory
            ret=1;
           }
         } else
        if(buffer_cmp("IR?", 3)) // Get IR code
         {
          if(ir.status & (1<<IR_RECEIVED))
           {
            uart_puthex(ir.address_l);
            uart_puthex(ir.address_h);
            uart_puthex(ir.command);
            uart_putchar('\n');
            // Reset state
            ir.status &= ~(1<<IR_RECEIVED);
            ret=2;
           }
         }
        break;  
      }
     if(ret==0)
      {
       // ** Basic commands (For all modes) **
       if(buffer_cmp("HI", 2)) // Ping
        {
         ret=1;
        } else
       if(buffer_ncmp("MO", 2, &tmpval)) // Set mode
        {
         if(tmpval<=2)
          {
           if(tmpval!=0) io_set_motor_timeout(1);
            else io_set_motor_timeout(0);
           // Reset some values
           io_set_beep(0);
           io_set_speed_a(0);
           io_set_speed_b(0);
           ir.status &= ~(1<<IR_RECEIVED);
           // Now set mode
           *controlmode=tmpval;
           ret=1;
          }
        } else
       if(buffer_cmp("VE?", 3)) // Get version
        {
         uart_putstring("Borsti v1.1\n\0");
         ret=2;
        } else
       if(buffer_cmp("MO?", 3)) // Get mode
        {
         uart_putdec(*controlmode);
         ret=2;
        } else
       if(buffer_cmp("SP?", 3)) // Get speeds
        {
         uart_puthex(io_get_speed_a());
         uart_puthex(io_get_speed_b());
         uart_putchar('\n');
         ret=2;
        } else
       if(buffer_cmp("BE?", 3)) // Get beep
        {
         uart_putdec(io_get_beep());
         ret=2;
        } else
       if(buffer_cmp("FR?", 3)) // Get front LED status
        {
         uart_putdec(io_get_led_front());
         ret=2;
        } else 
       if(buffer_cmp("RE?", 3)) // Get Rear LED status
        {
         uart_putdec(io_get_blink());
         ret=2;
        } else 
       if(buffer_cmp("FL?", 3)) // Get Rear LED status
        {
         uart_putdec(io_get_flash());
         ret=2;
        } else
       if(buffer_cmp("TO?", 3)) // Get motor timeout status
        {
         uart_putdec(io_get_motor_timeout());
         ret=2;
        }
      }
     // Print return value
     if(ret==0) uart_putstring("-\n\0");
      else if(ret==1) uart_putstring("+\n\0");
     uart_reset();
    }
  }


 void uart_reset(void)
  {
   // Reset pointers
   uart_buffer[0]='\0';
   uart_ptr = 0;
   uart_state = 0;  
  }


 // ***** RX interrupt *****
 ISR(USART_RX_vect)
  {
   char temp=UDR;
   if(temp!='\0'&&uart_state==0)
    {
     if(uart_ptr>(UART_BUFFERSIZE-1)) uart_ptr=(UART_BUFFERSIZE-1);
     uart_buffer[uart_ptr++] = temp;
     if(temp=='\n')
      {
       --uart_ptr;
       uart_state = 1;
      }
    }
  }
