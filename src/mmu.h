#ifndef MMU_H
#define MMU_H
#include <stdbool.h>
#include <stdlib.h>
#include "process.h"

typedef size_t physical_page_t;

typedef struct { bool P, R, M; size_t address; physical_page_t physical_page; } virtual_page_t;

typedef struct { size_t pid; virtual_page_t *pages; } process_t;

process_t
create_process(int pid, size_t virtual_pages);

physical_page_t
read_virtual_page (virtual_page_t *page);

physical_page_t
modify_virtual_page (virtual_page_t *page);

physical_page_t
pageFault (virtual_page_t *page);

physical_page_t
demandPage ();

physical_page_t
replace_page ();



#endif // MMU_H

