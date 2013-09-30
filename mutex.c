// INTER PROCESS COMMUNICATION AND PROCESS SYNCHRONIZATION USING BINARY SEMAPHORE(MUTEX)

#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
struct readyq
{
	int pid;
	int bt;
	struct readyq *next;
}rqobj,*headofrq=NULL,*temp=NULL;
typedef struct readyq rq;
char persign='%';
int mutex=1;
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
int main()
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
			    exit(0);
				break;
			default:
			    printf("\n\nYOU ENTERED WRONG CHOICE\n");
				break;				
		}
		printf("\n\nDO YOU WANNA CONTINUE ABOUT MUTEX (Y/N) :\n\n");
		mutexrepeat=getch();
	}while(mutexrepeat=='y'||mutexrepeat=='Y');
	printf("\n\n\t\t\tTHANKYOU FOR USING MUTEX E-LEARNING TUTORIAL\n\n");
	return 0;
}
