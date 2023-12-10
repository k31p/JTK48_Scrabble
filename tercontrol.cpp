#include "tercontrol.h"

#ifdef _WIN32

HANDLE hConsole = INVALID_HANDLE_VALUE, hAlternateScreen = INVALID_HANDLE_VALUE;
CONSOLE_SCREEN_BUFFER_INFO csbi;
CONSOLE_CURSOR_INFO cci;

char *tc_color_id(uint8_t cid, int l){ 
    // "l" flag is ignored, just to make it compatible with the POSIX version
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (cid / 16) << 4 | (cid % 16));
	return "";
}

#else

char *tc_color_id(uint8_t cid, int l)
{

	char *esc;
	if (!l)
	{
		asprintf(&esc, "\x1B[48;5;%dm", cid);
	}
	else
	{
		asprintf(&esc, "\x1B[38;5;%dm", cid);
	}
	return esc;
}

char *tc_rgb(int r, int g, int b, int l)
{
	char *esc;
	if (!l)
	{
		asprintf(&esc, "\x1B[48;2;%d;%d;%dm", r, g, b);
	}
	else
	{
		asprintf(&esc, "\x1B[38;2;%d;%d;%dm", r, g, b);
	}
	return esc;
}

#endif

#ifdef _WIN32 

void tc_hide_cursor()
{
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &cci);
}
void tc_show_cursor()
{
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	cci.bVisible = TRUE;
	SetConsoleCursorInfo(hConsole, &cci);
}

void tc_enter_alt_screen()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	hAlternateScreen = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hAlternateScreen);
	SetStdHandle(STD_OUTPUT_HANDLE, hAlternateScreen);
}

void tc_exit_alt_screen()
{
	if (hConsole == INVALID_HANDLE_VALUE)
	{
		return;
	}
	SetConsoleActiveScreenBuffer(hConsole);
	CloseHandle(hAlternateScreen);
	SetStdHandle(STD_OUTPUT_HANDLE, hConsole);
}

void tc_echo_off() // Not intended for user use
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD old_mode;
	GetConsoleMode(hConsole, &old_mode);
	SetConsoleMode(hConsole, old_mode & (~ENABLE_ECHO_INPUT));
}
void tc_echo_on()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD old_mode;
	GetConsoleMode(hConsole, &old_mode);
	SetConsoleMode(hConsole, old_mode | ENABLE_ECHO_INPUT);
}

void tc_canon_on()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD old_mode;
	GetConsoleMode(hConsole, &old_mode);
	SetConsoleMode(hConsole, old_mode | ENABLE_ECHO_INPUT);
}

void tc_canon_off()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD old_mode;
	GetConsoleMode(hConsole, &old_mode);
	SetConsoleMode(hConsole, old_mode & (~ENABLE_ECHO_INPUT));
}

void tc_clear_partial(int x, int y, int width, int height) // Clears a section of the screen
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	COORD homeCoords = {x, y};

	if (hConsole == INVALID_HANDLE_VALUE)
	{
		return;
	}

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}
	for (int i = 0; i < height; i++)
	{
		FillConsoleOutputCharacter(hConsole, ' ', width, homeCoords, &count);
		FillConsoleOutputAttribute(hConsole, csbi.wAttributes, width, homeCoords, &count);

		homeCoords.Y++;
	}
	homeCoords.Y = y;
	SetConsoleCursorPosition(hConsole, homeCoords);
	return;
}

void tc_get_cursor(int *x, int *y)
{
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	*x = csbi.dwCursorPosition.X;
	*y = csbi.dwCursorPosition.Y;
}
void tc_set_cursor(int x, int y)
{
	COORD pos = {x, y};
	SetConsoleCursorPosition(hConsole, pos);
}

void tc_move_cursor(int x, int y)
{
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	int cur_x = csbi.dwCursorPosition.X + x;
	int cur_y = csbi.dwCursorPosition.Y + y;
	if (cur_x < 0)
	{
		cur_x = 0;
	}
	if (cur_y < 0)
	{
		cur_y = 0;
	}
	COORD pos = {cur_x, cur_y};
	SetConsoleCursorPosition(hConsole, pos);

}

void tc_clear_screen()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	DWORD written;
	DWORD bufSize = csbi.dwSize.X * csbi.dwSize.Y;
	COORD homeCoords = {0, 0}; // Home coordinates
	FillConsoleOutputCharacter(hConsole, ' ', bufSize, homeCoords, &written);
}

void tc_clear_entire_line()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	tc_clear_partial(0, csbi.dwCursorPosition.Y, csbi.dwSize.X, 1);
}

void tc_clear_line_till_cursor()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	tc_clear_partial(0, csbi.dwCursorPosition.Y, csbi.dwCursorPosition.X, 1);
}

void tc_clear_line_from_cursor()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	tc_clear_partial(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y, csbi.dwSize.X, 1);
}

void tc_clear_from_top_to_cursor()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	tc_clear_partial(0, 0, csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
}

void tc_clear_from_cursor_to_bottom()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	tc_clear_partial(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y, csbi.dwSize.X, csbi.dwSize.Y - csbi.dwCursorPosition.Y);
}

void tc_print(const char *s)
{
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), s, strlen(s), NULL, NULL);
}

int tc_getch()
{
	int ch = _getch();
	if(ch == 0 || ch == 0xE0)
	{
		ch += 255;
	}
	return ch;
}

#else 

void tc_echo_off()
{
	struct termios term;
	tcgetattr(1, &term);
	term.c_lflag &= ~ECHO;
	tcsetattr(1, TCSANOW, &term);
}

void tc_echo_on()
{
	struct termios term;
	tcgetattr(1, &term);
	term.c_lflag |= ECHO;
	tcsetattr(1, TCSANOW, &term);
}

void tc_canon_on()
{
	struct termios term;
	tcgetattr(1, &term);
	term.c_lflag |= ICANON;
	tcsetattr(1, TCSANOW, &term);
}

void tc_canon_off()
{
	struct termios term;
	tcgetattr(1, &term);
	term.c_lflag &= ~ICANON;
	tcsetattr(1, TCSANOW, &term);
}

void tc_get_cursor(int *x, int *y)
{
	tc_echo_off();
	tc_canon_off();
	printf("\033[6n");
	scanf("\033[%d;%dR", x, y);
}

void tc_move_cursor(int x, int y)
{
	if (x > 0)
	{
		printf("\033[%dC", x);
	}
	else if (x < 0)
	{
		printf("\033[%dD", (x * -1));
	}

	if (y > 0)
	{
		printf("\033[%dB", y);
	}
	else if (y < 0)
	{
		printf("\033[%dA", (y * -1));
	}
}

void tc_clear_partial(int x, int y, int width, int height)
{
	char *buf = (char *)calloc(width + 1, 1);
	memset(buf, 32, width);
	tc_set_cursor(x, y);
	for (int i = 0; i < height; i++)
	{
		tc_set_cursor(x, y + i);
		fwrite(buf, width, 1, stdout);
	}
	free(buf);
}

void tc_print(const char *s)
{
	fprintf(stdout, "%s", s);
}

int tc_getch() // TODO: Implement this
{
	struct termios oldattr, newattr;
  int ch;
  tcgetattr(STDIN_FILENO, &oldattr );
  newattr = oldattr;
  newattr.c_lflag &= ~( ICANON | ECHO );
  tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
  ch = getchar();
  tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
  return ch;
}

#endif

void tc_get_cols_rows(int *cols, int *rows)
{
#ifdef _WIN32

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	*cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	*rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
	struct winsize size;
	ioctl(1, TIOCGWINSZ, &size);
	*cols = size.ws_col;
	*rows = size.ws_row;
#endif
}