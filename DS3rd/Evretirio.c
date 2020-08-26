#include "Evretirio.h"

#define Simple 1

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

void copy_elements_to_evr(EvrPtr E,TStoixeiouEvr Data) ;
#if (Simple)
int inorder(typos_deikti root,FILE *out,int *error,EvrPtr E);
#else   
int AVLinorder(typos_deikti root,FILE *out,int *error,EvrPtr E);
#endif

EvrPtr EvrConstruct(int MaxSize){
/* Oi diafores tvn ylopoihsevn Simple kai AVL einai mikres - 
	mporeite na xrhsimopoihsete thn  domh #if ... #else ...#endif */
   EvrPtr evrnode;
   
   //create evr node and dynamic array
   evrnode=malloc(sizeof(EvrNode));
   evrnode->DataArray=malloc(sizeof(TStoixeiouEvr)*MaxSize);
   evrnode->Index=0;
   //call given fuction
	#if (Simple)
   		printf("use simple BST\n");
   		Tree_dimiourgia(&(evrnode->TreeRoot));   
	#else   
    	printf("use AVL BST\n");
    	AVLTree_dimiourgia(&(evrnode->TreeRoot));
	#endif
	return evrnode;
}
//I allocate the needed space for strings.
//Then i copy the strings
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

int EvrInsert(EvrPtr E, TStoixeiouEvr Data)
{
	
	//variable to check if everything goes ok
	int error=0;

	//and also to implement fuction
	typos_deikti pointer;
	TStoixeiouDDA *airport;
	airport=malloc(sizeof(TStoixeiouDDA));
	
	//just to pass the parameter
	//not needed value
	int ypsilotero=5;
	
	//copy array index value to pass it in the fuction	
	airport->arrayIndex=E->Index;
	airport->key=Data.airport_id;

	//copy to array of evr
	copy_elements_to_evr(E,Data);
	//put the airport id in the tree
	#if (Simple)
	Tree_eisagogi(&E->TreeRoot,*airport,&error);
	
	//error checking
	if(error==1)
	{
		printf("Error.Insertion didn't work.Maybe airport already exists\n");
		return 0;
	}
	#else   	
    AVLTree_eisagogi(&E->TreeRoot,*airport,&ypsilotero,&error);
    
    	
    if(error==1)
	{
		printf("Error.Insertion didn't work.Maybe airport already exists\n");
		return 0;
	}
	#endif
	
	/*
	printf("%s\n",E->DataArray[E->Index].city);
	printf("%s\n",E->DataArray[E->Index].country);
	printf("%s\n",E->DataArray[E->Index].iata);
	printf("%s\n",E->DataArray[E->Index].icao);
	printf("%s\n\n",E->DataArray[E->Index].name);
	
	*/
	//put index value to next available element
	E->Index++;
	
	free(airport);

	return 1;
}
//delete nodes with evr pointer
int EvrDestruct(EvrPtr *E)
{
	int i;
	#if (Simple)
	printf("use simple BST destruct\n");
	Tree_katastrofi(&((*E)->TreeRoot));
	//if tree is not empty we have an error
	if(!Tree_keno((*E)->TreeRoot))
	{
		printf("Error\n");
		return 0;
	}	
	#else   
	printf("use AVL BST destruct\n");
    AVLTree_katastrofi(&(*E)->TreeRoot);
    if(!AVLTree_keno((*E)->TreeRoot))
	{
		printf("Error\n");
		return 0;
	}	
	#endif
	//free the array's elements
	for(i=0;i<(*E)->Index-1;i++)
	{
		destruct_data(&(*E)->DataArray[i]);
	}
	//destroy pointers
	free((*E)->DataArray);
	
	free(*E);
	
	*E=NULL;
	//all good
	return 1;
}
//countera is for values that were found
//counterb is for values that were not found
int EvrSearch(EvrPtr E, keyType key, int InOut, int * countera,int *counterb)
{
	typos_deikti *pointer;
	/*
	typos_deikti test;
	pointer=&test;
	*pointer=test;
	*/
//	TStoixeiouDDA value;
	//prepare values to pass in the fuction
	//by allocating space and copying data
	TStoixeiouDDA *airport;
	//k variable that indicates if the value was found or not
	int k=0;
	//index that shows tha place where the key is in the array
	int index;

	
	airport=malloc(sizeof(TStoixeiouDDA));
	//copy value
	airport->key=key;
	
 	#if (Simple)
 	//eror check
 	if(Tree_keno(E->TreeRoot))
	{
		printf("Error.The tree is empty or the root is NULL pointer.\n");
		return 0;
	}
	
	//calling given fuction
	Tree_anazitisi(E->TreeRoot,*airport,pointer,&k);
	
	//just  comments with code that did not work
	//It was for not counting double and more times every airport's arrivals and departures
	
//	if((*pointer)!=test)
//	{
	//		printf("check\n");
			
		//checkflag(Tree_data(*pointer));
	//	value=Tree_data(test);
	//	if(checkflag(value))
	//	{
//			if it was found
			if(k==1)
			{
				
				(*countera)++;
			//	printf("vrethike %d \n",key);
				//get array's index in evretirio
				index=Tree_data_key(*pointer);
			//	printf("%d\n",index);
			//increase the counter depending on the inout
			//zero for arrival
			//one for the depart
				if(InOut==0)
				{
					E->DataArray[index].arrival_counter++;	
				//	printf(" ac : %d\n",E->DataArray[index].arrival_counter);		
				}
				else if(InOut==1)
				{
					E->DataArray[index].depart_counter++;
				//	printf(" ad : %d\n",E->DataArray[index].depart_counter);
				}
			}
			//if key was not found
			else if(k==0)
			{
				(*counterb)++;
			//	printf("The %d data was not found.\n",key);
				return 0;
			}
	//	}
	//*/
//	}
//same for avl with different fuctions
	#else   
	if(AVLTree_keno(E->TreeRoot))
	{
		printf("Error.The tree is empty or the root is NULL pointer.\n");
		return 0;
	}
		
 	AVLTree_anazitisi(E->TreeRoot,*airport,pointer,&k);
 	
 	if(k==1)
	{
		(*countera)++;
	//	printf("vrethike %d \n",key);
		index=AVLTree_data_key(*pointer);
		if(InOut==0)
		{
			E->DataArray[index].arrival_counter++;
		}
		else if(InOut==1)
		{
			E->DataArray[index].depart_counter++;
		}
	}
	else  if(k==0)
	{
		(*counterb)++;
	//	printf("The %d data was not found.\n",key);
		return 0;
	}

	#endif
	//free the node that had the copies
	free(airport);
	//code for correct execution
	return 1;
	
}

//fuction that prints the arrivals and departures for every airport in a file
int EvrPrintAll(EvrPtr E, FILE *out, int *counter)
{
	
	int error;
	*counter=0;

	
	#if (Simple)
	//error check
	if(Tree_keno(E->TreeRoot))
	{
		printf("Tree is empty\n");
		return 0;
	}
	//counter for  printed airports
	*counter=inorder(E->TreeRoot,out,&error,E);
	//AVL implementation
	#else  
	if(AVLTree_keno(E->TreeRoot))
	{
		printf("Tree is empty\n");
		return 0;
	}
	*counter=AVLinorder(E->TreeRoot,out,&error,E);
	#endif
	return 1;
	
}



#if (Simple)
// A utility function to do inorder traversal of BST 
int inorder(typos_deikti root,FILE *out,int *error,EvrPtr E)
{
	int counter=1;
	
	if(!Tree_keno(root))
	{
		//count  left sub tree
		counter+=inorder(Tree_apaidi(root),out,error,E);
		//Because with separate files I cant access the data from this file
		//so i created a temporary node to copy values from tree with fuctions
		TStoixeiouDDA *variable;
		variable=malloc(sizeof(TStoixeiouDDA));
		TSDDA_setValue(variable,Tree_data(root));
		//print in file
		fprintf(out,"key : %d ",variable->key);
		fprintf(out,"depart count : %d ",E->DataArray[variable->arrayIndex].depart_counter);
		fprintf(out,"arrival count  : %d \n",E->DataArray[variable->arrayIndex].arrival_counter);
		//free
		free(variable);
		////count  right sub tree
		counter+=inorder(Tree_dpaidi(root),out,error,E); 
	}
	else 
	{
		//base case
		return 0;
	}
	return counter;
}
#else
//same for AVL
int AVLinorder(typos_deikti root,FILE *out,int *error,EvrPtr E)
{
	int counter=1;
	
	if(!AVLTree_keno(root))
	{
		counter+=AVLinorder(AVLTree_apaidi(root),out,error,E);
		TStoixeiouDDA *variable;
		variable=malloc(sizeof(variable));
		TSDDA_setValue(variable,AVLTree_data(root));
		fprintf(out,"key : %d ",variable->key);
		fprintf(out,"depart count : %d ",E->DataArray[variable->arrayIndex].depart_counter);
		fprintf(out,"arrival count  : %d ",E->DataArray[variable->arrayIndex].arrival_counter);
		free(variable);
		counter+=AVLinorder(AVLTree_dpaidi(root),out,error,E); 
	}
	else 
	{
		return 0;
	}
	return counter;
}
#endif

