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
#include "otto_audio_inout.h"

AudioClass Audio;

/**
  * @brief  Stops audio playing/recording and Power down the Audio Codec.
  * @param  sampleRate: sample rate of the sound file in Hz (ex: 48000Hz for 48kHz)
  * @param  preBufferSize: size of the audio out buffer (default 1024)
  * @param  audioMode: defined which audio path to configured:
  *			- AUDIO_IN
  *			- AUDIO_OUT (default)
  *			- AUDIO_BOTH
  * @note:  begin method can be extended to support more options
  * @retval AUDIO_OK if correct init, else wrong
  */
int AudioClass::begin(uint32_t sampleRate, uint32_t preBufferSize, AudioMode audioMode) {
	int ret = AUDIO_OK;
	mode = audioMode;

	/* Audio Out */
	if(mode != AUDIO_IN) {
		if (bufferOut != NULL) {
			free(bufferOut);
			bufferOut = NULL;
		}
		bufferOutSize = 2 * preBufferSize * sizeof(uint32_t);
		bufferOut = (uint8_t *) malloc(bufferOutSize);

		/* Buffering starts from the beginning */
		running = NULL;
		half = bufferOut + bufferOutSize/2;
		last = bufferOut + bufferOutSize;
	    next = bufferOut;
	}
	/* Required even if AUDIO_IN only*/
	ret = BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_HEADPHONE, 0, sampleRate);
	audio_out_init = ((mode != AUDIO_IN) && (ret == AUDIO_OK)) ? true : false;

	/* Audio In */
	if ((mode != AUDIO_OUT) && (ret == AUDIO_OK)) {
		bufferIn_fptr = 44; // Wave header size
		bufferInFull = false;
		bufferIn_ptr = 0;
		bufferIn_offset = 0;
		ret += BSP_AUDIO_IN_Init(INPUT_DEVICE_DIGITAL_MICROPHONE_2, 0, sampleRate);
		audio_in_init = (ret == AUDIO_OK) ? true : false;
		/* Start the record*/
		ret += BSP_AUDIO_IN_Record((uint16_t*)&bufferIn[0], bufferInSize);
	}

    return ret;
}

/**
  * @brief  Ends audio playing/recording and Power down the Audio Codec.
  * @param  Option: could be one of the following parameters
  *           - CODEC_PDWN_SW: for software power off (by writing registers).
  *                            Then no need to reconfigure the Codec after power on. (default)
  *           - CODEC_PDWN_HW: completely shut down the codec (physically).
  *                            Then need to reconfigure the Codec after power on.
  * @retval AUDIO_OK if correct communication, else wrong communication
  * @note   For Audio IN, begin() call is required in any case after called this function
  *         even if CODEC_PDWN_SW is used.
  */
uint32_t AudioClass::end(uint32_t Option) {
	uint32_t ret = AUDIO_OK;

	if ((Option != CODEC_PDWN_SW) && (Option != CODEC_PDWN_HW)) {
		Option = CODEC_PDWN_SW; // Force stop to avoid any noise issue
	}

	if ((audio_in_init) && (mode != AUDIO_OUT)) {
		/* Stop recorder */
		ret = BSP_AUDIO_IN_Stop(Option);
	}
	if (audio_in_init || audio_out_init) {
		ret |= BSP_AUDIO_OUT_Stop(Option);
	}
	audio_in_init = false;

	if (Option == CODEC_PDWN_HW) {
		audio_out_init = false;
		if (bufferOut) {
		free(bufferOut);
		bufferOut = NULL;
	}
		bufferOutSize = 0;
	}
	// Ensure to reset all variables
	// Audio Out
	half = bufferOut + bufferOutSize/2;
	last = bufferOut + bufferOutSize;
	next = bufferOut;
    running = NULL;
	// Audio In
	bufferIn_fptr = 0;
	bufferInFull = false;
	bufferIn_ptr = 0;
	bufferIn_offset = 0;
	return ret;
}

/**
  * @brief  Not used. Added to be inline with Arduino Audio library
  * @param  buffer
  * @param  S
  * @param  volume
  * @note: See: https://www.arduino.cc/en/Reference/Audio
  * @retval None
  */
void AudioClass::prepare(int16_t *buffer, int S, int volume) {
    uint16_t *ubuffer = (uint16_t*) buffer;

    if (volume >= 100)
        volume = 100;
    if (volume <= 0)
        volume = 0;
    amp(volume);
}

/**
  * @brief  Playing audio stream from a data buffer for a determined size.
  * @param  data: Pointer to the buffer
  * @param  size: Number of audio data bytes
  * @retval Number of bytes written
  */
size_t AudioClass::write(const uint32_t *data, size_t size) {
	int i;
	if (!audio_out_init) return 0;

	if (size > (bufferOutSize / 2))
		return size;

    /* Not running yet, need to fill-in full FIFO */
	if (running == NULL) {
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

	if (next == bufferOut) {
		next = half;
	} else {
		next = bufferOut;
	}

	return size;
}

/**
  * @brief  Controls the current audio volume level.
  * @param  Volume: Volume level to be set in percentage from 0% to 100% (0 for
  *         Mute and 100 for Max volume level).
  * @param  audioMode: defined which audio path to configured:
  *			- AUDIO_IN
  *			- AUDIO_OUT (default)
  *			- AUDIO_BOTH
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint32_t AudioClass::amp(uint8_t volume, AudioMode audioMode) {
	uint32_t ret = AUDIO_OK;
	if ((!audio_in_init) && (!audio_out_init))
		ret = AUDIO_ERROR;
	if ((audio_out_init) && (audioMode != AUDIO_IN))
		ret = BSP_AUDIO_OUT_SetVolume(volume);
	if ((audio_in_init) && (audioMode != AUDIO_OUT))
		ret |= BSP_AUDIO_IN_SetVolume(volume);
	return ret;
}

/* Accessors */
int AudioClass::receivedBytes(void) {
    return _receivedBytes;
}

int AudioClass::playedBytes(void) {
    return _playedBytes;
}
int AudioClass::getBufferOut(void) {
    return (int)bufferOut;
}
int AudioClass::getHalf(void) {
    return (int)half;
}
int AudioClass::getLast(void) {
    return (int)last;
}
int AudioClass::getBufferOutSize(void) {
    return (int)bufferOutSize;
}

extern int begin_status;
/**
  * @brief  Manages the DMA Half Transfer complete event.
  */
void BSP_AUDIO_OUT_HalfTransfer_CallBack(void) {
    if (Audio.running != NULL) {
        /* Tell write function we're now playing the 2nd half*/
        Audio.running = Audio.half;
        Audio._playedBytes = (Audio.bufferOutSize/2);
    }
}

/**
  * @brief  Manages the DMA full Transfer complete event.
  */
void BSP_AUDIO_OUT_TransferComplete_CallBack(void) {
   if (Audio.running != NULL) {
         /* Tell write function we're now playing the 1st half*/
        Audio.running = Audio.bufferOut;
        Audio._playedBytes += (Audio.bufferOutSize/2);
    }
}

/**
  * @brief  Audio OUT Error callback function.
  */
void BSP_AUDIO_OUT_Error_CallBack() {
  /* This function is called when an Interrupt due to transfer error on or peripheral
     error occurs. */
}

/**
  * @brief  Calculates the remaining file size and new position of the pointer.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_IN_TransferComplete_CallBack(void) {
  Audio.bufferIn_ptr+= Audio.bufferInSize/2;
  if (Audio.bufferIn_ptr == Audio.bufferInSize/2) {
    Audio.bufferInFull   =  true;
    Audio.bufferIn_offset  = 0;
  }

  if (Audio.bufferIn_ptr >= Audio.bufferInSize) {
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
void BSP_AUDIO_IN_HalfTransfer_CallBack(void) {
  Audio.bufferIn_ptr+= Audio.bufferInSize/2;
  if (Audio.bufferIn_ptr == Audio.bufferInSize/2) {
    Audio.bufferInFull = true;
    Audio.bufferIn_offset = 0;
  }

  if (Audio.bufferIn_ptr >= Audio.bufferInSize) {
    Audio.bufferInFull = true;
	Audio.bufferIn_offset  = Audio.bufferInSize/2;
    Audio.bufferIn_ptr = 0;
  }
}

/**
  * @brief  Audio IN Error callback function.
  */
void BSP_AUDIO_IN_Error_CallBack(void) {
  /* This function is called when an Interrupt due to transfer error on or peripheral
     error occurs. */
}
