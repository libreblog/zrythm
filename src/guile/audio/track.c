/*
 * Copyright (C) 2020 Alexandros Theodotou <alex at zrythm dot org>
 *
 * This file is part of Zrythm
 *
 * Zrythm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zrythm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "guile/modules.h"

#ifndef SNARF_MODE
#include "audio/track.h"
#include "project.h"
#endif

SCM_DEFINE (
  s_midi_track_new, "midi-track-new", 2, 0, 0,
  (SCM idx, SCM name),
  "Returns a new track with name @var{name} to be "
  "placed at position @var{idx} in the tracklist.")
{
  Track * track =
    track_new (
      TRACK_TYPE_MIDI, scm_to_int (idx),
      scm_to_locale_string (name), true);

  return scm_from_pointer (track, NULL);
}

SCM_DEFINE (
  s_track_get_name, "track-get-name", 1, 0, 0,
  (SCM track),
  "Returns the name of @var{track}.")
{
  Track * reftrack =
    scm_to_pointer (track);

  return
    scm_from_utf8_string (
      track_get_name (reftrack));
}

SCM_DEFINE (
  s_add_region, "track-add-lane-region", 3, 0, 0,
  (SCM track, SCM region, SCM lane_pos),
  "Adds @var{region} to track @var{track}. To "
  "be used for regions with lanes (midi/audio)")
{
  track_add_region (
    scm_to_pointer (track),
    scm_to_pointer (region),
    NULL,
    scm_to_int (lane_pos), true, true);

  return SCM_BOOL_T;
}

static void
init_module (void * data)
{
#ifndef SNARF_MODE
#include "audio_track.x"
#endif

  scm_c_export (
    "midi-track-new",
    "track-add-lane-region",
    "track-get-name", NULL);
}

void
guile_audio_track_define_module (void)
{
  scm_c_define_module (
    "audio track", init_module, NULL);
}
