#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <klee/klee.h>
// add to check out how does klee reason the array with symbolic index
#include <list.h>

#define STACK_SIZE 200
#define MPU_ENABLE_ADDRESS_START 0xefff3000
#define MPU_ENABLE_ADDRESS_END 0xefff4000

void vTaskFunction1( void *pvParameters );
void vTaskFunction2( void *pvParameters );
void vTaskFunction3( void *pvParameters );

struct test_structure{
    int a;
    int * p_a;
};
int main()
{
    




   
    xTaskCreate(vTaskFunction1, "Task1", STACK_SIZE, NULL, 1, NULL);
    // xTaskCreate(vTaskFunction2, "Task2", STACK_SIZE, NULL, 1, NULL);
    // xTaskCreate(vTaskFunction3, "Task3", STACK_SIZE, NULL, 1, NULL);
    

    struct test_structure * ts;
    int * p;
    klee_make_symbolic(&ts,sizeof(p),"ts");
    klee_make_symbolic(&p,sizeof(ts),"p");
    QueueHandle_t xQueue;
    klee_make_symbolic(&xQueue,sizeof(xQueue),"xQueue");
    const void * const pvItemToQueue;
    klee_make_symbolic(&pvItemToQueue,sizeof(pvItemToQueue),"pvItemToQueue");
    TickType_t xTicksToWait;
    klee_make_symbolic(&xTicksToWait,sizeof(xTicksToWait),"xTicksToWait");
    const BaseType_t xCopyPosition;
    klee_make_symbolic(&xCopyPosition,sizeof(xCopyPosition),"xCopyPosition");
    if(MPU_ENABLE_ADDRESS_START < ts && ts < MPU_ENABLE_ADDRESS_END){
        //xQueueGenericSend(xQueue,pvItemToQueue,xTicksToWait,xCopyPosition );
        ts->p_a=p;
    }
    
    // 开始调度任务
    //vTaskStartScheduler();

    // 如果运行到这里，那么说明任务调度器因为某种原因停止了，正常情况下，main函数是不应该返回的。
    
    return 0;
}

// 任务函数定义
void vTaskFunction1( void *pvParameters )
{
     QueueHandle_t xQueue;
    klee_make_symbolic(&xQueue,sizeof(xQueue),"xQueue");
    const void * const pvItemToQueue;
    klee_make_symbolic(&pvItemToQueue,sizeof(pvItemToQueue),"pvItemToQueue");
    TickType_t xTicksToWait;
    klee_make_symbolic(&xTicksToWait,sizeof(xTicksToWait),"xTicksToWait");
    const BaseType_t xCopyPosition;
    klee_make_symbolic(&xCopyPosition,sizeof(xCopyPosition),"xCopyPosition");
    xQueueGenericSend(xQueue,pvItemToQueue,xTicksToWait,xCopyPosition );
    assert(0);

}

void vTaskFunction2( void *pvParameters )
{
    for( ;; )
    {
        // 这里放你的任务代码
    }
}

void vTaskFunction3( void *pvParameters )
{
    for( ;; )
    {
        // 这里放你的任务代码
    }
}