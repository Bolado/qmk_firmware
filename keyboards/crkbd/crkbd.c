/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "quantum.h"

#ifdef SWAP_HANDS_ENABLE
__attribute__((weak)) const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    // Left
    {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}},
    {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}},
    {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}},
    {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}},
    // Right
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}},
    {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}},
    {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}},
    {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}}
};
#endif

#ifdef OLED_ENABLE


oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    }
    return OLED_ROTATION_270;
}


__attribute__((weak)) void oled_render_logo(void) {
    // clang-format off
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    // clang-format on
    oled_write_P(crkbd_logo, false);
}

// Animation parameters
#define FRAME_DURATION 155 // How long each frame lasts in milliseconds

// Animation variables
uint32_t timer = 0;
uint8_t current_frame = 0;
uint8_t direction = 1;

// Render animation
static void render_animation(void) {
    // Frame 1
    // 'Untitled-1', 32x128px
// 'Untitled-8', 32x128px
static const char epd_bitmap_Untitled_8 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8a, 0x20, 0x08, 0x42, 0x08,
	0x20, 0x8a, 0x00, 0x28, 0x82, 0x00, 0x48, 0x00, 0x04, 0x00, 0x20, 0x04, 0x00, 0x20, 0x04, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x08, 0x41, 0x08, 0x22,
	0x80, 0x0a, 0x20, 0x02, 0x48, 0x00, 0x04, 0x20, 0x01, 0x00, 0x48, 0x01, 0x20, 0x04, 0x00, 0x10,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x44, 0x00, 0x11, 0x44,
	0x00, 0x28, 0x01, 0x40, 0x0a, 0x00, 0x21, 0x00, 0x08, 0x02, 0x40, 0x04, 0x00, 0x11, 0x80, 0x04,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x14, 0x00, 0x21, 0x84,
	0x10, 0x01, 0x84, 0x20, 0x09, 0x80, 0x00, 0x08, 0x41, 0x00, 0x10, 0x00, 0x02, 0x90, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x41, 0x04, 0x80, 0x10,
	0x42, 0x00, 0x10, 0x82, 0x08, 0x00, 0x44, 0x00, 0x02, 0x80, 0x10, 0x02, 0x80, 0x10, 0x00, 0x04,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x50, 0x00, 0x04, 0x20,
	0x82, 0x00, 0x28, 0x00, 0x42, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x05, 0x00, 0x52, 0x00,
	0x80, 0x14, 0x40, 0x01, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x41, 0x04, 0x20, 0x04,
	0x80, 0x10, 0x42, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8a, 0x20, 0x84, 0x11, 0x40,
	0x04, 0x90, 0x04, 0xa0, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x48, 0x02, 0x20,
	0x0a, 0x00, 0x08, 0x02, 0x48, 0x00, 0x00, 0x01, 0x20, 0x00, 0x00, 0x21, 0x00, 0x00, 0x10, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x20, 0x00, 0x10,
	0x02, 0x00, 0x81, 0x10, 0x00, 0x08, 0x80, 0x02, 0x40, 0x00, 0x22, 0x00, 0x00, 0x08, 0x81, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x80, 0x09, 0x24, 0x41,
	0x08, 0x92, 0x40, 0x14, 0x41, 0x00, 0x94, 0x00, 0x22, 0x80, 0x08, 0x21, 0x84, 0x00, 0x52, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x04, 0x80, 0x25, 0x00,
	0x12, 0x00, 0x42, 0x08, 0x01, 0x04, 0x00, 0x00, 0x02, 0x40, 0x00, 0x02, 0x20, 0x00, 0x02, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x88, 0x00, 0x24, 0x80,
	0x10, 0x41, 0x04, 0x00, 0x51, 0x00, 0x80, 0x00, 0x88, 0x00, 0x40, 0x00, 0x08, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaa, 0x00, 0xa2, 0x08, 0x42,
	0x10, 0x41, 0x14, 0x81, 0x24, 0x00, 0x04, 0x50, 0x00, 0x8a, 0x00, 0x20, 0x85, 0x10, 0x02, 0x40,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x92, 0x00, 0x48,
	0x01, 0x24, 0x00, 0x82, 0x10, 0x01, 0x00, 0x00, 0x24, 0x00, 0x00, 0x84, 0x00, 0x20, 0x02, 0x00
};
// 'Untitled-6', 32x128px
static const char epd_bitmap_Untitled_6 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x80, 0x00, 0xd4, 0x09, 0xd2, 0x24, 0x49, 0x92, 0xa4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x01, 0x00,
	0x10, 0x00, 0xae, 0x11, 0xae, 0x51, 0x26, 0x99, 0x2a, 0x00, 0x80, 0x12, 0x00, 0x40, 0x0a, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
	0x00, 0x00, 0x4a, 0x15, 0x40, 0x8a, 0x11, 0x24, 0x49, 0x00, 0x00, 0x10, 0x00, 0x04, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x20, 0x40, 0x20, 0x90,
	0x00, 0xa0, 0x04, 0x01, 0x0a, 0x00, 0x05, 0x00, 0x09, 0x20, 0x80, 0x50, 0x00, 0xa0, 0x10, 0x40,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x44, 0x02,
	0x00, 0x02, 0x50, 0x28, 0x80, 0x50, 0x08, 0xa0, 0x10, 0x02, 0x04, 0x40, 0x05, 0x00, 0x12, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x11, 0x82, 0x00, 0x11, 0x82, 0x08, 0x01, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x88, 0x22, 0x48, 0x92, 0x28, 0x02, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x14, 0x63, 0x0c, 0x72, 0x05, 0x69, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x40, 0xc0, 0x40, 0xc0, 0x40, 0xa0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x80,
	0x00, 0x80, 0x1b, 0x46, 0x1d, 0x13, 0x0e, 0x99, 0x17, 0x00, 0x00, 0x40, 0x00, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x00, 0x00,
	0x04, 0x00, 0x48, 0x00, 0x12, 0x40, 0x04, 0x10, 0x40, 0x05, 0x00, 0x02, 0x00, 0x04, 0x00, 0x09,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x08,
	0x80, 0x20, 0x04, 0xa9, 0x00, 0x55, 0x80, 0x29, 0x80, 0x28, 0x00, 0x50, 0x00, 0x50, 0x00, 0x50,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x92, 0x00, 0x08,
	0x00, 0x42, 0x94, 0x28, 0x45, 0x98, 0x22, 0xcc, 0x10, 0x05, 0x40, 0x01, 0x04, 0x21, 0x02, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x51, 0x04, 0x11, 0x40, 0x04, 0x91, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x02, 0x14, 0xa2, 0x08,
	0x22, 0x89, 0x00, 0x80, 0x00, 0x80, 0x08, 0x80, 0x00, 0x4a, 0x20, 0x0a, 0x20, 0x8a, 0x20, 0x0a,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x20, 0x00,
	0x04, 0x00, 0x12, 0x24, 0x09, 0x22, 0x08, 0x12, 0x09, 0x00, 0x08, 0x01, 0x24, 0x00, 0x10, 0x02
};
// 'Untitled-7', 32x128px
static const char epd_bitmap_Untitled_7 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x8a, 0x20, 0x08, 0x42, 0x08, 0x20, 0x8a, 0x00, 0x10, 0x42, 0x08, 0x00, 0x42, 0x08, 0x40,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x22, 0x88, 0x55, 0x00, 0x55, 0x28, 0x85, 0x22, 0x48, 0x15, 0x40, 0x95, 0x2a, 0x41, 0x14, 0x49,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x20, 0x04, 0x10, 0x81, 0x08, 0x40, 0x04, 0x00, 0x21, 0x00, 0x00, 0x08, 0x40, 0x01, 0x20,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x10, 0xa5, 0x02, 0xa8, 0x42, 0x28, 0x82, 0x29, 0x04, 0x50, 0x01, 0x24, 0x81, 0x28, 0x02, 0x90,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x22, 0x88, 0x52, 0x04, 0x50, 0x25, 0x82, 0x28, 0x95, 0x40, 0x15, 0x22, 0x48, 0x95, 0x00, 0xaa,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x55, 0x00, 0x55, 0x80, 0x15, 0xa0, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x49, 0x92, 0x00, 0x24, 0x12, 0x40, 0x0a, 0x00, 0x20, 0x04, 0x00, 0x20, 0x04, 0x10, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x20, 0x04, 0x00, 0x41, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x44, 0x11, 0xaa, 0x41, 0x14, 0xa1, 0x14, 0x49, 0x04, 0x51, 0x24, 0x89, 0x22, 0x49, 0x14, 0xa1,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x81, 0x00, 0x00, 0x48, 0x00, 0x04, 0x00, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x88, 0x23, 0x54, 0x81, 0x2a, 0x51, 0x84, 0x29, 0x44, 0x10, 0x85, 0x20, 0x4a, 0x81, 0x14, 0x20,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x48, 0x12, 0xa5, 0x08, 0x62, 0x89, 0x14, 0xa2, 0x09, 0xa0, 0x0a, 0xa0, 0x0a, 0x50, 0x85, 0x10,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x04, 0x51, 0x8a, 0x21, 0x14, 0x41, 0x94, 0x09, 0xa4, 0x01, 0x54, 0x01, 0x54, 0x01, 0xa8, 0x05,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x92, 0x00, 0x24, 0x81, 0x28, 0x00, 0x12, 0x40, 0x14, 0x00, 0x41, 0x14, 0x00, 0x52, 0x00
};
// 'Untitled-5', 32x128px
static const char epd_bitmap_Untitled_5 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x08, 0x42, 0xa8, 0x00, 0x42, 0xa8, 0x52, 0x48, 0xc2, 0x14, 0xe2, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x25, 0x48, 0x95, 0x20, 0x4d, 0x90, 0xaf, 0x10, 0x6f, 0x84, 0x5b, 0xa4, 0x00, 0x00, 0x00, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x02, 0x00, 0x03, 0x00, 0x02, 0x00, 0x03, 0x00, 0x01, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x48, 0x82, 0x54, 0x22, 0x88, 0x22, 0x09, 0x94, 0x02, 0x29, 0x04, 0x12, 0x40, 0x00, 0x80, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x02, 0xa4, 0x09, 0x42, 0x14, 0x89, 0x20, 0x50, 0x84, 0x50, 0x22, 0x40, 0x09, 0x02, 0x00, 0x05,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x22, 0x00, 0x02, 0x20, 0x01, 0x02, 0x00, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x55, 0x00, 0x55, 0x80, 0x15, 0x40, 0x00, 0x00, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x08, 0x01, 0x0a, 0x00, 0x0a, 0x00, 0x82, 0x28, 0x81, 0x24, 0x40, 0x08, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x44, 0x20, 0x8a, 0x40, 0x15, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x20, 0x0a, 0x50, 0x02, 0x54, 0x01, 0x3d, 0x13, 0x2e, 0x99, 0x26, 0x1b, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x04, 0x81, 0x14, 0x01, 0x0a, 0x00, 0x01, 0x00, 0x84, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x20, 0x4c, 0x90, 0x24, 0x48, 0x92, 0x64, 0x09, 0x50, 0x4c, 0x90, 0x64, 0x00, 0x00, 0x00, 0x40,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x09, 0x92, 0x24, 0x89, 0x12, 0x24, 0x91, 0x04, 0x21, 0x08, 0x42, 0x14, 0x00, 0x02, 0x10, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x2a, 0x00, 0x48, 0x02, 0x90, 0x24, 0x40, 0x09, 0x50, 0x82, 0x50, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x24, 0x49, 0x94, 0x29, 0x44, 0xa8, 0x02, 0x01, 0x00, 0x11, 0x00, 0x02, 0xa8, 0x00, 0xa8, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x15, 0x00, 0x12, 0x24, 0x00, 0x1b, 0x24, 0x09, 0x25, 0x0a, 0x31, 0x00, 0x00, 0x00, 0x00
};
// 'Untitled-3', 32x128px
static const char epd_bitmap_Untitled_3 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
	0x00, 0x10, 0x60, 0x8a, 0x30, 0xc4, 0xb0, 0x50, 0xf0, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44,
	0x11, 0x80, 0x2f, 0x82, 0x2d, 0x8a, 0x4d, 0x17, 0x4a, 0xaf, 0x00, 0x20, 0x80, 0x20, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
	0x00, 0x00, 0x0d, 0x02, 0x0c, 0x03, 0x04, 0x0b, 0x04, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0xa0,
	0x50, 0xd0, 0x05, 0x0a, 0x05, 0x0a, 0x05, 0x48, 0x05, 0x0a, 0xa0, 0x00, 0xa0, 0x40, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x4a,
	0x05, 0x0a, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x11, 0xf4, 0x20, 0x05, 0x0a, 0x04, 0x09, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x40, 0x90, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xea, 0x15, 0xea, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xaf, 0x00, 0xaf, 0x55, 0x00, 0xb0, 0x40, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x20, 0xd0, 0x20, 0x50, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0,
	0x00, 0x10, 0xe5, 0x1a, 0xe5, 0x15, 0xed, 0xb3, 0x4c, 0xbb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04,
	0x09, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x02, 0x00, 0x05, 0x00, 0x02, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x28,
	0x82, 0x20, 0x8f, 0x20, 0x4f, 0x14, 0xa1, 0x4e, 0xb0, 0x45, 0x20, 0x00, 0xa0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a,
	0x40, 0x0a, 0xf0, 0x0a, 0xf1, 0x14, 0xe2, 0x18, 0xa2, 0x54, 0x01, 0x0a, 0x00, 0x05, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x90, 0x20, 0xd0, 0x10, 0x40, 0x90, 0x20, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd2, 0x35,
	0xca, 0xb2, 0x00, 0x04, 0x00, 0x02, 0x08, 0x02, 0x48, 0x00, 0x52, 0xb0, 0x44, 0x90, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a,
	0x00, 0x0a, 0x00, 0xaa, 0x05, 0x80, 0x2d, 0x03, 0x44, 0x0b, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
};
// 'Untitled-4', 32x128px
static const char epd_bitmap_Untitled_4 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x6a, 0x80, 0x28, 0x42, 0xa8, 0x12, 0x64, 0x82, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49,
	0xb6, 0x08, 0x65, 0x9a, 0x20, 0x4b, 0x24, 0x49, 0x92, 0x29, 0x04, 0x50, 0x09, 0x24, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
	0x04, 0x09, 0x02, 0x04, 0x09, 0x02, 0x05, 0x0a, 0x01, 0x00, 0x04, 0x00, 0x00, 0x09, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
	0xbe, 0x40, 0x14, 0xea, 0x04, 0x10, 0x2a, 0x04, 0x28, 0x40, 0x40, 0x84, 0x50, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x92,
	0x25, 0xca, 0x11, 0x6a, 0x80, 0x28, 0x90, 0x20, 0xc8, 0x05, 0x52, 0x05, 0x52, 0x05, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x80, 0x40, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11,
	0x44, 0xaa, 0x00, 0x55, 0x00, 0x80, 0x00, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x04, 0x0a, 0x41, 0x04, 0xa2, 0x08, 0x50, 0x02, 0xa8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x80, 0x00, 0xc0, 0xa4, 0x41, 0xc0, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50,
	0x8a, 0x30, 0xc8, 0x10, 0xee, 0x13, 0xec, 0x13, 0xee, 0x00, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x8a, 0x20, 0x00, 0x8a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x00, 0x0a, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x94,
	0x68, 0x14, 0xc2, 0x3c, 0x40, 0x14, 0x48, 0x32, 0x04, 0xa0, 0x88, 0x80, 0x28, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x54,
	0xa3, 0x1c, 0xe2, 0x15, 0x40, 0xb0, 0x00, 0x50, 0xa0, 0x0a, 0x02, 0x0c, 0x03, 0x04, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0xc0, 0x01, 0x80, 0x41, 0x80, 0x00, 0x41, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48,
	0xb7, 0x48, 0x22, 0x5d, 0x00, 0x02, 0x05, 0x00, 0x05, 0xa8, 0x48, 0xb0, 0x4a, 0xb0, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12,
	0x04, 0x19, 0x02, 0x0d, 0x10, 0x05, 0x12, 0x04, 0x19, 0x00, 0x0a, 0x00, 0x0a, 0x00, 0x00, 0x00
};
// 'Untitled-2', 32x128px
static const char epd_bitmap_Untitled_2 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xb8, 0x68, 0xb8, 0x10, 0x28, 0x18, 0xe0, 0x58, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xdf, 0xb6, 0xef, 0x08, 0x86, 0x04, 0xaf, 0x9b, 0x6f, 0x00, 0x20, 0x10, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x03, 0x02, 0x01, 0x01, 0x02, 0x03, 0x03, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xc0,
	0x10, 0xa8, 0x3a, 0x29, 0x06, 0x01, 0x06, 0x21, 0x0a, 0x54, 0xc0, 0x00, 0xe0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00,
	0x05, 0x7a, 0x50, 0x35, 0x80, 0x40, 0x00, 0x70, 0x55, 0x30, 0x0e, 0x05, 0x0a, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x40, 0xa0, 0x40, 0x01, 0x42, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x6d, 0x92, 0x6d, 0x00, 0x20, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x45, 0x1a, 0x25, 0x52, 0x24, 0x5a, 0x20, 0x50, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xba, 0x55, 0xb8, 0x17, 0x2c, 0x1a, 0xb5, 0x3c, 0xe9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05,
	0x02, 0x80, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x08, 0x01, 0x04, 0x02, 0x04, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xde, 0xb5, 0x6c, 0x14, 0x01, 0x0a, 0xb4, 0x5c, 0x94, 0x20, 0xc0, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xff, 0xa2, 0xdf, 0x40, 0xc0, 0x80, 0x2c, 0x19, 0x32, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x81, 0x80, 0x81, 0x20, 0x41, 0x10, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x58,
	0xc4, 0x13, 0x8a, 0x25, 0x02, 0x00, 0x01, 0x02, 0x92, 0x01, 0xec, 0x50, 0xac, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x27, 0x08, 0x27, 0x18, 0x28, 0x30, 0x15, 0x0a, 0x15, 0x00, 0x02, 0x04, 0x00, 0x00, 0x00
};
// 'Untitled-1', 32x128px
static const char epd_bitmap_Untitled_1 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xf8, 0xf8, 0x18, 0x18, 0x18, 0x18, 0xf8, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xff, 0xff, 0x04, 0x0c, 0x0c, 0x06, 0x0f, 0x9f, 0xfc, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
    0xf0, 0xf8, 0x1c, 0x0e, 0x06, 0x06, 0x06, 0x06, 0x0c, 0xb8, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x0f, 0x3f, 0x70, 0xc0, 0xc0, 0x80, 0xc0, 0xc0, 0x60, 0x7f, 0x1f, 0x07, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x40, 0xc0, 0xc0, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xff, 0xff, 0xd8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x1d, 0x1f, 0x1e, 0x30, 0x18, 0x10, 0x18, 0x18, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x80, 0xe0, 0xf8, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0xe0, 0x7c, 0x1f, 0x33, 0x30, 0x1f, 0x3f, 0xfc, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
    0x03, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x06, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x02, 0xfe, 0xfe, 0x06, 0x06, 0x06, 0x06, 0x1c, 0x3c, 0xf8, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0x60, 0x30, 0x3f, 0x1f, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x81, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30,
    0xfe, 0xff, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf7, 0xfe, 0xf8, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x07, 0x0e, 0x18, 0x18, 0x30, 0x18, 0x18, 0x0c, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'Untitled-1', 32x128px
const  char* epd_bitmap_allArray[] = {
	epd_bitmap_Untitled_1,
	epd_bitmap_Untitled_2,
	epd_bitmap_Untitled_3,
	epd_bitmap_Untitled_4,
	epd_bitmap_Untitled_5,
	epd_bitmap_Untitled_6,
	epd_bitmap_Untitled_7,
	epd_bitmap_Untitled_8
};

    // Frame sizes array
    uint16_t frame_sizes[8] = {
        sizeof(epd_bitmap_Untitled_1),
        sizeof(epd_bitmap_Untitled_2),
        sizeof(epd_bitmap_Untitled_3),
        sizeof(epd_bitmap_Untitled_4),
        sizeof(epd_bitmap_Untitled_5),
        sizeof(epd_bitmap_Untitled_6),
        sizeof(epd_bitmap_Untitled_7),
        sizeof(epd_bitmap_Untitled_8)
    };

    // Run animation
   if (timer_elapsed(timer) > (current_frame == 0 ? 1000 : FRAME_DURATION)) {
    // Set timer to updated time
    timer = timer_read();

    // Increment or decrement frame based on direction
    current_frame += direction;

    // Get array size
    int array_size = sizeof(epd_bitmap_allArray) / sizeof(epd_bitmap_allArray[0]);

    // Check if we've reached the end or the beginning of the array
    if (current_frame >= array_size) {
        // We've reached the end, reverse direction
        direction = -1;
        // Set to last valid index
        current_frame = array_size - 2;
    } else if (current_frame < 1) {
        // We've reached the beginning, reverse direction
        direction = 1;
        // Set to first index
        current_frame = 0;
    }

    // Draw frame to OLED
    oled_write_raw_P(epd_bitmap_allArray[current_frame], frame_sizes[current_frame]);
}
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    if (is_keyboard_master()) {
        render_animation();
    } else {
        oled_render_logo();
    }
    return false;
}

#endif // OLED_ENABLE
