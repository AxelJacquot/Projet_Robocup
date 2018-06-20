#include <stdio.h>

#define PERIODE_ECH (double)0.006 //6µs

#define M1DX (double)-0.36650
#define M1DY (double)0.930417
#define M2DX (double)-0.36650
#define M2DY (double)-0.930417
#define M3DX (double)0.707106
#define M3DY (double)-0.707106
#define M4DX (double)0.707106
#define M4DY (double)0.707106


typedef struct {
    signed short errors[100];
    double kp;
    double ki;
    double kd;
    unsigned char i;
}VariablesPID;

void initPID(VariablesPID *vars, double kp, double ki, double kd);


void getVMoteurs(signed short dx, signed short dy, signed short rot, signed char VMoteurs[4]);
//signed char calculPID(signed short commande, signed short retourCapteur, unsigned char grandeur);
signed short calculPID(signed short commande, signed short retourCapteur, VariablesPID *variablesPID);
void afficherVar(VariablesPID *var, unsigned char afficherTab);
unsigned long absL(signed long ch);
void convAngleAbsolu(signed short vitesse, signed char reset, double * angle);
signed short getConvAngle(signed short angle);