/**********************************************+**************************
Header File Name 		: TCOntroller.h
Author	Date			: Y. Cotronis 07/03/2016
Purpose					: Controller header file
Revision				:  Aris Tsilifonis 21/3/19
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef __TController__ 
#define __TController__
extern int QNUMBER;

typedef struct {
	int TimeBusy;
	int TimeInactive;
	int ArithmoPelaton;
	int enapomenonXronos; //enapomenon xronos sto tameio
	bool available;//diathesimotita controller
} TController; 

void ControllerDimiourgia(TController *Controller); // Initialize struct's parts
void ControllerNewCustomer(TController *Controller);
 // Increase by 1 customer's counter and adds 1 unit of time at the time of controller's service
void ControllerSetXrono(TController *Controller, int xronosEksipiretisis);
 //Arxikopoiei ton enapomenon xrono ws ton xrono eksipiretisis gia kathe neo pelati autokinito
void ControllerNoWork(TController *Controller); // Auxanei ton xrono adraneias kata mia monada
void ControllerBusy(TController *Controller);
// Auxanei ton xrono apasxolis kai meiwnei ton enapomenonxrono kata mia monada
int ControllerFree(TController Controller); // elegxei an einai diathesimos
int ControllerGetArithmosPelatwn(TController Controller); // epistrefei arithmo pelaton
int ControllerGetEnapomenonXronos(TController Controller); // eistrefei enapomenon xrono
int ControllerGetInactiveXronos(TController Controller); // epistrefei xrono adraneias
int ControllerGetBusyXronos(TController Controller); // epistrefei xrono apasxolisis

TController *CreateMultiController();
void DeleteMultiController(TController *controller);

int ControllerAV(TController *Controller);
#endif
