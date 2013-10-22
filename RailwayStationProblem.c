/*RAILWAY STATION PROBLEM ...
  IN A STATION MANAGING THE UPCOMING TRAIN FOR TAKING STOP AT PLATFORM.
  A TRAIN CAN STAY ON PLATFORM FOR A TIME AFTER NEXT TRAIN WILL COME AT THE STATION.
  IF ALL PLATFORM BUSY THEN TRAIN SHOULD BE STAY ON OUTSIDE UNTIL A TRAIN LEAVE THE STATION AND WAIT 
  FOR SIGNAL...
  1:-Create platform using link list with platform number.There should not be any train..
  2:-Add train to the platform if platform signal is on.
  3:If no signal mean all platform are busy .Train should wee wait on outer mean is a link list..
  4:-When one of the train leave the station signal will be on for that platform and one train 
     from the waiting queue come and stop on the platform then signal will be off(wait)..
  5: May be multiple train arrive at the same time together if platform are empty then signal will 
     be on and trains will stop on those platforms...
  6:-There will be time for each train for stopping at a platform using time.h and window.h headder file.
  7:-All train information will be store in another queue for some time ..
  8:- For current situation there is a function ..
  9:- For pre-scheduling We can use scheduling algo..
  10:-It is created for 5 platform....
  It work only for  platform station...
  
  Note:-its not complete. It will take some time for completing.May i request for some time to completing the problem...Please give some time...
  */
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
 typedef struct Train{                //for entering  trians details at the time signal on..
               int TrainNumber;
               char TrainName[15];
               struct Train *next;
                   }trn;
 typedef struct Platform{               //for platform information
        int platformNum; 
        int TrainNumber;
        char TrainName[15];
        struct Platform *next;
        }plat;
   typedef struct Train_Iformation        //For last total infomation of train as last 24 hours information of leaving trains. 
      {
           int pnum;
           int tnum;
           char tname[20];
           }tinfo;
void Create_Platform(int);   //It used for creating platform in a station..
void TrainToPlatfrom(int,char,int);
void DisplayCurrentDetailOfStation(plat *);//displaying the current position of station ...
void AddTrain();//for adding a train to station...
           
        tinfo *head=NULL;   
        
        plat *platform=NULL,*plm=NULL;
        trn *train_que=NULL;           
             int NumberOfPlatform;       
int main()
 {
          char NameOfStation[20];
          int choice;
          printf("\nPlease enter the name of Station:");
          scanf("%s",NameOfStation);
          printf("\nPlease enter the number of platform in %s  station: ",NameOfStation);
          scanf("%d",&NumberOfPlatform);
                    
          Create_Platform(NumberOfPlatform);//For creating platform for the given station.
           
          while(1)
           {
                  printf("\n1.Press 1 for entering one train in station. ");
                  printf("\n1.Press 2 for dishplaying the current positionof platform. ");
                  printf("\n3.Press 3 for exit. ");
                  printf("\n\nPle ase enter the choice: ");
                  scanf("%d",&choice);
               
                switch(choice)
                   { 
                              
                              case 1: AddTrain();break;
                              case 2: DisplayCurrentDetailOfStation(platform);
                                      break;
                              case 3: exit(0);break;
                              default:
                                      printf("\nYour choice is not valid...");                                                                                                      
                   }  
           }             
        getch();
        return 0;                                                       
  }
    
  void AddTrainToPlatfrom(int tno,char tname[20],int pno)//Function use to add a train to the platform. 
        {
          switch(pno)
              {
                  case 1:
                       if(platform->platformNum==1&&platform->TrainNumber==0)
                             {
                                  platform->TrainNumber=tno;
                                  strcpy(platform->TrainName,tname);
                                  }
                                  else
                                  printf("\nPlatform 1 busy please wait... ");
                                  break;                                             
                  case 2:while(platform!=NULL)
                          {
                           platform=platform->next;
                           if(platform->platformNum==2 && platform->TrainNumber!=0)
                              {
                              printf("\nPlatform 2 is busy...");break;
                              }
                           else if(platform->platformNum==2 && platform->TrainNumber==0)
                               {
                                  platform->TrainNumber=tno;
                                  strcpy(platform->TrainName,tname);
                                  break;                
                                  }
                             }
                             break;
                  case 3:
                       while(platform!=NULL)
                          {
                           platform=platform->next;
                           if(platform->platformNum==3 && platform->TrainNumber!=0)
                              {
                              printf("\nPlatfrom 3 is busy...");break;
                              }
                           else if(platform->platformNum==3 && platform->TrainNumber==0)
                               {
                                  platform->TrainNumber=tno;
                                  strcpy(platform->TrainName,tname);
                                  break;                
                                  }
                             }
                             break;
                  case 4:
                   while(platform!=NULL)
                          {
                       platform=platform->next;
                           if(platform->platformNum==4 && platform->TrainNumber!=0)
                              {
                              printf("\nPlatfrom 4 is busy...");break;
                              }
                           else if(platform->platformNum==4 && platform->TrainNumber==0)
                               {
                                  platform->TrainNumber=tno;
                                  strcpy(platform->TrainName,tname);
                                  break;                
                                  }
                             }
                             break;
                  case 5:
                       while(platform!=NULL)
                           {
                           platform=platform->next;
                           if(platform->platformNum==5 && platform->TrainNumber!=0)
                              {
                              printf("\nPlatfrom 5 is busy...");break;
                              }
                           else if(platform->platformNum==5 && platform->TrainNumber==0)
                               {
                                  platform->TrainNumber=tno;
                                  strcpy(platform->TrainName,tname);
                                  break;                
                                  }
                               }
                             break;
                        default:
                             printf("\nYou entered wrong platfrom number...");                            
                }                                              
            }
      
  void DisplayStationDetails(plat *p)
       {
             while(p!=NULL)
             {
              //printf("\n%d\n",p->platformNum);
               printf("\nPlatform number is: %d",p->platformNum);
               printf("\nTrain number at platform '%d' is: %d",p->platformNum,p->TrainNumber);
               printf("\nTrain name at Platform number '%d' is: %s\n\n",p->platformNum,p->TrainName);	                                   
               p=p->next;              
             }
       }     
   void DisplayQueueDetails(trn *p)
       {
          while(p!=NULL)
             {
              // printf("\nPlatform number is: %d",p->platformNum);
               printf("\nTrain number at platform  is: %d",p->TrainNumber);
               printf("\nTrain name is: %s\n\n",p->TrainName);	                
                   
              p=p->next;              
             }
       } 
  
  
        void AddTrain()
          {
              char ch;
              int j=0;
              trn *Node=NULL;
          do{
              int tno;
              char Tname[20];
              printf("\nEnter the train number: ");
              scanf("%d",&tno);
              printf("\nEnter the name of upcoming train: ");
              scanf("%s",Tname);              
              Node=(trn*)malloc(sizeof(trn));
              if(train_que==NULL)
               {
              Node->TrainNumber=tno;
              strcpy(Node->TrainName,Tname);
              Node->next=NULL;
              train_que=Node;
               }
               else
               {
                   Node=train_que;
                  while(Node->next!=NULL)
                      Node=Node->next;
                      /*trn *temp;
                      temp=(trn*)malloc(sizeof(trn));
                      temp->TrainNumber=tno;
                      strcpy(temp->TrainName,Tname);
                      temp->next=NULL;
                      Node->next=temp;*/
                      
                      Node->next=(trn *)malloc(sizeof(trn));
                      //Node->next->platformNum=i;
                      Node->next->TrainNumber=tno;
                      strcpy(Node->next->TrainName,Tname);
                      Node->next->next=NULL;//Null asign for next node...
                      
                      }
                   j++;   
              printf("\nDo you want to add another train press y else n:");
              ch=getch();
               }while((ch=='y'||ch=='Y')&&j<4);
               
          if(j>(NumberOfPlatform/3))
               printf("\nWe can not arrive more than 'Number_of_platform/3' train together at the station...\n\n"); 
                 
                 DisplayQueueDetails(train_que);          
              }        
                          
         void Create_Platform(int NumberOfPlatform)
             {
                plat *temp=NULL,*node=NULL;                  
                int i=1;                 
                  platform=node;   
                  //printf("\n%d\n",NumberOfPlatform);              
                  
                
                while(i<=NumberOfPlatform)  
                {
                   if(platform==NULL)
                   {
                   platform=(plat*)malloc(sizeof(plat));
                   platform->platformNum=i;
                   platform->TrainNumber=0;
                   strcpy(platform->TrainName,"NoTrain ");
                   platform->next=NULL;
                   }
                  else
                  {
                      temp=platform;
                      while(temp->next!=NULL)
                      temp=temp->next;
                      
                      temp->next=(plat *)malloc(sizeof(plat));
                      temp->next->platformNum=i;
                      temp->next->TrainNumber=0;
                      strcpy(temp->next->TrainName,"NoTrain");
                      temp->next->next=NULL;    
                  }
                  
                  i=i+1;
                                     
               }
                  
                 printf("\n\nAll platforms are created .\n\n");
                                  // DisplayStationDetails(platform);
                  
                      
         }
         
         
         void DisplayCurrentDetailOfStation(plat *t)
             {
                                          
        	while(t!=NULL)
	               {                
                if(t->TrainNumber!=0)
                    {                                     
	                  printf("\nPlatform number is: %d",t->platformNum);
	                  printf("\nTrain number at platform '%d' is: %d",t->platformNum,t->TrainNumber);
	                  printf("\nTrain name at Platform number '%d' is: %s\n\n",t->platformNum,t->TrainName);
	                }
                 else
                 printf("\nPlatform number %d is empty ready for stop a train...\n\n",t->platformNum);
                 t=t->next;
                 
                                  }
            } 
      
      
