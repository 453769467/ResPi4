//
//  GPIO registers from C-code on the Raspberry-Pi 4
//  Example program
//  Nov 04, 2020
//  Michael Chen
//  Revised: date

// Access from ARM Running Linux

#include <assert.h>

#define GPIO_BASE                0x7E215000 /* GPIO controller for BCM2711 on page 83, Register view */

// I/O access
volatile unsigned *gpio;

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

// only for GPIO 0 to 31
#define GPIO_SET(g) *(gpio+0x1C) |= (g<<1)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR(g) *(gpio+0x28) |= (g<<1)// clears bits which are 1 ignores bits which are 0

// only for GPIO 0 to 31
#define GET_GPIO(g) (*(gpio+0x34)&(1<<g)) // 0 if LOW, (1<<g) if HIGH

#define GPIO_PULL_N_Res(g,a) *(gpio+0xE4+((g/16)*4)) &= ~(0x3<<(g*2)) // No resistor is selected
#define GPIO_PULL_UP(g,a) do {GPIO_PULL_N_Res(g,a); *(gpio+0xE4+((g/16)*4)) |= (0x01 <<(g*2)); }while(0) // Pull up resistor is selected
#define GPIO_PULL_DOWN(g,a) do {GPIO_PULL_N_Res(g,a); *(gpio+0xE4+((g/16)*4)) |= (0x02 <<(g*2)); }while(0) // Pull down resistor is selected

//#define GPIO_PULL *(gpio+37) // Pull up/pull down
//#define GPIO_PULLCLK0 *(gpio+38) // Pull up/pull down clock
