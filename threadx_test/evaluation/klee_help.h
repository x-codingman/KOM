#ifndef KLEE_HELP_H
    #define KLEE_HELP_H
 
    #include "stdbool.h"
    #include "tx_api.h"
    #include <stdint.h>
    #include "tx_port.h"

    #define MPU_ENABLE_ADDRESS_START 0xefff2000
    #define MPU_ENABLE_ADDRESS_END 0xefff4000
    #define ATTACK_CAPABILITY_REGION_START 0x80000000
    #define ATTACK_CAPABILITY_REGION_END 0x8fffffff
    #define KERNEL_OBJECT_MEMORY_START 0x90000000
    #define KERNEL_OBJECT_MEMORY_END 0xa0000000

    extern ALIGN_TYPE _txm_module_manager_kernel_dispatch(ULONG kernel_request, ALIGN_TYPE param_0, ALIGN_TYPE param_1, ALIGN_TYPE param_2);
     ULONG (*_txm_module_kernel_call_dispatcher)(ULONG kernel_request, ULONG param_1, ULONG param_2, ULONG param3);

// _txm_module_manager_object_pool_created = true;
// _txm_module_manager_object_pool = 0;
// _txm_module_manager_callback_error_count = 0;

    UINT  __attribute__((weak))  _tx_thread_secure_stack_allocate(struct TX_THREAD_STRUCT *tx_thread, ULONG stack_size){}
    VOID  __attribute__((weak))      _tx_thread_schedule(VOID){}

    // #define TXM_MODULE_MANAGER_PARAM_CHECK_BUFFER_WRITE(module_instance, obj_ptr, obj_size) \
    // is_unprivilged_memory(obj_ptr,obj_size)


    // #define TXM_MODULE_MANAGER_CHECK_INSIDE_CODE(module_instance, obj_ptr, obj_size) \
    // is_unprivilged_memory(obj_ptr,obj_size)

    // #define TXM_MODULE_MANAGER_CHECK_OUTSIDE_CODE(module_instance, obj_ptr, obj_size) \
    // !is_unprivilged_memory(obj_ptr,obj_size)

    // #define TXM_MODULE_MANAGER_CHECK_INSIDE_OBJ_POOL(module_instance, obj_ptr, obj_size) \
    // ((_txm_module_manager_object_pool_created == TX_TRUE) && \
    // is_privilged_memory(obj_ptr,obj_size))

    

bool is_unprivilged_memory(uint64_t ptr, uint32_t size){
        if (ATTACK_CAPABILITY_REGION_START < ptr && ATTACK_CAPABILITY_REGION_END > ptr){
            return true;
        }else{
            return false;
        }
}
bool is_kernel_object_memory(uint64_t ptr, uint32_t size){
        if (KERNEL_OBJECT_MEMORY_START < ptr && KERNEL_OBJECT_MEMORY_END > ptr){
            return true;
        }else{
            return false;
        }
}

    #define MAKE_SYMBOLIC_CONTROLLABLE(ptr) klee_make_symbolic_controllable(&ptr, sizeof(ptr),"",true);


    #define MAKE_SYMBOLIC_UNCONTROLLABLE(ptr) klee_make_symbolic_controllable(&ptr, sizeof(ptr),"",false);



    




#endif