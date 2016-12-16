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
#include "BSP/OTTO/otto_audio_inout.h"



AudioClass Audio;

/*  Begin class can be extended to support more options */
int AudioClass::begin(uint32_t sampleRate, uint32_t msPreBuffer, AudioMode audioMode) {
	int ret;
	mode = audioMode;

	/* Audio Out */
	if(mode != AUDIO_IN)
	{
	    bufferOutSize = 2 * 1024 * sizeof(uint32_t);
		bufferOut = (uint8_t *) malloc(bufferOutSize);

		/* Buffering starts from the beginning */
		running = NULL;
		half = bufferOut + bufferOutSize/2;
		last = bufferOut + bufferOutSize;
	    next = bufferOut;
	}

	ret = BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_HEADPHONE, volume, sampleRate);

	/* Audio In */
	if(mode != AUDIO_OUT)
	{
		ret += BSP_AUDIO_IN_Init(INPUT_DEVICE_DIGITAL_MICROPHONE_2, volume, sampleRate);
		ret += BSP_AUDIO_IN_Record((uint16_t*)&bufferIn[0], bufferInSize);
		bufferIn_fptr += 44;
	}

    return ret;
}

void AudioClass::end() {
	if(mode != AUDIO_OUT)
	{
		/* Stop recorder */
	    BSP_AUDIO_IN_Stop(CODEC_PDWN_SW);
	}
    BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
    if (bufferOut) 
	{
		free(bufferOut);
		bufferOut = NULL;
	}
    running = NULL;
}

void AudioClass::prepare(int16_t *buffer, int S, int volume){
    uint16_t *ubuffer = (uint16_t*) buffer;

    if(volume >= 100)
        volume = 100;
    if (volume <= 10)
        volume = 10;
}

size_t AudioClass::write(const uint32_t *data, size_t size) {
	int i;

    if(size > (bufferOutSize / 2))
        return size;

    /*  not running yet, need to fill-in full FIFO */
    if(running == NULL) {
        memcpy(next, (uint8_t *) data, size);
        /* First half FIFO  */
        if(next == bufferOut) {
            next = half;
        /*  Second half FIfO, when copied, start playing */
        } else {
            next = bufferOut;
            running = bufferOut;
            BSP_AUDIO_OUT_Play((uint16_t*)bufferOut, bufferOutSize);
        }
        _receivedBytes += size;
        return size;
    }

    /*  Wait for room in FIFO*/
    while((int)next == (int) running);

    _receivedBytes += size;

    /*  If running is not next there is room in fifo */
    memcpy(next,(uint8_t *) data, size);

    if(next == bufferOut) {
        next = half;
    } else {
        next = bufferOut;
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
int AudioClass::getBufferOut(void)
{
    return (int)bufferOut;
}
int AudioClass::getHalf(void)
{
    return (int)half;
}
int AudioClass::getLast(void)
{
    return (int)last;
}
int AudioClass::getBufferOutSize(void)
{
    return (int)bufferOutSize;
}

extern int begin_status;
void BSP_AUDIO_OUT_HalfTransfer_CallBack(void)
{
    if(Audio.running != NULL) {
        /*  tell write function we're now playing the 2nd half*/
        Audio.running = Audio.half;
        Audio._playedBytes = (Audio.bufferOutSize/2);
    }
}

void BSP_AUDIO_OUT_TransferComplete_CallBack(void)
{
   if(Audio.running != NULL) {
         /*  tell write function we're now playing the 1st half*/
        Audio.running = Audio.bufferOut;
        Audio._playedBytes += (Audio.bufferOutSize/2);
    }
}

void BSP_AUDIO_OUT_Error_CallBack()
{

}

/**
  * @brief  Calculates the remaining file size and new position of the pointer.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_IN_TransferComplete_CallBack(void)
{
  Audio.bufferIn_ptr+= Audio.bufferInSize/2;
  if(Audio.bufferIn_ptr == Audio.bufferInSize/2)
  {
    Audio.bufferInFull   =  true;
    Audio.bufferIn_offset  = 0;
  }

  if(Audio.bufferIn_ptr >= Audio.bufferInSize)
  {
    Audio.bufferInFull = true;
    Audio.bufferIn_offset = Audio.bufferInSize/2;
    Audio.bufferIn_ptr = 0;
  }
}

/**
  * @brief  Manages the DMA Half Transfer complete interrupt.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_IN_HalfTransfer_CallBack(void)
{
  Audio.bufferIn_ptr+= Audio.bufferInSize/2;
  if(Audio.bufferIn_ptr == Audio.bufferInSize/2)
  {
    Audio.bufferInFull = true;
    Audio.bufferIn_offset = 0;
  }

  if(Audio.bufferIn_ptr >= Audio.bufferInSize)
  {
    Audio.bufferInFull = true;
	Audio.bufferIn_offset  = Audio.bufferInSize/2;
    Audio.bufferIn_ptr = 0;
  }
}

/**
  * @brief  Audio IN Error callback function.
  */
void BSP_AUDIO_IN_Error_CallBack(void)
{
  /* This function is called when an Interrupt due to transfer error on or peripheral
     error occurs. */
}
