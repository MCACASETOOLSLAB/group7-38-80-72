group7-38-80-72
===============
GROUP-7
READ-ME

	ABOUT THIS E-LERANING TUTORIAL :
This tutorial is completely developed in c-language on Dev C++ version 5.3.0.3 , because all the powerful operating systems are developed mostly in c-language. 
This tutorial comprises of four independent modules namely :
1.	Mutex.c (for binary semaphore)
2.	Semaphore.c (for counting semaphore).
3.	Monitor.c
4.	Busywaiting_spinlock.c

Each of these individual modules are also developed on same editor and these are also separately available on tutorial. On combining them we have developed a main module named “E_learningtutorial.c” ,that is also there on tutorial.
To understand the above modules properly and how it works you can just copy the code and run  it on your machine.

Take a small look over each module:

1.	Mutex.c : 
This module shows what is mutex? ,instructions and logic of module(recommended to read) and  how mutual exclusion is implemented over critical section.
For this it creates a ready queue  (using linked list) based on FCFS algorithm, and variable “mutex” is used over critical section as you will see in “How a mutex works” option while running the program in your editor.
If mutex is 1 then resource(critical section) is available and if it is 0 then resource is already in use.

2.	Semaphore.c :
This module depicts what is semaphore? What is producer – consumer problem and how to solve this problem using semaphore.
This module takes production rate and consumption rate as its input and the default size of buffer is 10.
At each step it shows the status of producer and consumer either “sleeping” or “waking”.
The condition for full buffer and empty buffer is also tested.
The maximum item to be produced will be your maximum rate either production rate or consumption rate.
For more detail just go through option 3 :”INSTRUCTIONS AND LOGIC OF THE PROGRAM” after running the module.

3.	Monitor.c :
This module shows what is monitor? And how it works using “Reader – Writers” problem in “online railway reservation system”. Because there also so many readers (travelers) accessing the database but only one writer is there to update the database and do reservation.
This module takes number of readers, id of each reader, their berth choice (lb/mb/ub) and the total number of initially available seats in each category (lb/mb/ub).
This module is also tested for insufficient available seats , if choice of user is not fulfilled i.e. , if other berth than user’s choice is allotted.
While writer is writing no other reader/writer can enter in it. But in case if a reader is reading then all other readers can read it but no writer can enter in monitor region.
For this it uses “canread” and “canwrite” variables .
For more detail go through option :2 “INSTRUCTION TO RUN THE MODULE” after running the module.


4.	Busywaiting_spinlock.c:
This module describes what is busy – waiting ? what is spinlock ? and how it works ?
This module takes input as number of processes , id of each process and priority of each process (an integer) based on which it creates a priority queue (using linked list).
As described in “Modern Operating Systems” second edition by Andrew S. Tanenbaum at page no. 103 in paragragraph “mutual exclusion with busy waiting “  that if control of enabling and disabling of interrupts is provided to user processes then it may be happen if any of the process forgets to enable interrupt after finishing its critical region then next process have to face busy – waiting.
Also I  have mixed the case of priority based busy – waiting that a lower priority process will get executed at last even if it has arrived earlier.


	Points to ponder:
1.	While running the “E_learningtutorial.c” or other individual module don’t forget to go through the option : “INSTRUCTIONS AND LOGIC OF THE MODULE/PROGRAM.”.
2.	You can switch in between the same module or different module by just entering your choice (y/n)  whenever prompted by the program.
3.	If you feeling that the program/module is so fast to understand then just go through source code of that program/module and just increase the sleeping time of system in”Sleep(time)”.
4.	Your improvable suggestions/feedbacks are warmly welcomed.


THANK - YOU
