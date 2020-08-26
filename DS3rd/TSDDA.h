#ifndef __TSDDA__
#define __TSDDA__
#include <stdio.h>

typedef int keyType; /* integer key for airport */

typedef struct KeyIndex{
        keyType key;
        int arrayIndex;
        int flag;//it wasnt used
        //it was not for overcounting airports
} TStoixeiouDDA;

int TSDDA_setValue (TStoixeiouDDA *target, TStoixeiouDDA source);

int TSDDA_setKey(keyType * key, keyType Val);

int TSDDA_setIndex(int * Index, int Val);

/* basikes sygkriseis gia xrhsh sthn eisagcgh-diagarfh-anazhthsh se DDA */
int TSDDA_iso(TStoixeiouDDA, TStoixeiouDDA);
int TSDDA_mikrotero(TStoixeiouDDA, TStoixeiouDDA);
int TSDDA_megalytero(TStoixeiouDDA, TStoixeiouDDA);

/* symplhrvmatikes sygkriseis */
int TSDDA_mikrotero_iso(TStoixeiouDDA, TStoixeiouDDA);
int TSDDA_megalytero_iso(TStoixeiouDDA, TStoixeiouDDA);
int TSDDA_diaforo(TStoixeiouDDA, TStoixeiouDDA);

//this fuction is in evretirio
int TSDDA_getkey(TStoixeiouDDA treenode);
//this in avl 
int TSDDA_writeValue(FILE *to, TStoixeiouDDA Elem);

//these fuction weren't used
//they were supposed for overcounting airports
int checkflag(TStoixeiouDDA node);
int flag(TStoixeiouDDA node);
//void set_flag(TStoixeiouDDA node);
#endif
