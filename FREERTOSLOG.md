# FreeRTOS中修改的文件
- 注释 wait_for_event.c 63、64、65、66行, 避免调用pthread_cond_wait()使程序陷入等待, 避免loop。
- 注释 port.c 498行，避免调用pthread_exit( NULL ), 使程序终止。
- 修改 tasks.c 141行while循环为if, 避免loop。
- 修改 list.c 179行while循环为if, 避免loop。
- 注释 queue.c 856行 for( ; ; ), 避免loop。
- 修改 queue.c 2372行while循环为if；并注释2389行break语句, 避免loop。
- 修改 queue.c 2292行while循环为if；并注释2332行break语句, 避免loop。
- 修改 memcpy.c 16行while循环为if, 避免因char*对char数组分配不足, 避免loop。
- 修改 tasks.c 2198行while循环变if, 避免loop。
- 注释 tasks.c 887行-906行，避免因char*对char数组分配不足的问题。
- 修改 queue.c 1403行 for( ; ; )为for( int i=0;i<2 ;i++ ), 避免过多loop。
- 修改 queue.c 1757行 for( ; ; )为for( int i=0;i<2 ;i++ ), 避免过多loop。
- 修改 event_groups.c 561行while循环为if, 避免loop。
- 修改 queue.c 1549行 for( ; ; )为for( int i=0;i<2 ;i++ ), 避免过多loop。

- 注释 tasks.c 997行, 避免调用external function pthread_once等。6/22
- 注释 tasks.c 3062行, 避免对pxCurrentTCB重复赋值。6/22

- 注释 tasks.c 2238-2239行, 2250行的循环