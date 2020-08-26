/**********************************************+**************************
Header File Name		: QArray.h
Author Date				: Y. Cotronis 07/03/2016
Purpose					: Header file of ATD Queue - counter - array
Revision				:  Aris Tsilifonis 21/3/19
**************************************************************************/
#ifndef __CH2_QARRAY__ 
#define __CH2_QARRAY__
#include "TStoixeiouOuras.h"
#include <stdbool.h>
#define QSIZE 1000
extern int QNUMBER;//external global variable for number of queues

typedef struct {
	int embros;		/* position of first element */
	int piso;		/* position of last  element */
	int metritis;   /* counter - elements in queue */
	int CountIn;
	int CountOut;
	bool available;
	TSOuras pinakas[QSIZE];	/* array of queue elements */
} TOuras;	   /* New Name of Type Queue */

void OuraDimiourgia(TOuras *oura);
TOuras *CreateMultiQueue();
void DeleteMultiQueue(TOuras *oura);

int	OuraKeni(TOuras oura);

int OuraProsthesi	(TOuras *oura, TSOuras stoixeio);
int OuraApomakrynsh (TOuras *oura, TSOuras *stoixeio);

int OuraGetSize(TOuras oura);

int GetCountIn(TOuras oura);
int GetCountOut(TOuras oura);

int findQueueWithMinCars(TOuras *oura);
int OuraCrowded(TOuras oura);

int ouraAV(TOuras *oura);
#endif

