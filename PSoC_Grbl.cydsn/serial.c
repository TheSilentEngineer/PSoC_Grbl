/*
  serial.c - Low level functions for sending and recieving bytes via the serial port
  Part of Grbl

  Copyright (c) 2011-2015 Sungeun K. Jeon
  Copyright (c) 2009-2011 Simen Svale Skogsrud
   Updated For PSOC BJD 2017

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <project.h>
//#include "serial.h"
#include "grbl.h"

#define RX_RING_BUFFER (RX_BUFFER_SIZE+1)
#define TX_RING_BUFFER (TX_BUFFER_SIZE+1)
#define USBFS_DEVICE    (0u) //used for UsbUart only

uint8_t serial_rx_buffer[RX_BUFFER_SIZE];
uint8_t serial_rx_buffer_head = 0;
volatile uint8_t serial_rx_buffer_tail = 0;

// no grbl +TX buffer required for PSoc verison



// Returns the number of bytes available in the RX serial buffer.
uint8_t serial_get_rx_buffer_available()
{
  uint8_t rtail = serial_rx_buffer_tail; // Copy to limit multiple calls to volatile
  if (serial_rx_buffer_head >= rtail) { return(RX_BUFFER_SIZE - (serial_rx_buffer_head-rtail)); }
  return((rtail-serial_rx_buffer_head-1));
}



// Returns the number of bytes used in the RX serial buffer.
uint8_t serial_get_rx_buffer_count()
{
  uint8_t rtail = serial_rx_buffer_tail; // Copy to limit multiple calls to volatile
  if (serial_rx_buffer_head >= rtail) { return(serial_rx_buffer_head-rtail); }
  return (RX_BUFFER_SIZE - (rtail-serial_rx_buffer_head));
}




// uint8_t serial_get_tx_buffer_count() // not req for PSoc





void serial_init()
{
    static bool started = false;
    
    // Start the component
    USBUART_Start(USBFS_DEVICE, USBUART_5V_OPERATION);
    //CyGlobalIntEnable;
    
   while (!started) {     
      /* Host can send double SET_INTERFACE request. */
        if (0u != USBUART_IsConfigurationChanged())
        { 
            if (0u != USBUART_GetConfiguration()) // Initialize IN endpoints when device is configured. 
            {
                // Enumeration is done, enable OUT endpoint to receive data from host. //
                USBUART_CDC_Init();
                started = true;   
            }
        }
        //LED_PWM_Start();  
    }   
}




// Writes one byte to the TX serial buffer. Called by main program.
void serial_write(uint8_t data) {
  // totally rewritten for PSoc
  USBUART_PutChar(data);
}





// Fetches the first byte in the serial read buffer. Called by main program.
uint8_t serial_read()
{
  uint8_t tail = serial_rx_buffer_tail; // Temporary serial_rx_buffer_tail (to optimize for volatile)
  if (serial_rx_buffer_head == tail) {
    return SERIAL_NO_DATA;
  } else {
    uint8_t data = serial_rx_buffer[tail];

    tail++;
    if (tail == RX_RING_BUFFER) 
    { tail = 0; }
    serial_rx_buffer_tail = tail;

    return data;
  }
}





//was ISR(SERIAL_RX)
void USBUART_RX_ISR()
{
  uint16 count;
  uint8_t data;
  uint8 buffer[64u];
  uint8_t next_head;  
  uint8 index =0;

  LED_PWM_Start();
  // Pick off realtime command characters directly from the serial stream. These characters are
  // not passed into the buffer, but these set system state flag bits for realtime execution.
  
  /* Read received data and re-enable OUT endpoint. */
  count = USBUART_GetAll(buffer);

    data = buffer[0];
    switch (data) {
        case CMD_STATUS_REPORT: system_set_exec_state_flag(EXEC_STATUS_REPORT); break; // Set as true
        case CMD_CYCLE_START:   system_set_exec_state_flag(EXEC_CYCLE_START); break; // Set as true
        case CMD_FEED_HOLD:     system_set_exec_state_flag(EXEC_FEED_HOLD); break; // Set as true
        case CMD_SAFETY_DOOR:   system_set_exec_state_flag(EXEC_SAFETY_DOOR); break; // Set as true
        case CMD_RESET:         mc_reset(); break; // Call motion control reset routine.
        default: // Write character to buffer    
            
            for (index = 0; index != (count-1); index++){
                data = buffer[index];    
                next_head = serial_rx_buffer_head + 1;
                if (next_head == RX_BUFFER_SIZE) 
                    { next_head = 0; } 
                if (next_head != serial_rx_buffer_tail) { // Write data to buffer unless it is full.
                    serial_rx_buffer[serial_rx_buffer_head] = data;
                    serial_rx_buffer_head = next_head;
                }
            }
      //TODO: else alarm on overflow?
    }
}




void serial_reset_read_buffer()
{
  serial_rx_buffer_tail = serial_rx_buffer_head;
}

