/**********************************************************************
Arxeio Ylopoihshs	: ch8_BSTpointerR.c
Syggrafeas			: X. Georgakopoylos, S. Gkiokas
Skopos				: Ylopoihsh me deiktes ATD Dyadiko Dentro 
					: Anazhthshs me anadromh
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "ch8_BSTpointer.h"

typedef struct typos_komboy{
	TStoixeiouDDA dedomena;
	typos_deikti apaidi;
	typos_deikti dpaidi;
} typos_komboy;

void Tree_dimiourgia(typos_deikti *tree)
{
	*tree=NULL;
	printf("simple\n");
}

void Tree_katastrofi(typos_deikti *tree)
{
	if(Tree_keno(*tree))
		return;

	Tree_katastrofi(&(*tree)->apaidi);
	Tree_katastrofi(&(*tree)->dpaidi);
	free(*tree);
	*tree=NULL;
}

int Tree_keno(typos_deikti tree)
{
 	return (tree==NULL);
}

void Tree_eisagogi(typos_deikti *tree, TStoixeiouDDA stoixeio, int *error)
{
	if(Tree_keno(*tree))
	{
		*tree=malloc(sizeof(typos_komboy));
		if(*tree==NULL)
		{
			*error=1;
			return;
		}
		TSDDA_setValue(&((*tree)->dedomena), stoixeio);
		/*(*tree)->dedomena=stoixeio;*/
		(*tree)->apaidi=NULL;
		(*tree)->dpaidi=NULL;
	}
	else if(TSDDA_mikrotero(stoixeio, (*tree)->dedomena))
		Tree_eisagogi(&((*tree)->apaidi), stoixeio, error);
	else if(TSDDA_megalytero(stoixeio, (*tree)->dedomena))
		Tree_eisagogi(&((*tree)->dpaidi), stoixeio, error);
	else
		*error=1;
}

void Tree_diagrafi(typos_deikti *tree, TStoixeiouDDA stoixeio, int *error)
{
	typos_deikti temp, next;
	error=0;
		
	if(Tree_keno(*tree))
	{
		*error=1;
		return;
	}
	
	if(TSDDA_iso(stoixeio, (*tree)->dedomena))
	{
		if(Tree_keno((*tree)->apaidi))
		{
			temp=*tree;
			*tree=(*tree)->dpaidi;
			free(temp);
		}
		else if(Tree_keno((*tree)->dpaidi))
		{
			temp=*tree;
			*tree=(*tree)->apaidi;
			free(temp);
		}
		else
		{
			next=(*tree)->dpaidi;
			while(next->apaidi!=NULL)
				next=next->apaidi;
			TSDDA_setValue(&((*tree)->dedomena), next->dedomena);
			/* (*tree)->dedomena=next->dedomena; */
			Tree_diagrafi(&((*tree)->dpaidi), (*tree)->dedomena, error);
		}
	}
	else if(TSDDA_mikrotero(stoixeio, (*tree)->dedomena))
		Tree_diagrafi(&((*tree)->apaidi), stoixeio, error);
	else
		Tree_diagrafi(&((*tree)->dpaidi), stoixeio, error);
}

typos_deikti Tree_apaidi(typos_deikti pateras){
	if(pateras!=NULL)
		return pateras->apaidi;
	else
		return NULL;
}
	
typos_deikti Tree_dpaidi(typos_deikti pateras){
	if(pateras!=NULL)
		return pateras->dpaidi;
	else
		return NULL;
}

void Tree_pateras(typos_deikti tree, typos_deikti *pateras, typos_deikti paidi, int *error)
{
	if(Tree_keno(tree)||Tree_keno(paidi)||TSDDA_iso(paidi->dedomena, tree->dedomena))
	{
		*pateras=NULL;
		*error=1;
		return;
	}
	if(paidi==tree->apaidi||paidi==tree->dpaidi)
		*pateras=tree;
	else if(TSDDA_mikrotero(paidi->dedomena, tree->dedomena))
		Tree_pateras(tree->apaidi, pateras, paidi, error);
	else if(TSDDA_megalytero(paidi->dedomena, tree->dedomena))
		Tree_pateras(tree->dpaidi, pateras, paidi, error); 	 
}
		
void Tree_anazitisi(typos_deikti tree, TStoixeiouDDA stoixeio, typos_deikti *deiktis, int *found)
{
	*found=0;
	
	if(Tree_keno(tree))
	{
		*deiktis=NULL;
		return;
	}
	if(TSDDA_iso(stoixeio, tree->dedomena))
	{
		*deiktis=tree;
		*found=1;
	}
	else if(TSDDA_mikrotero(stoixeio, tree->dedomena))
		Tree_anazitisi(tree->apaidi, stoixeio, deiktis, found);
	else if(TSDDA_megalytero(stoixeio, tree->dedomena))
		Tree_anazitisi(tree->dpaidi, stoixeio, deiktis, found);
}

void Tree_allagi(typos_deikti *tree, TStoixeiouDDA old, TStoixeiouDDA new, int *error)
{
	typos_deikti deiktis;
	int found;
	*error=found=0;
	deiktis=NULL;
	
	Tree_anazitisi(*tree, old, &deiktis, &found);
	if(found)
	{
		Tree_diagrafi(tree, old, error);
		if(!(*error))
			Tree_eisagogi(tree, new, error);
	}
	else
		*error=1;
}

void Tree_periexomeno(typos_deikti tree, TStoixeiouDDA *periexomeno)
{
	if(!Tree_keno(tree)){
		/* *periexomeno=&(tree->dedomena); */
		TSDDA_setValue(periexomeno, tree->dedomena);
	}
}
