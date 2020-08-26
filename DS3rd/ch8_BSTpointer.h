/**********************************************************************
Arxeio Epikefalidas	: ch8_BSTpointer.h
Syggrafeas			: X. Georgakopoylos, S. Gkiokas
Skopos				: Ylopoihsh me deiktes ATD Dyadiko Dentro Anazhthshs
					: (koino arxeio gia epanalhpsh kai anadromh)
***********************************************************************/
#ifndef __CH8_BSTPOINTER__ 
#define __CH8_BSTPOINTER__
#include "TSDDA.h"
typedef struct typos_komboy * typos_deikti;

void Tree_dimiourgia(typos_deikti *tree);
void Tree_katastrofi(typos_deikti *tree);
int Tree_keno(typos_deikti tree);
void Tree_eisagogi(typos_deikti *tree, TStoixeiouDDA stoixeio, int *error);
void Tree_diagrafi(typos_deikti *tree, TStoixeiouDDA stoixeio, int *error);
typos_deikti Tree_apaidi(typos_deikti pateras);
typos_deikti Tree_dpaidi(typos_deikti pateras);
void Tree_pateras(typos_deikti tree, typos_deikti *pateras, typos_deikti paidi, int *error);
void Tree_anazitisi(typos_deikti tree, TStoixeiouDDA stoixeio, typos_deikti *deiktis, int *found);
void Tree_periexomeno(typos_deikti tree, TStoixeiouDDA *periexomeno);


#endif /*#ifndef __CH8_BSTARRAY__ */
