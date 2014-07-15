/*
  This file is part of Deadbeef Player source code
  http://deadbeef.sourceforge.net

  streamer implementation

  Copyright (C) 2009-2013 Alexey Yakovenko

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  Alexey Yakovenko waker@users.sourceforge.net
*/
#ifndef __STREAMER_H
#define __STREAMER_H

#include "playlist.h"
#include "deadbeef.h"

// events to pass to streamer thread
enum {
    STR_EV_PLAY_TRACK_IDX, // p1 = idx, p2 = pstate; see streamer_set_nextsong semantics
    STR_EV_PLAY_CURR, // will play the current streamer track (playing_track), see more details in streamer_play_current_track
};

int
streamer_init (void);

void
streamer_free (void);

int
streamer_read (char *bytes, int size);

void
streamer_reset (int full);

void
streamer_lock (void);

void
streamer_unlock (void);

// pstate indicates what to do with playback
// -1 means "don't do anything"
// -2 means "end of playlist"
// 0 stop
// 1 switch to current (gui) playlist, play if not playing
// 2 pause
// 3 play if not playing, don't switch playlist
void
streamer_set_nextsong (int song, int pstate);

void
streamer_set_seek (float pos);

int
streamer_get_fill (void);

int
streamer_ok_to_read (int len);

float
streamer_get_playpos (void);

void
streamer_song_removed_notify (playItem_t *it);

playItem_t *
streamer_get_streaming_track (void);

playItem_t *
streamer_get_playing_track (void);

void
streamer_configchanged (void);

// if paused -- resume
// else, if have cursor track -- stop current, play cursor
// else, play next
void
streamer_play_current_track (void);

void
streamer_set_bitrate (int bitrate);

int
streamer_get_apx_bitrate (void);

// returns -1 if theres no next song, or playlist finished
// reason 0 means "song finished", 1 means "user clicked next"
int
streamer_move_to_nextsong (int reason);

int
streamer_move_to_prevsong (void);

int
streamer_move_to_randomsong (void);

struct DB_fileinfo_s *
streamer_get_current_fileinfo (void);

void
streamer_set_current_playlist (int plt);

int
streamer_get_current_playlist (void);

// returns track index in current streamer playlist
int
str_get_idx_of (playItem_t *it);

void
streamer_notify_playlist_deleted (playlist_t *plt);

struct ddb_dsp_context_s *
streamer_get_dsp_chain (void);

void
streamer_set_dsp_chain (struct ddb_dsp_context_s *chain);

void
streamer_dsp_refresh (void);

void
streamer_get_output_format (ddb_waveformat_t *fmt);

void
streamer_dsp_postinit (void);

int
streamer_dsp_chain_save (void);

void
streamer_notify_order_changed (int prev_order, int new_order);

void
audio_get_waveform_data (int type, float *data);

void
streamer_set_streamer_playlist (playlist_t *plt);

struct handler_s *
streamer_get_handler (void);

void
vis_waveform_listen (void *ctx, void (*callback)(void *ctx, ddb_audio_data_t *data));

void
vis_waveform_unlisten (void *ctx);

void
vis_spectrum_listen (void *ctx, void (*callback)(void *ctx, ddb_audio_data_t *data));

void
vis_spectrum_unlisten (void *ctx);

#endif // __STREAMER_H
