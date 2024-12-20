/* This is a small demo of the high-performance ThreadX kernel.  It includes examples of eight
   threads of different priorities, using a message queue, semaphore, mutex, event flags group, 
   byte pool, and block pool.  */

#include "tx_api.h"
#include "klee/klee.h"
#include "klee_help.h"

#define DEMO_STACK_SIZE         1024
#define DEMO_BYTE_POOL_SIZE     9120
#define DEMO_BLOCK_POOL_SIZE    100
#define DEMO_QUEUE_SIZE         100


/* Define the ThreadX object control blocks...  */

// TX_THREAD               thread_0;
// TX_THREAD               thread_1;
// TX_THREAD               thread_2;
// TX_THREAD               thread_3;
// TX_THREAD               thread_4;
// TX_THREAD               thread_5;
// TX_THREAD               thread_6;
// TX_THREAD               thread_7;
// TX_QUEUE                queue_0;
// TX_SEMAPHORE            semaphore_0;
// TX_MUTEX                mutex_0;
// TX_EVENT_FLAGS_GROUP    event_flags_0;
// TX_BYTE_POOL            byte_pool_0;
// TX_BLOCK_POOL           block_pool_0;
// UCHAR                   memory_area[DEMO_BYTE_POOL_SIZE];


// /* Define the counters used in the demo application...  */

// ULONG                   thread_0_counter;
// ULONG                   thread_1_counter;
// ULONG                   thread_1_messages_sent;
// ULONG                   thread_2_counter;
// ULONG                   thread_2_messages_received;
// ULONG                   thread_3_counter;
// ULONG                   thread_4_counter;
// ULONG                   thread_5_counter;
// ULONG                   thread_6_counter;
// ULONG                   thread_7_counter;


// /* Define thread prototypes.  */

// void    thread_0_entry(ULONG thread_input);
// void    thread_1_entry(ULONG thread_input);
// void    thread_2_entry(ULONG thread_input);
// void    thread_3_and_4_entry(ULONG thread_input);
// void    thread_5_entry(ULONG thread_input);
// void    thread_6_and_7_entry(ULONG thread_input);


// /* Define main entry point.  */
extern TX_THREAD *    _tx_thread_current_ptr;
int main()
{

    /* Enter the ThreadX kernel.  */
    //tx_kernel_enter();
    klee_make_symbolic_controllable(&_tx_thread_current_ptr, sizeof(_tx_thread_current_ptr), "_tx_thread_current_ptr", false);
    TX_THREAD *thread_ptr;
    ULONG new_time_slice;
    ULONG *old_time_slice;
    
    klee_make_symbolic_controllable(&thread_ptr, sizeof(thread_ptr), "thread_ptr", true);
    klee_make_symbolic_controllable(&new_time_slice, sizeof(new_time_slice), "new_time_slice", true);
    klee_make_symbolic_controllable(&old_time_slice, sizeof(old_time_slice), "old_time_slice", true);
    m_txe_thread_time_slice_change(thread_ptr,new_time_slice,old_time_slice);
}


/* Define what the initial system looks like.  */

void    tx_application_define(void *first_unused_memory)
{



}