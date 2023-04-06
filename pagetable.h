#pragma once
#include <vector>
using namespace std;
// Remember to add comments to your code

// A page table entry
class PageEntry
{
public:
	// Physical frame number for a given page
	int frame_num;
	// valid bit represents whether a page is in the physical memory
	bool valid = false;
	// dirty bit represents whether a page is changed
	bool dirty = false;
	//LRU last
	int last;

};

/**
 * \brief A page table is like an array of page entries. The size of the page table should equal to the number of pages in logical memory
 */
class Page_Algorithm
{
 public:

  void LRU(void);
  void FIFO(int pagesize, int mem_size);
  void Random(int pagesize, int mem_size);


};
