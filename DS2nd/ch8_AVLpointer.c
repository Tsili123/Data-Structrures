/*********************************************************
Αρχείο Υλoπoίησης	: ch8_AVLpointer.c
Συγγραφέας			: 
Σκοπός				: Υλοποίηση με δείκτες ΑΤΔ, AVL Δέντρο
**********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "ch8_AVLpointer.h"


#define FALSE 0
#define TRUE 1

#define printinfo FALSE /* an i printinfo ginei TRUE bgainoun miminata poy aforoun tis peristrofes tou dentrou*/

typedef enum{AY,IY,DY} paragon_isozygisis;

typedef struct typos_komvou{
	TStoixeiouDDA dedomena;
	typos_deikti	apaidi,dpaidi;
	paragon_isozygisis pi;
} typos_komvou;

/*Prakseis gia tin isozygisi tou AVL dentrou*/
void aristeri_peristrofi(typos_deikti *riza);
void dexia_peristrofi(typos_deikti *p);
void dexi_varos(typos_deikti *riza,int *ypsilotero, char parametros);
void aristero_varos(typos_deikti *riza,int *ypsilotero, char parametros);
void swap(typos_deikti *riza,typos_deikti *temp,int *ypsilotero);

void AVLTree_dimiourgia(typos_deikti *riza){
 /*	
 *	Πρo: 		καμία
 *	Μέτά: 		Δημιoυργία ενός AVL AVL δέντρου
*/	
	*riza = NULL;
	printf("AVL\n");
}

int	AVLTree_keno(typos_deikti riza){
 /*	
 *	Πρo: 		Δημιoυργία ενός AVL δέντρου
 *	Μέτά:		επιστρέφει 1 αν το δέντρο είναι κενό, διαφoρετικά 0
*/
	return ( riza == NULL );
}


typos_deikti AVLTree_apaidi(typos_deikti p){
/* *	Πρo: 		ο p δείχνει ένα κόμβο σε ένα AVL δέντρο
 *	Μέτά:		επιστρέφει το αριστερό παιδι που δείχνει ο p*/
     if(p!=NULL)
         return p->apaidi;
     else{
          return NULL;
     }
     
}


typos_deikti AVLTree_dpaidi(typos_deikti p){
/* *	Πρo: 		ο p δείχνει ένα κόμβο σε ένα AVL δέντρο
 *	Μέτά:		επιστρέφει το δεξί παιδι που δείχνει ο p*/
     if(p!=NULL)
         return p->dpaidi;
     else{
          return NULL;
     }
}


void dexia_peristrofi(typos_deikti *p){
/*	
 *	Πρo: 		ο *p δείνει την ρίζα του υποδέντρου που θα γίνει δεξιά περιστροφή
 *	Μέτά:		έχει γίνει δεξιά περιστροφή
*/
	typos_deikti prosoninos;
	if (AVLTree_keno(*p)) /*είναι αδύνατη η περιστροφή ενός κενού δέντρου*/
		printf("Keno Dentro\n");
	else if (AVLTree_keno((*p)->apaidi)) /*είναι αδύνατο να γίνει ρίζα ένα κενό δέντρο*/
		printf("Keno aristero ypodentro\n");
	else
	{
		prosoninos = (*p)->apaidi;
		(*p)->apaidi = prosoninos->dpaidi;
		prosoninos->dpaidi = *p;
		*p = prosoninos;
	}
}


void aristero_varos(typos_deikti *riza,int *ypsilotero, char parametros) { 
/*	
 *	Μέτά:		Αποκαθίσταται η ισοζύγιση με τις LL και LR περιστροφές στο δέντρο *riza
 *				Αν έχει αυξηθεί ο ύψος ενός υποδέντρου μετά την εκτέλεση της συνάρτησης τότε
 *				το *ypsilotero ειναι 1 αλλιώς 0. Η συνάρτηση δέχεται και μια παράμετρο (char parametros) με τιμές
 *				'e' ή 'd' που δηλώνει αν η συνάρτηση έχει κληθεί κατά την διάρκεια εισαγωγής κόμβου ή κατά την διάρκεια 
				διαγραφής κόμβου. Αυτό συμβαίνει, διότι οι παράγοντες ισοζύγισης των κόμβων διαφέρουν σε αυτές τις δύο ενέργειες
*/
	typos_deikti x; /*δείκτης στο αριστερό υπόδεντρο της ρίζας*/
	typos_deikti w;

	x = (*riza)->apaidi;
	if (parametros=='e'){ /*περίπτωση όπου η συνάρτηση έχει κληθεί για εισαγωγή κόμβου*/
		switch (x->pi)
		{
		case AY:/*απλή LL περιστροφή*/
			(*riza)->pi = IY;
			x->pi = IY;
            if(printinfo){  
		    	printf("dexia peristrofi: ");
		    	TSDDA_writeValue(stdout, (*riza)->dedomena);
		    	printf("\n");
             }
			dexia_peristrofi(riza);
			*ypsilotero = FALSE;  
			break;
		case IY:
			/*δεν συμβαίνει η περίπ89τωση αυτή*/
			break;
		case DY:/*διπλή LR περιστροφή*/
			w = x->dpaidi;
			switch (w->pi)
			{
			case IY:
				(*riza)->pi = IY;
				x->pi = IY;
				break;
			case DY:
				(*riza)->pi = IY;
				x->pi = AY;
				break;
			case AY:
				(*riza)->pi = DY;
				x->pi = IY;
				break;
			}
			w->pi = IY;
            if(printinfo){   
              printf("aristeri peristrofi: ");
 	          TSDDA_writeValue(stdout, x->dedomena);
            }
			aristeri_peristrofi(&x);
			/*ο x είχνει τώρα τον w*/
			(*riza)->apaidi = x;  
            if(printinfo) {
               printf(" --  dexia peristrofi:");
  	           TSDDA_writeValue(stdout, (*riza)->dedomena);
		    	printf("\n");
            }
			dexia_peristrofi(riza);
			*ypsilotero = FALSE;
		
		}
	}
	if (parametros=='d') /*περίπτωση όπου η συνάρτηση έχει κληθεί για διαγραφή κόμβου*/
	{
		switch (x->pi)
		{
		case AY:/*απλή LL περιστροφή*/
		case IY:
			if(x->pi==IY){
				(*riza)->pi = AY;
				x->pi = DY;  
					*ypsilotero = FALSE;  
			}
			else
			{
				(*riza)->pi = IY;
				x->pi = IY;
			}
			if(printinfo){
              printf("dexia peristrofi:");
  	          TSDDA_writeValue(stdout, (*riza)->dedomena);
  	          printf("\n");
            }
			dexia_peristrofi(riza);
		
			break;
		case DY:/*διπλή LR περιστροφή*/
			w = x->dpaidi;
			switch (w->pi)
			{
			case IY:
				(*riza)->pi = IY;
				x->pi = IY;
				break;
			case DY:
				(*riza)->pi = IY;
				x->pi = AY;
				break;
			case AY:
				(*riza)->pi = DY;
				x->pi = IY;
				break;
			}
			w->pi = IY; 
            if(printinfo){  
			   /* printf("aristeri peristrofi: "); */
               TSDDA_writeValue(stdout, x->dedomena);
            }
			aristeri_peristrofi(&x);
			/*ο x είχνει τώρα τον w*/
			(*riza)->apaidi = x; 
            if(printinfo){  
               /* printf(" --  dexia peristrofi:",(*riza)->dedomena); */
               TSDDA_writeValue(stdout, (*riza)->dedomena);
  	           printf("\n");
            }
			dexia_peristrofi(riza);
		}
	}
}

void aristeri_peristrofi(typos_deikti *p){
 /*	
 *	Πρo: 		ο *p δείνει την ρίζα του υποδέντρου που θα γίνει αριστερή περιστροφή
 *	Μέτά:		έχει γίνει αριστερή περιστροφή
*/
	typos_deikti prosoninos;
	if (AVLTree_keno(*p)) /*είναι αδύνατη η περιστροφή ενός κενού δέντρου*/
		printf("Keno Dentro\n"); 
	else if (AVLTree_keno((*p)->dpaidi)) /*είναι αδύνατο να γίνει ρίζα ένα κενό δέντρο*/
		printf("Keno deksi ypodentro\n");
	else
	{
		prosoninos = (*p)->dpaidi;
		(*p)->dpaidi = prosoninos->apaidi;
		prosoninos->apaidi = *p;
		*p = prosoninos;
	}
}

void dexi_varos(typos_deikti *riza,int *ypsilotero, char parametros){
/*
 *	Μέτά:		Αποκαθίσταται η ισοζύγιση με τις RR και RL περιστροφές στο δέντρο *riza
 *				Αν έχει αυξηθεί ο ύψος ενός υποδέντρου μετά την εκτέλεση της συνάρτησης τότε
 *				το *ypsilotero ειναι 1 αλλιώς 0. Η συνάρτηση δέχεται και μια παράμετρο (char parametros) με τιμές
 *				'e' ή 'd' που δηλώνει αν η συνάρτηση έχει κληθεί κατά την διάρκεια εισαγωγής κόμβου ή κατά την διάρκεια 
				διαγραφής κόμβου. Αυτό συμβαίνει, διότι οι παράγοντες ισοζύγισης των κόμβων διαφέρουν σε αυτές τις δύο ενέργειες
*/
	typos_deikti x; /*δείκτης στο δεξί υπόδεντρο της ρίζας*/
	typos_deikti w;

	x = (*riza)->dpaidi;
	if(parametros=='e'){ /*περίπτωση όπου η συνάρτηση έχει κληθεί για εισαγωγή κόμβου*/
	switch (x->pi)
	{
		case DY:/*απλή RR περιστροφή*/
			(*riza)->pi = IY;
			x->pi = IY;
            if(printinfo){               
               printf("aristeri peristrofi:");
 	           TSDDA_writeValue(stdout, (*riza)->dedomena);
  	           printf("\n");
            }
			aristeri_peristrofi(riza);
			*ypsilotero = FALSE;  
			break;
		case IY:
			break;
		case AY:/*διπλή RL περιστροφή*/
			w = x->apaidi;
			switch (w->pi)
			{
			case DY:
				(*riza)->pi = AY;  
				x->pi = IY;
				break;
			case IY:
				(*riza)->pi = IY;
				x->pi = IY;
				break;
			case AY:
				(*riza)->pi = IY;  
				x->pi = DY;
				break;
			}
			w->pi = IY;	
			if(printinfo){
			   printf("dexia peristrofi:");
               TSDDA_writeValue(stdout, x->dedomena);
            }
			dexia_peristrofi(&x);
			/*ο x είχνει τώρα τον w*/
			(*riza)->dpaidi = x;
			if(printinfo){
			   printf("aristeri peristrofi:");
               TSDDA_writeValue(stdout, (*riza)->dedomena);
  	           printf("\n");
            }
			aristeri_peristrofi(riza);
			*ypsilotero = FALSE;  
		
		}
	}
	if(parametros=='d') /*περίπτωση όπου η συνάρτηση έχει κληθεί για διαγραφή κόμβου*/
	{
	switch (x->pi)
	{
		case DY:/*απλή RR περιστροφή*/
		case IY:
			if(x->pi==IY){
				(*riza)->pi = DY;
				x->pi = AY; 
				*ypsilotero = FALSE;  
			}
			else{
			(*riza)->pi = IY;
			x->pi = IY;
			}
			if(printinfo){
               printf("aristeri peristrofi:");
               TSDDA_writeValue(stdout, (*riza)->dedomena);
  	           printf("\n");
            }
			aristeri_peristrofi(riza);
			
			break;

		case AY:/*διπλή RL περιστροφή*/
			w = x->apaidi;
			switch (w->pi)
			{
			case DY:
				(*riza)->pi = AY;  
				x->pi = IY;
				break;
			case IY:
				(*riza)->pi = IY;
				x->pi = IY;
				break;
			case AY:
				(*riza)->pi = IY;  
				x->pi = DY;
				break;
			}
			w->pi = IY;	
			if(printinfo){
			   printf("dexia peristrofi:");
               TSDDA_writeValue(stdout, x->dedomena);
            }
			dexia_peristrofi(&x);
			/*ο x είχνει τώρα τον w*/
			(*riza)->dpaidi = x;
			if(printinfo){
			    printf("aristeri peristrofi:");
                TSDDA_writeValue(stdout, (*riza)->dedomena);
  	            printf("\n");
            }
			aristeri_peristrofi(riza);
		}
	}
}

void AVLTree_eisagogi(typos_deikti *riza,TStoixeiouDDA stoixeio, int *ypsilotero,int *error){
 /*	
 *	Πρo: 		Δημιoυργία ενός AVL δέντρου
 *	Μέτά:		Εισαγωγή του κόμβου στο δέντρο εφόσον αυτος δεν υπάρχει ήδη. 
 *				Επίσης γίνονται οι κατάλληλες ενέργειες ώστε μετά την εισαγωγή του
 *				κόμβου, το δέντρο να παραμείνει ισοζυγισμένο
*/

	if (AVLTree_keno(*riza))
	{
		*riza = malloc(sizeof(struct typos_komvou));
		if(*riza==NULL){
           *error=1;
           return;
        }
		TSDDA_setValue(&((*riza)->dedomena),stoixeio);
		/* ((*riza)->dedomena)=stoixeio; */
		(*riza)->apaidi = NULL;
		(*riza)->dpaidi = NULL;
		(*riza)->pi = IY;
		*ypsilotero = TRUE;
	}
	else if (TSDDA_iso(stoixeio,(*riza)->dedomena)) {
		/* printf("O komvos yparxei idi sto AVL-dentro!\n"); */
		*error=1;
	} else if (TSDDA_mikrotero(stoixeio,(*riza)->dedomena)) 
	{			
		/*εισαγωγή στο αριστερό υπόδεντρο*/
		AVLTree_eisagogi(&((*riza)->apaidi),stoixeio,ypsilotero,error);
		if (*ypsilotero)
		{
			switch((*riza)->pi)
			{
			case AY:
				aristero_varos(&(*riza),ypsilotero,'e');
				break;
			case IY:
				(*riza)->pi=AY;
				*ypsilotero = TRUE;   
				break;
			case DY: 
				(*riza)->pi = IY;
				*ypsilotero = FALSE;
				break;
			}
		}
	}
	else /*εισαγωγή στο δεξί υποδέντρο*/
	{
		AVLTree_eisagogi(&((*riza)->dpaidi),stoixeio,ypsilotero,error);
		if (*ypsilotero)
		{
			switch((*riza)->pi)
			{
			case AY:
				(*riza)->pi = IY;
				*ypsilotero = FALSE;
				break;
			case IY:
				(*riza)->pi=DY;
				*ypsilotero = TRUE;  
				break;
			case DY:
				dexi_varos(&(*riza),ypsilotero,'e');
				break;
			}
		}
	}
}


void AVLTree_diagrafi(typos_deikti *riza,TStoixeiouDDA stoixeio,int *ypsilotero, int *error){
/*	
 *	Πρo: 		Δημιoυργία ενός AVL δέντρου
 *	Μέτά:		Διαγραφή του κόμβου με περιεχόμενο stoixeio.
 *				Επίσης γίνονται οι κατάλληλες ενέργειες ώστε μετά την διαγραφή του
 *				κόμβου, το δέντρο να παραμείνει ισοζυγισμένο
*/
	typos_deikti prosorinos;
	
	*error=0;

	if(AVLTree_keno(*riza))
	{
		*error=1;
		return;
	}
	else if (TSDDA_mikrotero(stoixeio, (*riza)->dedomena) )/*αναζήτηση στο αριστερό υποδέντρο*/
	{
		AVLTree_diagrafi(&((*riza)->apaidi),stoixeio,ypsilotero, error);
		if (*ypsilotero)
		{
			switch((*riza)->pi)
			{
			case AY:
				(*riza)->pi = IY;
				break;
			case IY:
				(*riza)->pi=DY;
				*ypsilotero = FALSE;
				break;
			case DY:
				dexi_varos(&(*riza),ypsilotero,'d');
				break;
			}
		}
	}
	else if (TSDDA_megalytero(stoixeio,(*riza)->dedomena)) /*αναζήτηση στο δεξί υποδέντρο*/
	{
		AVLTree_diagrafi(&((*riza)->dpaidi),stoixeio,ypsilotero,error);
		if (*ypsilotero)
		{
			switch((*riza)->pi)
			{
			case AY:
				aristero_varos(&(*riza),ypsilotero,'d');
				break;
			case IY:
				(*riza)->pi=AY;
				*ypsilotero = FALSE;
				break;
			case DY: 
				(*riza)->pi = IY;
				break;
			}
		}
	}
	else /*ο κόμβος με περιεχόμενο stoixeio βρέθηκε*/
	{
		prosorinos=(*riza);

		if( prosorinos->dpaidi == NULL ) /*ο κόμβος δεν έχει δεξί παιδί*/
		{
			(*riza)=prosorinos->apaidi;
			*ypsilotero=TRUE;
			free(prosorinos);
		}
		else if( prosorinos->apaidi == NULL) /*ο κόμβος δεν έχει αριστερό παιδί*/
		{
			(*riza)=prosorinos->dpaidi;
			*ypsilotero=TRUE;
			free(prosorinos);
		}
		else /*ο κόμβος έχει 2 παιδιά*/
		{
			/*το περιεχόμενο του κόμβου προς διαγραφή αντικαθιστάται από το δεξιότερο στοιχείο του αριστερού του παιδιού*/
			swap(&(prosorinos->apaidi),&prosorinos, ypsilotero);
			if (*ypsilotero)
			{
				switch((*riza)->pi)
				{
					case AY:
						(*riza)->pi = IY;
						break;
					case IY:
						(*riza)->pi=DY;
						*ypsilotero = FALSE;
						break;
					case DY:
						dexi_varos(&(*riza),ypsilotero,'d');
						break;
				}
			}

		} 
	}
}



void AVLTree_anazitisi(typos_deikti riza, TStoixeiouDDA stoixeio, typos_deikti *deiktis, int *found){
 /*	
 *	Πρo: 		Δημιoυργία ενός AVL δέντρου
 *	Μέτά:		επιστρέφει ένα δείκτη στον κόμβο που περιέχει το stoixeio διαφορετικά NULL
*/
    *found=0;
    
	if (AVLTree_keno(riza)){ /*κενό δεντρο*/
		*deiktis=NULL;
		return;
    }
	if (TSDDA_iso(stoixeio, riza->dedomena)) {
        *deiktis=riza;                     
		*found=1;
    }
	else if (TSDDA_mikrotero(stoixeio,riza->dedomena) ) /*αναζήτηση στο αριστερο υπόδενδρο*/
		 AVLTree_anazitisi(riza->apaidi, stoixeio,deiktis,found);
	else	/*αναζήτηση στο δεξί υπόδενδρο*/
		 AVLTree_anazitisi(riza->dpaidi, stoixeio,deiktis,found);

}


/*anadromiki synartisi gia diagrafi olwn twn komvwn*/
void AVLTree_katastrofi(typos_deikti *riza){
 /*	
 *	Πρo: 		Δημιoυργία ενός AVL δέντρου
 *	Μέτά:		Διαγραφή όλων των κόμβων του δέντρου. 
*/
	int ypsilotero;
	int error;
	if(!AVLTree_keno(*riza))
	{    /*μεταδιατεταγμένη διαδρομή στο δέντρο*/
         AVLTree_katastrofi(&(*riza)->apaidi);
		 AVLTree_katastrofi(&(*riza)->dpaidi);

		
		AVLTree_diagrafi(& (*riza), (*riza)->dedomena,&ypsilotero,&error);
		free(*riza);
		*riza=NULL;	
	}
}


void AVLTree_periexomeno(typos_deikti riza, TStoixeiouDDA *stoixeio){
     if(!AVLTree_keno(riza))
        /* *stoixeio=&(riza->dedomena); */
        TSDDA_setValue(stoixeio,riza->dedomena);
}


void AVLTree_pateras(typos_deikti riza, typos_deikti *pateras, typos_deikti paidi, int *error){
    if(AVLTree_keno(riza)||AVLTree_keno(paidi)||TSDDA_iso(paidi->dedomena, riza->dedomena)){
		*pateras=NULL;
		*error=1;
		return;
	}
	if(paidi==riza->apaidi||paidi==riza->dpaidi)
		*pateras=riza;
	else if(TSDDA_mikrotero(paidi->dedomena, riza->dedomena))
		AVLTree_pateras(riza->apaidi, pateras, paidi, error);
	else if(TSDDA_megalytero(paidi->dedomena, riza->dedomena))
		AVLTree_pateras(riza->dpaidi, pateras, paidi, error); 	 
}



/*Βοηθητική συνάρτηση για την διαγραφή κόμβου από το δέντρο. Ανταλάσσει το περιεχόμενα του temp με το δεξιότερο παιδί της riza */
void swap(typos_deikti *riza,typos_deikti *temp,int *ypsilotero){
	typos_deikti delnode;

	delnode=(*riza);

	if((*riza)->dpaidi != NULL)
	{
		swap(&((*riza)->dpaidi),temp,ypsilotero);
		if (*ypsilotero)
		{
			switch((*riza)->pi)
			{
			case AY:
				aristero_varos(&(*riza),ypsilotero,'d');
				break;
			case IY:
				(*riza)->pi=AY;
				*ypsilotero = FALSE;
				break;
			case DY: 
				(*riza)->pi = IY;
				break;
			}
		} 

	}
	else
	{
		delnode=(*riza);
		(*temp)->dedomena=(*riza)->dedomena;
		(*riza)=(*riza)->apaidi;
		if(printinfo){
           printf("swap with [ ");
           TSDDA_writeValue(stdout, delnode->dedomena);
  	           printf("]\n");
        }
		free(delnode);
		*ypsilotero=TRUE;
	}
}

