#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Session.h"

#define NUMBER_OF_STRINGS 500
#define NUMBER_OF_LETTERS_PER_STRING 30

int main(void) {
	InfoSessionPtr 	MySession1=NULL, MySession2=NULL;
	int i;
	char **array;
	int option, session;
	//create 1-D dynamic array of strings that are arguments in the fuctions
	array=malloc(sizeof(char*)*NUMBER_OF_STRINGS);
	for(i=0;i<NUMBER_OF_STRINGS;i++)
	{
		array[i] = malloc (NUMBER_OF_LETTERS_PER_STRING*sizeof(char));
	}
	//initialize index
	i=0;
	do {
		session= get_session();
		option = get_option();
		switch (option) {
		case 1:
			if(session==1)
			{
				printf("Type opening address: ");
				//get string from input and put it in the array
				fgets(array[i], sizeof(array[i]), stdin);
				remove_newline_ch(array[i]);
				MySession1 = SessionNew(array[i]);
				i++;		
			}
			else if(session==2)
			{
				printf("Type opening address: ");
				fgets(array[i], sizeof(array[i]), stdin);
				remove_newline_ch(array[i]);
				MySession2 = SessionNew(array[i]);
				i++;	
			}
			break;
		case 2:
			if(session==1)
			{
				SessionNewTab(MySession1);
			}
			else if(session==2)
			{
				SessionNewTab(MySession2);
			}
			break;
		case 3:
			if(session==1)
			{
				SessionTabShow(MySession1);
			}
			else if(session==2)
			{
				SessionTabShow(MySession2);
			}
			break;
		case 4:
			if(session==1)
			{
				SessionTabNext(MySession1);
			}
			else if(session==2)
			{
				SessionTabNext(MySession2);
			}
			break;
		case 5:
			if(session==1)
			{
				SessionTabPrev(MySession1);
			}
			else if(session==2)
			{
				SessionTabPrev(MySession2);
			}
			break;
		case 6:
			if(session==1)
			{
				SessionTabMoveLeft(MySession1);
			}
			else if(session==2)
			{
				SessionTabMoveLeft(MySession2);
			}
			break;
		case 7:
			if(session==1)
			{
				SessionTabMoveRight(MySession1);
			}
			else if(session==2)
			{
				SessionTabMoveRight(MySession2);
			}
			break;
		case 8:
			if(session==1)
			{
				printf("Type opening address: ");
				fgets(array[i], sizeof(array[i]), stdin);
				remove_newline_ch(array[i]);
				SessionNewOpeningAddress(MySession1,array[i]);
				i++;
			}
			else if(session==2)
			{
				printf("Type opening address: ");
				fgets(array[i], sizeof(array[i]), stdin);
				remove_newline_ch(array[i]);
				SessionNewOpeningAddress(MySession2,array[i]);
				i++;
			}
			break;
		case 9:
			if(session==1)
			{
				SessionShowOpeningAddress(MySession1);
			}
			else if(session==2)
			{
				SessionShowOpeningAddress(MySession2);
			}
			break;
		case 10:
			if(session==1)
			{
				SessionSiteNext(MySession1);
			}
			else if(session==2)
			{
				SessionSiteNext(MySession2);
			}
			break;
		case 11:
			if(session==1)
			{
				SessionSitePrev(MySession1);
			}
			else if(session==2)
			{
				SessionSitePrev(MySession2);
			}
			break;
		case 12:
			if(session==1)
			{
				SessionSiteShow(MySession1);
			}
			else if(session==2)
			{
				SessionSiteShow(MySession2);
			}
			break;
		case 13:
			if(session==1)
			{
				SessionTabClose(&MySession1);
			}
			else if(session==2)
			{
				SessionTabClose(&MySession2);
			}
			break;
		case 14:
			if(session==1)
			{
				SessionClose(&MySession1);
			}
			else if(session==2)
			{
				SessionClose(&MySession2);
			}
			break;
		case 15:
			if(session==1)
			{
				printf("Type address of new site: ");
				fgets(array[i], sizeof(array[i]), stdin);
				remove_newline_ch(array[i]);
				SessionNewAddress(MySession1,array[i]);
				i++;
			}
			else if(session==2)
			{
				printf("Type address of new site: ");
				fgets(array[i], sizeof(array[i]), stdin);
				remove_newline_ch(array[i]);
				SessionNewAddress(MySession2,array[i]);
				i++;
			}
			break;
			
		case 16:
			if(session==1)
			{
				//to better hide information i have typedefs on .c file
				//so I cant use variable sitenodeptr at main file
				//thats why i put fuction's value in the argument
				SessionOpenNewTab(MySession1,SessionGetCurrentSite(MySession1));
			}
			else if(session==2)
			{
				SessionOpenNewTab(MySession1,SessionGetCurrentSite(MySession2));
			}
			break;
		}
	}
	while (option);
	
	return 0;
}
