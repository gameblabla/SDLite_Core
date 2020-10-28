// SPDX-License-Identifier: GPL-3.0-or-later
/*******************************************************************************
 * Library       : SDLite 1.2.x
 * Purpose       : Low-level access to a framebuffer, audio output and HID.
 * Module        : Core
 * Project       : Redux for Embedded System
 * Description   : Stripped-down and optimized libraries for RISC processors
 * License       : GNU General Public License v3.0
 *******************************************************************************
 *
 * Rætro and SDLite 1.2.x:
 * Copyright (c) 2019-2020 Marcus Andrade <marcus@raetro.org>
 *
 * Simple DirectMedia Layer and SDL:
 * Copyright (c) 1997-2012 Sam Lantinga <slouken@libsdl.org>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.
 * If not, see <https://www.gnu.org/licenses/gpl-3.0.html>.
 *
 ******************************************************************************/
#include "SDL_config.h"

#ifndef SDL_sysaudio_h_
#define SDL_sysaudio_h_

#include "SDL_mutex.h"
#include "SDL_thread.h"

/* The SDL audio driver */
typedef struct SDL_AudioDevice SDL_AudioDevice;

/* Define the SDL audio driver structure */
#define _THIS    SDL_AudioDevice *_this
#ifndef _STATUS
#define _STATUS    SDL_status *status
#endif

struct SDL_AudioDevice {
	/* * * */
	/* The name of this audio driver */
	const char *name;

	/* * * */
	/* The description of this audio driver */
	const char *desc;

	/* * * */
	/* Public driver functions */
	int (*OpenAudio)(_THIS, SDL_AudioSpec *spec);

	void (*ThreadInit)(_THIS);    /* Called by audio thread at start */
	void (*WaitAudio)(_THIS);

	void (*PlayAudio)(_THIS);

	Uint8 *(*GetAudioBuf)(_THIS);

	void (*WaitDone)(_THIS);
	void (*PauseAudio)(_THIS, int pause_on);
	void (*WakeAudio)(_THIS);
	void (*CloseAudio)(_THIS);

	/* * * */
	/* Lock / Unlock functions added for the Mac port */
	void (*LockAudio)(_THIS);

	void (*UnlockAudio)(_THIS);

	void (*SetCaption)(_THIS, const char *caption);

	/* * * */
	/* Data common to all devices */

	/* The current audio specification (shared with audio thread) */
	SDL_AudioSpec spec;

	/* An audio conversion block for audio format emulation */
	SDL_AudioCVT convert;

	/* Current state flags */
	int enabled;
	int paused;
	int dev_paused;
	int opened;

	/* Fake audio buffer for when the audio hardware is busy */
	Uint8 *fake_stream;

	/* A semaphore for locking the mixing buffers */
	SDL_mutex *mixer_lock;

	/* A thread to feed the audio device */
	SDL_Thread *thread;
	Uint32 threadid;

	/* * * */
	/* Data private to this driver */
	struct SDL_PrivateAudioData *hidden;

	/* * * */
	/* The function used to dispose of this structure */
	void (*free)(_THIS);
};

#undef _THIS

typedef struct AudioBootStrap {
	const char *name;
	const char *desc;

	int (*available)(void);

	SDL_AudioDevice *(*create)(int devindex);
} AudioBootStrap;

#if SDL_AUDIO_DRIVER_PULSEAUDIO
extern AudioBootStrap PULSE_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_ALSA
extern AudioBootStrap ALSA_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_OSS
extern AudioBootStrap DSP_bootstrap;
extern AudioBootStrap DMA_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_DUMMY
extern AudioBootStrap DUMMYAUD_bootstrap;
#endif
/* This is the current audio device */
extern SDL_AudioDevice *current_audio;

#endif /* SDL_sysaudio_h_ */
