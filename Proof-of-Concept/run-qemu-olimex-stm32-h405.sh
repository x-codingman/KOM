#!/bin/bash

PATH_PREFIX=${1:-"/workspace/threadx_exploitation"}

OUTPUT_FILES=(
    "read_before_kom.txt"
    "read_after_kom.txt"
    "write_before_kom.txt"
    "write_after_kom.txt"
)

STM32F405_PATHS=(
    "$PATH_PREFIX/qemu_stm32f405_m4_read_before_exploit/qemu_stm32f405_m4_read_before_exploit/STM32CubeIDE/Tx_ModuleManager/Debug/Tx_ModuleManager.elf"
    "$PATH_PREFIX/qemu_stm32f405_m4_read_before_exploit/qemu_stm32f405_m4_read_before_exploit/STM32CubeIDE/Tx_Module/Debug/Tx_Module.elf"
    "$PATH_PREFIX/qemu_stm32f405_m4_read_after_exploit/qemu_stm32f405_m4_read_after_exploit/STM32CubeIDE/Tx_ModuleManager/Debug/Tx_ModuleManager.elf"
    "$PATH_PREFIX/qemu_stm32f405_m4_read_after_exploit/qemu_stm32f405_m4_read_after_exploit/STM32CubeIDE/Tx_Module/Debug/Tx_Module.elf"
    "$PATH_PREFIX/qemu_stm32f405_m4_write_before_exploit/qemu_stm32f405_m4_write_before_exploit/STM32CubeIDE/Tx_ModuleManager/Debug/Tx_ModuleManager.elf"
    "$PATH_PREFIX/qemu_stm32f405_m4_write_before_exploit/qemu_stm32f405_m4_write_before_exploit/STM32CubeIDE/Tx_Module/Debug/Tx_Module.elf"
    "$PATH_PREFIX/qemu_stm32f405_m4_write_after_exploit/qemu_stm32f405_m4_write_after_exploit/STM32CubeIDE/Tx_ModuleManager/Debug/Tx_ModuleManager.elf"
    "$PATH_PREFIX/qemu_stm32f405_m4_write_after_exploit/qemu_stm32f405_m4_write_after_exploit/STM32CubeIDE/Tx_Module/Debug/Tx_Module.elf"
)

DEVICE3=olimex-stm32-h405
DEVICE3_DIR=$(pwd)/$DEVICE3

echo -e "Enter \033[1;34m./run_gdb.sh $PATH_PREFIX $DEVICE3\033[0m in another terminal"
qemu-system-arm -M $DEVICE3 -serial file:output.txt -cpu cortex-m4 -nographic -kernel ${STM32F405_PATHS[2]} --device loader,file=${STM32F405_PATHS[3]} -s -S 
wait
echo -e "\033[1;32mFinished running QEMU on $DEVICE3 with MPU disabled\033[0m"
echo "Press Enter to continue..."
read

mkdir -p "$DEVICE3_DIR"  
echo "Created directory: $DEVICE3_DIR"
cd $DEVICE3_DIR
for i in 0 2 4 6; do
    kernel="${STM32F405_PATHS[$i]}"
    module="${STM32F405_PATHS[$i+1]}"
    output="${OUTPUT_FILES[$i/2]}"

    expect <<EOF
    spawn qemu-system-arm -M $DEVICE3 -serial file:output.txt -cpu cortex-m4 -nographic -kernel $kernel --device loader,file=$module -d int,exec,guest_errors -s -S -D $output
    expect "(qemu)" { send "c\r" } 
    after 300
    send "q\r"
    expect eof
EOF

    echo "Finished running QEMU on $DEVICE3 $output"
    
    if [[ "$output" == *"before"* ]]; then
        echo -e "\033[1;32mYou can find the fault information with MemManage Handler in file: $DEVICE3/$output\033[0m"
    elif [[ "$output" == *"after"* ]]; then
        echo -e "\033[1;32mKOM has been successfully launched. You can review the $output, which contains no fault information.\033[0m"
    fi

    echo "Grep manager_memory_fault_handler"
    grep "manager_memory_fault_handler" $output 
    echo "Press Enter to continue..."
    read
done
