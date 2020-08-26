/*************************************************************************
Implementation File	: TController.c
Author Date			: Y. Cotronis 07/03/2016
Purpose				: Controller implementatio file
Revision			:  Aris Tsilifonis 21/3/19
**************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "TController.h"
void ControllerDimiourgia(TController *Controller)//initialize controller's parts
{
	Controller-> TimeBusy = 0;
	Controller-> TimeInactive = 0;
	Controller-> ArithmoPelaton = 0;
	Controller-> enapomenonXronos = 0;
	Controller-> available = true;
}

void ControllerNewCustomer(TController *Controller)
{
	Controller-> ArithmoPelaton++;
	Controller-> TimeBusy++;
}

int ControllerAV(TController *Controller)
{
	return Controller-> available == true;
}

void ControllerSetXrono(TController *Controller, int xronosEksipiretisis)
{
	Controller->enapomenonXronos=xronosEksipiretisis-1; 
}

void ControllerNoWork(TController *Controller)
{
	Controller-> TimeInactive++;
}

void ControllerBusy(TController *Controller)
{
	Controller-> TimeBusy++;
	Controller-> enapomenonXronos--;
}

int ControllerFree(TController Controller)
{
	return (Controller.enapomenonXronos == 0);
}

int ControllerGetArithmosPelatwn(TController Controller)
{
	return Controller.ArithmoPelaton;
}

int ControllerGetEnapomenonXronos(TController Controller)
{
	return Controller.enapomenonXronos;
}

int ControllerGetInactiveXronos(TController Controller)
{
	return Controller.TimeInactive;
}

int ControllerGetBusyXronos(TController Controller)
{
	return Controller.TimeBusy;
}

TController *CreateMultiController()//create dynamic array
{
	TController *controller;
	controller=malloc(QNUMBER*sizeof(TController));
	return controller;
	
}
void DeleteMultiController(TController *controller)//free dynamic arrays
{
	// Free the array of queues
    free(controller);
    
    controller=NULL;
}



