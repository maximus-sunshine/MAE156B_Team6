/*****************************************************************
 * ---------------------------------------------------------------
 * ARMOR Lab @UC San Diego, Kenneth Loh Ph.D
 * 
 * MAE 156B Spring 2018 Team 6: Warfighter Protection
 * 	- Maxwell Sun		(maxsun96@gmail.com)
 *	- Jacob Rutheiser	(jrutheiser@gmail.com)
 *	- Matthew Williams	(mwilliams31243@gmail.com)
 *	- Aaron Gunn		(gunnahg@gmail.com)
 * ---------------------------------------------------------------
 * 
 * UI.h
 * 
 * Header file for the EIT device's user interface
 ********************************************************************/

#ifndef UI_H
#define UI_H

/*******************************************************************************
* INCLUDES/EXTERNS
*******************************************************************************/
/* Lib Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <signal.h>
#include <pthread.h>

/* Header Files */
#include "I2C.h"
#include "SSD1306_OLED.h"
#include "gpiolib.h"

/* Externs - I2C.c */
extern I2C_DeviceT I2C_DEV_2;

/*******************************************************************************
* ENUMS/DEFINES/VARIABLES
*******************************************************************************/
#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define POLL_TIMEOUT (3 * 1000) /* 3 seconds */
#define OPT_STR_LEN 15   
#define MAX_BUF 64
#define mod(a,b) (a%b+b)%b

/************************************************************************************
* STRUCTS
*************************************************************************************/

typedef struct state_t{
    int menu;
    int back;
    int index;
    int prev_index;
    int len; 
    float batt;
    int system;
} state_t;

/*******************************************************************************
* ARMOR LOGO BITMAP
*******************************************************************************/
//ARMOR Lab logo 128x64
static const unsigned char ARMOR_Logo_128_64_bmp[] =
{
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xff, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xff, 0xe0, 0x0, 0xc, 0x0, 0xf, 
0xe0, 0x1, 0xc0, 0x1c, 0x0, 0xfc, 0x0, 0x7f, 0x80, 0xf, 0xff, 0xf8, 0x0, 0xe, 0x0, 
0x1f, 0xf8, 0x1, 0xc0, 0x1c, 0x1, 0xfe, 0x0, 0x7f, 0xe0, 0x7, 0xff, 0xf0, 0x0, 0xe, 
0x0, 0x1c, 0x1c, 0x1, 0xc0, 0x3c, 0x3, 0x87, 0x0, 0x70, 0xf0, 0x3, 0xff, 0xc0, 0x0, 
0x1e, 0x0, 0x18, 0xe, 0x1, 0xe0, 0x3c, 0x7, 0x3, 0x80, 0x60, 0x30, 0x10, 0xff, 0x4, 
0x0, 0x1f, 0x0, 0x18, 0x6, 0x1, 0xe0, 0x3c, 0x6, 0x1, 0x80, 0x60, 0x18, 0x10, 0x3e, 
0xc, 0x0, 0x1f, 0x0, 0x18, 0x6, 0x1, 0xe0, 0x7c, 0x6, 0x1, 0x80, 0x60, 0x18, 0x18, 
0x8, 0xc, 0x0, 0x3b, 0x0, 0x18, 0x6, 0x1, 0xf0, 0x6c, 0x6, 0x1, 0x80, 0x60, 0x18, 
0x18, 0x0, 0xc, 0x0, 0x33, 0x0, 0x18, 0xe, 0x1, 0xb0, 0x6c, 0x6, 0x1, 0x80, 0x60, 
0x38, 0x1c, 0x0, 0x1c, 0x0, 0x31, 0x80, 0x1c, 0x1c, 0x1, 0xb0, 0xcc, 0x6, 0x1, 0x80, 
0x70, 0x70, 0x1c, 0x0, 0x1c, 0x0, 0x71, 0x80, 0x1f, 0xfc, 0x1, 0x98, 0xcc, 0x6, 0x1, 
0x80, 0x7f, 0xf0, 0x1c, 0x0, 0x3c, 0x0, 0x61, 0x80, 0x1f, 0xfc, 0x1, 0x98, 0xcc, 0x6, 
0x1, 0x80, 0x7f, 0xf0, 0x1e, 0x0, 0x3c, 0x0, 0x60, 0xc0, 0x1c, 0xc, 0x1, 0x98, 0xcc, 
0x6, 0x1, 0x80, 0x60, 0x70, 0x1e, 0x0, 0x7c, 0x0, 0x60, 0xc0, 0x18, 0xe, 0x1, 0x99, 
0x8c, 0x6, 0x1, 0x80, 0x60, 0x38, 0x1f, 0x0, 0x7c, 0x0, 0xc0, 0xc0, 0x18, 0x6, 0x1, 
0x8d, 0x8c, 0x6, 0x1, 0x80, 0x60, 0x18, 0x1f, 0x0, 0xfc, 0x0, 0xc0, 0xe0, 0x18, 0x6, 
0x1, 0x8f, 0x8c, 0x6, 0x1, 0x80, 0x60, 0x18, 0x1f, 0x80, 0xfc, 0x0, 0xc0, 0x60, 0x18, 
0x6, 0x1, 0x8f, 0xc, 0x7, 0x3, 0x80, 0x60, 0x18, 0x1f, 0x81, 0xfc, 0x1, 0xc0, 0x60, 
0x18, 0x6, 0x1, 0x87, 0xc, 0x3, 0x3, 0x0, 0x60, 0x18, 0xf, 0xc1, 0xf8, 0x1, 0x80, 
0x70, 0x18, 0x6, 0x1, 0x87, 0xc, 0x3, 0xff, 0x0, 0x60, 0x18, 0x3, 0xc3, 0xe0, 0x1, 
0x80, 0x30, 0x18, 0x6, 0x1, 0x86, 0xc, 0x0, 0xfc, 0x0, 0x60, 0x18, 0x0, 0xe3, 0x80, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x62, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0,
};

/************************************************************************************
* FUNCTION DECLARATIONS
*************************************************************************************/

/* OLED FUNCTIONS */

/****************************************************************************
* void display_bitmap()
*
* Prints ARMOR logo
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
void display_bitmap();

/****************************************************************************
* void printCenter(const unsigned char *text, int size)
*
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
void printCenter(const unsigned char *text, int size);

/****************************************************************************
* void printCenterX(const unsigned char *text, int y1, int size)
*
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
void printCenterX(const unsigned char *text, int y1, int size);

/****************************************************************************
* void printCenterY(const unsigned char *text, int x1, int size)
*
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
void printCenterY(const unsigned char *text, int x1, int size);

/****************************************************************************
* void printRight(const unsigned char *text, int y1, int size)
*
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
void printRight(const unsigned char *text, int y1, int size);

/****************************************************************************
* void printLeft(const unsigned char *text, int y1, int size)
*
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
void printLeft(const unsigned char *text, int y1, int size);

/****************************************************************************
* void printMenuCenterSelect(const unsigned char *text, int size)
*
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
void printMenuCenterSelect(const unsigned char *text, int size);

/****************************************************************************
* void prevSelect()
* 
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
void prevSelect();

/****************************************************************************
* void nextSelect()
*
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
void nextSelect();

/****************************************************************************
* void backSelect()
*
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
void backSelect();

/****************************************************************************
* void printBattery(float batt)
*
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
void printBattery(float batt);

/****************************************************************************
* void printUI(state_t state, char opt_list[][OPT_STR_LEN])
*
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
void printUI(state_t state, const char opt_list[][OPT_STR_LEN]);

/****************************************************************************
* void print_sample_screen()
*
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
void print_sample_screen();

/****************************************************************************
* void mainSelect(state_t state, char opt_list[][OPT_STR_LEN])
*
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
void mainSelect(state_t state, const char opt_list[][OPT_STR_LEN]);

/* USER BUTTON FUNCTIONS */
/****************************************************************************
* int gpio_export(unsigned int gpio)
*
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
int gpio_export(unsigned int gpio);

/****************************************************************************
* int gpio_unexport(unsigned int gpio)
*
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
int gpio_unexport(unsigned int gpio);

/****************************************************************************
* vint gpio_set_dir(unsigned int gpio, unsigned int out_flag)
*
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
int gpio_set_dir(unsigned int gpio, unsigned int out_flag);

/****************************************************************************
* int gpio_set_value(unsigned int gpio, unsigned int value)
*
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
int gpio_set_value(unsigned int gpio, unsigned int value);

/****************************************************************************
* int gpio_get_value(unsigned int gpio, unsigned int *value)
*
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
int gpio_get_value(unsigned int gpio, unsigned int *value);

/****************************************************************************
* int gpio_set_edge(unsigned int gpio, char *edge)
*
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
int gpio_set_edge(unsigned int gpio, char *edge);

/****************************************************************************
* int gpio_fd_open(unsigned int gpio)
*
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
int gpio_fd_open(unsigned int gpio);

/****************************************************************************
* int gpio_fd_close(int fd)
*
* DESCRIPTION
*
* Inputs : 
* 
* Outputs: 
*****************************************************************************/
int gpio_fd_close(int fd);


#endif //UI_H