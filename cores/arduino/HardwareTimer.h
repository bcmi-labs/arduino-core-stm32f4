/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Bryan Newbold.
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

/**
 *  @brief Wirish timer class.
 */

 /*
 * Arduino srl - www.arduino.org
 * 2016 Jun 9: Edited Francesco Alessi (alfran) - francesco@arduino.org
 */

#ifndef _HARDWARETIMER_H_
#define _HARDWARETIMER_H_

// TODO [0.1.0] Remove deprecated pieces, pick a better API

#include "timer.h"

/** Timer mode. */
typedef timer_mode TimerMode;

/** @brief Deprecated; use TIMER_OUTPUT_COMPARE instead. */
#define TIMER_OUTPUTCOMPARE TIMER_OUTPUT_COMPARE

/**
 * @brief Interface to one of the 16-bit timer peripherals.
 */
class HardwareTimer {
private:
    timer_dev *dev;

public:
    /**
     * @brief Construct a new HardwareTimer instance.
     * @param timerNum number of the timer to control.
     */
    HardwareTimer(uint8 timerNum);

    /**
     * @brief Stop the counter, without affecting its configuration.
     *
     * @see HardwareTimer::resume()
     */
    void pause(void);

    /**
     * @brief Resume a paused timer, without affecting its configuration.
     *
     * The timer will resume counting and firing interrupts as
     * appropriate.
     *
     * Note that there is some function call overhead associated with
     * using this method, so using it in concert with
     * HardwareTimer::pause() is not a robust way to align multiple
     * timers to the same count value.
     *
     * @see HardwareTimer::pause()
     */
    void resume(void);

    /**
     * @brief Get the timer's clock speed.
     * @return Timer input clock speed in Hz/second
     */
	  uint32 getClockSpeed(void);

    /**
     * @brief Get the timer's prescale factor.
     * @return Timer prescaler, from 1 to 65,536.
     * @see HardwareTimer::setPrescaleFactor()
     */
    uint32 getPrescaleFactor();

    /**
     * @brief Set the timer's prescale factor.
     *
     * The new value won't take effect until the next time the counter
     * overflows.  You can force the counter to reset using
     * HardwareTimer::refresh().
     *
     * @param factor The new prescale value to set, from 1 to 65,536.
     * @see HardwareTimer::refresh()
     */
    void setPrescaleFactor(uint32 factor);

    /**
     * @brief Get the timer overflow value.
     * @see HardwareTimer::setOverflow()
     */
    uint16 getOverflow();

    /**
     * @brief Set the timer overflow (or "reload") value.
     *
     * The new value won't take effect until the next time the counter
     * overflows.  You can force the counter to reset using
     * HardwareTimer::refresh().
     *
     * @param val The new overflow value to set
     * @see HardwareTimer::refresh()
     */
    void setOverflow(uint16 val);

    /**
     * @brief Get the current timer count.
     *
     * @return The timer's current count value
     */
    uint16 getCount(void);

    /**
     * @brief Set the current timer count.
     *
     * @param val The new count value to set.  If this value exceeds
     *            the timer's overflow value, it is truncated to the
     *            overflow value.
     */
    void setCount(uint16 val);

    /**
     * @brief Set the timer's period in microseconds.
     *
     * Configures the prescaler and overflow values to generate a timer
     * reload with a period as close to the given number of
     * microseconds as possible.
     *
     * @param microseconds The desired period of the timer.  This must be
     *                     greater than zero.
     * @return The new overflow value.
     */
    uint16 setPeriod(uint32 microseconds);

    /**
     * @brief Configure a timer channel's mode.
     * @param channel Timer channel, from 1 to 4
     * @param mode Mode to set
     */
    void setMode(int channel, timer_mode mode);

    /**
     * @brief Get the compare value for the given channel.
     * @see HardwareTimer::setCompare()
     */
    uint16 getCompare(int channel);

    /**
     * @brief Set the compare value for the given channel.
     *
     * @param channel the channel whose compare to set, from 1 to 4.
     * @param compare The compare value to set.  If greater than this
     *                timer's overflow value, it will be truncated to
     *                the overflow value.
     *
     * @see timer_mode
     * @see HardwareTimer::setMode()
     * @see HardwareTimer::attachInterrupt()
     */
    void setCompare(int channel, uint16 compare);

    /**
     * @brief Attach an interrupt handler to the given channel.
     *
     * This interrupt handler will be called when the timer's counter
     * reaches the given channel compare value.
     *
     * @param channel the channel to attach the ISR to, from 1 to 4.
     * @param handler The ISR to attach to the given channel.
     * @see voidFuncPtr
     */
    void attachInterrupt(int channel, voidFuncPtr handler);

    /**
     * @brief Remove the interrupt handler attached to the given
     *        channel, if any.
     *
     * The handler will no longer be called by this timer.
     *
     * @param channel the channel whose interrupt to detach, from 1 to 4.
     * @see HardwareTimer::attachInterrupt()
     */
    void detachInterrupt(int channel);

    /**
     * @brief Reset the counter, and update the prescaler and overflow
     *        values.
     *
     * This will reset the counter to 0 in upcounting mode (the
     * default).  It will also update the timer's prescaler and
     * overflow, if you have set them up to be changed using
     * HardwareTimer::setPrescaleFactor() or
     * HardwareTimer::setOverflow().
     *
     * @see HardwareTimer::setPrescaleFactor()
     * @see HardwareTimer::setOverflow()
     */
    void refresh(void);

};

#endif
