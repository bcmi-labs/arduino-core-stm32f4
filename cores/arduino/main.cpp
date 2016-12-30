/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 LeafLabs LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

 /*
 * Arduino srl - www.arduino.org
 * 2016 Jun 9: Edited Francesco Alessi (alfran) - francesco@arduino.org
 */

#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_cdc_if.h"
#include "io.h"

extern void setup(void);
extern void loop(void);
extern void init(void);


extern USBD_HandleTypeDef hUsbDeviceFS;


// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need libmaple may fail.
 __attribute__(( constructor )) void premain() {
    init();
}

int main(void) {

	/* Initialize USB device stack */
	uint8_t ttBuf[1]={9};
	MX_USB_DEVICE_Init();

	/* Enable FPU
	 * Note: this should have already been done in SystemInit() in HAL/src/system_stm32f4xx.c */
	SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
	analogReadResolution(10);
  
  // Set MIC Connected to CODEC
  pinMode(MIC_SEL, OUTPUT);
  digitalWrite(MIC_SEL, CODEC);

	setup();

	while (1) {
		loop();
	}
	return 0;
}
