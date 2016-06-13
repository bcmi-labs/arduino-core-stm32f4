/* Tone.cpp

  A Tone Generator Library

  Written by Brett Hagman

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

Version Modified By Date     Comments
------- ----------- -------- --------
0001    B Hagman    09/08/02 Initial coding
0002    B Hagman    09/08/18 Multiple pins
0003    B Hagman    09/08/18 Moved initialization from constructor to begin()
0004    B Hagman    09/09/26 Fixed problems with ATmega8
0005    B Hagman    09/11/23 Scanned prescalars for best fit on 8 bit timers
                    09/11/25 Changed pin toggle method to XOR
                    09/11/25 Fixed timer0 from being excluded
0006    D Mellis    09/12/29 Replaced objects with functions
0007    M Sproul    10/08/29 Changed #ifdefs from cpu to register
0008    S Kanemoto  12/06/22 Fixed for Leonardo by @maris_HY
0009    Arduino.org 15/06/30 Add M0/M0 Pro support
0010 		F Alessi    16/06/09 Add Star OTTO support
*************************************************/

#include "HardwareTimer.h"
#include "Arduino.h"
#include "Tone.h"

volatile static int toggle_count=0;
static int tone_pin;
int timer_CH = 2;

HardwareTimer timer(timer_CH);

void tone(uint8_t pin, unsigned int frequency, unsigned long duration)
{
	timer.pause();
  pinMode(pin,OUTPUT);
  tone_pin = pin;
  if (duration > 0 ) toggle_count = 2 * frequency * duration / 1000;
   else toggle_count = -1;
  timer.setPrescaleFactor(CYCLES_PER_MICROSECOND);  // microseconds
  timer.setOverflow(1000000/frequency/4);
	timer.setMode(TIMER_CH1, TIMER_OUTPUT_COMPARE);
  timer.setCompare(TIMER_CH1, 1);  // Interrupt 1 count after each update
	timer.attachInterrupt(TIMER_CH1, handler_tone);
  timer.refresh(); // start it up
  timer.resume();

	  return;
}


void noTone(uint8_t pin)
{
    timer.pause();
    gpio_write_bit(PIN_MAP[pin].gpio_device, PIN_MAP[pin].gpio_bit, 0);

return;
}

void set_timer(int ch)
{
  HardwareTimer timer(ch);
  timer_CH = ch;
}

void handler_tone(void)
{
  if (toggle_count != 0){
    gpio_toggle_bit(PIN_MAP[tone_pin].gpio_device, PIN_MAP[tone_pin].gpio_bit);
  if (toggle_count > 0)  toggle_count--;
  } else noTone(tone_pin);
}
