/*
 * Copyright (c) 2012 by Cristian Maglie <c.maglie@arduino.cc>
 * Audio library for Arduino Due.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef AUDIO_H
#define AUDIO_H

#include <Arduino.h>
#include <Print.h>
#include "Wave.h"
/* otto includes component */
#include "otto_audio_inout.h"

#define AUDIO_IN_BUFFER_SIZE 4*2304

typedef enum {
	AUDIO_OUT = 0,			/* (0) Enable Audio out */
	AUDIO_IN,				/* (1) Enable Audio in*/
	AUDIO_BOTH				/* (2) Enable Audio in and out */
} AudioMode;

class AudioClass : public Print {
public:
	void prepare(int16_t *buffer, int S, int volume);
	int begin(uint32_t sampleRate, uint32_t preBufferSize = 1024, AudioMode audioMode = AUDIO_OUT);
	uint32_t end(uint32_t Option = CODEC_PDWN_SW);

    int playedBytes(void);
    int receivedBytes(void);
    int getBufferOut(void);
    int getBufferOutSize(void);
    int getHalf(void);
    int getLast(void);

	virtual size_t write(uint8_t c)                         { /* not implemented */ };
	virtual size_t write(const uint8_t *data, size_t size)  { return write(reinterpret_cast<const uint32_t*>(data), size/4) * 4; };
	virtual size_t write(const uint16_t *data, size_t size) { return write(reinterpret_cast<const uint32_t*>(data), size/2) * 2; };
	virtual size_t write(const int16_t *data, size_t size)  { return write(reinterpret_cast<const uint32_t*>(data), size/2) * 2; };
	virtual size_t write(const uint32_t *data, size_t size);

	uint32_t setVolume(uint8_t volume, AudioMode audioMode = AUDIO_OUT);

	// Total number of samples
	uint32_t getSampleIn(void) { return bufferIn_fptr; }
	// Return true if the audio in buffer is full else false
	bool isBufferInFull(void) { return bufferInFull; }
	// Reset audio in buffer status (should be performed after process the buffer data)
	void setBufferInEmpty(uint32_t bytes) { bufferIn_fptr+= bytes; bufferInFull = false;}
	// Return the audio in buffer pointer
	uint16_t* getBufferIn(void) { return bufferIn;}
	// Return the audio in buffer pointer with offset of the available data
    uint16_t* getBufferInWithOffset(void) { return bufferIn + bufferIn_offset;}
	// Return size of data available in the audio in buffer
    uint32_t getBufferInSize(void) { return bufferInSize;}
;

	void debug() {
	}

	/* Audio Out */
	uint32_t bufferOutSize;
	uint8_t *bufferOut = NULL;
	uint8_t *half;
	uint8_t *last;
	uint8_t *volatile running;
	uint8_t *volatile next;
	uint32_t _playedBytes;
	uint32_t _receivedBytes;

	/* Audio In */
	const uint32_t bufferInSize = AUDIO_IN_BUFFER_SIZE;
	uint16_t bufferIn[AUDIO_IN_BUFFER_SIZE];//pcm_buff
	bool bufferInFull = false; //wr_state
	uint32_t bufferIn_offset = 0;
	uint32_t bufferIn_ptr = 0; //pcm_ptr
	uint32_t bufferIn_fptr = 0; //fptr

private:
	uint32_t volume = 100;
	bool audio_in_init = false; // init codec status for audio in
	bool audio_out_init = false; // init codec status for audio out
	AudioMode mode;
};

extern AudioClass Audio;

#endif
