#include <stdio.h>
#include "os.h"

process_t g_process_table [MAX_PID]; //TODO smarter data structure with deleting process

int
create_process (pid_t pid, size_t virtual_pages)
{
  if (pid > MAX_PID)
    {
      return 1;
    }
  
  process_t *process = g_process_table + pid;
  if (process->created)
    {
      return -1;
    }

  process->page_table = (page_t *) calloc (sizeof (page_t), virtual_pages);
  process->created = 1;
  return 0;
}

int
switch_context (pid_t pid)
{
  if (pid > MAX_PID)
    {
      return 1;
    }

  process_t process = g_process_table [pid];
  if (!process.created)
    {
      return -1;
    }

  set_page_table (process.page_table);
  set_page_table_size (process.page_table_size);
  return 0;
}

void
resetBitR()
{
  page_t *table = get_page_table ();
  unsigned int size = get_page_table_size ();
  for (size_t i = 0; i < size; i++)
    {
      table->R = 0;
      ++table;
    }
}

page_num_t
page_fault (page_t *page)
{
  return demand_page ();
}

page_num_t
demand_page ()
{
  page_t *table = get_page_table ();
  unsigned int size = get_page_table_size ();

  // attempt to find free page
  for (unsigned int i = 0; i < size; i ++)
    {
      if (table->P) //TODO
        {
          table[i] = page;
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
  // just returning the first accessible one
  return table[0].page_frame;
}
