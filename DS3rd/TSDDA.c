#include "TSDDA.h"

int TSDDA_setValue (TStoixeiouDDA *target, TStoixeiouDDA source)
{
	(*target).key = source.key; 
	(*target).arrayIndex = source.arrayIndex;
	(*target).flag=0;//NOT USED
}

//NOT USED
int checkflag(TStoixeiouDDA node)
{
	if(node.flag==0)
	{
		node.flag=1;
		return 1;
	}
	else 
		return 0;
}
//NOT USED
int flag(TStoixeiouDDA node)
{
	return node.flag;
}

int TSDDA_getkey(TStoixeiouDDA treenode)
{
	return treenode.arrayIndex;
}

int TSDDA_setKey(keyType * key, keyType Val)
{
	*key=Val; /* basic type assignment */
}

int TSDDA_setIndex(int * Index, int Val)
{
	*Index=Val; /* basic type assignment */
}

int TSDDA_iso(TStoixeiouDDA s1, TStoixeiouDDA s2)
{
	return s1.key == s2.key;
}

int TSDDA_mikrotero(TStoixeiouDDA s1, TStoixeiouDDA s2)
{
	return s1.key < s2.key;
}

int TSDDA_megalytero(TStoixeiouDDA s1, TStoixeiouDDA s2)
{
	return s1.key > s2.key;
}

/* The Following are already Implemented using Above */

int TSDDA_mikrotero_iso(TStoixeiouDDA s1, TStoixeiouDDA s2)
{ 
    return TSDDA_mikrotero(s1,s2)||TSDDA_iso(s1,s2);
}

int TSDDA_megalytero_iso(TStoixeiouDDA s1, TStoixeiouDDA s2)
{
    return TSDDA_megalytero(s1,s2)||TSDDA_iso(s1,s2);
}

int TSDDA_diaforo(TStoixeiouDDA s1, TStoixeiouDDA s2)
{
    return !TSDDA_iso(s1,s2);
}

int TSDDA_writeValue(FILE *to, TStoixeiouDDA Elem)
{
	fprintf(to,"key : %d index : %d \n",Elem.key,Elem.arrayIndex);
}
