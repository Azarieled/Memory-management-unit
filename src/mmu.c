#include "mmu.h"

page_t *g_page_table = NULL;
unsigned int g_page_table_size = 0;

page_t *
get_page_table ()
{
  return g_page_table;
}

void
set_page_table (page_t *new_page_table)
{
  g_page_table = new_page_table;
}

unsigned int get_page_table_size ()
{
  return g_page_table_size;
}

void
set_page_table_size (unsigned int new_size)
{
  g_page_table_size = new_size;
}

physical_address_t
convert (virtual_address_t addr, char modification)
{
	int page_num = addr >> PAGE_NUMBER_BITS;
	page_t *p = g_page_table + page_num;

	if (!p->P)
	  {
	    printf("Page fault at virtual page: %lx\n", page_num);
	    page_fault(p);
	    p->P = 1;
	  }
	p->R = 1;
	p->M |= modification;
}
