#include "klee_help.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>



#include <klee/klee.h>
// add to check out how does klee reason the array with symbolic index
#include <list.h>

#define STACK_SIZE 200
#define MPU_ENABLE_ADDRESS_START 0xefff2000
#define MPU_ENABLE_ADDRESS_END 0xefff4000







void vTaskFunction1( void *pvParameters );
void vTaskFunction2( void *pvParameters );
void vTaskFunction3( void *pvParameters );

struct test_structure{
    int a;
    int * p_a;
};
typedef struct test_structure  test_structure_t;

void vAssertCalled( const char * const pcFileName,
                           unsigned long ulLine ){
    assert(0);
}


void vResetPrivilege(){

}

bool xIsPrivileged(){
    return false;
}


void test_func(struct test_structure* ts){
    ts->p_a = 0;
}


int main()
{
    




   
    
    // xTaskCreate(vTaskFunction2, "Task2", STACK_SIZE, NULL, 1, NULL);
    // xTaskCreate(vTaskFunction3, "Task3", STACK_SIZE, NULL, 1, NULL);
    

    struct test_structure * ts, *ts_uncontrollable;
    int * p;

    QueueHandle_t xQueue;
    klee_make_symbolic_controllable(&ts,sizeof(ts),"ts",true);
     klee_make_symbolic_controllable(&p,sizeof(p),"p",true);
     
     klee_make_symbolic_controllable(&ts_uncontrollable,sizeof(ts_uncontrollable),"ts_uncontrollable",false);
    klee_make_symbolic_controllable(&xQueue,sizeof(xQueue),"xQueue",true);
    const void * const pvItemToQueue;
    klee_make_symbolic_controllable(&pvItemToQueue,sizeof(pvItemToQueue),"pvItemToQueue",true);
    TickType_t xTicksToWait;
    klee_make_symbolic_controllable(&xTicksToWait,sizeof(xTicksToWait),"xTicksToWait",true);
    const BaseType_t xCopyPosition;
    klee_make_symbolic_controllable(&xCopyPosition,sizeof(xCopyPosition),"xCopyPosition",true);
   
     xTaskCreate(vTaskFunction1, "Task1", STACK_SIZE, NULL, 1, NULL);
     
    // if(xQueue>MPU_ENABLE_ADDRESS_START && xQueue<MPU_ENABLE_ADDRESS_END)
    //     xQueueGenericSend(xQueue,pvItemToQueue,xTicksToWait,xCopyPosition );


    TaskHandle_t xTaskToNotify;
    UBaseType_t uxIndexToNotify;
    uint32_t ulValue;
    eNotifyAction eAction;
    uint32_t * pulPreviousNotificationValue;
    klee_make_symbolic_controllable(&xTaskToNotify,sizeof(xTaskToNotify),"xTaskToNotify",true);
    klee_make_symbolic_controllable(&uxIndexToNotify,sizeof(uxIndexToNotify),"uxIndexToNotify",true);
    klee_make_symbolic_controllable(&ulValue,sizeof(ulValue),"ulValue",true);
    klee_make_symbolic_controllable(&eAction,sizeof(eAction),"eAction",true);
    klee_make_symbolic_controllable(&pulPreviousNotificationValue,sizeof(pulPreviousNotificationValue),"pulPreviousNotificationValue",true);
    xTaskGenericNotify(xTaskToNotify,uxIndexToNotify,ulValue,eAction,pulPreviousNotificationValue);


    // // Test function parameters passing
    // {
        
    //         struct test_structure *ts_1 = ts;


    //         test_func(ts_1);
        
        
    // }
    
    // // test controllable flag propagation 
    //    {
    //     if(ts->a > 0){
    //         struct test_structure *ts_2 = ts;
    //         ts_2->p_a = 0;
    //     }
        
    // }
    


    // // test bitcast issue
    // {
    //     struct test_structure * ts_3 = (test_structure_t *) p;
    //     ts_3->a = 0;
    // }
    

    // // Test uncontrollable variable
    // {
    //     ts_uncontrollable -> a  = 0;
    // }

    // // Test uncontrollable varible after a controllable assignment
    // {
    //     ts_uncontrollable->p_a = ts->p_a;
    //     *(ts_uncontrollable->p_a) = 0;
    // }


    // Test bit-level writing
    // *p = 0x2;

    
    return 0;
}

// 任务函数定义
void vTaskFunction1( void *pvParameters )
{

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