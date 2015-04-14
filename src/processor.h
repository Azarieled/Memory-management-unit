#ifndef PROCESSOR
#define PROCESSOR

#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

// hardware properties
const size_t       MAIN_MEMORY_SIZE = 512 * 1024 * 1024;             // 512 MB
#define PAGE_SIZE        4096                                        //   4 KB
#define PAGE_FRAME_COUNT MAIN_MEMORY_SIZE / PAGE_SIZE

const unsigned int SWAP_SIZE        = 1024 * 1024 * 1024;            //   1 GB
const unsigned int MAX_PID          = 255;

typedef size_t pid_t;
typedef size_t virtual_address_t;
typedef size_t physical_address_t;
typedef size_t page_num_t;

typedef struct
{
  bool               P            : 1;
  bool               R            : 1;
  bool               M            : 1;
  page_num_t         page_frame   : sizeof (size_t) * CHAR_BIT - (int) ceil(log2(PAGE_SIZE));
} page_t;

typedef struct
{
  int created : 1;
  page_t *page_table;
  size_t page_table_size : sizeof (size_t) * CHAR_BIT - (int) ceil(log2(PAGE_SIZE));
} process_t;

/*
 * Returns 0 if created, -1 if process is already created, 1 if pid > MAX_PID.
 */
int
create_process (pid_t pid, size_t virtual_pages);

/*
 * Returns 0 if switched, -1 if process is not created, 1 if pid > MAX_PID.
 */
int
switch_context (pid_t pid);

page_t *
get_page_table ();

unsigned int
get_page_table_size ();

physical_address_t
read_virtual_page (pid_t pid, virtual_address_t addr);

physical_address_t
modify_virtual_page (pid_t pid, virtual_address_t addr);

#endif // PROCESSOR

