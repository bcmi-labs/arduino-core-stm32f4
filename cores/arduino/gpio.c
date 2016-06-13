/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
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

 #ifdef STM32F2

/**
 * @file gpio.c
 * @brief GPIO initialization routine
 */

 /*
 * Arduino srl - www.arduino.org
 * 2016 Jun 9: Edited Francesco Alessi (alfran) - francesco@arduino.org
 */


#include "gpio.h"
#include "rcc.h"

/*
 * GPIO devices
 */

/** GPIO port A device. */
gpio_dev gpioa = {
    .regs      = GPIOA_BASE,
    .clk_id    = RCC_GPIOA,
    .exti_port = AFIO_EXTI_PA,
};
gpio_dev* const GPIOA = &gpioa;

/** GPIO port B device. */
gpio_dev gpiob = {
    .regs      = GPIOB_BASE,
    .clk_id    = RCC_GPIOB,
    .exti_port = AFIO_EXTI_PB,
};
gpio_dev* const GPIOB = &gpiob;

/** GPIO port C device. */
gpio_dev gpioc = {
    .regs      = GPIOC_BASE,
    .clk_id    = RCC_GPIOC,
    .exti_port = AFIO_EXTI_PC,
};
gpio_dev* const GPIOC = &gpioc;

/** GPIO port D device. */
gpio_dev gpiod = {
    .regs      = GPIOD_BASE,
    .clk_id    = RCC_GPIOD,
    .exti_port = AFIO_EXTI_PD,
};
gpio_dev* const GPIOD = &gpiod;

#ifdef STM32_HIGH_DENSITY

/** GPIO port E device. */
gpio_dev gpioe = {
    .regs      = GPIOE_BASE,
    .clk_id    = RCC_GPIOE,
    .exti_port = AFIO_EXTI_PE,
};
gpio_dev* const GPIOE = &gpioe;

/** GPIO port F device. */
gpio_dev gpiof = {
    .regs      = GPIOF_BASE,
    .clk_id    = RCC_GPIOF,
    .exti_port = AFIO_EXTI_PF,
};
gpio_dev* const GPIOF = &gpiof;

/** GPIO port G device. */
gpio_dev gpiog = {
    .regs      = GPIOG_BASE,
    .clk_id    = RCC_GPIOG,
    .exti_port = AFIO_EXTI_PG,
};
gpio_dev* const GPIOG = &gpiog;

/** GPIO port H device. */
gpio_dev gpioh = {
    .regs      = GPIOH_BASE,
    .clk_id    = RCC_GPIOH,
    .exti_port = AFIO_EXTI_PH,
};
gpio_dev* const GPIOH = &gpioh;

/** GPIO port I device. */
gpio_dev gpioi = {
    .regs      = GPIOI_BASE,
    .clk_id    = RCC_GPIOI,
    .exti_port = AFIO_EXTI_PI,
};
gpio_dev* const GPIOI = &gpioi;

/** GPIO port J device. */
gpio_dev gpioj = {
    .regs      = GPIOJ_BASE,
    .clk_id    = RCC_GPIOJ,
    .exti_port = AFIO_EXTI_PJ,
};
gpio_dev* const GPIOJ = &gpioj;

/** GPIO port K device. */
gpio_dev gpiok = {
    .regs      = GPIOK_BASE,
    .clk_id    = RCC_GPIOK,
    .exti_port = AFIO_EXTI_PK,
};
gpio_dev* const GPIOK = &gpiok;

#endif

/*
 * GPIO convenience routines
 */

/**
 * Initialize a GPIO device.
 *
 * Enables the clock for and resets the given device.
 *
 * @param dev GPIO device to initialize.
 */
void gpio_init(gpio_dev *dev) {
    rcc_clk_enable(dev->clk_id);
    rcc_reset_dev(dev->clk_id);
}

/**
 * Initialize and reset all available GPIO devices.
 */
void gpio_init_all(void) {
    gpio_init(GPIOA);
    gpio_init(GPIOB);
    gpio_init(GPIOC);
    gpio_init(GPIOD);
    gpio_init(GPIOE);
    gpio_init(GPIOF);
    gpio_init(GPIOG);
    gpio_init(GPIOH);
    gpio_init(GPIOI);
    gpio_init(GPIOJ);
    gpio_init(GPIOK);
}

/**
 * Set the mode of a GPIO pin.
 *
 * @param dev GPIO device.
 * @param pin Pin on the device whose mode to set, 0--15.
 * @param mode General purpose or alternate function mode to set the pin to.
 * @see gpio_pin_mode
 */
void gpio_set_mode(gpio_dev *dev, uint8 pin, gpio_pin_mode mode) {
    gpio_reg_map *regs = dev->regs;

    regs->MODER      = (regs->MODER      & ~( 3 << (2*pin)))     | (((mode >> 0) & 3)  << (2*pin));
    regs->PUPDR      = (regs->PUPDR      & ~( 3 << (2*pin)))     | (((mode >> 2) & 3)  << (2*pin));
    regs->OSPEEDR    = (regs->OSPEEDR    & ~( 3 << (2*pin)))     | (((mode >> 4) & 3)  << (2*pin));
    regs->OTYPER     = (regs->OTYPER     & ~( 1 << (1*pin)))     | (((mode >> 6) & 1)  << (1*pin));
}

/**
 * Set the alternate function mode of a GPIO pin.
 *
 * @param dev GPIO device.
 * @param pin Pin on the device whose mode to set, 0--15.
 * @param mode alternate function mode to set the pin to.
 * @see gpio_pin_mode
 */
void gpio_set_af_mode(gpio_dev *dev, uint8 pin, int mode) {
    gpio_reg_map *regs = dev->regs;

	regs->AFR[pin/8] = (regs->AFR[pin/8] & ~(15 << (4*(pin&7)))) | (((mode >> 0) & 15) << (4*(pin&7)));
}

/*
 * AFIO
 */

/**
 * @brief Initialize the AFIO clock, and reset the AFIO registers.
 */
void afio_init(void) {
     // do nothing
}

#define AFIO_EXTI_SEL_MASK 0xF

/**
 * @brief Select a source input for an external interrupt.
 *
 * @param exti      External interrupt.
 * @param gpio_port Port which contains pin to use as source input.
 * @see afio_exti_num
 * @see afio_exti_port
 */
void afio_exti_select(afio_exti_num exti, afio_exti_port gpio_port) {
    __io uint32 *exti_cr = &SYSCFG_BASE->EXTICR1 + exti / 4;
    uint32 shift = 4 * (exti % 4);
    uint32 cr = *exti_cr;

    cr &= ~(AFIO_EXTI_SEL_MASK << shift);
    cr |= gpio_port << shift;
    *exti_cr = cr;
}

/**
 * @brief Perform an alternate function remap.
 * @param remapping Remapping to perform.
 */
#if 0
void afio_remap(afio_remap_peripheral remapping) {
    if (remapping & AFIO_REMAP_USE_MAPR2) {
        remapping &= ~AFIO_REMAP_USE_MAPR2;
        AFIO_BASE->MAPR2 |= remapping;
    } else {
        AFIO_BASE->MAPR |= remapping;
    }
}
#endif

#endif
