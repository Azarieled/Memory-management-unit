#include <stdio.h>
#include "os.h"

process_t g_process_table [MAX_PID]; //TODO smarter data structure with possibility to delete process
unsigned int swap_remaining_size = SWAP_SIZE;
page_frame_list_t *g_free_page_frame_list = NULL;

void
load_RAM ()
{
  page_num_t last_page = PAGE_FRAME_COUNT - 1;
  page_frame_list_t *cur = malloc(sizeof (page_frame_list_t));
  g_free_page_frame_list = cur;

  for (size_t i = 0; i < last_page; ++i)
    {
      cur->current = i;
      cur->next = malloc(sizeof (page_frame_list_t));
      cur = cur->next;
    }
  cur->next = NULL;
  cur->current = last_page;
}

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
      table->M = 0;
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
  // attempt to find free page
  if (g_free_page_frame_list != NULL)
    {
      page_frame_list_t *old_node = g_free_page_frame_list;
      page_num_t free_page_num = g_free_page_frame_list->current;

      g_free_page_frame_list = g_free_page_frame_list->next;
      free(old_node);
      return free_page_num;
    }

  return replace_page(); //TODO handle swap crash
}


page_num_t
replace_page ()
{
  swap_remaining_size -= PAGE_SIZE;
  return NRU ();
}

page_num_t
NRU ()
{
  page_t *table = get_page_table ();
  unsigned int size = get_page_table_size ();
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
      if (~table[i].R & table[i].M)
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


physical_address_t read_virtual_page(virtual_address_t addr)
{
  printf("Reading from address: %lu\n", addr);
  return convert(addr, 0);
}


physical_address_t modify_virtual_page(virtual_address_t addr)
{
  printf("Writing to address: %lu\n", addr);
  return convert(addr, 1);
}
