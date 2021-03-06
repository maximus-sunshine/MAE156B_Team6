/*****************************************************************
 * ---------------------------------------------------------------
 * ARMOR Lab @UC San Diego, Kenneth Loh Ph.D
 * 
 * MAE 156B Spring 2018 Team 6: Warfighter Protection
 *  - Maxwell Sun       (maxsun96@gmail.com)
 *  - Jacob Rutheiser   (jrutheiser@gmail.com)
 *  - Matthew Williams  (mwilliams31243@gmail.com)
 *  - Aaron Gunn        (gunnahg@gmail.com)
 * ---------------------------------------------------------------
 * 
 * UI.c
 * 
 * Function Library for UI
 ********************************************************************/
 
/*******************************************************************************
* INCLUDES
*******************************************************************************/
#include "../includes/UI.h"

/************************************************************************************
* FUNCTIONS
*************************************************************************************/

/* OLED FUNCTIONS */
void display_bitmap()
{
    drawBitmap(0, 0,  ARMOR_Logo_128_64_bmp, 128, 64, 1);
}

void printCenter(const unsigned char *text, int size)
{
    int charcount = strlen(text);
    int pad = 5;

    int x1 = (SSD1306_LCDWIDTH - 6*size*charcount)/2 + 1;
    int x2 = (SSD1306_LCDWIDTH + 6*size*charcount)/2 - 1;

    int y1 = (SSD1306_LCDHEIGHT - 8*size)/2 + 1;
    int y2 = (SSD1306_LCDHEIGHT + 8*size)/2 - 1;

    fillRect(12,y1 - pad,SSD1306_LCDWIDTH - 12*2,(y2 - y1) + 2*pad,BLACK);
    setTextSize(size);
    setTextColor(WHITE);
    setCursor(x1,y1);
    print_str(text);
}

void printCenterX(const unsigned char *text, int y1, int size)
{
    int charcount = strlen(text);

    int x1 = (SSD1306_LCDWIDTH - 6*size*charcount)/2 + 1;

    setTextSize(size);
    setTextColor(WHITE);
    setCursor(x1,y1);
    print_str(text);
}

void printCenterY(const unsigned char *text, int x1, int size)
{
    int charcount = strlen(text);

    int y1 = (SSD1306_LCDHEIGHT - 8*size)/2 + 1;

    setTextSize(size);
    setTextColor(WHITE);
    setCursor(x1,y1);
    print_str(text);
}

void printRight(const unsigned char *text, int y1, int size)
{
    int charcount = strlen(text);
    int x1 = SSD1306_LCDWIDTH - 6*size*charcount;

    setTextSize(size);
    setTextColor(WHITE);
    setCursor(x1,y1);
    print_str(text);
}

void printLeft(const unsigned char *text, int y1, int size)
{
    int charcount = strlen(text);
    int x1 = 1;

    setTextSize(size);
    setTextColor(WHITE);
    setCursor(x1,y1);
    print_str(text);
}

void printMenuCenterSelect(const unsigned char *text, int size)
{
    int charcount = strlen(text);
    int pad = 5;

    int x1 = (SSD1306_LCDWIDTH - 6*size*charcount)/2 + 1;
    int x2 = (SSD1306_LCDWIDTH + 6*size*charcount)/2 - 1;

    int y1 = (SSD1306_LCDHEIGHT - 8*size)/2 + 1;
    int y2 = (SSD1306_LCDHEIGHT + 8*size)/2 - 1;

    fillRect(12,y1 - pad,SSD1306_LCDWIDTH - 12*2,(y2 - y1) + 2*pad,BLACK);
    fillRect(x1 - pad,y1 - pad,(x2 - x1) + 2*pad,(y2 - y1) + 2*pad,WHITE);
    setTextSize(size);
    setTextColor(INVERSE);
    setCursor(x1,y1);
    print_str(text);
}

void prevSelect()
{
    int pad = 2;
    int size = 2;

    int x1 = 1;
    int x2 = 12;

    int y1 = (SSD1306_LCDHEIGHT - 8*size)/2 + 1;
    int y2 = (SSD1306_LCDHEIGHT + 8*size)/2 - 1;

    fillRect(x1,y1-pad,12,(y2 - y1) + 2*pad,BLACK);

    fillRect(x1,y1-pad,12,(y2 - y1) + 2*pad,WHITE);

    setTextSize(size);
    setTextColor(INVERSE);
    setCursor(x1,y1);
    print_str("<");
    Display();
    usleep(0.1*1e6);

    fillRect(x1,y1-pad,12,(y2 - y1) + 2*pad,BLACK);
    setTextSize(size);
    setTextColor(WHITE);
    setCursor(x1,y1);
    print_str("<");
    Display();
}

void nextSelect()
{
    int pad = 2;
    int size = 2;

    int x1 = SSD1306_LCDWIDTH-12-1;
    int x2 = SSD1306_LCDWIDTH;

    int y1 = (SSD1306_LCDHEIGHT - 8*size)/2 + 1;
    int y2 = (SSD1306_LCDHEIGHT + 8*size)/2 - 1;

    fillRect(x1,y1-pad,12,(y2 - y1) + 2*pad,BLACK);

    fillRect(x1,y1-pad,12,(y2 - y1) + 2*pad,WHITE);

    setTextSize(size);
    setTextColor(INVERSE);
    setCursor(x1,y1);
    print_str(">");
    Display();
    usleep(0.1*1e6);

    fillRect(x1,y1-pad,12,(y2 - y1) + 2*pad,BLACK);
    setTextSize(size);
    setTextColor(WHITE);
    setCursor(x1,y1);
    print_str(">");
    Display();
}

void backSelect()
{
    int pad = 2;
    int size = 2;

    int x1 = SSD1306_LCDWIDTH-12;
    int x2 = SSD1306_LCDWIDTH;

    int y1 = (SSD1306_LCDHEIGHT - 8*size)/2 + 1;
    int y2 = (SSD1306_LCDHEIGHT + 8*size)/2 - 1;

    fillRect(x1,y1-pad,12,(y2 - y1) + 2*pad,BLACK);

    fillRect(x1,y1-pad,12,(y2 - y1) + 2*pad,WHITE);

    setTextSize(size);
    setTextColor(INVERSE);
    setCursor(x1,y1);
    print_str(">");
    Display();
    usleep(0.1*1e6);

    fillRect(x1,y1-pad,12,(y2 - y1) + 2*pad,BLACK);
    setTextSize(size);
    setTextColor(WHITE);
    setCursor(x1,y1);
    print_str(">");
    Display();
}

void printBattery(float batt)
{  
    setTextSize(1);
    setTextColor(WHITE);

    if(batt >= 100){
        int charcount = 6;
        int x1 = SSD1306_LCDWIDTH - 6*charcount - 1;
        setCursor(x1,1);
        printFloat(batt,1);
        print_str("%"); 
    }
    else if(batt >= 10 && batt < 100){
        int charcount = 5;
        int x1 = SSD1306_LCDWIDTH - 6*charcount - 1;
        setCursor(x1,1);
        printFloat(batt,1);
        print_str("%"); 
    }
    else{
        int charcount = 4;
        int x1 = SSD1306_LCDWIDTH - 6*charcount - 1;
        setCursor(x1,1);
        printFloat(batt,1);
        print_str("%"); 
    }
}

void printUI(state_t state, const char opt_list[][OPT_STR_LEN])
{
    char MENU_OPTS[8][OPT_STR_LEN] = {"HOME","SETTINGS","NODES","CURRENT","CONFIG","MODE","TIME","CYCLES"};

    int center = mod(state.index,state.len);
    int left = mod((state.index-1),state.len);
    int right = mod((state.index+1),state.len);

    clearDisplay();
    printCenter(opt_list[center],2);
    printLeft(MENU_OPTS[state.menu],1,1); //TODO
    printBattery(state.batt);
    printLeft(opt_list[left],SSD1306_LCDHEIGHT-9,1);
    printRight(opt_list[right],SSD1306_LCDHEIGHT-9,1);
    printCenterY("<",1,2);
    printCenterY(">",SSD1306_LCDWIDTH-12-1,2);
    Display();
}

void print_sample_screen(){
    clearDisplay();
    printCenter("SAMPLING",2);
    Display();
}

void mainSelect(state_t state, const char opt_list[][OPT_STR_LEN])
{
    int center = mod(state.index,state.len);

    printMenuCenterSelect(opt_list[center],2);
    Display();
    usleep(0.1*1e6);

    printCenter(opt_list[center],2);
    Display();
}

/* USER BUTTON FUNCTIONS */
int gpio_export(unsigned int gpio)
{
        int fd, len;
        char buf[MAX_BUF];
 
        fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
        if (fd < 0) {
                perror("gpio/export");
                return fd;
        }
 
        len = snprintf(buf, sizeof(buf), "%d", gpio);
        write(fd, buf, len);
        close(fd);
 
        return 0;
}

int gpio_unexport(unsigned int gpio)
{
        int fd, len;
        char buf[MAX_BUF];
 
        fd = open(SYSFS_GPIO_DIR "/unexport", O_WRONLY);
        if (fd < 0) {
                perror("gpio/export");
                return fd;
        }
 
        len = snprintf(buf, sizeof(buf), "%d", gpio);
        write(fd, buf, len);
        close(fd);
        return 0;
}

int gpio_set_dir(unsigned int gpio, unsigned int out_flag)
{
        int fd, len;
        char buf[MAX_BUF];
 
        len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%d/direction", gpio);
 
        fd = open(buf, O_WRONLY);
        if (fd < 0) {
                perror("gpio/direction");
                return fd;
        }
 
        if (out_flag)
                write(fd, "out", 4);
        else
                write(fd, "in", 3);
 
        close(fd);
        return 0;
}

int gpio_set_value(unsigned int gpio, unsigned int value)
{
        int fd, len;
        char buf[MAX_BUF];
 
        len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);
 
        fd = open(buf, O_WRONLY);
        if (fd < 0) {
                perror("gpio/set-value");
                return fd;
        }
 
        if (value)
                write(fd, "1", 2);
        else
                write(fd, "0", 2);
 
        close(fd);
        return 0;
}

int gpio_get_value(unsigned int gpio, unsigned int *value)
{
        int fd, len;
        char buf[MAX_BUF];
        char ch;

        len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);
 
        fd = open(buf, O_RDONLY);
        if (fd < 0) {
                perror("gpio/get-value");
                return fd;
        }
 
        read(fd, &ch, 1);

        if (ch != '0') {
                *value = 1;
        } else {
                *value = 0;
        }
 
        close(fd);
        return 0;
}

int gpio_set_edge(unsigned int gpio, char *edge)
{
        int fd, len;
        char buf[MAX_BUF];

        len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/edge", gpio);
 
        fd = open(buf, O_WRONLY);
        if (fd < 0) {
                perror("gpio/set-edge");
                return fd;
        }
 
        write(fd, edge, strlen(edge) + 1); 
        close(fd);
        return 0;
}

int gpio_fd_open(unsigned int gpio)
{
        int fd, len;
        char buf[MAX_BUF];

        len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);
 
        fd = open(buf, O_RDONLY | O_NONBLOCK );
        if (fd < 0) {
                perror("gpio/fd_open");
        }
        return fd;
}

int gpio_fd_close(int fd)
{
        return close(fd);
}
