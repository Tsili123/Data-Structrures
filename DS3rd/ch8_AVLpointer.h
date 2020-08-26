/*********************************************************
Αρχείο Επικεφαλίδας	: ch8_AVLpointer.h
Συγγραφέας			:  
Σκοπός				: Υλοποίηση με δείκτες ΑΤΔ, AVL Δέντρο
**********************************************************/
#ifndef __CH8_AVLPOINTER__ 
#define __CH8_AVLPOINTER__

#include "TSDDA.h"

/*δηλώσεις τύπων*/

typedef struct typos_komvou *typos_deikti; 

/*δηλώσεις συναρτήσεων*/

/*δημιουργία λιστας*/
void AVLTree_dimiourgia(typos_deikti *riza);

/*Πράξεις έλεγχου*/
int	AVLTree_keno(typos_deikti riza);

/*Πράξεις πρόσβασης*/

typos_deikti AVLTree_apaidi(typos_deikti p);
typos_deikti AVLTree_dpaidi(typos_deikti p);

void AVLTree_pateras(typos_deikti riza, typos_deikti *pateras, typos_deikti paidi, int *error);

/*Πράξεις Διαχείρισης */

void AVLTree_eisagogi(typos_deikti *riza,TStoixeiouDDA stoixeio,int *ypsilotero,int *error);
void AVLTree_diagrafi(typos_deikti *riza,TStoixeiouDDA stoixeio,int *ypsilotero,int *error);

void AVLTree_katastrofi(typos_deikti *riza);

/*Πράξεις αναζήτησης*/
void AVLTree_anazitisi(typos_deikti riza, TStoixeiouDDA stoixeio, typos_deikti *deiktis, int *found);
void AVLTree_periexomeno(typos_deikti riza,TStoixeiouDDA *stoixeio);

TStoixeiouDDA AVLTree_data(typos_deikti tree);
int AVLTree_data_key(typos_deikti tree);

#endif /*#ifndef __CH8_AVLPOINTER__ */
