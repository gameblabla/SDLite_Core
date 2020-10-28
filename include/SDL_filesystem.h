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
/*!*****************************************************************************
 * @file SDL_filesystem.h
 * @brief Header for filesystem routines.
 ******************************************************************************/
/*!*****************************************************************************
* @defgroup fs_path Filesystem Paths
* @brief Filesystem Paths
* @details This category contains functions for getting commonly used paths
* such as the application directory and the user write directory.
* @{
******************************************************************************/
#ifndef SDL_filesystem_h_
#define SDL_filesystem_h_

#include "SDL_stdinc.h"

#include "begin_code.h"

/** Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get the path where the application resides.
 *
 * Get the "base path". This is the directory where the application was run
 *  from, which is probably the installation directory, and may or may not
 *  be the process's current working directory.
 *
 * This returns an absolute path in UTF-8 encoding, and is guaranteed to
 *  end with a path separator ('\\' on Windows, '/' most other places).
 *
 * The pointer returned by this function is owned by you. Please call
 *  SDL_free() on the pointer when you are done with it, or it will be a
 *  memory leak. This is not necessarily a fast call, though, so you should
 *  call this once near startup and save the string if you need it.
 *
 * Some platforms can't determine the application's path, and on other
 *  platforms, this might be meaningless. In such cases, this function will
 *  return NULL.
 *
 *  \return String of base dir in UTF-8 encoding, or NULL on error.
 *
 * @sa SDL_GetPrefPath
 */
extern DECLSPEC char *SDLCALL SDL_GetBasePath(void);

/**
 * @brief Get the user-and-app-specific path where files can be written.
 *
 * Get the "pref dir". This is meant to be where users can write personal
 *  files (preferences and save games, etc) that are specific to your
 *  application. This directory is unique per user, per application.
 *
 * This function will decide the appropriate location in the native filesystem,
 *  create the directory if necessary, and return a string of the absolute
 *  path to the directory in UTF-8 encoding.
 *
 * On Linux, the string might look like:
 *  "/home/bob/.local/share/My Program Name/"
 *
 * You specify the name of your organization (if it's not a real organization,
 *  your name or an Internet domain you own might do) and the name of your
 *  application. These should be untranslated proper names.
 *
 * Both the org and app strings may become part of a directory name, so
 *  please follow these rules:
 *
 *    - Try to use the same org string (including case-sensitivity) for
 *      all your applications that use this function.
 *    - Always use a unique app string for each one, and make sure it never
 *      changes for an app once you've decided on it.
 *    - Unicode characters are legal, as long as it's UTF-8 encoded, but...
 *    - ...only use letters, numbers, and spaces. Avoid punctuation like
 *      "Game Name 2: Bad Guy's Revenge!" ... "Game Name 2" is sufficient.
 *
 * This returns an absolute path in UTF-8 encoding, and is guaranteed to
 *  end with a path separator ('\\' on Windows, '/' most other places).
 *
 * The pointer returned by this function is owned by you. Please call
 *  SDL_free() on the pointer when you are done with it, or it will be a
 *  memory leak. This is not necessarily a fast call, though, so you should
 *  call this once near startup and save the string if you need it.
 *
 * You should assume the path returned by this function is the only safe
 *  place to write files (and that SDL_GetBasePath(), while it might be
 *  writable, or even the parent of the returned path, aren't where you
 *  should be writing things).
 *
 * Some platforms can't determine the pref path, and on other
 *  platforms, this might be meaningless. In such cases, this function will
 *  return NULL.
 *
 *  \param org The name of your organization.
 *  \param app The name of your application.
 *  \return UTF-8 string of user dir in platform-dependent notation. NULL
 *          if there's a problem (creating directory failed, etc).
 *
 * @sa SDL_GetBasePath
 */
extern DECLSPEC char *SDLCALL SDL_GetPrefPath(const char *org, const char *app);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#include "close_code.h"

#endif /* SDL_filesystem_h_ */
