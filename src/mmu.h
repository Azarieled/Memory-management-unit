#ifndef MMU_H
#define MMU_H
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

// operation system properties
#define MAIN_MEMORY_SIZE    512 * 1024 * 1024              // 512 MB
#define PAGE_SIZE           4096                           //   4 KB
#define PHYSICAL_PAGE_COUNT (MAIN_MEMORY_SIZE / PAGE_SIZE)
#define SWAP_SIZE           1024 * 1024 * 1024             //   1 GB
#define MAX_PID SIZE_MAX

// mmu propeties
#define MAX_PROCESS_NUMBER 1024 * 1024

typedef size_t pid_t;

typedef size_t physical_address_t;

typedef struct
{
  bool               P            : 1;
  bool               R            : 1;
  bool               M            : 1;
  size_t             number       : sizeof (size_t) * CHAR_BIT - 3;
  physical_address_t physical_page;
} virtual_page_t;

typedef struct { pid_t pid; virtual_page_t *pages; } process_t;

process_t *
get_process(pid_t pid);

/*
 * Returns true if created, false in other case.
 */
bool
create_process_virtual_table (pid_t pid, size_t virtual_pages);

physical_address_t
read_virtual_page (pid_t pid, size_t number);

physical_address_t
modify_virtual_page (pid_t pid, size_t number);

void
resetBitR();

physical_address_t
pageFault (virtual_page_t *page);

/*
 * Function is called when there are no free memory to satisfy
 */
physical_address_t
replace_page ();

/*
 * NRU page replacement algorithm.
 * In worst case 3*n complexity.
 * Need to be optimized.
 */
physical_address_t
NRU ();

#endif // MMU_H

