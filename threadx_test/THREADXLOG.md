### 代码注释部分
- 注释 /home/klee/threadx/threadx/common/inc/tx_api.h 128行，“#include "tx_port.h"”, 不考虑架构相关代码。
- 注释 /home/klee/threadx/threadx/common/src/tx_initialize_kernel_enter.c 117，121行，忽略架构相关代码。
- 注释 /home/klee/threadx/threadx/common/src/tx_thread_create.c 225行，忽略thread的stack初始化，
- 注释 /home/klee/threadx/threadx/ports/cortex_m33/gnu/inc/tx_port.h 628，629行，忽略架构底层汇编指令
- 在klee_help.h中增加_tx_thread_secure_stack_allocate、_tx_thread_schedule的弱定义。
- 在module-lib中的函数定义上，增加一个前缀m，避免编译带来的符号重定义问题。


- 注释txm_module_manager_thread_reset.c里面的TX_DISABLE和TX_RESOTRE
- 注释txm_module_manager_thread_reset.c里面的_txm_module_manager_thread_stack_build

- 注释 /home/klee/threadx/threadx/ports_module/cortex_m33/gnu/inc/tx_port.h 575行的 | _tx_ipsr_get()
- 注释 /home/klee/threadx/threadx/common/src/tx_thread_initialize.c 74行=  TX_INITIALIZE_IN_PROGRESS;
- 注释 tx_timer_change.c里面的TX_DISABLE和TX_RESOTRE
- 注释 tx_thread_time_slice_change.c里面的TX_DISABLE和TX_RESOTRE
- 注释 tx_thread_system_resume.c里面的TX_DISABLE, TX_RESOTREE和TX_THREAD_SYSTEM_RETURN_CHECK(), _tx_thread_system_return()
- 注释 tx_queue_delete.c里面的TX_DISABLE和TX_RESOTRE
- 修改 tx_queue_delete.c 148行while循环为if语句
- 注释 tx_queue_front_send.c里面的TX_DISABLE和TX_RESOTRE
- 注释 tx_queue_flush.c里面的TX_DISABLE和TX_RESOTRE, 153行break
- 修改 tx_queue_flush.c 142行while循环为if语句
- 注释 tx_queue_prioritize.c里面的TX_DISABLE和TX_RESOTRE, 147行do, 210行while循环
- 注释 tx_queue_receive.c里面的TX_DISABLE和TX_RESOTRE
- 注释 tx_queue_send_notify.c里面的TX_DISABLE和TX_RESOTRE
- 注释 tx_queue_send.c里面的TX_DISABLE和TX_RESOTRE
- 注释 tx_thread_entry_exit_notify.c里面的TX_DISABLE和TX_RESOTRE
- 注释 tx_preemption_change.c里面的TX_DISABLE和TX_RESOTRE



- 注释 tx_thread_system_suspend.c里面的TX_DISABLE和TX_RESOTRE, _tx_thread_system_return()
- 注释 tx_queue_create.c里面的TX_DISABLE和TX_RESOTRE
- 注释 txe_queue_create.c里面的TX_DISABLE和TX_RESOTRE
- 注释 txe_mutex_get.c里面的TX_DISABLE和TX_RESOTRE

- 注释/home/klee/threadx/threadx/ports_module/cortex_m33/gnu/inc/tx_port.h 的674行constant地址赋值, 对constant值进行了寻址操作。


### 额外修改
- 重写了参数检查部分，具体见modified_files文件夹。


### 编译问题
- 编译后发现运行程序，在klee::Executor::initializeGlobals处报Segmentation fault (core dumped)，后面调试发现是由于threadx中定义了函数指针，KLEE在load函数指针的时候报错。
- 上述问题解决，是由于对global function pointer 的初始化错误所导致。因为我们会对所有的全局指针进行内存分配，然后全局变量初始化过程中未考虑函数指针类型的的全局变量。


### 问题记录
- 2023-11-03, tx_timer_create()函数无法通过参数检查调用_txe_timer_create()



