/* Librairie nécéssaire */
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <linux/input.h>
#include <linux/joystick.h>
#include <math.h>
#include "serial.h"
#include "calculs.h"

#define FD_JOY "/dev/input/js0"
#define FD_SER "/dev/ttyUSB0"
#define CLEAR printf("\033c")

void triggerScale(unsigned short *trig){
	if (*trig >= 32769)
		*trig = *trig -32769;
	else
		*trig = *trig + 32768;
	return;
}

void axisScale(int *axes,int test){
	int deadzone = 3500;
	if (fabs(*axes) < deadzone){
		*axes = 0;
	}
	if (test == 1 || test == 4){ 
		*axes = (-*axes);
	}
	return;
}
char main (int argc, char **argv)
{
	int fd, i;
	unsigned char axes = 2;
	unsigned char buttons = 2;
	int *axis;
    unsigned short *trigger;
	signed short trigger_rot;
	char *button;
	unsigned char data[8];
	struct js_event js;
	VariablesPID dxPID, dyPID, rotPID;
	unsigned char j;
	double k = 1.0;
	signed char vOut[4]={0x55,0x55,0x55,0x55};
	int fdu;
	unsigned char end=0;
	unsigned char put = 0x55;
	signed short angleRobot;
	signed short vRotation = 0;
	signed short angleTemp;

	
	
	/* On vérifie que la manette est connectée */
	if ((fd = open(FD_JOY, O_RDONLY | O_NONBLOCK)) == -1) {
		perror("Controlleur");
		return 1;
	}

	// On vérifie que le periphérique pour la communication est connecté
	if ((fdu = serialport_init(FD_SER,115200)) == -1){
		printf("Veuillez vérifier qu'il y est une commnication série.\n");
		return 1;
	}

	axis = calloc(axes, sizeof(int));
	button = calloc(buttons, sizeof(char));
	trigger = calloc(axes, sizeof(unsigned short));

	initPID(&dxPID, k,k,k);
	initPID(&dyPID, k,k,k);
	initPID(&rotPID,k,k,k);

	CLEAR;

	printf ("\nAppuyer sur le bouton START ou SELECT pour passer à la suite de l'application.");
	printf ("\n\nSeul le joystick gauche de la manette permet de déplacer le robot.");
	printf ("\n\nLa gachette RT permet de faire une rotation à droite.");
	printf ("\n\nLa gachette LT permet de faire une rotation à gauche.");
	printf ("\n\nLa rotation finale est calculé à partir de ces deux rotations.");
	printf ("\n\nLa touche X permet de tirer.");
	printf ("\n\nLe bouton B permet de remettre à zéro l'angle du robot.");
	printf ("\n\n");
	
	do {
		read(fd,&js,sizeof(struct js_event));

		switch(js.type) {
		case JS_EVENT_BUTTON:
			if (js.number == 6 ){
				button[js.number] = (char)js.value;
			}
			if (js.number == 7)
				button[js.number] = (char)js.value;
			break;		
		}
	}while (button[6] != 1 && button[7] != 1);

	if (button[6] == 1 || button[7] == 1)
		CLEAR;
	
	printf("\r");
	printf("\nDonnées reçues par le biai du microcontrôleur:\n");
	printf("Batterie:");
	printf("	Vitesse du Robot:");
	printf("	 Angle du robot:");
	printf("	  Tir Possible:" );

	printf("\n\n");
	printf("Axe Horizontale:");
	printf("	 Axe Verticale:");
	printf ("	 	Rotation:");
	printf ("	  Tirer (X):");

	printf("\n\nPour Tirer appuyer sur X");
		
	printf("\n\n");
	

	printf("*---------------------------*\n");
	printf("  Valeur sortie moteur :\n");
	printf("    Moteur 1 :");
	printf("\n    Moteur 2 :");
	printf("\n    Moteur 3 :");
	printf("\n    Moteur 4 :");
	printf("\n\n Pour fermer l'application appuyez sur le logo XBOX.");
	printf("\n");

	while (1) {

		read(fd,&js,sizeof(struct js_event));

		switch(js.type) {
		case JS_EVENT_BUTTON:
			if (js.number == 1)
				button[js.number] = (char)js.value;
			if (js.number == 2 || js.number == 8)
				button[js.number] = (char)js.value;
			break;
		case JS_EVENT_AXIS:
			if (js.number == 2 || js.number == 5 ){
				trigger[js.number] = (unsigned short)js.value;
				triggerScale(&trigger[js.number]);
			}
			else if (js.number < 2){
				axis[js.number] = js.value;
				axisScale(&axis[js.number],js.number);
			}
			break;
		
		}

		trigger_rot = (signed short)(((trigger[5]/2)-1)-((trigger[2]/2)-1));

		serialport_read_until(fdu, &data[0],'\0',8);

		vRotation = (unsigned short)(data[0]<<8) | (unsigned short)data[1];
		
		getVMoteurs(axis[0],axis[1],trigger_rot,vOut);

		angleTemp = (unsigned short)data[0]<<8;
		angleTemp |= data[1];

		angleRobot = getConvAngle(angleTemp);

		if (button[2] == 1 && data[6] != 0x55)
			button[2]=0;

		printf("\033[3;10f %3d%%",data[4]);
		printf("\033[3;34f %3dm/s",data[5]);
		printf("\033[3;58f %x", data[0]);
		printf("\033[3;61f %x", data[1]);
		if (data[6]==0x55)
			printf("\033[3;80f oui");
		else
			printf("\033[3;80f non");
		printf("\033[5;17f %6d  ",axis[0]);
		printf("\033[5;40f %6d  ",axis[1]);
		printf("\033[5;58f %6d  ",trigger_rot);
		printf("\033[5;80f %d  ",button[2]);
		printf("\033[11;20f %d  ",vOut[0]);
		printf("\033[12;20f %d  ",vOut[1]);
		printf("\033[13;20f %d  ",vOut[2]);
		printf("\033[14;20f %d  ",vOut[3]);
		
		serialport_write(fdu,&vOut[0]);

		if (button[8] == 1){
			CLEAR;
			return -1;
		}
		/*
			* Librairie: stdio.h
			* Prototype: int fflush(FILE *stream);
			* Vide l'espace tampon (buffer) d'un flux 
			*/
		fflush(stdout);
	}
}

