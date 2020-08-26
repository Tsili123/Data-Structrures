/*************************************************
Arxeio ylopoihshs	: ch6_Simulation.c
Syggrafeas			: Y. Cotronis 07/03/2016
Skopos				: Ylopoihsh ouras prosomoiwshs
Revision 			:  Aris Tsilifonis 21/3/19
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "ch6_QArray.h"
#include "TStoixeiouOuras.h"
#include "TController.h"


int QNUMBER;

int main(void)
{	TOuras      	*oura;				 /*oura pelatwn-aytokinhtvn */
	TController		*controller;			// Elegktis
	float			pithanotita_afiksis; /*pi8anothta afikshs*/
	unsigned int	xronos_eksipiretisis;/*xronos e3yphrethshs enos pelath*/ 
	unsigned int	xronos_prosomoiosis; /*synolikos xronos prosomoiwshs*/
	unsigned int i,j,k;//test variable
	unsigned int index;//index for queue with min cars
	unsigned int 	arithmos_pelaton_tameiou=0;
	
	unsigned int	xronos;				 /*roloi prosomoiwshs*/
	unsigned int	enapomenon_xronos;	 /*xronos gia to telos e3yphrethshs enos pelath*/
	unsigned int	arithmos_pelaton=0; 	 /*plh8os e3yphreth8entwn pelatwn*/
	unsigned int 	left_cars;           //cars that were not serviced
	unsigned int 	cars_entered_queue;
	unsigned int	cars_left_queue;
	unsigned int	xronos_anamonis;	 /*synolikos xronos anamonhs*/
	unsigned int 	min_xronos_eksipiretisis;
	unsigned int	max_xronos_eksipiretisis;
	int    duration;//duration of service at the toll
	TSOuras		Pelatis;		 	/* o pelaths sthn oyra*/
	float			mesos_xronos;		 /*mesos xronos anamonhs tvn pelatvn*/
	float			randomAfixi;
	int             tamiasInactive;
	int 			tamiasBusy;
	time_t			t;
	
	

	printf("Dwste units of time prosomoiwshs (0 <=), pi8anothta afikshs in unit of time (0,1) kai min max xrono e3yphrethshs (>=1) in unit of times )\n");
	scanf("%u %f %u %u %d",&xronos_prosomoiosis,&pithanotita_afiksis,&min_xronos_eksipiretisis,&max_xronos_eksipiretisis,&QNUMBER);
	getchar();
	printf("H prosomoiwsh 8a diarkesei %4u units of time.\n",xronos_prosomoiosis);
	printf("H pi8anothta afikshs pelath se ena unit of time einai: %4.2f.\n",pithanotita_afiksis);
	printf("Oi minimum kai maxumum times tou xronou e3yphrethshs enos pelath einai %d units & %d of time .\n",min_xronos_eksipiretisis,max_xronos_eksipiretisis);
	
	//Allocate dynamic array of queues and controllers
	oura=CreateMultiQueue();
	controller=CreateMultiController();
	
	//Initialize them 
	for(i=0;i<QNUMBER;i++)
	{
		OuraDimiourgia(&oura[i]);
		ControllerDimiourgia(&controller[i]);
	}

	//initialize test variables and time
	xronos = 0;
	xronos_anamonis =0;
	srand(time(&t));
	i=0;
	index=0;

	while( xronos < xronos_prosomoiosis )
	{	/* Pelatis- Aytokinhto  */
		randomAfixi = (float)rand()/(float)RAND_MAX; 

		if ( randomAfixi < pithanotita_afiksis ){
			PelatisSetXronoEisodou(&Pelatis, xronos);
			duration = rand()%(max_xronos_eksipiretisis-min_xronos_eksipiretisis+1)+min_xronos_eksipiretisis;
			//etsi apofeugoume megalous xronous eksipiretisis
			if(duration>=8*(max_xronos_eksipiretisis-min_xronos_eksipiretisis+1)/10 && max_xronos_eksipiretisis>5*(min_xronos_eksipiretisis))
			{
				//prostimo- o pelatis dn eisagetai stin oura
				//	printf("Customer %d has been kicked-out with duration of service : %d \n",i,duration);
				//	i++;	
			}
			else
			{
				PelatisSetXronoEksipiretisis(&Pelatis, duration);
			//	i++;
			//	printf("Customer %d duration of service : %d \n",i,duration);
				index=findQueueWithMinCars(oura);
				if(controller[index].available==false)
				{
					//dont add more customers to the queue
				}
				else if(ouraAV(oura))//if queue is open(If the there is controller for the queue)
				{
					if (!OuraProsthesi(&oura[index], Pelatis))//prosthesi stin oura
					{
						//an gemisei h oura to programma kremaei
	                  printf("H oyra einai mikrh! H prosomoivsh stamataei \n");
	                  getchar();
	                  return 0;
	        		};
				}
			}
    	};
    	
    	/* Tamies-Elegxos */
    	for(j=0;j<QNUMBER;j++)
    	{
    		if ( ControllerFree(controller[j]) && ControllerAV(&controller[j]))	/*eley8eros tamias*/
				if (!OuraKeni(oura[j]))			/*yparxei pelaths*/
				{	
					OuraApomakrynsh(&oura[j],&Pelatis);		/*phgainei sto tamio*/
					xronos_anamonis += xronos - PelatisGetXronoEisodou(Pelatis);	/*ypologismos xronoy paramonhs sthn oura*/
					//printf("Time is %d Time out %d\n", xronos, PelatisGetXronoEisodou(Pelatis)); 
					xronos_eksipiretisis=PelatisGetXronoEksipiretisis(Pelatis);
					ControllerNewCustomer(&controller[j]);
					ControllerSetXrono(&controller[j],xronos_eksipiretisis); /* kallyptei to trexon unit time */
				}else ControllerNoWork(&controller[j]);//tamias adranis
			else
			{
				if(!ControllerAV(&controller[j]))//an to tameio exei kleisei sunexise sto epomeno
					continue;
				else if(!ControllerFree(controller[j]))
					ControllerBusy(&controller[j]);		/*o tamias apasxolhmenos me pelath */
			}
				
		}
		//den einai kali texniki na kleinw oures
		//alla egine gia na fanei h leitourgia stin askisi
		
		for(j=0;j<QNUMBER;j++)
		{
			tamiasInactive=ControllerGetInactiveXronos(controller[j]);
			if(tamiasInactive > xronos_prosomoiosis/2 )//an o tamias einai adranis gia toso xroniko diastima kleise to tameio kai tin oura
			{
				controller[j].available=false;
				oura[j].available=false;
			}
		}
		
		
		for(j=0;j<QNUMBER;j++)
		{
			if(OuraCrowded(oura[j]))//an h oura exei pollous pelates dimiourgise mia epipleon oura
			{
					
				oura=realloc(oura,(QNUMBER+1)*sizeof(TOuras));
				controller=realloc(controller,(QNUMBER+1)*sizeof(TController));
				QNUMBER++;//megalwse ton arithmo twn ourwn
				OuraDimiourgia(&oura[QNUMBER-1]);//arxikopoihse times gia to neo tameio-controller
				ControllerDimiourgia(&controller[QNUMBER-1]);
			}
		}
	
			
		xronos++; /*o xronos prosomoivshs ay3anetai kata 1 unit of time*/
	} /*while( xronos < xronos_prosomoiosis )*/


	for(i=0;i<QNUMBER;i++)
	{
		arithmos_pelaton+=ControllerGetArithmosPelatwn(controller[i]);
		tamiasInactive=ControllerGetInactiveXronos(controller[i]);
		printf("\nO tamias %d htan adranhs gia %d units of time\n",i, tamiasInactive);
		tamiasBusy=ControllerGetBusyXronos(controller[i]);
		printf("Xronos pou o tamias %d itan apasxolimenos : %d\n",i, tamiasBusy);
		enapomenon_xronos=ControllerGetEnapomenonXronos(controller[i]);
		printf("Enapomenon xronos diadikasias sto tameio %d : %d\n",i, enapomenon_xronos);
		cars_entered_queue=GetCountIn(oura[i]);
		printf("The number of cars that entered the queue %d is %d\n",i, cars_entered_queue);
		cars_left_queue=GetCountOut(oura[i]);
		printf("The number of cars that left the queue %d (and went to the toll) is %d\n",i, cars_left_queue);
		left_cars=OuraGetSize(oura[i]);
		printf("The number of cars in queue %d that were not serviced is %d\n",i, left_cars);
		arithmos_pelaton_tameiou=ControllerGetArithmosPelatwn(controller[i]);
		printf("Eksyphreth8hkan %d pelates sto tameio %d \n",arithmos_pelaton_tameiou, i);
		if(controller[i].available==false)
			printf("To tameio ekleise\n");
	}
		
	if (arithmos_pelaton == 0)
		mesos_xronos = 0.0;
	else
		mesos_xronos = ((float)xronos_anamonis)/((float)arithmos_pelaton);

	printf("\nEksyphreth8hkan %d pelates\n",arithmos_pelaton);
	printf("O mesos xronos anamonhs htan %4.2f units of time.\n",mesos_xronos);

	DeleteMultiQueue(oura);//free the dynamic arrays safely
	DeleteMultiController(controller);
	
	
    getchar();
	return 0;
}

