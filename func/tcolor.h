// https://en.wikipedia.org/wiki/ANSI_escape_code
#pragma once

#define TCLR_ESC           "\e["
#define TCLR_RESET         TCLR_ESC"0m"

#define TCLR_BOLD          TCLR_ESC"1m"
#define TCLR_FAINT         TCLR_ESC"2m"
#define TCLR_NORMAL        TCLR_ESC"22m"

#define TCLR_UNDERLINE     TCLR_ESC"4m"
#define TCLR_UNDERLINE_OFF TCLR_ESC"24m"

#define TCLR_FRAMED        TCLR_ESC"51m"
#define TCLR_ENCIRCLED     TCLR_ESC"22m"
#define TCLR_FRAMED_OFF    TCLR_ESC"54m"
#define TCLR_ENCIRCLED_OFF TCLR_ESC"54m"

// 8-bit 256 colors
#define TCLR_FG(n)    TCLR_ESC"38;5;"#n"m"
#define TCLR_BG(n)    TCLR_ESC"48;5;"#n"m"

// 24-bit
#define TCLR_FG_RGB(r,g,b)  TCLR_ESC"38;2;"#r";"#g";"#b"m"
#define TCLR_BG_RGB(r,g,b)  TCLR_ESC"48;2;"#r";"#g";"#b"m"

#define TCLR_RED      TCLR_FG(1)

