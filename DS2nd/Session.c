#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Session.h"

//Complete concealment of information(apokripsi)
//by defining the pointers at .c implementation file
typedef struct TabNode *TabNodePtr;
typedef struct SiteNode *SiteNodePtr;

//some decleration
TabNodePtr insert_tabnode_after_identifier(SiteNodePtr site,TabNodePtr identifier);
void swap_pointers(TabNodePtr *value1,TabNodePtr *value2);
void delete_site_list(SiteNodePtr FirstSite);
void delete_TabNode(InfoSessionPtr *Session,TabNodePtr *identifier);
void SessionOpenNewTab(InfoSessionPtr Session,SiteNodePtr site);
void print(SiteNodePtr sitelist);
SiteNodePtr SessionGetCurrentSite(InfoSessionPtr Session);

//Given data
struct InfoSession {
	TabNodePtr FirstTab;
	TabNodePtr LastTab;
	TabNodePtr CurrTab;
	TabNodePtr AuxTab;
	char* 	  OpeningAddress;
};

struct TabNode {	
	TabNodePtr PrevTab, NextTab;
	SiteNodePtr FirstSite;
	SiteNodePtr CurrSite;
	SiteNodePtr UpSite;
};
//I added some tabnode pointers for the bonus function
struct SiteNode{
	SiteNodePtr PrevSite, NextSite;
	TabNodePtr UpTab;
	char *Address;
};



/*
The parameter of the fuction is the string opening address
that defines the infosession node 

*/



InfoSessionPtr SessionNew(char * OpeningAddress)
{
	//Create infosession node
	InfoSessionPtr info;
	//create first tab node
	TabNodePtr tab;
	//create first site node under the first tab
	SiteNodePtr site;
	
	//allocate the proper memory for each one of them
	info = malloc(sizeof(struct InfoSession));
	tab = malloc(sizeof(struct TabNode));
	site = malloc(sizeof(struct SiteNode));
	
	//make the pointers point at the desired memory address
	//Below,current tab in infosession node points at the first tab that is created etc.
	info->CurrTab = tab;
	info->FirstTab = tab;
	info->LastTab = tab;
	info->AuxTab = NULL;
	/*
	Debugging info
	
	printf("%d\n",info->CurrTab );
	printf("%d\n",info->FirstTab );
	printf("%d\n",info->LastTab );
	printf("%d\n",info->AuxTab  );
	*/
	//copy the address of the string to infonode's opening address
	info->OpeningAddress=OpeningAddress;
	
	//Debugging info
	//	printf("%p",info->OpeningAddress);
	
	//Because the first tab is the only one in the list
	//I made it to point at itself
	tab->PrevTab = tab;
	tab->NextTab = tab;
	//The first site under the tab is the current site also
	tab->CurrSite = site;
	tab->FirstSite = site;
	tab->UpSite=NULL;
	
	/*
	Debugging info
	
	printf("%d\n",tab->PrevTab );
	printf("%d\n",tab->NextTab );
	printf("%d\n",tab->CurrSite );
	printf("%d\n",tab->FirstSite );
	printf("%d\n",tab->UpSite );
	*/
	
	//uptab is the tab that owns the list of sites
	//first site has neither previous site nor next site
	//the site's address is the parameter of the fuction
	site->UpTab=tab;
	site->PrevSite=NULL;
	site->NextSite=NULL;
	site->Address=OpeningAddress;
	
	/*
	Debugging info
	
	printf("%d\n",site->UpTab );
	printf("%d\n",site->PrevSite );
	printf("%d\n",site->NextSite );
	printf("%p\n",site->Address );
	printf("%d\n",info );
	*/
	
	//return the address of the info node only
	return info;
}

/*
Insert tabnode after identifier
parameters:	address of site node and address of the last tab(identifier)
Algorithm of the tab's insertion:

1.create temporary tabnode

2.insert site's address to tab's struct part
	        temporary
prevTab  FirstSite    CurrSite    NextTab
X		 site param   site param  X

3.Put the right addresses at at prevtab and nexttab part of the new node
			temporary
prevTab  FirstSite    CurrSite    NextTab
last tab  site param   site param  identifier's next tab
(identifier)
4.Put the right address at the [temporary's  next tab] previous tab struct part(because we insert after identifier)
				identifier's pre next tab
	prevTab  				FirstSite    CurrSite    NextTab
temporary(new tab node)			X			X			X

5.Put the right address at the identifier's(previous last tab)next tab struct part
			identifier(previous last tab)
prevTab  FirstSite    CurrSite    NextTab
X 			X			X			temporary(new tab node)

6.return the address of the new node
*/


TabNodePtr insert_tabnode_after_identifier(SiteNodePtr site,TabNodePtr identifier)
{
	//1
	TabNodePtr temporary;
	
	temporary=malloc(sizeof(struct TabNode));
	
	
	
	temporary->UpSite=NULL;
	/*
	Debugging info
	
	printf("%p\n",temporary );
	
	printf("%p\n",temporary->UpSite );
	*/
	//2
	temporary->FirstSite = site;
	/*
	Debugging info
	
	printf("%p\n",temporary->FirstSite );
	*/
	temporary->CurrSite = site;
	/*
	Debugging info
	printf("%p\n",temporary->CurrSite );
	*/
	//3
	temporary->NextTab=identifier->NextTab;
	/*
	Debugging info
	
	printf("%p\n",temporary->NextTab);
	*/
	temporary->PrevTab=identifier;
	/*
	Debugging info
	
	printf("%p\n",temporary->PrevTab);
	*/
	//4
	temporary->NextTab->PrevTab=temporary;
	/*
	Debugging info
	
	printf("%p\n",temporary->NextTab->PrevTab);
	*/
	//5
	identifier->NextTab=temporary;
	/*
	Debugging info
	
	printf("%p\n",identifier->NextTab);
	*/
	//6
	return temporary;
}

/*
Inserts the tab node at the end of the double linked cyclic list
*/
void SessionNewTab(InfoSessionPtr Session)
{

	//create the first site under the new tab
	SiteNodePtr site;
	//allocate memory for the site
	site = malloc(sizeof(struct SiteNode));
	/*
	Debugging info
	printf("%p\n",Session->CurrTab );
	printf("%p\n",Session->LastTab );
	*/

	//set the current tab's value with the new node value
	Session->CurrTab=insert_tabnode_after_identifier(site,Session->LastTab);
	/*
	Debugging info
	
	printf("%p\n",Session->CurrTab );
	printf("%p\n",Session->FirstTab );
	*/
	
	//last tab's new value is the same as the current tab of the infosession
	Session->LastTab=Session->CurrTab;
	/*
	Debugging info
	
	printf("%p\n",Session->LastTab );
	*/
	
	//Set the proper values for the new site that is created under the new tab
	site->UpTab=Session->CurrTab;
	site->PrevSite=NULL;
	site->NextSite=NULL;
	site->Address=Session->OpeningAddress;
	/*
	Debugging info
	
	printf("%d\n",site->UpTab );
	printf("%d\n",site->PrevSite );
	printf("%d\n",site->NextSite );
	printf("%p\n",site->Address );
	*/
}
//Prints the address of the currsite that currtab is pointing to.
void SessionTabShow(InfoSessionPtr Session)
{
	printf("Opening address of current tab is : %s\n",Session->CurrTab->CurrSite->Address);
}
//Ctrl+tab fuction on the real browser
//The current tab in infosession now has the value of previous current tab's next tab node
void SessionTabNext(InfoSessionPtr Session)
{
	Session->CurrTab=Session->CurrTab->NextTab;
}
//Ctrl+shift+tab fuction on the real browser
//The current tab in infosession now has the value of previous current tab's previous tab node
void SessionTabPrev(InfoSessionPtr Session)
{
	Session->CurrTab=Session->CurrTab->PrevTab;
//	printf("%p\n",Session->CurrTab);
}

//To change the value of a pointer you need a double pointer
void swap_pointers(TabNodePtr *value1,TabNodePtr *value2)
{
	TabNodePtr temp;
	temp=*value1;
	*value1=*value2;
	*value2=temp;
}


void SessionTabMoveLeft(InfoSessionPtr Session)
{
	TabNodePtr left ;
	left = Session->CurrTab->PrevTab;//(1)
//	printf("%p\n",Session->CurrTab->PrevTab);
//	printf("%p\n",Session->CurrTab->PrevTab->PrevTab);
	if(Session->CurrTab->PrevTab==Session->LastTab  )
	{
		printf("Dont move tabs in a cyclic way\n");
		return;
	}
	//corner cases
	if(left->NextTab==Session->LastTab)
	{
		Session->LastTab=left;
	}
	if(left==Session->FirstTab)
	{
		Session->FirstTab=Session->CurrTab;
	}
	if(Session->CurrTab->NextTab==Session->CurrTab->PrevTab )
	{
		printf("There are only 2 nodes in the list\n");
		Session->CurrTab=left;
		return;
	}

//	printf("%p\n",left);
	left->NextTab = Session->CurrTab->NextTab;//(2)
//	printf("%p\n",left->NextTab);
	Session->CurrTab->PrevTab = left->PrevTab;//(3)
///	printf("%p\n",Session->CurrTab->PrevTab);
	left->PrevTab->NextTab=Session->CurrTab;//(7)
//	printf("%p\n",left->PrevTab->NextTab);

	left->NextTab->PrevTab = left;//(4)
//	printf("%p\n",left->NextTab->PrevTab);
		
	Session->CurrTab->NextTab = left;//(5)
//	printf("%p\n",Session->CurrTab->NextTab);
		
	left->PrevTab=Session->CurrTab;//(6)
//	printf("%p\n",left->PrevTab);


}

void SessionTabMoveRight(InfoSessionPtr Session)
{
	TabNodePtr right ;
	right = Session->CurrTab->NextTab;//(1)
	/*
	printf("%p\n",Session->CurrTab->NextTab);
	printf("%p\n",Session->CurrTab->NextTab->NextTab);
	*/
	if(Session->CurrTab->NextTab==Session->FirstTab )
	{
		printf("Dont move tabs in a cyclic way\n");
		return;
	}
	//corner cases
	if(right==Session->LastTab)
	{
		Session->LastTab=Session->CurrTab;
	}
	if(right->PrevTab==Session->FirstTab)
	{
		Session->FirstTab=right;
	}
	if(Session->CurrTab->NextTab==Session->CurrTab->PrevTab )
	{
		printf("There are only 2 nodes in the list\n");
		Session->CurrTab=right;
		return;
	}
	/*
	printf("%p\n",right);
	printf("%p\n",Session->CurrTab);
	*/
	right->PrevTab = Session->CurrTab->PrevTab;//(2)
	/*
	printf("%p\n",right->PrevTab);
	*/
	Session->CurrTab->NextTab = right->NextTab;//(3)
	/*
	printf("%p\n",Session->CurrTab->NextTab);
	*/
	right->NextTab->PrevTab=Session->CurrTab;//(7)
	/*
	printf("%p\n",right->NextTab->PrevTab);
	*/
	right->PrevTab->NextTab = right;//(4)
	/*
	printf("%p\n",right->PrevTab->NextTab);
	*/		
	Session->CurrTab->PrevTab = right;//(5)
	/*
	printf("%p\n",Session->CurrTab->PrevTab);
	*/	
	right->NextTab=Session->CurrTab;//(6)
	/*
	printf("%p\n",right->NextTab);
	*/
}


//Change the value of the openingAddress in the infosession node
void SessionNewOpeningAddress(InfoSessionPtr Session,char *string)
{
	Session->OpeningAddress=string;//copy addresses
}
//print it
void SessionShowOpeningAddress(InfoSessionPtr Session)
{
	printf("Opening Address is : %s" , Session->OpeningAddress);
}
//Change the value of the pointer to current site with the address of the current site's next site
void SessionSiteNext(InfoSessionPtr Session)
{
	Session->CurrTab->CurrSite=Session->CurrTab->CurrSite->NextSite;
}
//Change the value of the pointer to current site with the address of the current site's previous site
void SessionSitePrev(InfoSessionPtr Session)
{
	Session->CurrTab->CurrSite=Session->CurrTab->CurrSite->PrevSite;
}
//Prints the address string of current site
void SessionSiteShow(InfoSessionPtr Session)
{
	printf("Opening address of current site is : %s\n",Session->CurrTab->CurrSite->Address);
}
//From the notes of the class
void delete_site_list(SiteNodePtr FirstSite)
{
	SiteNodePtr todel,todel2;
	//first site 
	todel=FirstSite;
	//Until we reach the end
	while(todel!=NULL)
	{
		
		todel2=todel;
		//go to the next node
	 	todel=todel->NextSite;
	 	//free the previous
	 	free(todel2);
	}

}

/*
parameters:infosession node , identifier(double pointer because we change the value of the pointer)

Algorithm

Because we have a cyclic linked list we create a condition to check if:
1.we have to change value of pointers because we have more than one node in the list
2.There is only one node in the list so what we have to do is a simple free

Because the list is also doubly linked we need to modify the pointers in step 1 in a specific way.

Identifier is the address of the session's current tab .The current tab is going to be deleted


*/
void delete_TabNode(InfoSessionPtr *Session,TabNodePtr *identifier)
{
	TabNodePtr temporary,previous;
	/*
	printf("%p\n",Session->CurrTab);
	printf("%p\n",Session->CurrTab->PrevTab);
	printf("%p\n",Session->FirstTab);
	*/
	
	//If there is no node just return
	if(*identifier==NULL)
	{
		//prevent segme fault NULL->something
		return;
	}
	
	//Set the correct value of current tab
	if((*identifier)->UpSite!=NULL)
	{
	//	printf("%p\n",(*Session)->CurrTab);
	//	printf("%p\n",(*Session)->CurrTab->CurrSite);
		(*Session)->CurrTab=(*identifier)->UpSite->UpTab;
		(*Session)->CurrTab->CurrSite=(*identifier)->UpSite;
		//	printf("%p\n",(*Session)->CurrTab);
	//	printf("%p\n",(*Session)->CurrTab->CurrSite);
	}
	else
	{
		//normal procedure
		//set the current tab as the identifier's next tab
		(*Session)->CurrTab=(*identifier)->NextTab;
	}
	
	//We set temporary as the identifier 
	temporary=*identifier;
	//The previous pointer has the the address of the previous tab of the temporary/*identifier
	previous=(*identifier)->PrevTab;
	/*
	printf("%p\n",previous->NextTab);
	*/
	//We then set identifier as the next tab of the temporary tab (identifier's next struct part or session's current tab new value)
	*identifier=temporary->NextTab;
	
	//If there is no node just return
	if(*identifier==NULL)
	{
		return;
	}
	
	if((*Session)->FirstTab->NextTab!=(*Session)->FirstTab)//not only one
	{
		//Correct previous tab pointer
		previous->NextTab=*identifier;//or = temporary->NextTab
		//Correct the previous struct part of the  current tab's next tab  
		(*identifier)->PrevTab=previous;
		
	//	In case we delete first or last tab of the session,we put the proper values in the infosession node
		if((*Session)->FirstTab==temporary)//first node
			(*Session)->FirstTab=temporary->NextTab;
		else if((*Session)->LastTab==temporary)//last node
			(*Session)->LastTab=temporary->PrevTab;
		
		//delete the list of sites under the tab
		delete_site_list(temporary->FirstSite);
		
		//free the desired node
		free(temporary);
	}
	else//if only 1 node
	{
		//delete the list of sites under the tab
		delete_site_list(temporary->FirstSite);
		//free the memory for the first and only tab node
		free((*Session)->FirstTab);
		//There is no node in the list anymore
		//free the info node
		free(*Session);
		*Session=NULL;
	}
	
	/*
	printf("%p\n",(*identifier)->PrevTab);
	printf("%p\n",previous->NextTab);
	printf("%p\n",Session->CurrTab);
	printf("%p\n",Session->CurrTab->PrevTab);
	*/
}


//Deletes a tab node from the double linked cyclic list
void SessionTabClose(InfoSessionPtr *Session)
{
	TabNodePtr identifier;
	/*
	printf("%p\n",(*Session)->LastTab);
	printf("%p\n",(*Session)->CurrTab->PrevTab);
	printf("%p\n",(*Session)->CurrTab->NextTab->PrevTab);
	printf("%p\n",(*Session)->CurrTab);
	*/
	//set the identifier as the current tab
	identifier=(*Session)->CurrTab;
	//delete the desired node and change the value of the identifier
	delete_TabNode(Session,&identifier);
	/*
	printf("%p\n",(*Session)->LastTab);
	printf("%p\n",(*Session)->CurrTab->PrevTab);
	printf("%p\n",(*Session)->CurrTab);
	*/
}

//From the notes of the class
void SessionClose(InfoSessionPtr *Session)
{
	TabNodePtr todel,todel2;
	//first site 
	todel=(*Session)->FirstTab;
	
	//Until we reach the end
	while(todel!=(*Session)->LastTab)
	{
		todel2=todel;
		//go to the next node
		todel=todel->NextTab;
		//free the previous
		delete_TabNode(Session,&todel2);
		
	}
	//delete last node(because the list has no null to reach the last)
	delete_TabNode(Session,&todel);

}



/*
This fuction deletes all the other sites after the current site.
Then inserts a site after current site , makes is the new current site 
and also puts an address in its struct part.
*/
void SessionNewAddress(InfoSessionPtr Session,char *Address)
{
	
	SiteNodePtr site,identifier;
	//create a site node
	site=malloc(sizeof(struct SiteNode));
	//shortcut(simplicity)
	identifier= Session->CurrTab->CurrSite;
	//delete the list of sites after the current site
	delete_site_list(identifier->NextSite);
	//put the correct pointer value at current site's next site struct part
	identifier->NextSite=site;
	//The correct value of the previous part in the new site
	site->PrevSite=identifier;
	//The correct value of the next part in the new site
	site->NextSite=NULL;
	//The correct value of uptab
	site->UpTab=Session->CurrTab;
	//copy the opening address inside
	site->Address=Address;
	//Put the correct value on the current site of the session
	Session->CurrTab->CurrSite=site;
	
	print(Session->CurrTab->FirstSite);
}

void print(SiteNodePtr sitelist) /* Print elements of list */
{ 
	while (sitelist != NULL) 
	{
	 	/* Visit list elements up to the end */
		printf("%s --> ", sitelist->Address); /* Print current element */
		sitelist = sitelist->NextSite; /* Go to next element */
	}
	printf("NULL\n"); /* Print end of list */
}

void remove_newline_ch(char *line)
{
    int new_line = strlen(line) -1;
    if (line[new_line] == '\n')
        line[new_line] = '\0';
}

/*
Inserts the tab node at the end of the double linked cyclic list
*/
void SessionOpenNewTab(InfoSessionPtr Session,SiteNodePtr site)
{
	//create new site node for new tab
	SiteNodePtr new_site;
	new_site=malloc(sizeof(struct SiteNode));
	//check if there are more than one tab that are opened by the same site
	TabNodePtr temp,start;
//	printf("%p\n",Session->CurrTab);
	start=Session->CurrTab;
	temp=start;
	if(temp->NextTab->UpSite==NULL)
	{
		//nothing
		//if there is not one tab  that is opened by this site ignore ...
	}
	else
	{
		//move to the last tab that is opened by this site
		while(temp->NextTab->UpSite->UpTab==Session->CurrTab)
		{
			temp=temp->NextTab;
			if(temp->NextTab->UpSite==NULL)
			{
				//if we reach last break loop
				break;
			}
		}
	}
	
	//We want to implement the real browser search
	//In that implementation we see that the tabs that are opened by a site are alligned from first to last
	//for example the first tab that is opened by the site is just right of the tab that owns this site
	//the second tab that is opened by the site is just right of the first tab that is opened by the tab that owns this site etc etc
	if(temp!=start)
	{
		//for every other tab that is opened
		//we reach the last tab
		Session->CurrTab=temp;
		Session->CurrTab=insert_tabnode_after_identifier(new_site,Session->CurrTab);
		//note that the allignment doesn't work for some tab if we move that one tab a lot right or left from the tab that owns the current site
		//because its not on the secquence of the tabs that are opened by a specific site  
	//	printf("%p\n",Session->CurrTab);
	}
	else
	// if its the first tab
		Session->CurrTab=insert_tabnode_after_identifier(new_site,Session->CurrTab);
	//printf("%p\n",Session->CurrTab);
	//Set an upsite value so as if we delete the tab then we are sent at the site in which we opened the tab
	Session->CurrTab->UpSite=site;
	//set new site node values
	new_site->UpTab=Session->CurrTab;
	new_site->PrevSite=NULL;
	new_site->NextSite=NULL;
	new_site->Address=Session->OpeningAddress;
//	printf("%p\n",Session->CurrTab->UpSite);
//	printf("%p\n",site);
}

SiteNodePtr SessionGetCurrentSite(InfoSessionPtr Session)
{
	return Session->CurrTab->CurrSite;
}

void print_options(void)
{
        printf("\n");
        printf("0. Exit\n");
        printf("1. SessionNew\n");
        printf("2. SessionNewTab\n");
        printf("3. SessionTabShow\n");
        printf("4. SessionTabNext\n");
        printf("5. SessionTabPrev\n");
        printf("6. SessionTabMoveLeft\n");
        printf("7. SessionTabMoveRight\n");
        printf("8. SessionNewOpeningAddress\n");
        printf("9. SessionShowOpeningAddress\n");
        printf("10. SessionSiteNext\n");
        printf("11. SessionSitePrev\n");
        printf("12. SessionSiteShow\n");
        printf("13. SessionTabClose\n");
        printf("14. SessionClose\n");
        printf("15. SessionNewAddress\n");
        printf("16. SessionOpenNewTab\n");
        printf("Enter your input (0-16): ");
}

void print_session(void)
{
        printf("\n");
        printf("Press Ctrl C to exit \n");
        printf("1. 1st Session \n");
        printf("2. 2nd Session\n");
        printf("Enter your input (0-2): ");
}

int get_option()
{
	char buf[100];
	int option;

	option = -1;
	while (option < 0 || option > 16) {
		print_options();
		fgets(buf, sizeof(buf), stdin);
		sscanf(buf, "%d", &option);
	}
	return option;
}

int get_session()
{
	char buf[100];
	int session;
	
	session=0;
	
	while (session <= 0 || session > 2) {
		print_session();
		fgets(buf, sizeof(buf), stdin);
		sscanf(buf, "%d", &session);
	}
	return session;
}







