#ifndef OS_H
#define OS_H

#include <stdint.h>
#include "mmu.h"

#define MAX_PID 255


typedef size_t pid_t;

typedef struct process_t
{
	int     created : 1;
	size_t  page_table_size : sizeof(size_t) * CHAR_BIT - 1;
	page_t *page_table;
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

physical_address_t
read_virtual_page(virtual_address_t addr);

physical_address_t
modify_virtual_page(virtual_address_t addr);

void
resetBitR();

page_num_t
page_fault (page_t *page);

/*
 * Function is called during pageFault handling.
 */
page_num_t
demand_page ();

/*
 * Function is called when there are no free memory to satisfy
 */
page_num_t
replace_page ();

/*
 * NRU page replacement algorithm.
 * In worst case 3*n complexity.
 * Need to be optimized.
 */
page_num_t
NRU ();

#endif // MMU_H

