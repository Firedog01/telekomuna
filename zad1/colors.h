#ifndef COLORS_H_INCLUDED
#define COLORS_H_INCLUDED

///IMPORTANT!!! on windows you must use system("cls") on start of teh program!!!
#ifndef COLORS_OFF

/// STYLES
#define s_reset   "[0m" // Reset
#define s_bold    "[1m" // Bold
#define s_under   "[4m" // Underline
#define s_invers  "[7m" // Inverse

/// NORMAL FOREGROUND COLORS
#define f_black   "[30m" // Black
#define f_red     "[31m" // Red
#define f_green   "[32m" // Green
#define f_yellow  "[33m" // Yellow
#define f_blue    "[34m" // Blue
#define f_magenta "[35m" // Magenta
#define f_cyan    "[36m" // Cyan
#define f_white   "[37m" // White

/// NORMAL BACKGROUND COLORS
#define b_black   "[40m" // Black
#define b_red     "[41m" // Red
#define b_green   "[42m" // Green
#define b_yellow  "[43m" // Yellow
#define b_blue    "[44m" // Blue
#define b_magenta "[45m" // Magenta
#define b_cyan    "[46m" // Cyan
#define b_white   "[47m" // White

/// STRONG FOREGROUND COLORS
#define f_BLACK   "[90m" // Black
#define f_RED     "[91m" // Red
#define f_GREEN   "[92m" // Green
#define f_YELLOW  "[93m" // Yellow
#define f_BLUE    "[94m" // Blue
#define f_MAGENTA "[95m" // Magenta
#define f_CYAN    "[96m" // Cyan
#define f_WHITE   "[97m" // White

/// STRONG BACKGROUND COLORS
#define b_BLACK   "[100m" // Black
#define b_RED     "[101m" // Red
#define b_GREEN   "[102m" // Green
#define b_YELLOW  "[103m" // Yellow
#define b_BLUE    "[104m" // Blue
#define b_MAGENTA "[105m" // Magenta
#define b_CYAN    "[106m" // Cyan
#define b_WHITE   "[107m" // White
#else
#define s_reset   '\0'
    #define s_bold    '\0'
    #define s_under   '\0'
    #define s_invers  '\0'
    #define f_black   '\0'
    #define f_red     '\0'
    #define f_green   '\0'
    #define f_yellow  '\0'
    #define f_blue    '\0'
    #define f_magenta '\0'
    #define f_cyan    '\0'
    #define f_white   '\0'
    #define b_black   '\0'
    #define b_red     '\0'
    #define b_green   '\0'
    #define b_yellow  '\0'
    #define b_blue    '\0'
    #define b_magenta '\0'
    #define b_cyan    '\0'
    #define b_white   '\0'
    #define f_BLACK   '\0'
    #define f_RED     '\0'
    #define f_GREEN   '\0'
    #define f_YELLOW  '\0'
    #define f_BLUE    '\0'
    #define f_MAGENTA '\0'
    #define f_CYAN    '\0'
    #define f_WHITE   '\0'
    #define b_BLACK   '\0'
    #define b_RED     '\0'
    #define b_GREEN   '\0'
    #define b_YELLOW  '\0'
    #define b_BLUE    '\0'
    #define b_MAGENTA '\0'
    #define b_CYAN    '\0'
    #define b_WHITE   '\0'
#endif

#endif // COLORS_H_INCLUDED
