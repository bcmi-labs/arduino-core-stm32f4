/*
 * Copyright (c) 2012 by Cristian Maglie <c.maglie@arduino.cc>
 * Audio library for Arduino Due.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#include "Audio.h"
#include "BSP/OTTO/stm32469i_otto_audio_inout.h"


AudioClass Audio;

/*  Begin class can be extended to support more options */
int AudioClass::begin(uint32_t sampleRate, uint32_t msPreBuffer) {




    // Allocate a buffer to keep msPreBuffer milliseconds of audio
	//bufferSize = msPreBuffer * sampleRate / 1000;
	//if (bufferSize < 1024)

    bufferSize = 2 * 1024 * sizeof(uint32_t);
    buffer = (uint8_t *) malloc(bufferSize);

	// Buffering starts from the beginning
	running = NULL;
	half = buffer + bufferSize/2;
    last = buffer + bufferSize;
    next = buffer;

    /*  Default volume */
    volume = 40;
    return(BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_HEADPHONE, volume, sampleRate));
}

void AudioClass::end() {
    BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
    free( buffer);
    running = NULL;
}

void AudioClass::prepare(int16_t *buffer, int S, int volume){
    uint16_t *ubuffer = (uint16_t*) buffer;

    if(volume >= 100)
        volume = 100;
    if (volume <= 10)
        volume = 10;

    /*for (int i=0; i<S; i++) {
        // set volume amplitude (signed multiply)
        buffer[i] = buffer[i] * volume / 1024;
        // convert from signed 16 bit to unsigned 12 bit for DAC.
        ubuffer[i] += 0x8000;
        ubuffer[i] >>= 4;
    }*/
}
extern int cb_error;
int test_flag;
size_t AudioClass::write(const uint32_t *data, size_t size) {
	int i;

    if(size > (bufferSize / 2))
        return size;

    /*  not running yet, need to fill-in full FIFO */
    if(running == NULL) {
        memcpy(next, (uint8_t *) data, size);
        /* First half FIFO  */
        if(next == buffer) {
            next = half;
        /*  Second half FIfO, when copied, start playing */
        } else {
            next = buffer;
            running = buffer;
            BSP_AUDIO_OUT_Play((uint16_t*)buffer, bufferSize);
        }
        _receivedBytes += size;
        return size;
    }

    /*  Wait for room in FIFO*/
    while((int)next == (int) running);

    _receivedBytes += size;

    /*  check state of running */
    test_flag = 0;

    if(next == half)
        written_half++;
    if(next == buffer)
        written_buffer++;

    /*  If running is not next there is room in fifo */
    memcpy(next,(uint8_t *) data, size);

    if(test_flag)
        cb_error++;

    if(next == buffer) {
        next = half;
    } else {
        next = buffer;
    }

	return size;
}

int AudioClass::receivedBytes(void)
{
    return _receivedBytes;
}

int AudioClass::playedBytes(void)
{
    return _playedBytes;
}
int AudioClass::getBuffer(void)
{
    return (int)buffer;
}
int AudioClass::getHalf(void)
{
    return (int)half;
}
int AudioClass::getLast(void)
{
    return (int)last;
}
int AudioClass::getBufferSize(void)
{
    return (int)bufferSize;
}

extern int begin_status;
void BSP_AUDIO_OUT_HalfTransfer_CallBack(void)
{
    if(Audio.running != NULL) {
        test_flag = 1;
        /*  tell write function we're now playing the 2nd half*/
        Audio.running = Audio.half;
        Audio._playedBytes = (Audio.bufferSize/2);
    }
}

void BSP_AUDIO_OUT_TransferComplete_CallBack(void)
{
   if(Audio.running != NULL) {
        test_flag = 1;
         /*  tell write function we're now playing the 1st half*/
        Audio.running = Audio.buffer;
        Audio._playedBytes += (Audio.bufferSize/2);
    }
}
void BSP_AUDIO_OUT_Error_CallBack()
{
    //cb_error++;
}
