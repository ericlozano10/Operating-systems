#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>


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
      cout<<newT->name<<" Turn-around time = "<<turnAroundTime<<" WaitTime = "<<waitTime<<endl;
      preVal = 0;//reset preval to 0
      if(numTasks == SIZE)
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
  display(newT);
  
}

/**
 *  * Run the FCFS scheduler
 *   */
void schedule() 
{
  // TODO: add your implementation here
  while(numTasks > 0)
    {  
      Task *temp = h1->task; 
      run(temp,temp->burst);//run task
      remove(&h1, temp);//once done running remove task
      numTasks--;//decrement count
     
    }
}
