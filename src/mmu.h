#ifndef MMU_H
#define MMU_H

#include <stdlib.h>
#include <limits.h>
#include <math.h>

// hardware props
const size_t       MAIN_MEMORY_SIZE = 512 * 1024 * 1024;             // 512 MB

// paging props
#define PAGE_SIZE        4096                                        //   4 KB
#define PAGE_NUMBER_BITS 12
#define PAGE_FRAME_COUNT MAIN_MEMORY_SIZE / PAGE_SIZE

const unsigned int SWAP_SIZE        = 1024 * 1024 * 1024;            //   1 GB

typedef size_t virtual_address_t;
typedef size_t physical_address_t;
typedef size_t page_num_t;

typedef struct page_t
{
  int        P          : 1;
  int        R          : 1;
  int        M          : 1;
  page_num_t page_frame : PAGE_NUMBER_BITS;
} page_t;

page_t *
get_page_table ();

void
set_page_table(page_t *new_page_table);

unsigned int
get_page_table_size ();

void
set_page_table_size(unsigned int new_size);

physical_address_t
convert(virtual_address_t addr, char modification);

#endif // MMU_H

