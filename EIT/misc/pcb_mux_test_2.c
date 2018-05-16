/* MAE 156B Team 6
* 
* Preliminary Mux Switching Test 2:
* 	-attempt to clean up code using loops instead of hard coding
* 
* User selects Current, GND, and Voltage nodes from command line
* 
* 4/30/18
*/

/************************************************************************************
* INCLUDES/DEFINES
*************************************************************************************/
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>		// for atoi
#include <fcntl.h>		// for open
#include <unistd.h>		// for close
#include <stdio.h>		
#include <string.h>
#include <errno.h>
 
#include <assert.h>		//for gpiolib stuff
#include <signal.h>
#include <sys/time.h>
#include "gpiolib.h"
#include "eit_config.h" //project specific setup stuff

#define MUX_PINS 5

// /************************************************************************************
// * SIGINT HANDLER, TODO: improve
// *************************************************************************************/
// void sigint(int s __attribute__((unused))) {
// 	printf("\nReceived SIGINT:\n");
// 	fflush(stdout);

// 	gpio_info *current_mux_gpio_info[MUX_PINS];
// 	gpio_info *ground_mux_gpio_info[MUX_PINS];
// 	gpio_info *voltage_mux_gpio_info[MUX_PINS];

// 	int i;
// 	for(i=0;i<MUX_PINS;i++){
// 		gpio_detach(current_mux_gpio_info[i]);
// 		gpio_detach(ground_mux_gpio_info[i]);
// 		gpio_detach(voltage_mux_gpio_info[i]);
// 	}
// 	gpio_finish();
// 	exit(0);
// }

/************************************************************************************
* SETUP
*************************************************************************************/

//mux array declarations
int current_mux[NODAL_NUM];              // current?                                           

int ground_mux[NODAL_NUM];               // ground?
int voltage_mux[NODAL_NUM][NODAL_NUM-2]; // voltage sampling?

// gpio pin IDs, used for exporting pins 
// gpio pin ID = gpio_bank*32 + gpio_pinmask (e.g. gpio 86 = gpio2_22 (86 = 2*32 + 22))
// mux channels {A4, A3, A2, A1, A0}
int current_mux_gpio[5] = CURRENT_MUX_GPIO;
int ground_mux_gpio[5]  = GROUND_MUX_GPIO;
int voltage_mux_gpio[5] = VOLTAGE_MUX_GPIO;

/************************************************************************************
* MAIN
*************************************************************************************/
int main(int argc, char **argv) {
	int i, bank, mask;
	printf("\nentered MAIN...\n");
	fflush(stdout);

	// //Sigint setup, needs work
	// signal(SIGINT, sigint);
	// printf("setup SIGINT...\n");
	// fflush(stdout);

	//initialize gpiolib
	if (gpio_init()) {
		fprintf(stderr, "gpio_init failed with %i\n", gpio_errno);
		exit(1);
	}
	printf("intialized gpiolib...\n");
	fflush(stdout);

	// TODO: Figure out arrays/pointers/structs
	gpio_info *current_mux_gpio_info[MUX_PINS];
	gpio_info *ground_mux_gpio_info[MUX_PINS];
	gpio_info *voltage_mux_gpio_info[MUX_PINS];

	for(i = 0; i < MUX_PINS; i++){
		current_mux_gpio_info[i] = malloc(sizeof(gpio_info));
		ground_mux_gpio_info[i] = malloc(sizeof(gpio_info));
		voltage_mux_gpio_info[i] = malloc(sizeof(gpio_info));
	}
	printf("setup structs \n");
	fflush(stdout);


	//Attach mux logic pins
	//Current
	for(i = 0; i < MUX_PINS; i++){                            
		printf("attaching current gpio%d_%d \n", current_mux_gpio[i]/32, current_mux_gpio[i]%32);
		fflush(stdout);
		bank = current_mux_gpio[i]/32;
		mask = bit(current_mux_gpio[i]%32);
		current_mux_gpio_info[i] = gpio_attach(bank, mask, GPIO_OUT);
	}	

	//Ground
	for(i = 0; i < MUX_PINS; i++){                            
		printf("attaching ground gpio%d_%d \n", ground_mux_gpio[i]/32, ground_mux_gpio[i]%32);
		fflush(stdout);
		bank = ground_mux_gpio[i]/32;
		mask = bit(ground_mux_gpio[i]%32);
		ground_mux_gpio_info[i] = gpio_attach(bank, mask, GPIO_OUT);
	}

	//Voltage
	for(i = 0; i < MUX_PINS; i++){                            
		printf("attaching voltage gpio%d_%d \n", voltage_mux_gpio[i]/32, voltage_mux_gpio[i]%32);
		fflush(stdout);
		bank = voltage_mux_gpio[i]/32;
		mask = bit(voltage_mux_gpio[i]%32);
		voltage_mux_gpio_info[i] = gpio_attach(bank, mask, GPIO_OUT);	
	}
	printf("attached mux logic pins...\n");
	fflush(stdout);

	//Parse input arguments
	int current_node = atoi(argv[1])-1;
	int ground_node = atoi(argv[2])-1;
	int voltage_node = atoi(argv[3])-1;
	printf("parsed input args. current node: %d, gnd node: %d, V node: %d...\n",current_node+1, ground_node+1, voltage_node+1);
	fflush(stdout);

	//Set and clear mux logic pins
	//Current
	for(i=0;i<MUX_PINS;i++){
		if(CHAN[current_node][i]==0){
			gpio_clear(current_mux_gpio_info[i]);
		}
		else{
			gpio_set(current_mux_gpio_info[i]);
		}
	}

	//Ground
	for(i=0;i<MUX_PINS;i++){
		if(CHAN[ground_node][i]==0){
			gpio_clear(ground_mux_gpio_info[i]);
		}
		else{
			gpio_set(ground_mux_gpio_info[i]);
		}
	}

	//Voltage
	for(i=0;i<MUX_PINS;i++){
		if(CHAN[voltage_node][i]==0){
			gpio_clear(voltage_mux_gpio_info[i]);
		}
		else{
			gpio_set(voltage_mux_gpio_info[i]);
		}
	}
	printf("set mux logic pins...\n");
	fflush(stdout);

	//Sleep
	int sleep_time = 10;
	printf("Sleeping...\n");
	fflush(stdout);
	usleep(sleep_time * 1000000);

	//Detach mux logic pins
	for(i=0;i<MUX_PINS;i++){
		gpio_detach(current_mux_gpio_info[i]);
		gpio_detach(ground_mux_gpio_info[i]);
		gpio_detach(voltage_mux_gpio_info[i]);
	}
	printf("detached mux logic pins...\n");
	fflush(stdout);

	//Finish up
	gpio_finish();
	printf("FINISHED!\n");
	fflush(stdout);
}

//FUCKK