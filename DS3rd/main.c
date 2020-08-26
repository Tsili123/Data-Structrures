/************************************************************************
Programma pelaths	: AirportManagement.c
Syggrafeas			: 
Skopos				: skeleton main for askhsh 3
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "TSEvr.h"
#include "TSDDA.h"
#include "Evretirio.h"
#include "timer.h"

int main(int argc, char *argv[])
{ 
    //pointer for evretirio
	EvrPtr E;
	//pointer for dynamic array
	//with it i copy values from file
	//and i pass them to fuction as an argument
	TStoixeiouEvr *stoixeio;
	
	
	int i,max_stoixeia=0,max_routes=0,*source_id,*dest_id,*found,j,t=0,g=0,total=0,*countera,*counterb;
	//pointer for files
	FILE * fp,*fp2,*fp3;
	fp = fopen ("airportsLinuxRandom.txt", "r");
//	fp = fopen ("airportsLinuxSorted.txt", "r");
	fp2 = fopen ("routesLinux.txt", "r");
	fp3 = fopen ("file.txt", "w");
	double average;
	//variables for time count
	clock_t start_t1, end_t1,start_t2, end_t2,start_t3, end_t3,start_t4, end_t4,start_t5, end_t5;   //Preparing clock fuction and implementing it
	timestamp_t start, end;
	float time1,time2,time3,time4,time5,time6;
	
	//Initialize pointers
	int m=2;
	int p=12;
	int k=3;
	int l=3;
	//index=&p;
	found=&k;
	source_id=&m;
	dest_id=&p;
	countera=&t;
	counterb=&g;
	//count lines from airport's file
	max_stoixeia=countlines(fp);
	//count lines from route's file
	max_routes=countlines(fp2);
	printf("max routes %d\n",max_routes);
	//return pointers to the start
	rewind(fp2);
	rewind(fp);
	
	//allocate space for the array of copies
	stoixeio=malloc(sizeof(TStoixeiouEvr)*max_stoixeia);
	
	//Create evretirio
  	E=EvrConstruct(max_stoixeia);
	
	
	//printf("%d %d \n",*source_id,*dest_id);
	max_stoixeia=2047;
	//fill the array from file
  	lineByline(fp,stoixeio);
  	///start counting time
  	start_t1 = clock();	
  	start_t2 = clock();	
  	start_t3 = clock();	
 	start_t4 = clock();	
 	start_t5 = clock();	
 	//insert to evretirio from the array
 	//also put value to timers(stopwatch values)
  	for(i=0;i<max_stoixeia;i++)
  	{
  		if(EvrInsert(E,stoixeio[i]))
  		{
  			if(i==pow(2,9)-1)
	  		{
	  			end_t2 = clock();
			}
			else if(i==pow(2,10)-1)
	  		{
	  			end_t3 = clock();
			}
			else if(i==pow(2,11)-1)
	  		{
	  			end_t4 = clock();
			}
			else if(i==pow(2,12)-1)
	  		{
	  			end_t5 = clock();
			}
		}
		else
		{
			printf("Error inserting data.Quit.\n");
			break;
		}
  	}
  	//error check
  	if(i==max_stoixeia)
  		printf("All inserted\n");
  	//counter for the whole insertion
	end_t1 = clock();
	
	time1 = (float) (end_t1-start_t1) / CLOCKS_PER_SEC;
	time2 = (float) (end_t2-start_t2) / CLOCKS_PER_SEC;
	time3 = (float) (end_t3-start_t3) / CLOCKS_PER_SEC;
	time4 = (float) (end_t4-start_t4) / CLOCKS_PER_SEC;
	time5 = (float) (end_t5-start_t5) / CLOCKS_PER_SEC;
	
	
    printf("Time spent for insertion of 2^9-1 data  : %8.7f msec\n",time2*1000);
    printf("Time spent for insertion of 2^10-1 data : %8.7f msec\n",time3*1000);
    printf("Time spent for insertion of 2^11-1 data : %8.7f msec\n",time4*1000);
    printf("Time spent for insertion of 2^12-1 data : %8.7f msec\n",time5*1000);
    printf("Time spent for insertion of all the data: %8.7f msec\n",time1*1000);
    
 	//the array of copies is not needed anymore
 	//so destruct it
	destruct_copies(max_stoixeia,stoixeio);
	free(stoixeio);
    
    //error check
   // EvrSearch(E, 2965, 1,found);
   
   
   //timer for evrsearch does not work
    //start = clock(); 
  start = get_timestamp();
    for(i=0;i<max_routes;i++)
	{
		
		j=read_routes_file(fp2,source_id,dest_id);
	//	printf("%d %d\n",*source_id,*dest_id);
		EvrSearch(E, *source_id, 1 , countera, counterb);
		EvrSearch(E, *dest_id, 0 , countera, counterb);
	}
//	end=clock();
		end = get_timestamp();
	average=(end-start)/(double)max_routes;
	printf("mesos xronos anazitisis : %f\n",average);
//	time6 = (float) (end-start) / CLOCKS_PER_SEC;
//	printf("overall time for evrsearch : %8.7f sec\n ",time6);
	
	//print tree
	start = get_timestamp();
	EvrPrintAll(E, fp3,  &max_stoixeia);
	end = get_timestamp();
	average=(end-start)/(double)max_routes;
	printf("xronos ektupwsis %8.7f\n",average);
	total=*countera + *counterb;
	printf("total : %d\n",total);
	printf("counter a: %d\n",*countera);
	printf("counter b: %d\n",*counterb);
	printf("arithmos stoixeiwn %d  \n",max_stoixeia);
	
	//i counted values that contain '\N' 
	//values for source if and dest id
	// i dont know the meaning exactly i think that means NULL and i should not increase count
	
  //  printf("strange : %d\n",j);
    	
	//destruct evretirio
    EvrDestruct(&E);
    //printf("total : %d\n",total);
    
	getchar();	
	return 0;
}

