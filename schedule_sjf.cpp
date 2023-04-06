#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#include "task.h"
#include "list.h"
#include "cpu.h"

using namespace std;

//create global head 
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


//next task function
Task * nextTask()
{
  double lowburst;

  struct node *temp = h1;
  //looking for the lowest burtst time
  lowburst=temp->task->burst;
  for(int i=0;i<numTasks;i++)
    {
      if(temp->task->burst<lowburst)
	{
	  lowburst=temp->task->burst;temp=temp->next;
	}
      else
	{
	  temp=temp->next;
	}
    }
  temp=h1;

  for(int i=0;i<numTasks;i++)
    {if(temp->task->burst==lowburst){break;}
      else{temp=temp->next;}
    }
  Task * task1 =temp->task;
  temp=h1;

  //cout<< task1->tid;
  //temp=temp->next;
  //cout<< temp->task->tid;
  //for(int i=0;i<numTasks;i++){cout<< temp->task->tid;temp=temp->next;}
  //temp=h1;
  for(int i=0;i<numTasks;i++)
    {//cout<<"comparing task1:  "<<task1->tid<<"  to temp:  "<<temp->task->tid<<endl;
      if(temp->task->burst==lowburst && temp->task->tid < task1->tid)
	{
	  task1=temp->task;temp=temp->next;
	}
      else
	{
	  temp=temp->next;
	}
      //cout<<"this the number it is currently looking at: "<<temp->task->tid<<endl;
    }
  return task1;
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
      //  if(numTasks == 0)
      {
	//avg wait time
	avgWaitTime = (float) avgWaitTime/numTasks;
	//cout<<"avgWaitTIme = "<<avgWaitTime<<endl;
	//turn around time
	avgTurnAroundTime = (float) avgTurnAroundTime/numTasks;
	//cout<<"avgTurnAroundTIme = "<<avgTurnAroundTime<<endl;
      }

    }
  else if(numTasks > 1)
    {
      //wait time calculation
      waitTime = waitTime + newT->burst;
      avgWaitTime += waitTime;
      //turn around time calculation
      turnAroundTime = turnAroundTime + newT->burst;
      avgTurnAroundTime += turnAroundTime;
      cout<<newT->name<<" Turn-around time = "<<turnAroundTime<<" WaitTime = "<<waitTime<<endl;
      preVal = 0;//reset preval to 0
      if(numTasks == 0)
        {
          //ave wait time
          avgWaitTime = (float) avgWaitTime/numTasks;
          cout<<"avgWaitTIme = "<<avgWaitTime<<endl;
          //turn around time
          avgTurnAroundTime = (float) avgTurnAroundTime/numTasks;
          cout<<"avgTurnAroundTIme = "<<avgTurnAroundTime<<endl;
        }
    }


}

int prevBurst(int burst)
{
  return burst;
}


// add a new task to the list of tasks
 void add(char *name, int priority, int burst) 
{
  // TODO: add your implementation here

  //TODO: add your implementation here
  //create Task
  Task *newT = (Task*) malloc(sizeof(Task));
  //inititalize struct values in Tasks
  newT->name = name;
  newT->tid = TID;
  newT->priority = priority;
  newT->burst = burst;


  //insert a node pointer and task object
  //h1 should be pinting to newT in insert function
  insert(&h1, newT);
  numTasks++;
  TID++;
  if(TID == 1)
    {
      preVal = prevBurst(newT->burst);
      //cout<<"prevVal = "<<prevVal<<endl;
    }
}

/**
 *  * Run the SJF scheduler
 *   */
void schedule() 
{
  // TODO: add your implementation here
  Task *current;
  while(numTasks > 0)
    {
      current = nextTask();
      display(current);
      run(current,current->burst);
      remove(&h1, current);
      numTasks--;
    }
}


