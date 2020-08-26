/*************************************************************************
Implementation File	: QArray.c
Author Date			: Y. Cotronis 07/03/2016
Purpose				: ATD QUEUE with counter - array
Revision			:  Aris Tsilifonis 21/3/19
**************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ch6_QArray.h"


void OuraDimiourgia(TOuras *oura )
{
	oura->embros =  0;
	oura->piso = 0;
	oura->metritis = 0;
	oura->CountIn = 0;
	oura->CountOut = 0;
	oura->available = true;
}

TOuras *CreateMultiQueue()//Create dynamic array
{
	TOuras *oura;
	oura=malloc(QNUMBER*sizeof(TOuras));
	return oura;
}

void DeleteMultiQueue(TOuras *oura)
{
    // Free the array of queues
    free(oura);
    
    oura=NULL;
}


int OuraKeni(TOuras oura)
{
	return ( oura.metritis == 0 );
}

int OuraGemati(TOuras oura) /* OXI sthn diepafi-edv bohthitikh */
{
		return oura.metritis == QSIZE;
}

int OuraCrowded(TOuras oura)
{
		if(oura.metritis>8*(QSIZE/10))
			return 1;
		else
			return 0;
}
int OuraProsthesi(TOuras *oura, TSOuras stoixeio)
{
	if (OuraGemati(*oura))
		return 0;
	else
	{
		TSOurasSetValue(&(oura->pinakas[oura->piso]),stoixeio); /* abstraction of = for any type */
		oura->piso = ( oura->piso + 1 )% QSIZE;
		oura->metritis++;
		oura->CountIn++;
	}
	return 1;
}

int OuraApomakrynsh(TOuras *oura, TSOuras *stoixeio)
{
	if (OuraKeni(*oura))
		return 0;
	else
	{
		TSOurasSetValue(stoixeio, oura->pinakas[oura->embros]); /* abstraction of = for any type */
		oura->embros = ( oura->embros + 1 )% QSIZE;
		oura->metritis--;
		oura->CountOut++;
	}
	return 1;
}

int OuraGetSize(TOuras oura)
{
	return oura.metritis;
}

int GetCountIn(TOuras oura)
{
	return oura.CountIn;
}

int GetCountOut(TOuras oura)
{
	return oura.CountOut;
}

int findQueueWithMinCars(TOuras *oura)
{
	int min_index=0,min,i;
	min=oura[0].metritis;//initialize min
	for(i=0;i<QNUMBER;i++)//gia kathe oura 
	{
		if(oura[i].metritis<min)//vriskw ton mikrotero metriti
		{
			min_index=i;
		}
	}
	return min_index;
}

int ouraAV(TOuras *oura)
{
	return oura-> available == true;
}

