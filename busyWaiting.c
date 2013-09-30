#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
struct priorityq
{
	int pid;
	int priority;
	struct priorityq *next;
}*headofprq=NULL;
typedef struct priorityq prq;
int spinlockturn=1;
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
//FUNCTION TO DSPLAY PRIORITY QUEUE
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

//FUNCTION TO DISPLAY CRITICAL REGION
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
void definespinlock()
{
	printf("\nSPINLOCK :\n\n\t\tThe lock which uses busy - waiting is called spinlock.Suppose if the control of enabling and disabling the external\
	\n\nintrupts is given to the process which uses critical region i.e., when process enters in critical region it sets the control variable\
	\n\nto 0 and disables all external intrrupts to use mutual exclusion and suppose if after finishing its task it forgets to reset the \
	\n\n condition variable(lock) to 1 then no next process can enter in critical region even if it is empty.\n" );
}
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
// FUNCTION FOR BUSY - WAITING AND SPINLOCK
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
int main()
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
			    exit(0);
				break;
			default:
			    printf("\n\nYOU ENTERED WRONG CHOICE\n");
				break;					
	    }
	    printf("\n\nDO YOU WANNA CONTINUE BUSY-WAITING AND SPINLOCK (y/n) :\n");
	    bwaitrepeat=getch();
	}while(bwaitrepeat=='y'||bwaitrepeat=='Y');
	printf("\n\n\t\t\tTHANKYOU FOR USING BUSY-WAITING AND SPINLOCK E-TUTORIAL\n\n");
	
	return 0;
}
