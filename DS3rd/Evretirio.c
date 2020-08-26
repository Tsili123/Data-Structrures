#include "Evretirio.h"


#define Simple 1 /* 0 for AVL - any Evr integer for Simple  */
#define SIZE 7200

/* Oi diafores tvn ylopoihsevn Simple kai AVL einai mikres - mporeite na xrhsimopoihsete 
   thn  domh #if ... #else ...#endif gia na diaforopihsete tis dyo ylopoihseis  */
   
#if (Simple)
#include "ch8_BSTpointer.h" /* gia Simple Ylopoihsh */
#else
#include "ch8_AVLpointer.h" /* gia AVL Ylopoihsh */
#endif


struct EvrNode{
       TStoixeiouEvr *DataArray; /* array of size MaxSize */
       int Index;              /* index of first available element in array */
       typos_deikti TreeRoot;     /* Root of DDA */
} EvrNode;


void inorder(typos_deikti root,FILE *out,int *counter,int *error) ;
void copy_elements_to_evr(EvrPtr E,TStoixeiouEvr Data) ;


EvrPtr EvrConstruct(int MaxSize){
/* Oi diafores tvn ylopoihsevn Simple kai AVL einai mikres - 
	mporeite na xrhsimopoihsete thn  domh #if ... #else ...#endif */
   EvrPtr evrnode;
   
   evrnode=malloc(sizeof(EvrNode));
   evrnode->DataArray=malloc(sizeof(TStoixeiouEvr)*SIZE);
   evrnode->Index=0;
   
	#if (Simple)
   		printf("use simple BST\n");
   		Tree_dimiourgia(&(evrnode->TreeRoot));   
	#else   
    	printf("use AVL BST\n");
    	AVLTree_dimiourgia(&(evrnode->TreeRoot));
	#endif

}


void copy_elements_to_evr(EvrPtr E,TStoixeiouEvr Data)
{
	E->DataArray[E->Index].name = malloc(strlen(Data.name)+1);
	E->DataArray[E->Index].city = malloc(strlen(Data.city)+1);
	E->DataArray[E->Index].country = malloc(strlen(Data.country)+1);
	E->DataArray[E->Index].iata = malloc(strlen(Data.iata)+1);
	E->DataArray[E->Index].icao = malloc(strlen(Data.icao)+1);
	
	strcpy(E->DataArray[E->Index].name,Data.name);
	strcpy(E->DataArray[E->Index].city,Data.city);
	strcpy(E->DataArray[E->Index].country,Data.country);
	strcpy(E->DataArray[E->Index].iata,Data.iata);
	strcpy(E->DataArray[E->Index].icao,Data.icao);
}

int Evr_Insert(EvrPtr E, TStoixeiouEvr Data)
{
	//variable to check if everything goes ok
	int error=0;
	//and also to implement fuction
	typos_deikti pointer;
	TStoixeiouDDA airport;
	bool ypsilotero=false;
	//copy array index value to pass it in the fuction
	airport.arrayIndex=E->Index;
	airport.key=Data.airport_id;
	//copy to array of evr
	copy_elements_to_evr(E,Data);
	//put the airport id in the tree
	#if (Simple)
	Tree_eisagogi(&E->TreeRoot,airport,&error);
		
	if(error==1)
	{
		printf("Error.Insertion didn't work.Maybe airport already exists\n");
		return 0;
	}
	#else   	
    AVLTree_eisagogi(&E->TreeRoot,airport,&ypsilotero,&error);
    
    if(error==1)
	{
		printf("Error.Insertion didn't work.Maybe airport already exists\n");
		return 0;
	}
	#endif
	
	//put index value to next available element
	E->Index++;
}

int EvrDestruct(EvrPtr *E)
{
	#if (Simple)
	Tree_katastrofi(&((*E)->TreeRoot));
//	if(!Tree_Keno((*E)->TreeRoot))
	//	printf("Error\n");
	#else   	
    AVLTree_katastrofi(&(*E)->TreeRoot);
   // if(!AVLTree_Keno((*E)->TreeRoot))
	//	printf("Error\n");
	#endif
}

int EvrSearch(EvrPtr E, keyType key, int InOut, int * found)
{
	typos_deikti pointer;
	TStoixeiouDDA airport;
	airport.key=key;
	
	if(Tree_Keno(E->TreeRoot))
	{
		printf("Error.The tree is empty or the root is NULL pointer.\n");
		return 0;
	}
	
 	#if (Simple)
	Tree_anazitisi(E->TreeRoot,airport,&pointer,found);
	
	if(*found==1)
	{
		if(InOut==0)
		{
			E->DataArray->arrival_counter++;
		}
		else if(InOut==1)
		{
			E->DataArray->depart_counter++;
		}
	}
	else if(*found==0)
	{
		printf("The data was not found.\n");
		return 0;
	}
	
	#else   	
 	AVLTree_anazitisi(E->TreeRoot,airport,pointer,found);
 	
 	if(*found==1)
	{
		if(InOut==0)
		{
			E->DataArray->arrival_counter++;
		}
		else if(InOut==1)
		{
			E->DataArray->depart_counter++;
		}
	}
	else if(*found==0)
	{
		printf("The data was not found.\n");
		return 0;
	}

	#endif
}
/*

int Evr_PrintAll(EvrPtr E, FILE *out, int * counter)
{
	typos_deikti a=E->TreeRoot;
	int error;
	typos_deikti pateras;
	
	if(Tree_Keno(E->TreeRoot))
	{
		printf("Tree is empty\n");
		return 0;
	}
	
	
	/* endo-diadromh - use recursion with apaidi-depaidi */ 
	/* example of use 
	
	#if (Simple)
	
		a=Tree_apaidi(a);
	    inorder(a,out,counter,error);
		Tree_pateras(E->TreeRoot,&pateras,a,&error);
		if(error==0)
		{
			fprintf(out,"key : %d  afixeis%d %d",pateras->dedomena->key);
			a=Tree_dpaidi(pateras);
			inorder(a,out,counter,error);
		}
		else
		{
			return 0;
		}
		inorder(E,out,counter,error);
		
	#else  
	 
		inorder(a);
	    a=AVLTree_apaidi(a);
		inorder(a,out);
		AVLTree_pateras(E->TreeRoot,&pateras,a,&error);
		if(error==0)
		{
			fprintf(out,"key : %d  afixeis%d %d",pateras->dedomena->key);
			a=AVLTree_dpaidi(pateras);
			inorder(a,out,counter,error,E);
		}
		else
		{
			return 0;
		}
		inorder(E,out,counter,error);
		
	#endif
	
}
*/
int Evr_PrintAll(EvrPtr E, FILE *out, int * counter)
{
	int error;
	
	if(Tree_Keno(E->TreeRoot))
	{
		printf("Tree is empty\n");
		return 0;
	}
	
	#if (Simple)

		inorder(E->TreeRoot,out,counter,&error);
//	#else  
	
		
	#endif
}
/*
// A utility function to do inorder traversal of BST 
void inorder(typos_deikti root,FILE *out,int *counter,int *error,EvrPtr E) 
{ 
    if (!Tree_Keno(root)) 
    { 
        inorder(Tree_apaidi(root),out,counter,error); 
        if(*counter>7200)
        {
        	*error=1;
        	printf("Strange number of variables.Quit\n");
        	return;
		}
		else
		{
			*counter++;
			fprintf(out,"key : %d , arrival count  : %d , depart count : %d",,E->DataArray[E->TreeRoot->dedomena->arrayIndex].arrival_counter,E->DataArray[E->TreeRoot->dedomena->arrayIndex].depart_counter);
        	inorder(Tree_dpaidi(root),out,counter,error); 	 
		}
		
    } 
} 
*/


// A utility function to do inorder traversal of BST 
void inorder(typos_deikti root,FILE *out,int *counter,int *error)
{
	if(!Tree_Keno(root))
	{
		inorder(Tree_apaidi(root),out,counter,error);
		if(*counter>7200)
        {
        	*error=1;
        	printf("Strange number of variables.Quit\n");
        	return;
		}
		else
		{
			*counter++;
			//fprintf(out,"key : %d , arrival count  : %d , depart count : %d",,E->DataArray[E->TreeRoot->dedomena->arrayIndex].arrival_counter,E->DataArray[E->TreeRoot->dedomena->arrayIndex].depart_counter);
			fprintf(out,"key : %d",&(root->dedomena->key));
        	inorder(Tree_dpaidi(root),out,counter,error); 	 
		}
		
	}
}



