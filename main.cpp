// Remember to add comments to your code



#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>
#include <time.h>
#include "pagetable.h"
using namespace std;


// Check if an integer is power of 2
bool isPowerOfTwo(unsigned int x)
{
  /* First x in the below expression is for the case when x is 0 */
  return x && (!(x & (x - 1)));
}

int main(int argc, char* argv[]) {
  //Print basic information about the program
  std::cout << "=================================================================" << std::endl;
  std::cout << "CS 433 Programming assignment 5" << std::endl;
  std::cout << "Author: Eric Lozano and  Ting Wei Chien(Willy) and Isaac Ferrel" << std::endl;
  std::cout << "Date: 12/12/2021" << std::endl;
  std::cout << "Course: CS433 (Operating Systems)" << std::endl;
  std::cout << "Description : Program to simulate different page replacement algorithms" << std::endl;
  std::cout << "=================================================================\n" << std::endl;

  if (argc < 3) {
    // user does not enter enough parameters
    std::cout << "You have entered too few parameters to run the program.  You must enter" << std::endl
	      << "two command-line arguments:" << std::endl
	      << " - page size (in bytes): between 256 and 8192, inclusive" << std::endl
	      << " - physical memory size (in megabytes): between 4 and 64, inclusive" << std::endl;
    exit(1);
  }
  
  // Page size and Physical memory size 
  // Their values should be read from command-line arguments, and always a power of 2
  unsigned int page_size = atoi(argv[1]);
  if(!isPowerOfTwo(page_size))
    {
      std::cout << "You have entered an invalid parameter for page size (bytes)" << std::endl
		<< "  (must be an power of 2 between 256 and 8192, inclusive)." << std::endl;
      return 1;
    }
  unsigned int phys_mem_size = atoi(argv[2]) << 20; // convert from MB to bytes
  if(!isPowerOfTwo(phys_mem_size))
    {
      std::cout << "You have entered an invalid parameter for physical memory size (MB)" << std::endl
		<< "  (must be an even integer between 4 and 64, inclusive)." << std::endl;
      return 1;
    }

  // calculate number of pages and frames;
  int logic_mem_bits = 27;// 27-bit logical memory (128 MB logical memory assumed by the assignment)
  int phys_mem_bits = std::log2(phys_mem_size);// Num of bits for physical memory addresses, calculated from physical memory size, e.g. 24 bits for 16 MB memory
  int page_offset_bits = std::log2(page_size);// Num of bits for page offset, calculated from page size, e.g. 12 bits for 4096 byte page
  // Number of pages in logical memory = 2^(logic_mem_bits - page_bit)
  int num_pages = 1 << (logic_mem_bits - page_offset_bits);
  // Number of free frames in physical memory = 2^(phys_mem_bits - page_offset_bits)
  int num_frames = 1 << (phys_mem_bits - page_offset_bits);
  
  std::cout << "Page size = " << page_size << " bytes" << std::endl;
  std::cout << "Physical Memory size = " << phys_mem_size << " bytes" << std::endl;
  std::cout << "Number of pages = " << num_pages << std::endl; 
  std::cout << "Number of physical frames = " << num_frames << std::endl;

  // Test 1: Read and simulate the small list of logical addresses from the input file "small_refs.txt"
  std::cout <<"\n================================Test 1==================================================\n";
  // TODO: Add your code here for test 1 that prints out logical page #, frame # and whether page fault for each logical address
  ifstream file;
  string lagical_add;  // lagical address
  vector<int> v;       // vector
  int frame_counter = -1; // frame counter, to make first frame 0, so counter = -1 at the begining
  int fault_checker;   // fault checker

  file.open("small_refs.txt"); // open file

  if (file.is_open())
    {
      while(getline(file,lagical_add)) // get line by line
	{
	  int p_num = stoi(lagical_add) / page_size; // calculate the page number

	  // if frame number is not in the vector, add it
	  if(find(v.begin(),v.end(),p_num) == v.end())
	    {
	      v.push_back(p_num);
	      frame_counter++;
	      fault_checker = 1;
	    }
	  else
	    {
	      fault_checker = 0;
	    }

	  //--------------below is printing out the result---------------//
	  cout<<"Logical address: "<<lagical_add<<",    ";
	  cout<<"Page number: "<<p_num<<",    ";

	  // loop for element comparing
	  for(int i=0;i<v.size();i++)
	    {
	      //if index's value = page number then frame number equal to that index
	      if(v[i] == p_num)
		{
		  cout<<"Frame number: "<<i<<",    ";
		}
	    }
	  cout<<"is page fault? "<<fault_checker<<endl;
	}

      cout<<"Number of references: 100"<<endl;
      cout<<"Number of page faults: "<<frame_counter+1<<endl;
      cout<<"Number of page replacements: 0"<<endl;

      file.close();
    }

  
  // Test 2: Read and simulate the large list of logical addresses from the input file "large_refs.txt"
  std::cout <<"\n================================Test 2==================================================\n";

  std::cout<<"Total number of references: 2000000"<<std::endl;

  std::cout << "****************Simulate FIFO replacement****************************" << std::endl;
  // TODO: Add your code to calculate number of page faults using FIFO replacement algorithm
  Page_Algorithm pa;

  time_t f_start = time(0);
  // pa.FIFO(page_size,phys_mem_size);
  time_t f_end = time(0);
  double f_total_time = difftime(f_end,f_start);


  
  // TODO: print the statistics and run-time
  //std::cout<<"Number of references: "<<std::endl;        
  //std::cout<<"Number of page faults: "<<std::endl;
  //std::cout<<"Number of page replacements: "<<std::endl;
  std::cout<<"Elapsed time = "<< "<TIME var>" <<"seconds"<<std::endl;



  std::cout << "****************Simulate Random replacement****************************" << std::endl;
  // TODO: Add your code to calculate number of page faults using Random replacement algorithm
  pa.Random(page_size, phys_mem_size);

  // TODO: print the statistics and run-time
  std::cout<<"Number of references: "<<std::endl;
  std::cout<<"Number of page faults: "<<std::endl;
  std::cout<<"Number of page replacements: "<<std::endl;
  std::cout<<"Elapsed time = "<< "<TIME var>" <<"seconds"<<std::endl;

  std::cout << "****************Simulate LRU replacement****************************" << std::endl;
  // TODO: Add your code to calculate number of page faults using LRU replacement algorithm



  // TODO: print the statistics and run-time
  std::cout<<"Number of references: "<<std::endl;
  std::cout<<"Number of page faults: "<<std::endl;
  std::cout<<"Number of page replacements: "<<std::endl;
  std::cout<<"Elapsed time = "<< "<TIME var>" <<"seconds"<<std::endl;

}
