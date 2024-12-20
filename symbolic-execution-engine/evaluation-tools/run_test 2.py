import shlex
import subprocess
import concurrent.futures
import os
import json


output_dir = "/home/klee/FreeRTOS-Kernel-10.6.0/symbolic_execution/output/"
test_files_dir = "/home/klee/FreeRTOS-Kernel-10.6.0/symbolic_execution/test_files/"
# funcs = [
#     {
#         "name": "vTaskDelay",
#         "arg_nums": 1,
#         "arguments": "xTicksToDelay",
#         "type": "TickType_t ",
#         "control_flags" : "true"
#     },
#     {
#         "name": "xTaskDelayUntil",
#         "arg_nums": 2,
#         "arguments": "pxPreviousWakeTime, xTimeIncrement",
#         "type": "TickType_t *, TickType_t",
#         "control_flags" : " restricted, true"
#     },
#     {
#         "name": "xTaskAbortDelay",
#         "arg_nums": 1,
#         "arguments": "xTask",
#         "type": "TaskHandle_t",
#         "control_flags" : "false"
#     },
#     {
#         "name": "uxTaskPriorityGet",
#         "arg_nums": 1,
#         "arguments": "xTask",
#         "type": "TaskHandle_t",
#         "control_flags" : "false"
#     },
#     {
#         "name": "eTaskGetState",
#         "arg_nums": 1,
#         "arguments": "xTask",
#         "type": "TaskHandle_t",
#         "control_flags" : "false"
#     },
#     {
#         "name": "vTaskGetInfo",
#         "arg_nums": 4,
#         "arguments": "xTask, pxTaskStatus, xGetFreeStackSpace, eState",
#         "type": "TaskHandle_t, TaskStatus_t *, BaseType_t, eTaskState",
#         "control_flags" : "false, restricted, true, true"
#     },
#     {
#         "name": "vTaskSuspend",
#         "arg_nums": 1,
#         "arguments": "xTaskToResume",
#         "type": "TaskHandle_t",
#         "control_flags" : "false"
#     },
#     {
#         "name": "vTaskResume",
#         "arg_nums": 1,
#         "arguments": "xTaskToResume",
#         "type": "TaskHandle_t",
#         "control_flags" : "false"
#     },
#     {
#         "name": "pcTaskGetName",
#         "arg_nums": 1,
#         "arguments": "xTaskToQuery",
#         "type": "TaskHandle_t",
#         "control_flags" : "false"
#     },
#     {
#         "name": "uxTaskGetStackHighWaterMark",
#         "arg_nums": 1,
#         "arguments": "xTask",
#         "type": "TaskHandle_t",
#         "control_flags" : "false"
#     },
#     {
#         "name": "uxTaskGetStackHighWaterMark2",
#         "arg_nums": 1,
#         "arguments": "xTask",
#         "type": "TaskHandle_t",
#         "control_flags" : "false"
#     },
#     {
#         "name": "vTaskSetApplicationTaskTag",
#         "arg_nums": 2,
#         "arguments": "xTask, pxHookFunction",
#         "type": "TaskHandle_t, TaskHookFunction_t",
#         "control_flags" : "false, true"
#     },
#     {
#         "name": "xTaskGetApplicationTaskTag",
#         "arg_nums": 1,
#         "arguments": "xTask",
#         "type": "TaskHandle_t",
#         "control_flags" : "false"
#     },
#     {
#         "name": "vTaskSetThreadLocalStoragePointer",
#         "arg_nums": 3,
#         "arguments": "xTaskToQuery, xIndex, pvValue",
#         "type": "TaskHandle_t, BaseType_t, void *",
#         "control_flags" : "false, true, true"
#     },
#     {
#         "name": "pvTaskGetThreadLocalStoragePointer",
#         "arg_nums": 2,
#         "arguments": "xTaskToQuery, xIndex",
#         "type": "TaskHandle_t, BaseType_t",
#         "control_flags" : "false,true"
#     },
#     {
#         "name": "uxTaskGetSystemState",
#         "arg_nums": 2,
#         "arguments": "pxTaskStatusArray,uxArraySize,pulTotalRunTime",
#         "type": "TaskStatus_t *,UBaseType_t,configRUN_TIME_COUNTER_TYPE *",
#         "control_flags" : "true,false,false"
#     },
#     {
#         "name": "ulTaskGetRunTimeCounter",
#         "arg_nums": 1,
#         "arguments": "xTask",
#         "type": "TaskHandle_t",
#         "control_flags" : "false"
#     },
#     {
#         "name": "ulTaskGetRunTimePercent",
#         "arg_nums": 1,
#         "arguments": "xTask",
#         "type": "TaskHandle_t",
#         "control_flags" : "false"
#     },
#     {
#         "name": "xTaskGenericNotify",
#         "arg_nums": 5,
#         "arguments": "xTaskToNotify,uxIndexToNotify,ulValue,eAction,pulPreviousNotificationValue",
#         "type": "TaskHandle_t,UBaseType_t,uint32_t,eNotifyAction,uint32_t *",
#         "control_flags" : "false, true, true, true, true"
#     },
#     {
#         "name": "xTaskGenericNotifyWait",
#         "arg_nums": 5,
#         "arguments": "uxIndexToWaitOn, ulBitsToClearOnEntry, ulBitsToClearOnExit, pulNotificationValue, xTicksToWait",
#         "type": "UBaseType_t, uint32_t, uint32_t,uint32_t *,TickType_t",
#         "control_flags" : "true, true, true, true, true"
#     },
#     {
#         "name": "ulTaskGenericNotifyTake",
#         "arg_nums": 3,
#         "arguments": "uxIndexToWaitOn, xClearCountOnExit, xTicksToWait",
#         "type": "UBaseType_t, BaseType_t, TickType_t",
#         "control_flags" : "true, true, true"
#     },
#     {
#         "name": "xTaskGenericNotifyStateClear",
#         "arg_nums": 2,
#         "arguments": "xTask, uxIndexToClear",
#         "type": "TaskHandle_t, UBaseType_t",
#         "control_flags" : "true, true"
#     },
#     {
#         "name": "ulTaskGenericNotifyValueClear",
#         "arg_nums": 3,
#         "arguments": "xTask, uxIndexToClear, ulBitsToClear",
#         "type": "TaskHandle_t, UBaseType_t, uint32_t",
#         "control_flags" : "true, true, true"
#     },
#     {
#         "name": "vTaskSetTimeOutState",
#         "arg_nums": 1,
#         "arguments": "pxTimeOut",
#         "type": "TimeOut_t *",
#         "control_flags" : "true"
#     },
#     {
#         "name": "xTaskCheckForTimeOut",
#         "arg_nums": 2,
#         "arguments": "pxTimeOut, pxTicksToWait",
#         "type": "TimeOut_t *, TickType_t *",
#         "control_flags" : "true, true"
#     }
#     # you can add more function definitions here
# ]



funcs_delete = [
    "uxTaskGetSystemState",
    "ulTaskGetRunTimeCounter",
    "ulTaskGetRunTimePercent",
    "xTaskGenericNotify",
    "xTaskGenericNotifyWait",
    "ulTaskGenericNotifyTake",
    "xTaskGenericNotifyStateClear",
    "ulTaskGenericNotifyValueClear",
    "vTaskSetTimeOutState",
    "xTaskCheckForTimeOut"
]

# for func in funcs_delete:

#     command_clean = [
#         "rm", 
#         "/home/klee/FreeRTOS-Kernel-10.6.0/symbolic_execution/"+shlex.quote(func)+".c"
#     ]
#     print("Executing command: " + " ".join(command_clean))
#     subprocess.run(command_clean, check=True)
def run_command(func):
    func_name = func["name"]
    command_clean_dir = [
        "rm", 
        "-rf", 
        "/home/klee/FreeRTOS-Kernel-10.6.0/symbolic_execution/"+shlex.quote(func_name)
    ]
    print("Executing command: " + " ".join(command_clean_dir))
    subprocess.run(command_clean_dir, check=True)
    
    temp_output_path = output_dir+shlex.quote(func_name)+"_temp_output.txt"
    os.makedirs(output_dir, exist_ok=True)
    with open(temp_output_path, "w") as temp_file:
        command = [
            "/home/klee/klee_test/build/bin/klee", 
            "--search=dfs", 
            "-debug-print-instructions=all:stderr", 
            "--output-dir="+output_dir+shlex.quote(func_name), 
            test_files_dir+shlex.quote(func_name)+".test.bc"
        ]
        print("Executing command: " + " ".join(command))
        subprocess.run(command, stdout=temp_file, stderr=temp_file)

    output_path = output_dir+shlex.quote(func_name)+"_output.txt"
    with open(output_path, "w") as output_file:
        # run the tail command and redirect the output to your target file
        subprocess.run(["tail", "-n", "40", temp_output_path], stdout=output_file)
    
    # Delete the temp file
    os.remove(temp_output_path)


# func = funcs[0]
# run_command(func)

with concurrent.futures.ProcessPoolExecutor() as executor:
    with open('funcs_info_v2.json', 'r') as f:
        funcs = json.load(f)
        executor.map(run_command, funcs)