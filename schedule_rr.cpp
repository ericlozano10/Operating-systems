#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

#include "task.h"
#include "list.h"
#include "cpu.h"
#include "schedulers.h"

using namespace std;

//create node
struct node *h1 = NULL;

//counters and max size
int numTasks = 0;   // task counter
static int TID = 1; // task ID
const int SIZE = 6; // total size of task

//burst time
int burst_time = 50;

//turn around times
int turnAroundTime = 0;
float avgTurnAroundTime = 0.0;
int turn_Around_Time[SIZE];

//wait times
int waitTime = 0;
int totalWaitTime = 0;
float avgWaitTime = 0.0;
int wait_Time[SIZE];

//stores previous value
int preVal = 0;
string newT_[SIZE];


//-----------------------------------------------//
// function for inserting at the end
void insertAtEnd(struct node**head, Task *task)
{
  struct node* temp = (struct node*) malloc(sizeof(struct node));
  temp->task = task;
  temp->next = NULL;

  if((*head) == NULL)
    {
      *head = temp;
    }
  else
    {
      struct node *newTemp = *head;
      while(newTemp->next != NULL)
	{
	  newTemp = newTemp->next;
	}
      newTemp->next = temp;
    }
}

// display function
void display()
{
  for(int i=0;i<SIZE;i++)
    {
      cout<<"T"<<i+1<<" Turn-around time = "<<turn_Around_Time[i]<<" waiting time = "<< wait_Time[i]<<endl;
    }

  cout<<"Average turn-around tIme = "<<avgTurnAroundTime<<", ";
  cout<<"Average waiting time = "<<avgWaitTime<<endl;
}

// calculation function
void calculate(Task* newT)
{
  int slot=SIZE-numTasks; //displays the same as run

  if(numTasks>=1)
    {

      // total wait time for the next task
      totalWaitTime+=QUANTUM;

      //turnaround time is the same as the wait time of the next task
      turnAroundTime=totalWaitTime;

      //wait time for this task
      if(waitTime<0)
	{
	  waitTime=0;
	}
      else
	{
	  waitTime=turnAroundTime-burst_time;
	}

      // save the turn-around time of this particular task
      turn_Around_Time[slot]=turnAroundTime;

      // save the wait time of this particular task
      wait_Time[slot]=waitTime;
    }

  // this should run once every task has been accounted for
  if(numTasks == 1)
    {
      //calculate the final total turn-around time
      for(int i=0;i<SIZE;i++)
	{
	  avgTurnAroundTime+=turn_Around_Time[i];
	}

      //calculate the final total waitting time
      for(int i=0;i<SIZE;i++)
	{
	  avgWaitTime+=wait_Time[i];
	}

      // calculate each average
      avgTurnAroundTime=(float)avgTurnAroundTime/SIZE;
      avgWaitTime=(float)avgWaitTime/SIZE;
    }
}// end of calculation function


int prevBurst(int burst)
{
  return burst;
}

void add(char *name, int priority, int burst)
{
  //create a Task
  Task *newT = (Task*)malloc(sizeof(Task));

  // inititalize struct values in Tasks
  newT->name = name;
  newT->tid = TID;
  newT->priority = priority;
  newT->burst = burst;

  // insert a node pointer and task object at the end
  // h1 should be pinting to newT in insert function
  insertAtEnd(&h1,newT);

  // next task
  TID++;
  numTasks++;

  if(TID == 1)
    {
      preVal = prevBurst(newT->burst);
    }
}// end of add function

/**
 *  * Run the RR scheduler
 *   */

// schedule function
void schedule()
{
  struct node *temp = h1;

  while(numTasks > 0)
    {
      Task *t1  = temp->task;

      // if task's burst time > quantum case
      if(t1->burst > QUANTUM)
	{
	  // run task
	  run(t1,QUANTUM);

	  // calculate
	  calculate(t1);

	  // minus quantum and go to next task
	  t1->burst = t1->burst - QUANTUM;
	  temp = temp->next;


	  if(temp != NULL)
	    {
	      t1 = temp->task;
	    }
	  else
	    {
	      temp = h1;
	      if(temp == NULL)
		{
		  break;
		}
	      else
		{
		  t1 = temp->task;
		}
	    }
	}

      // burst time < quantum case
      else
	{
	  int remaining_time = t1->burst;

	  //run task
	  run(t1,remaining_time);

	  //calculate
	  calculate(t1);

	  // minus remaining time
	  t1->burst = t1->burst - remaining_time;

	  // if burst time is empty then print out finish info
	  if(t1->burst <= 0)
	    {
	      cout<<"Task "<<t1->name<<" finished."<<endl;
	    }

	  // next task
	  temp = temp->next;

	  //remove task
	  remove(&h1, t1);

	  //decrment count
	  numTasks--;

	  if(temp != NULL)
	    {
	      t1 = temp->task;
	    }
	  else
	    {
	      temp = h1;
	      if(temp == NULL)
		{
		  break;
		}
	      else
		{
		  t1 = temp->task;
		}
	    }

	}
    }// end of while

  //display function
  display();
}// end of schedule function
