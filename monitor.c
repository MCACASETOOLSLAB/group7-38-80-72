#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
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
char *writerstatus="sleeping";
int canwrite=0,canread=0;
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
//FUNTION TO INITIALIZE SEATS
void initializemr()
{
	printf("\n\nEnter the total number of lower births initially available :\n");
	scanf("%d",&objofmr.lb);
	printf("\n\nEnter the total number of middle births initially available :\n");
	scanf("%d",&objofmr.mb);
	printf("\n\nEnter the total number of upper births initially available :\n");
	scanf("%d",&objofmr.ub);
}
//FUNCTION TO UPDATE THE NUMBER OF SEATS
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
//FUNCTION TO DISPLAY READER'S BUFFER
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
//FUNCTION TO DISPLAY MONITOR REGION
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
//FUNCTION TO DISPLAY WRITER
void displaywriter()
{
	printf("\n\t\t\t\t\t\tWRITER\n");
	printf("\n\t\t\t\t|------------------------------------|\n");
	printf("\t\t\t\t|------------------------------------|\n");
	printf("\n\t\t\t\t|              %s                |\n",writerstatus);
	printf("\n\t\t\t\t|------------------------------------|\n");
	printf("\t\t\t\t|------------------------------------|\n");
}
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
int main()
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
		    exit(0);
			break;
		default:
		    printf("\n\nYOU ENTERED WRONG CHOICE\n");
			break;				
	  }
	  printf("\n\nDO YOU WANNA CONTINUE ABOUT MONITORS (y/n):\n");
	  monitorrepeat=getch();
    }while(monitorrepeat=='y'||monitorrepeat=='Y');
    printf("\n\n\t\t\tTHANKYOU FOR USING MONITOR E-LEARNING TUTORIAL\n\n");
	return 0;
	
}
