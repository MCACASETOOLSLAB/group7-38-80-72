//Inplementation of semaphore with applying  producer and consumer code.. 

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>  //for dinamic running display window..
#include<math.h> //for using math function ..
 
# define bufsize 10 ///buffer for running process.
struct buffer
{
	int pid;
	struct buffer *next;
};

struct buffer *headofbuffer=NULL,*temp=NULL;
typedef struct buffer bf;

int semaphore=0,in=0,out=0,tpid=1,max_item;

bf* createbuffer(bf** t)
{
	bf *newnode=(bf*)malloc(sizeof(bf));
	newnode->pid=tpid++;
	newnode->next=*t;
	*t=newnode;
	in++;
	return (*t);
}
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

void display(bf *t,int n)
{
	printf("\n\t\t======== PRODUCER - CONSUMER PROBLEM USING COUNTING SEMAPHORE========\n");
	printf("\n\t\t\tTOTAL NUMBER OF ITEMS TO BE PRODUCED IS : %d\n",n);
	printf("\n\t\t\tBUFFER WITH SIZE : 10\n");
	printf("\n  ___________________________________________________________ ");
	printf("\n\tPRODUCER -->");
	printf("          ");
	while(t)
	{
		printf("| %d |",t->pid);
		t=t->next;
	}
	printf("\n\t\t                            --> CONSUMER");
	printf("\n    -------------------------------------------------------------\n");	
}  
void prod_cons_working()
{
  	int i,loop_var1=0,loop_var2=0,max_item;
	float prod_rate,cons_rate,percent,temper=0;
    printf("\n Enter Production rate and consumption rate: \n");
    scanf("%f %f",&prod_rate,&cons_rate);//Rate for running the process consumer and producer..
    if(prod_rate>cons_rate)  //it is use for comparing the consumer and procedure process..  
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
	     if(cons_rate>prod_rate)// it is use for comparing the consumer and procedure process..  
	       printf("\n\nCONSUMER IS FASTER THAN PRODUCER\n");
	     else
		   printf("\n\nBOTH ARE HAVING SAME RATES\n");
		 Sleep(1000);    
	}
	printf("\n INITIAL BUFFER SIZE IS 10\n");
	printf("\n Max-item : %d \t,Percent : %f",max_item,percent); Sleep(1500);
	printf("\n\t\t\t INITIALLY\n");
	display(headofbuffer,max_item);
	printf("\n\tPRODUCER : Sleeping");
	printf("                                                                                                            CONSUMER : SLEEPING\n");
	prod:
	while(1)
	{
		if(out>=max_item&&in>=max_item)
		{
		    system("cls");	
			display(headofbuffer,max_item);
			printf("\n\tPRODUCER : Sleeping");
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
		if(in-out==bufsize&&in<max_item)//if condition use for checking the buffer with running process.
		{
			printf("\n\t\t BUFFER FULL\n");
			printf("\n\t\t\t\t PRODUCER CALLING TO CONSUMER\n");
			goto cons;
		}   
		Sleep(2000);
		system("cls");
		headofbuffer=createbuffer(&headofbuffer);
		display(headofbuffer,max_item);
		if(loop_var1>0)
			printf("\n\tPRODUCER : WAKING\t\t\t\t\tCONSUMER : SLEEPING\n");
		else
		    printf("\n\tPRODUCER : Producing process...\tCALL FROM CONSUMER\t\tCONSUMER : Sleeping...\n");	
		loop_var1--;
		if(loop_var2>0)  goto loop2;
	
	    }
	    
		goto cons;
	}

    cons: 
	while(1)
	{
		if(out>=max_item)
		{
			system("cls");
			display(headofbuffer,max_item);
			printf("\n\tPRODUCER : Sleeping");
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
			printf("\n                     BUFFER EMPTY\n");
			printf("\n\t\t\tCONSUMER CALLING TO PRODUCER\n");
			goto prod;
		}
	
		removeproduct(&headofbuffer);
		display(headofbuffer,max_item);
		if(loop_var2>0)
		     printf("\n\tPRODUCER : Sleeping\t\t\t\tCONSUMER : Working...\n");
		else
		     printf("\n\tPRODUCER : Sleeping\tCALL FROM PRODUCER\t\t\t\tCONSUMER : Working\n");     
		loop_var2--;
		if(loop_var1>0)  goto loop1;
	   }
	   goto prod;
	
	}
	
}
int main()
{
	int semchoice;
	char semrepeat;
	do
	{
	system("cls");	
	printf("\n\\t\t\t++++++++++SEMAPHORE++++++++++\n");
	printf("\n           WISH YOU A HAPPY TO LEARNING  SEMAPHORE\n\n");
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
		    guideforcountingsemaphore();
			break;
		case 4:
		    prod_cons_working();
			break;
		case 5:
			printf("\n\n\nThanks for using on semphore tutorials...\n\n");
		    exit(0);
			break;
		default :
		    printf("\n You entered wrong choice...\n");
			break;				 		
    }
    printf("\n\n Do you want continue to using counting semaphore press y(y/n)\n");
    semrepeat=getch();
    }while(semrepeat=='y'||semrepeat=='Y');
    printf("\n\n\nThanks for using on semphore tutorials...\n\n");
	return 0;
	}	  	

