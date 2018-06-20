/*
 * RF.c
 *
 *  Created on: Jun 6, 2018
 *      Author: dwenm
 */

#include "RF.h"

unsigned char ADDR_RF_TX[]={0xB3,0xB3,0xB3,0xB3,0xB3};				//adresse du module 1

unsigned char ADDR_RF_RX[]={0x42,0x42,0x42,0x42,0x42};				//adresse du module 2

void Receive_Register (unsigned char Addr_reg, unsigned char *read, unsigned char lenght){
	CS_LOW;
	SPI_w(&Addr_reg,1);
	SPI_Read_Multiple(read,lenght);
	CS_HIGH;
	return;
}

void Config_Register (unsigned char Addr_reg,unsigned char Data_reg){
	CS_LOW;
	SPI_w(&Addr_reg,1);
	SPI_w(&Data_reg,1);
	CS_HIGH;
	delai(50);
	return;
}

void Transmit_Data (unsigned char Addr_reg, unsigned char *data, unsigned char lenght){
	CS_LOW;
	SPI_w(&Addr_reg,1);
	SPI_w(data,lenght);
	CS_HIGH;
	return;
}

unsigned char STATUS(void){
	unsigned char NOP=0xFF;
	volatile unsigned char status;
	CS_LOW;
	status = SPI_w(&NOP,1);
	CS_HIGH;
	return status;
}

unsigned char RX_RF (unsigned char *receive_data, unsigned char lenght){
	volatile unsigned char status,result;
	if (dataReceive()){												//vérifie qu'une donnée a été reçu
		Receive_Register(R_RX_PAYLOAD,&receive_data[0],lenght);		//Réception des données reçu
		status = STATUS();											
		if (dataReceive())									//vérification si une autre donnée a été reçu
			FLUSH_RX_RF();									//nettoyage des données se trouvant dans le buffer de réception
		result = SUCCES_RX;									//flag signalant le succés de la réception
	}
	else 
		result = FAILURE_RX;								//flag signalant que nous n'avaons rien reçu
	CE=1;
	return result;
}

unsigned char dataReceive(void) {
	volatile unsigned char status;
	status=STATUS();
	if ( status & 0x40 ) 								//signifit qu'une donnée a été reçu sur le module
		return 1;
	return 0;
}

void TX_RF (unsigned char *data, unsigned char lenght_data){
	PowerUP_TX();											//régle le module en transmission
	delais(250);
	Transmit_Data(W_TX_PAYLOAD,&data[0],lenght_data);		//transmission des données a émettre
	CE=1;													//active la transmission
	while(Test_Sending());									//attente de fin de transmission
	PowerUP_RX();											//régle en mode réception le module
	delais(250);
}

unsigned char Test_Sending(void){					//attente de fin de transmission
	volatile unsigned char status;
	status=STATUS();
	if ((status & 0x20) || (status & 0x10)){		//Transmission terminée ou nombre de retransmission maximum atteint
		return 0;
	}
	return 1;
}

void FLUSH_RX_RF (void){
	unsigned char flush_rx = FLUSH_RX;
	CS=0;
	SPI_w(&flush_rx,1);
	CS=1;
	return;
}

void RF_Init (void){										//Confugure le module radio
	CE=0;
	CS=1;
	Config_Register(WRITE_RF_CH,RF_CH_FREQUENCY);
	Config_Register(WRITE_RX_PW_P0,RX_PW_P0_4BYTES);
	Config_Register(WRITE_RX_PW_P1,RX_PW_P1);
	Config_Register(WRITE_RX_PW_P2,RX_PW_P2);
	Config_Register(WRITE_RX_PW_P3,RX_PW_P3);
	Config_Register(WRITE_RX_PW_P4,RX_PW_P4);
	Config_Register(WRITE_RX_PW_P5,RX_PW_P5);
	Config_Register(WRITE_RF_SETUP,RF_SETUP);
	Config_Register(WRITE_CONFIG_RF,0x78);
	Config_Register(WRITE_EN_AA, EN_AA);
	Config_Register(WRITE_EN_RXADDR,EN_REXADDR_P0);
	Config_Register(WRITE_SETUP_RETR,SETUP_RETR);
	Config_Register(WRITE_SETUP_AW,SETUP_AW_3BYTES);
	PowerUP_RX();
	return;
}

void RX_ADDR(void){										//configure l'adresse du canal de réception 1
	CE=0;
	Transmit_Data(WRITE_RX_ADDR_P1,&ADDR_RF_RX[0],5);
	CE=1;												//active la réception
	return;
}

void TX_ADDR(void){										//configure l'adresse de transmission
	Transmit_Data(WRITE_RX_ADDR_P0,&ADDR_RF_TX[0],5);
	Transmit_Data(WRITE_TX_ADDR,&ADDR_RF_TX[0],5);
	return;
}

void PowerUP_TX(void){									//régle le mdoule en transmission
	CE=0;
	Config_Register(WRITE_STATUS,0x70);
	Config_Register(WRITE_CONFIG_RF,CONFIG_RF_TX);
	return;
}

void PowerUP_RX(void){									//régle module en réception
	FLUSH_RX_RF();
	Config_Register(WRITE_STATUS,0x70);
	CE=0;
	Config_Register(WRITE_CONFIG_RF,CONFIG_RF_RX);
	CE=1;
	return;
}

void delais(unsigned long delai){
	unsigned long i;
	for(i=0;i==delai;i++);
	return;
}
