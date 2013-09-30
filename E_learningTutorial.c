#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<windows.h>
# define bufsize 10 // BUFFER SIZE FOR PRODUCER-CONSUMER PROBLEM 
//STRUCTURE FOR BUSYWAITING_SPINLOCK MODULE
struct priorityq
{
	int pid;
	int priority;
	struct priorityq *next;
}*headofprq=NULL;
typedef struct priorityq prq;
//STRUCTURE FOR MONITOR MODULE
struct readersbuffer
{
	int rid;
	char birth[3];
	char status[10];
	struct readersbuffer *next;
}*headofreadersbf=NULL;
typedef struct readersbuffer rf;
struct monitor_region
{
	int lb,mb,ub;
}objofmr;
//STRUCTURE FOR COUNTING_SEMAPHORE MODULE
struct buffer
{
	int pid;
	struct buffer *next;
}*headofbuffer=NULL;
typedef struct buffer bf;
//STRUCTURE FOR MUTEX MODULE
struct readyq
{
	int pid;
	int bt;
	struct readyq *next;
}rqobj,*headofrq=NULL;
typedef struct readyq rq;
//GLOBAL VARIABLES FOR ALL MODULES
int spinlockturn=1,canwrite=0,canread=0,semaphore=0,in=0,out=0,tpid=1,max_item,mutex=1;
char *writerstatus="sleeping",persign='%';
//FUNCTION OF MUTEX MODULE
//FUNXRION RO CREATE READY QUEUE

rq* createrq(rq **t)
{
	rq *temp;
	rq *newnode=(rq*)malloc(sizeof(rq));
	printf("\n Enter process id and its Burst time\n");
	scanf("%d%d",&newnode->pid,&newnode->bt);
	newnode->next=*t;
	*t=newnode;
	return *t;
}
//FUNCTION TO DISPLAY READY QUEUE
void displayrq(rq *t)
{
	printf("\n\t\t\tREADY QUEUE\t\tMUTEX: %d\n",mutex);
	printf("_______________________________________________________________________________\n");
	while(t)
	{
		printf("| %d | %d |",t->pid,t->bt);
		t=t->next;
	}
	printf("\n------------------------------------------------------------------------------\n");
}
//FUNCTION TO REMOVE PROCESS AFTER FINISHING ITS CRITICAL SECTION
rq* removeprocess(rq **t)
{
	rq *t1=*t,*t2;
	if(!*t) return NULL;
	if((*t)->next==NULL)
	{
		t2=*t;
		*t=NULL;
		return t2;
	}
	while(t1->next)
	{
		t2=t1;
		t1=t1->next;
	}
	t2->next=NULL;
	return(t1);
}
//FUNCTION TO DISPLAY CRITICAL SECTION ON SCREEN
void criticalsection(rq *t)
{
	int btime=t->bt;
	float per=0,rt=0;
	mutex=0;
while(1)
	{
		if(rt>btime) break;
		per=(rt/btime)*100;
		if(per>=100) mutex=1;
		displayrq(headofrq);
		printf("\n\t\t\t\t  CRITICAL SECTION\n");
		printf("\t\t\t||___________________________________||\n");
		printf("\t\t\t||           PROCESS %d               ||\n",t->pid);
		printf("\t\t\t||-----------------------------------||");
		printf("\n\n\tMUTEX: %d\t\t\t%3.0f %c COMPLETE \n\n",mutex,per,persign);// printf(" %c COMPLETE",persign);
	    Sleep(1000);
		rt++;
		system("cls");
	}
	//semaphore=0;	
}
//FUNCTION TO DEFINE MUTEX
void definemutex()
{
	printf("\n\nMUTEX :\n\n\t\tMutex is a binary semaphore(integer variable) that can have only one value at a time either 1 or 0\
	\n\nand is used to provide the mutual exclusion over a shared resource among various processes to avoid deadlocks .\
	\n\nIf the mutex value is one means resource is available for use and if it's 0 means another process is already running in its\
	\n\ncritical section . The entering process sets mutex to 0 and the exiting process must set it to 1 to know other processes\
	\n\n about critical section's status\n.");
}
//FUNCTION FOR GUIDANCE 
void guidencetorunmutex()
{
	printf("\n\nINSTRUCTIONS TO KEEP IN MIND WHILE RUNNING THE MUTEX PROGRAM:\n\n\t\t\tAlthough the program is generalised one but read\
	\n\nfollowing instructions to easy understanding the working process.\
	\n\n1.Give number of processes less than 10 for better visualization.\
	\n\n2.Give a unique process id to each process to avoid ambiguity.\
	\n\n3.Give the burst time between 5 to 30 for each process to not let it to give a wait of long time.\
	\n\n4.The module uses (runtime/burst_time)*100 as its percentage computation.\
	\n\n5.The module uses a ready queue(using linked list) to represent the ready processes and uses critical section one by one.\
	\n\n6.The first part of each node contain the process id and the second part contain its burst time\n\n");
}
//FUNCTION TO DEMONSTRATE MUTEX USE
void runmutex()
{
	rq *temp=NULL;
  int np,i;
	printf("\n Enter number of processes in ready queue\n");
	scanf("%d",&np);
	while(np--)
	    headofrq=createrq(&headofrq);
	temp=removeprocess(&headofrq);
	while(temp)
	  {
	  	if(mutex)
	  	{
	  	   criticalsection(temp);
	  	   temp=removeprocess(&headofrq);
	    }
	  }
	printf("\n\n All Processes have finished their critical sections successfully\n\n");	
}
//FUNCTIONS OF COUNTING_SEMAPHORE MODULE
//FUNCTION TO CREATE BUFFER FOR PRODUCER - CONSUMER PROBLEM

bf* createbuffer(bf** t)
{
	bf *newnode=(bf*)malloc(sizeof(bf));
	newnode->pid=tpid++;
	newnode->next=*t;
	*t=newnode;
	in++;
	return (*t);
}
//FUNCTION TO REMOVE PRODUCT BY CONSUMER FROM BUFFER

int removeproduct(bf** t)
{
	bf *temp1=*t,*temp2;
	if(!*t)
	{
	    return 0;
	}
	else if((*t)->next==NULL)
	{
		temp2=*t;
		*t=NULL;
		free(temp2);
		out++;
		return 1;
	}
	else
	{
		while(temp1->next)
		{
			temp2=temp1;
			temp1=temp1->next;
		}
		temp2->next=NULL;
		free(temp1);
		out++;
		return 1;
	}    
}
// FUNCITION TO DEFINE COUNTING SEMAPHORE
void aboutcountingsemaphore()
{
	printf("\nCOUNTING SEMAPHORE :\n\t\tIt is a special case of semaphore(integer variable) that can have any non-negative value equal to\
           the number of shared \n\nresources available and is used to manage these resources among sharing processes avoiding deadlocks\
		   \n\nEXAMPLE :\n\nProducer - consumer problem discussed in the module\n" );
}
//FUCTION TO DEFINE PRODUCER - CONSUMER PROBLEM
void producer_consumer()
{
	printf("\nPRODUCER - CONSUMER PROBLEM:\n\n \t\tThis is an real life example of counting semaphore in which a producer is producing items\
	\n\nat different production rate and placing them in fixed size buffer(queue as a shared resource), while the consumer is taking out items\
	\n\nfrom the queue and consuming them at different consumption rate\n" );
}
// FUNCTION FOR INSTRUCTIONS FOR PROGRAM
void guideforcountingsemaphore()
{
	printf("\nINSTRUCTIONS TO KEEP IN MIND WHILE RUNNING THE MODULE :\n\nHowever the module is a generalised one written in c language but\
	\n\nfollowing instructions will help you to better understand the logic of the program\n\n1.The fixed size of the buffer I have taken is 10\
	\n\nbut you can change it in module.\n\n2.The program takes production rate(number of items produced in unit time) and consumption rate(\
	\n\nnumber of items consumed in same unit of time) as its inputs from user.\n\n3.The program will take the maximum rate (production/consumption\
	) \n\nas its maximum items to run for it.\n\n4.The producer or consumer whoever is waking means he has a lock over the semaphore and sleeping\
	\n\nmeans the semaphore is locked by othe person(producer/consumer)\n\n5.Your maximum rate(production or consumption) should be in between\
	\n\n15 to 25 and other rate should be in between 5 to 10 for better checking the waiting,sleeping and calling functions\n\n6.check the module\
	\n\nusing all the three cases as production rate>consumption rate, production rate<consumption rate and production rate=consumption rate\
	\n\n7.The program uses the relative rate of both production and consumption as incrementing factor\n\n8.Use full screen editor for better visualization\n");
}
//FUNCTION TO DISPLAY UPDATED BUFFER EACH TIME ON SCREEN

void display(bf *t,int n)
{
	printf("\n\t\t================================= PRODUCER - CONSUMER PROBLEM USING COUNTING SEMAPHORE ====================================\n");
	printf("\n\t\t\t\t\t\t\tTOTAL NUMBER OF ITEMS TO BE PRODUCED IS : %d\n",n);
	printf("\n\t\t\t\t\t\t\t\tBUFFER WITH SIZE : 10\n");
	printf("\n                      ____________________________________________________________________________________________________ ");
	printf("\n\tPRODUCER -->");
	printf("                        ");
	while(t)
	{
		printf("| %d |",t->pid);
		t=t->next;
	}
	printf("\n\t\t                                                                                                            --> CONSUMER");
	printf("\n                      ----------------------------------------------------------------------------------------------------\n");	
} 
//FUNCTION FOR PRODUCING AND CONSUMING ITEMS  INTO THE BUFFER AND FROM THE BUFFER

void prod_cons_working()
{
  	int i,loop_var1=0,loop_var2=0,max_item;
	float prod_rate,cons_rate,percent,temper=0;
    printf("\n Enter Production rate and consumption rate\n");//TAKE PRODUCTION RATE AND CONSUMPTION RATE FROM USER
    scanf("%f%f",&prod_rate,&cons_rate);
    if(prod_rate>cons_rate)
	{
		   max_item=(int)prod_rate;
           percent=prod_rate/cons_rate;
           printf("\n\nPRODUCER IS FASTER THAN CONSUMER\n");
           Sleep(1000);
    }
    else
    {
    	max_item=(int)cons_rate;
	     percent=cons_rate/prod_rate; 
	     if(cons_rate>prod_rate)
	       printf("\n\nCONSUMER IS FASTER THAN PRODUCER\n");
	     else
		   printf("\n\nBOTH ARE HAVING SAME RATES\n");
		 Sleep(1000);    
	}
	printf("\n INITIAL BUFFER SIZE IS 10\n"); //DISPLAYS INITIAL BUFFER
	printf("\n Max-item : %d \t\t,Percent : %f",max_item,percent); Sleep(1500);
	printf("\n\t\t\t\t\t\t\t\t INITIALLY\n");
	display(headofbuffer,max_item);
	printf("\n\tPRODUCER : SLEEPING");
	printf("                                                                                                            CONSUMER : SLEEPING\n");
        //CODE FOR PRODUCING ITEMS BY PRODUCER
        
	prod:
	while(1)
	{
		if(out>=max_item&&in>=max_item)
		{
		    system("cls");	
			display(headofbuffer,max_item);
			printf("\n\tPRODUCER : SLEEPING");
        	printf("                                                                                                    CONSUMER : SLEEPING\n");
			printf("\n\t PRODUCTION - CONSUMPTION PROCESS TERMINATES\n");
			return;
		}
		
		if(prod_rate>cons_rate)
		{
			temper+=percent;
			loop_var1=(int)temper-in;
	    }
	    else
	        loop_var1=1;
	   
		while(loop_var1&&in<max_item) 
		{ 
		  loop1:
		  	if(in==max_item&&out<max_item)
		  	{
		  		loop_var1=0;
		  		printf("\n PRODUCTION IS OVER , PRODUCED %d ITEMS\n");
		  		goto loop2;
		  	}
		if(in-out==bufsize&&in<max_item)
		{
			printf("\n\t\t\t\t\t BUFFER FULL\n");
			printf("\n\t\t\t\t PRODUCER CALLING TO CONSUMER\n");
			goto cons;
		}   
		Sleep(2000);
		system("cls");
		headofbuffer=createbuffer(&headofbuffer);
		display(headofbuffer,max_item);
		if(loop_var1>0)
			printf("\n\tPRODUCER : WAKING\t\t\t\t\t\t\t\t\t\t\t\t\t\tCONSUMER : SLEEPING\n");
		else
		    printf("\n\tPRODUCER : WAKING\tCALL FROM CONSUMER\t\t\t\t\t\tCONSUMER : SLEEPING\n");	
		loop_var1--;
		if(loop_var2>0)  goto loop2;
	
	    }
	    
		goto cons;
	}
  
        //CODE FOR CONSUMPTION OF ITEMS BY CONSUMER
   
    cons: 
	while(1)
	{
		if(out>=max_item)
		{
			system("cls");
			display(headofbuffer,max_item);
			printf("\n\tPRODUCER : SLEEPING");
        	printf("                                                                                                    CONSUMER : SLEEPING\n");
			printf("\n PRODUCTION - CONSUMPTION PROCESS TERMINATES\n");
			return;
		}
	
		if(prod_rate<cons_rate)
		{
			temper+=percent;
			loop_var2=(int)temper-out;
	    }
	    else
	        loop_var2=1;  
	       
		while(loop_var2&&out<max_item) 
		{ 
		  loop2:
		Sleep(2000);
		system("cls");
		if(out==in&&in<max_item)
		{
			display(headofbuffer,max_item);
			printf("\n                                                BUFFER EMPTY\n");
			printf("\n\t\t\t\t\t\tCONSUMER CALLING TO PRODUCER\n");
			goto prod;
		}
	
		removeproduct(&headofbuffer);
		display(headofbuffer,max_item);
		if(loop_var2>0)
		     printf("\n\tPRODUCER : SLEEPING\t\t\t\t\t\t\t\t\t\t\t\t\t\tCONSUMER : WAKING\n");
		else
		     printf("\n\tPRODUCER : SLEEPING\tCALL FROM PRODUCER\t\t\t\t\t\tCONSUMER : WAKING\n");     
		loop_var2--;
		if(loop_var1>0)  goto loop1;
	   }
	   goto prod;
	
	}
}
//FUNCTIONS FOR MONITOR MODULE
//FUNCTION TO CREATE READY BUFFER OF READERS IN READER - WRITERS PROBLEM

rf* createrb(rf **t)
{
		rf *newnode=(rf*)malloc(sizeof(rf));
		printf("\nEnter the id of reader: \n");
		scanf("%d",&newnode->rid);
		printf("\nEnter the birth choice (LB/MB/UB):\n");
		scanf("%s",newnode->birth);
		strcpy(newnode->status,"sleeping");
		newnode->next=*t;
		*t=newnode;
return *t;		
}
//FUNCTION TO REMOVE A READER WHEN IT FINISHES IT'S CRITICAL SECTION

rf* removereader(rf **t)
{
  rf *t1=*t,*t2;
	if(!*t)
	   {
	   	return NULL;
	   }
	else if((*t)->next==NULL)
	{
		t2=*t;
		*t=NULL;
		return (t2);
	}   
	else
	{
		while(t1->next)
		{
			t2=t1;
			t1=t1->next;
		}
		t2->next=NULL;
		return(t1); 
	}
}
//FUNTION TO INITIALLY AVAILABLE SEATS IN ONLINE TRAIN RESERVATION SYSTEM
void initializemr()
{
	printf("\n\nEnter the total number of lower births initially available :\n");
	scanf("%d",&objofmr.lb);
	printf("\n\nEnter the total number of middle births initially available :\n");
	scanf("%d",&objofmr.mb);
	printf("\n\nEnter the total number of upper births initially available :\n");
	scanf("%d",&objofmr.ub);
}
//FUNCTION TO UPDATE THE NUMBER OF SEATS EACH TIME WHEN A WRITER DOES A RESERVATION
int updatemr(char *t)
{
	if(!(strcmp(t,"lb")&&strcmp(t,"LB")))
	{
		if(objofmr.lb)
		   objofmr.lb--;
	    else if(objofmr.mb)
	    {
	    objofmr.mb--;
		printf("\n LOWER BERTH IS NOT AVAILABLE , MIDDLE BERTH IS ALLOTED\n");	
	    }
	    else if(objofmr.ub)
	    {
	    	objofmr.ub--;
	        printf("\n LOWER AND MIDDLE BERTHS ARE NOT AVAILABLE , UPPER BERTH ALLOTED\n");	
	    }
	   else
	       return 0;
	}
	else if(!(strcmp(t,"mb")&&strcmp(t,"MB")))
	{
	  if(objofmr.mb)
	     objofmr.mb--;
	  else if(objofmr.ub)
	  {
	  	objofmr.ub--;
	  printf("\n MIDDLE BERTH IS NOT AVAILABLE , UPPER BERTH IS ALLOTED\n");	
	  }
	 else if(objofmr.lb)
	 {
	 	objofmr.lb--;
	 printf("\n MIDDLE AND UPPER BERTHS ARE NOT AVAILABLE , LOWER BERTH ALLOTED\n");	
	 }
	 else 
	   return 0;
	}
	else if(!(strcmp(t,"ub")&&strcmp(t,"UB")))
	{
	   if(objofmr.ub)
	      objofmr.ub--;
	   else if(objofmr.lb)
	   {
	   	objofmr.lb--;
	   	   printf("\n UPPER BERTH IS NOT AVAILABLE , LOWER BERTH IS ALLOTED\n");
	   }
	   else if(objofmr.mb)
	   {
	   	objofmr.mb--;
	   	   printf("\n UPPER AND LOWER BERTHS ARE NOT AVAILABLE , MIDDLE BERTH IS ALLOTED\n");
	   }
	   else 
	      return 0;	   	   	
	}       
	return 1;   
}
//FUNCTION TO DISPLAY READER'S BUFFER EACH TIME ON THE SCREEN
void displayrbuf(rf *t)
{
	printf("\n\t\t\t\t\t\tREADER'S BUFFER\n");
	printf("\n___________________________________________________________________________________________________________________________________________\n");
 	while(t)
 	{
 		printf("| %d | %s | %s |",t->rid,t->birth,t->status);
 		t=t->next;
 	}
 	printf("\n--------------------------------------------------------------------------------------------------------------------------------------------\n\n\n");
}
//FUNCTION TO DISPLAY MONITOR REGION EACH TIME ON THE SCREEN
void displaymr()
{
	printf("\n\t\t\t\t\tCANREAD : %d\t\tCANWRITE : %d\n",canread,canwrite);
	printf("\n\t\t\t\t\tMONITOR REGION(CRITICAL SECTION)");
	printf("\n\t\t\t\t\t-------------------------------\n");
	printf("\n\t\t\t\t\tTOTAL AVAILABLE SITS IN LB,MB AND UB\n");
	printf("\n\t\t\t\t|-----------------------------------------------|\n");
	printf("\t\t\t\t\tLB\t\tMB\t\tUB\n");
	printf("\t\t\t\t|------------|----------------|------------------|\n");
	printf("\t\t\t\t|     %d      |        %d       |      %d          |\n",objofmr.lb,objofmr.mb,objofmr.ub);
	printf("\t\t\t\t|------------|----------------|------------------|\n");
	printf("\t\t\t\t|-----------------------------------------------|\n\n\n");
}
//FUNCTION TO DISPLAY WRITER EACH TIME WITH ITS STATUS 
void displaywriter()
{
	printf("\n\t\t\t\t\t\tWRITER\n");
	printf("\n\t\t\t\t|------------------------------------|\n");
	printf("\t\t\t\t|------------------------------------|\n");
	printf("\n\t\t\t\t|              %s                |\n",writerstatus);
	printf("\n\t\t\t\t|------------------------------------|\n");
	printf("\t\t\t\t|------------------------------------|\n");
}
//FUNCTION TO CHANGE THE STATUS OF ALL READERSE IN BETWEEN SWITHCNIG EITHER READING OR WAITING

void changestatusofbr(char *ts)
{
	rf *t=headofreadersbf;
	while(t)
	{
		strcpy(t->status,ts);
		t=t->next;
	}
}
//FUNCTION TO DEFINE MONITOR
void definemonitor()
{
	printf("\nMONITOR :\n\n\t\tMonitor is a collection of procedures ,variables ,and data structures that are all grouped together in a special\
	\n\n kind of module or package.Processes can call the procedures in a monitor whenever they want to, but they cannot directly access the \
	\n\n monitors internal data structures from outside procedures. Only one process can be active in a monitor at any instant.It uses two \
	\n\n condition variables wait and signal to check the status. In my program these are as canread and canwrite.\
	\n\nEXAMPLE:\n\t\t Readers - Writers problem as I have discussed in this module over railway reservation system\n.");
}
//FUNCTION TO DISPLAY INSTRUCTIONS AND LOGIC OF THE MODULE
void guideformonitor()
{
	printf("\n\nINSTRCTIONS TO KEEP IN MIND WHILE RUNNING THE MODULE :\n\n1.The problem I have solved using monitor is reader - writer's problem\
	\n\n using online railway reservation system because there also at the same time there are many readers but only writer which allots and\
	\n\n assures the reservation.\n\n2.The program takes number of readers and reader id, berth preference as input for each reader and stores\
	\n\n it in a ready buffer.\n\n3.The next input is total number of berths(lb and mb and ub) available for reservation.\
	\n\n4.The critical section or monitor region is the total berths (lb/mb/b) that are available and monitor has a lock over it only one user\
	\n\ncan enter at a time i.e., either a reader or a writer .\n\n5.It uses two condition variables canread and canwrite to check the status of \
	\n\n of reader and writer. If a writer is writing then it sets the canread=0 and canwrite=1, so that at that time no reader can read the\
	\n\n information.When writer finishes it sets canread=1 and canwrite=0. Similarly if a reader want to read then it just checks canread=1 \
	\n\n and only then it can read.\n\n6.Whenever a writer enters monitor region it just allots a seat to the reader who has read first.\
	\n\n7.The program is also tested for insufficient seats.\n\n" );
}
// MAIN MODULE FOR READER - WRITERS PROBLEM
void monitorusingreadwrite()
{
	int nor,tnor;
	rf *node;
	printf("\n\nEnter the number of readers:\n");
	scanf("%d",&nor);
	tnor=nor;
	while(nor--)
	  headofreadersbf=createrb(&headofreadersbf);
	initializemr();
	system("cls");
	printf("\n\t\t\t\t\t\t\tINITIALLY\n");
	displayrbuf(headofreadersbf);
	displaymr();
	displaywriter();
	while(tnor--)
	{
		Sleep(3000);
		system("cls");
		changestatusofbr("reading");
		writerstatus="waiting";
		canread=1; canwrite=0;
		displayrbuf(headofreadersbf);
    	displaymr();
	    displaywriter();
	    canread=0;
	    canwrite=1;
	    node=removereader(&headofreadersbf);
	    if(!updatemr(node->birth))
	         {
	         	system("cls");
	         	printf("\n NO SITS ARE AVAILABLE \n");
	         	canread=1;canwrite=0;
	         	displaymr();
	            writerstatus="sleeping";
	            displaywriter();
	         	Sleep(1000);
	         	return ;
	         }
	    changestatusofbr("waiting");
	    writerstatus="writing";
	    Sleep(3000);
		system("cls");
		displayrbuf(headofreadersbf);
    	displaymr();
	    displaywriter();
	}
	canread=0;canwrite=0;
	writerstatus="sleeping";
    Sleep(3000);
	system("cls");
	displayrbuf(headofreadersbf);
    displaymr();
	displaywriter();
}
//FUNCTIONS OF BUSYWAITING_SPINLOCK MODULE
//FUNCTION TO CREATE INITIAL PRIORITY QUEUE USING LIKED LIST FOR PROCESSES ENTERED BY USER

void createprq(prq** t)
{
	int nop;
	prq *t1,*t2;
	printf("\nEner the number of processes :\n");
	scanf("%d",&nop);
	while(nop--)
	{
	prq *newnode=(prq*)malloc(sizeof(prq));
	printf("\nEnter the process id :\n");
	scanf("%d",&newnode->pid);
	printf("\nEnter the priority of the process %d\n",newnode->pid);
	scanf("%d",&newnode->priority);
	newnode->next=NULL;
	if(!*t)
		*t=newnode;
	else
	{
		t1=*t;
		if(newnode->priority<=t1->priority)
		{
			newnode->next=t1;
			*t=newnode;
		}
		else
		{
		while(t1&&t1->priority<newnode->priority)
		{
			t2=t1;
			t1=t1->next;
		}
		newnode->next=t2->next;
		t2->next=newnode;
	    }
	}
   }
}
//FUNCTION TO DSPLAY PRIORITY QUEUE EACH TIME ON THE SCREEN
void displayprq(prq *t)
{
	printf("\n============================================ WELCOME TO BUSY-WAITING AND SPINLOCK E-LERNING TUTORIAL ==========================================\n");
	printf("\n\t\t\t\t\t\t\tWISH YOU A HAPPY E-LERANING\n\n");
	printf("\n\t\t\t\tPRIORITY QUEUE\n\n");
	printf(" pid   | priority\n");
	printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
	while(t)
	{
		printf("|  %d  |   %d   |",t->pid,t->priority);
		t=t->next;
	}
	printf("\n------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
	
}
//FUNCTION TO REMOVE A PROCESS EACH TIME WHEN IT FINISHES ITS CRITICAL REGION WORK

prq* removenodeofprq(prq **t)
{
	prq *t1=*t,*t2;
	if(!(*t)->next)
	   return NULL;
	else
	{
		while(t1->next)
		{
			t2=t1;
			t1=t1->next;
		}
		t2->next=NULL;
		return t1;
	}   
}

//FUNCTION TO DISPLAY CRITICAL REGION EACH TIME ON SCREEN
void displaycsofbwaiting(prq *t)  
{
 printf("\n\n\t\t\tCRITICAL REGION");
 printf("\n\t\t\t---------------\n\n");
 printf("\t\t\tSPINLOCK TURN : %d\n",spinlockturn);
 printf("\t\t|-------------------------------|\n");
 if(t)
 printf("\t\t|\t    %d                  |",t->pid);
 else
 printf("\t\t|\t    EMPTY               |");
 printf("\n\t\t|-------------------------------|\n");	
}
//FUNCITON TO DEFINE BUSY - WAITING
void definebwaiting()
{
	printf("\nBUSY-WAITING :\n\n\t\tBusy-waiting is a form of waiting where a thread continuously tests a condition to be true that will let the\
	\n\nthread proceed eventually.While busy waiting the thread uses processor time.It should be avoided since it wasts the cpu time.\
	\n\nEXAMPLE :\n\n\t\tIn priority based execution the lower priority process always uses busy waiting.\n");
}
//FUNCITON TO DEFINE SPINLOCK
void definespinlock()
{
	printf("\nSPINLOCK :\n\n\t\tThe lock which uses busy - waiting is called spinlock.Suppose if the control of enabling and disabling the external\
	\n\nintrupts is given to the process which uses critical region i.e., when process enters in critical region it sets the control variable\
	\n\nto 0 and disables all external intrrupts to use mutual exclusion and suppose if after finishing its task it forgets to reset the \
	\n\n condition variable(lock) to 1 then no next process can enter in critical region even if it is empty.\n" );
}
//FUNCTION FOR INSTRUCTIONS AND LOGIC OF MODULE TO DISPLAY
void guideofbwaiting()
{
	printf("\nLOGIC OF THE PROGRAM:\n\n\t\tAs I have already mentioned in definition that when processes are themselves provided the control of \
	\n\n enabling and disabling external interrupts(h/w and i/o) while entering in and exiting out the critical region to safely perform their work\
	\n\n and provide mutual exclusion.In that case suppose if a process fails to enabling intrrupts and reseting the lock variable(in this case spinlock)\
	\n\n then no other process can enter in critical region even if it is not in use.The process contiuosly cheks the lock variable and always finds it\
	\n\n false(0).In this program I have used this concept on second last process based on its priority. All other processes will enable the intrrupts \
	\n\n and resets the lock variable SPINLOCK TURN=1 while exiting but the second last process forgets this.Also this program uses priority based \
	\n\n execution i.e., the processes/threads are being executed based on their priority given by user i.e., higher priority based process will execute\
	\n\nfirst and so on.\n\nINSTRUCTIONS TO RUN THE PROGRAM :\n\n\t\t1.The program takes number of processes ,process id and its priority(an integer)\
	\n\n as its input from user then it displays the sorted priority queue(using linked list) based on increasing order of their priority.\
	\n\n2.The busy waiting happens with the lowest priority process that cann't enter in critical region due to spinlock.\n");
}
// MAIN FUNCTION FOR BUSY - WAITING AND SPINLOCK
void spinlockinbwaiting()
{
	int tpid;
	prq *tp,*ntp=NULL;
	createprq(&headofprq);
	system("cls");
	displayprq(headofprq);
	Sleep(2000);
	tp=removenodeofprq(&headofprq);
	while(tp)
	{
		system("cls");
		spinlockturn=0;
		displayprq(headofprq);
		displaycsofbwaiting(tp);
		spinlockturn=1;
		printf("\nINTRUPTS ARE DISABLED BY PROCESS : %d",tp->pid);
		Sleep(2000);
		system("cls");
		displayprq(headofprq);
		displaycsofbwaiting(ntp);
		if(!headofprq->next)
		{
          tpid=tp->pid;  
		  printf("\nINTRRUPTS ARE NOT ENABLED BY PROCESS :%d",tp->pid);
	    }
		else  
		  printf("\nINTRRUPTS ARE ENABLED BY PROCESS : %d",tp->pid);
		Sleep(1500);
		tp=removenodeofprq(&headofprq);
	}
	system("cls");
	displayprq(headofprq);
	printf("\n\n\t\t\tPROCESS %d WITH BUSY WAITING.....",headofprq->pid);
	spinlockturn =0;
	displaycsofbwaiting(tp);
	printf("\n\n\t\tINTRRUPTS ARE NOT ENABLED BY PRIVIOUS PROCESS :%d\n\n",tpid);
	printf("\n\n\t\tPROCESS %d LEFT WITHOUT SETTING SPINLOCK TURN =1\n\n",tpid);
} 
//MAIN MODULE FOR MUTEX

void mainmutexmodule()
{
	int mutexchoice;
	char mutexrepeat;
	do
	{
		system("cls");
		printf("\n================================================== WELCOME TO MUTEX E - LEARNING TUTORIAL =================================\n");
	    printf("\n                                                       WISH YOU A HAPPY E - LEARNING \n\n");
		printf("\n1.WHAT IS MUTEX?\n\n2.INSTRUCTIONS AND LOGIC OF MODULE (READ IT RECOMMENDED\n\n3.HOW A MUTEX WORKS?\n\n4.EXIT\n\nENTER YOUR CHOICE\n\n");
		scanf("%d",&mutexchoice);
		switch(mutexchoice)
		{
			case 1:
				system("cls");
				definemutex();
				break;
			case 2:
			    system("cls");
				guidencetorunmutex();
				break;
			case 3:
			    system("cls");
				runmutex();
				break;
			case 4:
				printf("\n\n\t\t\tTHANKYOU FOR USING MUTEX E-LEARNING TUTORIAL\n\n");
			    return;
				break;
			default:
			    printf("\n\nYOU ENTERED WRONG CHOICE\n");
				break;				
		}
		printf("\n\nDO YOU WANNA CONTINUE ABOUT MUTEX (Y/N) :\n\n");
		mutexrepeat=getch();
	}while(mutexrepeat=='y'||mutexrepeat=='Y');
	printf("\n\n\t\t\tTHANKYOU FOR USING MUTEX E-LEARNING TUTORIAL\n\n");
}
//MAIN MODULE FOR COUNTING_SEMAPHORE

void mainsemaphoremodule()
{
	int semchoice;
	char semrepeat;
	do
	{
	system("cls");	
	printf("\n======================================================= WELCOME TO SEMAPHORE E - LEARNING TUTORIAL ==================================\n");
	printf("\n                                                             WISH YOU A HAPPY E - LEARNING \n\n");
    printf("\n1.WHAT IS SEMAPHORE?\n\n2.WHAT IS PRODUCER - CONSUMER PROBLEM?\n\n3.INSTRUCTIONS AND LOGIC OF PROGRAM\n\n4.HOW TO SOLVE PRODUCER - CONSUMER PROBLEM?\n\n5.EXIT\n\nENTER YOUR CHOICE\n");
    scanf("%d",&semchoice);
    switch(semchoice)
    {
    	case 1:
    		system("cls");
    		aboutcountingsemaphore();
    		break;
        case 2:
        	system("cls");
		    producer_consumer();
			break;
		case 3:
			system("cls");
		    guideforcountingsemaphore();
			break;
		case 4:
			system("cls");
		    prod_cons_working();
			break;
		case 5:
			printf("\n\n\t\t\tTHANKYOU FOR USING SEMAPHORE E-LEARNING TUTORIAL\n\n");
		    return;
			break;
		default :
		    printf("\n You entered wrong choice\n");
			break;				 		
    }
    printf("\n\n DO YOU WANNA CONTINUE ABOUT COUNTING SEMAPHORE(y/n)\n");
    semrepeat=getch();
    }while(semrepeat=='y'||semrepeat=='Y');
    printf("\n\n\t\t\tTHANKYOU FOR USING SEMAPHORE E-LEARNING TUTORIAL\n\n");
}
//MAIN MODULE FOR MONITOR

void mainmonitormodule()
{
		int monitorchoice;
	char monitorrepeat;
	do
	{
	  system("cls");
	  printf("\n====================================================== WELCOME TO MONITOR E - LERANING TUTORIAL =================================================\n");	
      printf("\n                                                            WISH YOU A HAPPY E - LEARNING \n\n");	 
	  printf("\n\n1.WHAT IS MONITOR?\n\n2.INSTRUCTIONS TO RUN THE MODULE (READ IT RECOMMENDED)\n\n3.HOW MONITOR WORKS ?(USING READER - WRITER'S PROBLEM)\n\n4.EXIT\n\nENTER YOUR CHOICE\n\n");
	  scanf("%d",&monitorchoice);
	  switch(monitorchoice)
	  {
	  	case 1:
	  		system("cls");
	  		definemonitor();
	  		break;
	  	case 2:
		    system("cls");
			guideformonitor();
			break;
		case 3:
		    system("cls");
			monitorusingreadwrite();
			break;
		case 4:
			printf("\n\n\t\t\tTHANKYOU FOR USING MONITOR E-LEARNING TUTORIAL\n\n");
		    return;
			break;
		default:
		    printf("\n\nYOU ENTERED WRONG CHOICE\n");
			break;				
	  }
	  printf("\n\nDO YOU WANNA CONTINUE ABOUT MONITORS (y/n):\n");
	  monitorrepeat=getch();
    }while(monitorrepeat=='y'||monitorrepeat=='Y');
    printf("\n\n\t\t\tTHANKYOU FOR USING MONITOR E-LEARNING TUTORIAL\n\n");
}
//MAIN MODULE FOR BYSYWAITING_SPINLOCK 

void mainbwaitingmodule()
{
		int bwaitchoice;
	char bwaitrepeat;
	do
	{
		system("cls");
		printf("\n============================================ WELCOME TO BUSY-WAITING AND SPINLOCK E-LERNING TUTORIAL ==========================================\n");
	    printf("\n\t\t\t\t\t\t\tWISH YOU A HAPPY E-LERANING\n\n");
	    printf("\n1.WHAT IS BUSY-WAITING?\n\n2.WHAT IS SPINLOCK?\n\n3.INSTRUCTIONS AND LOGIC OF THE PROGRAM(READ IT RECOMMENDED)\n\n4.RUN THE PROGRAM\n\n5.EXIT\n\nENTER YOUR CHOICE:\n\n");
	    scanf("%d",&bwaitchoice);
	    switch(bwaitchoice)
	    {
	    	case 1:
	    		system("cls");
	    		definebwaiting();
	    		break;
	    	case 2:
			    system("cls");
				definespinlock();
				break;
			case 3:
			    system("cls");
				guideofbwaiting();
				break;
			case 4:
			    system("cls");
				spinlockinbwaiting();
				break;
			case 5:
				printf("\n\t\t\tTHANKYOU FOR USING BUSY-WAITING AND SPINLOCK E-TUTORIAL\n\n");
			    return;
				break;
			default:
			    printf("\n\nYOU ENTERED WRONG CHOICE\n");
				break;					
	    }
	    printf("\n\nDO YOU WANNA CONTINUE BUSY-WAITING AND SPINLOCK (y/n) :\n");
	    bwaitrepeat=getch();
	}while(bwaitrepeat=='y'||bwaitrepeat=='Y');
	printf("\n\n\t\t\tTHANKYOU FOR USING BUSY-WAITING AND SPINLOCK E-TUTORIAL\n\n");
}

//OVERALL MAIN FUNCTION OF THE PROGRAM

int main()
{
	int mainchoice;
	char mainrepeat;
	do
	{
     system("cls"); 
	printf("\n================================================== WELCOME TO E - LEARNING TUTORIAL =================================\n");
    printf("\n                                                     WISH YOU A HAPPY E - LEARNING \n\n");
    printf("\n1.ABOUT MUTEX\n\n2.ABOUT COUNTING SEMAPHORE\n\n3.ABOUT MONITOR\n\n4.ABOUT BUSYWAITING AND SPINLOCK\n\n5.EXIT.\n\nENTER YOUR CHOICE:\n");
    scanf("%d",&mainchoice);
    switch(mainchoice)
    {
    	case 1:
    		system("cls");
    		mainmutexmodule();
    		break;
    	case 2:
		    system("cls");
			mainsemaphoremodule();
			break;
		case 3:
		    system("cls");
			mainmonitormodule();
			break;
		case 4:
		    system("cls");
			mainbwaitingmodule();
			break;
		case 5:
		    printf("\n\nTHANKYOU FOR USING E-LEARNING TUTORIAL\n\n");
			exit(0);
			break;
		default:
		    printf("\n\nYOU ENTERED WRONG CHOICE\n");
			break;					
    }
    printf("\n\nDO YOU WANNA CONTINUE IN E-LERNING TUTORIAL (y/n):\n");
	mainrepeat=getch(); 
   }while(mainrepeat=='Y'||mainrepeat=='y');
   printf("\n\nTHANKYOU FOR USING E-LEARNING TUTORIAL\n\n");
   return 0;
}


