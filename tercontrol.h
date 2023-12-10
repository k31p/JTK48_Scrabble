/**********************************************************************************

	Basic Terminal Control Library
	Copyright 2022 Zackery Smith
	This library is released under the GPLv3 license

	This library has no dependencies other than the standard C runtime library

***********************************************************************************/
#ifndef TC_H
#define TC_H

#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#include <conio.h> // For _getch() function
HANDLE hConsole = INVALID_HANDLE_VALUE, hAlternateScreen = INVALID_HANDLE_VALUE; // WinAPI structures for console
CONSOLE_SCREEN_BUFFER_INFO csbi;
CONSOLE_CURSOR_INFO cci;
#else
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#endif
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef _WIN32
#define TC_NRM ""
#else
#define TC_NRM "\x1B[0m" /* Normalize color */
#endif

#define TC_RED "\x1B[1;31m" /* Red */
#define TC_GRN "\x1B[1;32m" /* Green */
#define TC_YEL "\x1B[1;33m" /* Yellow */
#define TC_BLU "\x1B[1;34m" /* Blue */
#define TC_MAG "\x1B[1;35m" /* Magenta */
#define TC_CYN "\x1B[1;36m" /* Cyan */
#define TC_WHT "\x1B[1;37m" /* White */

#define TC_B_NRM "\x1B[0m"	  /* Normalize Bright Color */
#define TC_B_RED "\x1B[0;31m" /* Bright Red */
#define TC_B_GRN "\x1B[0;32m" /* Bright Green */
#define TC_B_YEL "\x1B[0;33m" /* Bright Yellow */
#define TC_B_BLU "\x1B[0;34m" /* Bright Blue */
#define TC_B_MAG "\x1B[0;35m" /* Bright Magenta */
#define TC_B_CYN "\x1B[0;36m" /* Bright Cyan */
#define TC_B_WHT "\x1B[0;37m" /* Bright White */

#define TC_BG_NRM "\x1B[40m" /* Normalize Background Color */
#define TC_BG_RED "\x1B[41m" /* Background Red */
#define TC_BG_GRN "\x1B[42m" /* Background Green */
#define TC_BG_YEL "\x1B[43m" /* Background Yellow */
#define TC_BG_BLU "\x1B[44m" /* Background Blue */
#define TC_BG_MAG "\x1B[45m" /* Background Magenta*/
#define TC_BG_CYN "\x1B[46m" /* Background Cyan */
#define TC_BG_WHT "\x1B[47m" /* Background White */

// `asprintf` is usable on any POSIX-2008 compliant system (any modern Linux system)
// My compiler likes to complain about it.. Another way to preform this is with `vsprintf`
// Or maybe I'm just a bad programmer :I

#ifdef _WIN32

char *tc_color_id(uint8_t cid, int l);

#else

char *tc_color_id(uint8_t cid, int l);

//////////////////////////////////////////////////////////////////
//    WARNING: WinAPI doesn't natively support 24-bit colors    //
//    So this function is not available on Windows systems      //
//////////////////////////////////////////////////////////////////
char *tc_rgb(int r, int g, int b, int l);

#endif

//////////////////////////////////////
//   Additional formatting (ANSI)   //
//////////////////////////////////////

#define TC_BLD "\x1B[1m"  /* Bold */
#define TC_DIM "\x1B[2m"  /* Dim */
#define TC_ITAL "\x1B[3m" /* Standout (italics) */
#define TC_UNDR "\x1B[4m" /* Underline */
#define TC_BLNK "\x1B[5m" /* Blink */
#define TC_REV "\x1B[7m"  /* Reverse */
#define TC_INV "\x1B[8m"  /* Invisible */

//////////////////////////////////////

void tc_get_cols_rows(int *cols, int *rows);

//////////////////////////////
//   Common private modes   //
//////////////////////////////

#ifdef _WIN32

void tc_hide_cursor();
void tc_show_cursor();
void tc_enter_alt_screen();
void tc_exit_alt_screen();

#else

#define tc_hide_cursor() puts("\033[?25l")
#define tc_show_cursor() puts("\033[?25h")

/* These functions don't seem to be doing anything

	#define tc_save_screen() puts("\033[?47h")
	#define tc_restore_screen() puts("\033[?47l")

*/
#define tc_enter_alt_screen() puts("\033[?1049h\033[H")
#define tc_exit_alt_screen() puts("\033[?1049l")
#endif
//////////////////////////////

void tc_echo_off();
void tc_echo_on();

void tc_get_cols_rows(int *cols, int *rows);

#ifdef _WIN32
void tc_echo_off(); // Not intended for user use

void tc_echo_on();

void tc_canon_on();

void tc_canon_off();
void tc_clear_partial(int x, int y, int width, int height);

void tc_get_cursor(int *x, int *y);
void tc_set_cursor(int x, int y);

void tc_move_cursor(int x, int y);
void tc_clear_screen();

void tc_clear_entire_line();

void tc_clear_line_till_cursor();

void tc_clear_line_from_cursor();

void tc_clear_from_top_to_cursor();

void tc_clear_from_cursor_to_bottom();
void tc_print(const char *s);
int tc_getch();

#else

#define tc_clear_entire_line() puts("\x1B[2K")
#define tc_clear_line_till_cursor() puts("\x1B[1K")
#define tc_clear_line_from_cursor() puts("\x1B[0K")

void tc_echo_off();
void tc_echo_on();
void tc_canon_on();
void tc_canon_off();
void tc_get_cursor(int *x, int *y);
#define tc_set_cursor(x, y) printf("\033[%d;%dH", y,x)
void tc_move_cursor(int x, int y);

#define tc_clear_screen() puts("\x1B[2J")
#define tc_clear_from_top_to_cursor() puts("\x1B[1J")
#define tc_clear_from_cursor_to_bottom() puts("\x1B[0J")

void tc_clear_partial(int x, int y, int width, int height);

void tc_print(const char *s);

int tc_getch(); // TODO: Implement this

#endif
#endif