/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#ifdef VIA_ENABLE
/* VIA configuration. */
#    define DYNAMIC_KEYMAP_LAYER_COUNT 6
#endif // VIA_ENABLE

/* Disable unused features. */
#define NO_ACTION_ONESHOT

/* Charybdis-specific features. */

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 210

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define QUICK_TAP_TERM 0

#define MACCEL_TAKEOFF 2.0      // lower/higher value = curve takes off more smoothly/abrubtly
#define MACCEL_GROWTH_RATE 0.25 // lower/higher value = curve reaches its upper limit slower/faster
#define MACCEL_OFFSET 2.2       // lower/higher value = acceleration kicks in earlier/later
#define MACCEL_LIMIT 6.0        // upper limit of accel curve (maximum acceleration factor)
