/*
 * CAN.c
 *
 *  Created on: Jun 10, 2018
 *      Author: dwenm
 */

#include "CAN.h"

void Batterie(unsigned char *bat){					//fonction permettant de r�cup�rer l'information sur le taux de charge de la batterie
	volatile unsigned short batterie;			
	while (ADCSC1_COCO == 0);						//attente de la fin de conversion
	*bat = ~ADCRL;									//stockage de la valeur convertie avec un compl�ment pour l'inverser
	batterie=*bat;									//pour le calcul nous avons besoin de deux octet
	batterie=batterie*100;							//Calcul du taux de charge de la batterie en pourcetage
	batterie=batterie/255;
	*bat=(unsigned char)batterie;					//on ram�ne la donn�e sur un octet
	return;
}
