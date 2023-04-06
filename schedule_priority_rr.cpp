#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

#include "task.h"
#include "list.h"
#include "cpu.h"
using namespace std;

//create node
struct node *h1 = NULL;

//counters and max size
int numTasks = 0;
int TID = 1;
const int SIZE = 8;

//turn around times
int arrvTime = 0;
int turnAroundTime = 0;
float avgTurnAroundTime = 0.0;

//wait times
int waitTime = 0;
int totalWaitTime = 0;
float avgWaitTime = 0.0;
//stores previous value
int preVal = 0;
bool priorityCheck = false;

void insertAtEnd(struct node**head, Task *task)
{
  struct node* temp = (struct node*) malloc(sizeof(struct node));
  struct node *newTemp = *head;

  temp->task = task;
  temp->next = NULL;

  if(*head == NULL)
    {
      *head = temp;
    }
  else
    {
      while(newTemp->next != NULL)
	{
	  newTemp = newTemp->next;
	}
      newTemp->next = temp;
    }
}



void display(Task* newT)
{
  //check arrival time
  if(numTasks == 1)
    {
      waitTime = 0;
      preVal = newT->burst;//store burst time to preval
      turnAroundTime = preVal;//store preval in turn around time
      cout<<newT->name<<" Turn-around time = "<<turnAroundTime<<" WaitTime = "<<waitTime<<endl;
    }
  else if(numTasks > 1)
    {
      //wait time calculation
      waitTime = waitTime + newT->burst;
      avgWaitTime += waitTime;
      //turn around time calculation
      turnAroundTime = turnAroundTime + newT->burst;
      avgTurnAroundTime += turnAroundTime;
      //cout<<newT->name<<" Turn-around time = "<<turnAroundTime<<" WaitTime = "<<waitTime<<endl;
      preVal = 0;//reset preval to 0
      if(numTasks == SIZE)
	{
	  //ave wait time
	  avgWaitTime = (float) avgWaitTime/numTasks;
	  //cout<<"avgWaitTIme = "<<avgWaitTime<<endl;
	  //turn around time
	  avgTurnAroundTime = (float) avgTurnAroundTime/numTasks;
	  //cout<<"avgTurnAroundTIme = "<<avgTurnAroundTime<<endl;
	}
    }
}

int prevBurst(int burst)
{
  return burst;
}

void add(char *name, int priority, int burst)
{
  // TODO: add your implementation here
  //create a Task
  Task *newT = (Task*)malloc(sizeof(Task));
  newT->name = name;
  newT->tid = TID;
  newT->priority = priority;
  newT->burst = burst;

  //insert a node pointer and task object
  insertAtEnd(&h1,newT);
  
  if(TID == 1)
    {
      preVal = prevBurst(newT->burst);
      //cout<<"prevVal = "<<prevVal<<endl;
    }
  TID++;
  numTasks++;

}

Task *RRPriority()
{
  struct node * headTask = h1->next;
  Task * currentTask = h1->task;//points to h1 task
  Task* prevTask =  h1->task;
  
  while(headTask != NULL)
    {
      //4                             5
      if(headTask->task->priority > currentTask->priority)
        {
	  currentTask = headTask->task;
	  priorityCheck = false;
	}
      else if(headTask->task->priority == currentTask->priority)
	{
	  priorityCheck = true;
	}
      headTask = headTask->next;
    }//while
  return currentTask;
}


/**
 *  * Run the RR scheduler
 *   */
void schedule()
{
  // TODO: add your implementation here
  
  struct node *temp = h1;
  Task * t1;//points to h1 task
  while(numTasks > 0)
    {
      t1 = RRPriority();
      //cout<<"priorityCheckT: "<<priorityCheck<<endl;
      if(priorityCheck == true)
	{
	  if(t1->burst > QUANTUM)
	    {
	      run(t1,QUANTUM);
	      //display(t1);
	      t1->burst = t1->burst - QUANTUM;
	      insertAtEnd(&h1,t1);
	      remove(&h1,t1);
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
		      return;
		    }
		  else
		    {
		      t1 = temp->task;
		    }
		}

	      
	    }
	  else
	    {
	      int timeRemaining = t1->burst;
	      run(t1,timeRemaining);
	      t1->burst = t1->burst - timeRemaining;
	      temp = temp->next;
	      remove(&h1, t1);
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
		      return;
		    }
		  else
		    {
		      t1 = temp->task;
		    }
		}

	    }
	}
      else
	{
	  /*
	  if(t1->burst > QUANTUM)
	    {
	      run(t1,QUANTUM);
	      //display(t1);
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
		      return;
		    }
		  else
		    {
		      t1 = temp->task;
		    }
		}
	    }
	  else*/
	    {
	      int timeRemaining = t1->burst;
	      //display(t1);
	      run(t1,timeRemaining);
	      t1->burst = t1->burst - timeRemaining;
	      temp = temp->next;
	      remove(&h1, t1);

	      if(temp != NULL)
		{
		  t1 = temp->task;
		}
	      else
		{
		  temp = h1;
		  if(temp == NULL)
		    {
		      return;
		    }
		  else
		    {
		      t1 = temp->task;
		    }
		}
	    }
	}

    }//while

}//func
