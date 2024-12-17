- 注释 wait_for_event.c 63、64、65、66行, 避免调用pthread_cond_wait()使程序陷入等待, 避免loop。
- 注释 tasks.c 1001行, 避免调用external function pthread_once等。
- 修改 tasks.c 2203行while循环变if, 避免loop。
- 注释 port.c 501行，避免调用pthread_exit( NULL ), 使程序终止。
- 修改 tasks.c 141行while循环为if, 避免loop。
- 修改 list.c 179行while循环为if, 避免loop。
- 注释 queue.c 901行 for( ; ; ), 避免loop。
- 修改 queue.c 2343行while循环为if；并注释2383行,2406行break语句, 避免loop。
- 修改 queue.c 2423行while循环为if；并注释2440行break语句, 避免loop。
- 修改 memcpy.c 16行while循环为if, 避免因char*对char数组分配不足, 避免loop。

- 注释 tasks.c 891行-910行，避免因char*对char数组分配不足的问题。
- 修改 queue.c 1448行 for( ; ; )为for( int i=0;i<2 ;i++ ), 避免过多loop。
- 修改 queue.c 1802行 for( ; ; )为for( int i=0;i<2 ;i++ ), 避免过多loop。
- 修改 event_groups.c 566行while循环为if, 避免loop。
- 修改 queue.c 1594行 for( ; ; )为for( int i=0;i<2 ;i++ ), 避免过多loop。
- 注释 tasks.c 3114行, 避免对pxCurrentTCB重复赋值。
- 注释 portable.h 107-133行，避免重复定义

- 注释 task.c 949，978行，该行为external函数