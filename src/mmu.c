#include <stdio.h>
#include "mmu.h"

void
resetBitR()
{
  page_t *table = get_page_table ();
  unsigned int *size = get_page_table_size ();
  for (unsigned int i = 0; i < size; i ++)
    {
      table->R = 0;
      ++table;
    }
}

page_num_t
pageFault (page_t *page)
{
  return
}

page_num_t
demand_page ()
{
  page_t *table = get_page_table ();
  unsigned int *size = get_page_table_size ();

  // attempt to find free page
  for (unsigned int i = 0; i < size; i ++)
    {
      if (table[i]) //TODO
        {
          g_present_page_table[i] = page;
          page->physical_page = i * PAGE_SIZE;
          printf ("Free physical page found at: %llx\n", page->physical_page);
          return page->physical_page;
        }
    }
  return replace_page(); //TODO handle swap crash
}


page_num_t
replace_page ()
{
  return NRU ();
}

page_num_t
NRU ()
{
  page_t *table = get_page_table ();
  unsigned int *size = get_page_table_size ();
  unsigned int i;

  // class 0
  for (i = 0; i < size; i ++)
    {
      if (!table[i].R & !table[i].M)
        {
          return table[i].page_frame;
        }
    }

  // class 1
  for (i = 0; i < size; i ++)
    {
      if (!table[i].R & table[i].M)
        {
          return table[i].page_frame;
        }
    }

  // class 2
  for (i = 0; i < size; i ++)
    {
      if (table[i].R & !table[i].M)
        {
          return table[i].page_frame;
        }
    }

  // if we reach here, - all pages are class 3
  return table[0].page_frame;
}
