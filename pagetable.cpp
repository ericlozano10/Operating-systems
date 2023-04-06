#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include "pagetable.h"



using namespace std;

void Page_Algorithm::Random(int page_size, int mem_size)
{
  int buffersize = mem_size/page_size;
  cout<<"bs: "<<buffersize<<endl;
  ifstream file;
  string logical_add;
  vector<int> frame_buffer;
  int fault_counter = 0;
  int replacement_counter = 0;
  int ref_counter = 0;
  int x = 0;

  file.open("large_refs.txt");

  if(file.is_open())
    {

      while(getline(file,logical_add))
        {
          int p_num =stoi(logical_add) / page_size;

          ref_counter++;

          //when frame buffer is not full
          if(x<buffersize)
            {
              // not found page
              if(find(frame_buffer.begin(),frame_buffer.end(),p_num) == frame_buffer.end())
                {
                  frame_buffer.push_back(p_num);
                  fault_counter++;
                  x++;
                }
              // found, do nothing
              else
                {}
            }

          // when frame buffer is full
	  else
            {
              // not found
              if(find(frame_buffer.begin(),frame_buffer.end(),p_num) == frame_buffer.end())
                {
                  auto i =  frame_buffer.begin() + rand()% buffersize;
                  frame_buffer.insert(i,p_num);
                  fault_counter++;
                  replacement_counter++;
                }

              // not found, nothing
              else
                {}
            }

	}
      cout<<"Total references: "<<ref_counter<<endl;
      cout<<"Total fault: "<<fault_counter<<endl;
      cout<<"Total replacement: "<<replacement_counter<<"\n"<<endl;;
    }
}

void Page_Algorithm::FIFO(int page_size, int mem_size)
{

  int buffersize = mem_size/page_size;
  cout<<"bs: "<<buffersize<<endl;
  ifstream file;
  string logical_add;
  vector<int> frame_buffer;
  int fault_counter = 0;
  int replacement_counter = 0;
  int ref_counter = 0;
  int x = 0;

  file.open("large_refs.txt");

  if(file.is_open())
    {

      while(getline(file,logical_add))
	{
	  int p_num =stoi(logical_add) / page_size;

	  ref_counter++;

	  //when frame buffer is not full
	  if(x<buffersize)
	    {
	      // not found page
	      if(find(frame_buffer.begin(),frame_buffer.end(),p_num) == frame_buffer.end())
		{
		  frame_buffer.push_back(p_num);
		  fault_counter++;
		  x++;
		}
	      // found, do nothing
	      else
		{}
	    }

	  // when frame buffer is full
	  else
	    {
	      //  not found
	      if(find(frame_buffer.begin(),frame_buffer.end(),p_num) == frame_buffer.end())
		{
		  frame_buffer.erase(frame_buffer.begin());
		  frame_buffer.push_back(p_num);
		  fault_counter++;
		  replacement_counter++;
		}
	      // not found, nothing
	      else
		{}
	    }
	}	      
      cout<<"Total references: "<<ref_counter<<endl;
      cout<<"Total fault: "<<fault_counter<<endl;
      cout<<"Total replacement: "<<replacement_counter<<"\n"<<endl;
    }
}

