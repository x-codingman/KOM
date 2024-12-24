#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <base_path>"
    exit 1
fi

PATH_PREFIX=$1

OUTPUT_FILES=(
    "read_before_exploit.txt"
    "read_after_exploit.txt"
    "write_before_exploit.txt"
    "write_after_exploit.txt"
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


STM32L475_PATHS=(
    "$PATH_PREFIX/qemu_stm32l475_m4_read_before_exploit/qemu_stm32l475_m4_read_before_exploit/STM32CubeIDE/Tx_Module_Manager_Debug/qemu_stm32l475_m4_read_before_exploit.elf"
    "$PATH_PREFIX/qemu_stm32l475_m4_read_before_exploit/qemu_stm32l475_m4_read_before_exploit/STM32CubeIDE/Tx_Module_Debug/qemu_stm32l475_m4_read_before_exploit.elf"
    "$PATH_PREFIX/qemu_stm32l475_m4_read_after_exploit/qemu_stm32l475_m4_read_after_exploit/STM32CubeIDE/Tx_Module_Manager_Debug/qemu_stm32l475_m4_read_after_exploit.elf"
    "$PATH_PREFIX/qemu_stm32l475_m4_read_after_exploit/qemu_stm32l475_m4_read_after_exploit/STM32CubeIDE/Tx_Module_Debug/qemu_stm32l475_m4_read_after_exploit.elf"
    "$PATH_PREFIX/qemu_stm32l475_m4_write_before_exploit/qemu_stm32l475_m4_write_before_exploit/STM32CubeIDE/Tx_Module_Manager_Debug/qemu_stm32l475_m4_write_before_exploit.elf"
    "$PATH_PREFIX/qemu_stm32l475_m4_write_before_exploit/qemu_stm32l475_m4_write_before_exploit/STM32CubeIDE/Tx_Module_Debug/qemu_stm32l475_m4_write_before_exploit.elf"
    "$PATH_PREFIX/qemu_stm32l475_m4_write_after_exploit/qemu_stm32l475_m4_write_after_exploit/STM32CubeIDE/Tx_Module_Manager_Debug/qemu_stm32l475_m4_write_after_exploit.elf"
    "$PATH_PREFIX/qemu_stm32l475_m4_write_after_exploit/qemu_stm32l475_m4_write_after_exploit/STM32CubeIDE/Tx_Module_Debug/qemu_stm32l475_m4_write_after_exploit.elf"
)

DEVICE1=b-l475e-iot01a
DEVICE2=netduinoplus2
DEVICE3=olimex-stm32-h405

DEVICE1_DIR=$(pwd)/$DEVICE1
DEVICE2_DIR=$(pwd)/$DEVICE2
DEVICE3_DIR=$(pwd)/$DEVICE3

echo "Enter ./run_gdb.sh <base_path> $DEVICE1 in another terminal"
qemu-system-arm -M $DEVICE1 -serial file:output.txt -cpu cortex-m4 -nographic -kernel ${STM32L475_PATHS[2]} --device loader,file=${STM32L475_PATHS[3]} -s -S 
wait
echo "Press Enter to continue..."
read

mkdir -p "$DEVICE1_DIR"  
echo "Created directory: $DEVICE1_DIR"
echo "Finished running QEMU on $DEVICE1 with MPU disabled"
cd $DEVICE1_DIR
for i in 0 2 4 6; do
    kernel="${STM32L475_PATHS[$i]}"
    module="${STM32L475_PATHS[$i+1]}"
    output="${OUTPUT_FILES[$i/2]}"

    expect <<EOF
    spawn qemu-system-arm -M $DEVICE1 -serial file:output.txt -cpu cortex-m4 -nographic -kernel $kernel --device loader,file=$module -d int,exec,guest_errors -s -S -D $output
    expect "(qemu)" { send "c\r" } 
    after 300
    send "q\r"
    expect eof
EOF

    echo "Finished running QEMU on $DEVICE1 $output"
    echo "Grep Fault_Handler"
    grep "MemManage_Handler" $output
    echo "Press Enter to continue..."
    read
done


echo "Enter ./run_gdb.sh <base_path> $DEVICE2 in another terminal"
qemu-system-arm -M $DEVICE2 -serial file:output.txt -cpu cortex-m4 -nographic -kernel ${STM32F405_PATHS[2]} --device loader,file=${STM32F405_PATHS[3]} -s -S 
wait
echo "Finished running QEMU on $DEVICE2 with MPU disabled"
echo "Press Enter to continue..."
read

mkdir -p "$DEVICE2_DIR"  
echo "Created directory: $DEVICE2_DIR"
cd $DEVICE2_DIR
for i in 0 2 4 6; do
    kernel="${STM32F405_PATHS[$i]}"
    module="${STM32F405_PATHS[$i+1]}"
    output="${OUTPUT_FILES[$i/2]}"

    expect <<EOF
    spawn qemu-system-arm -M $DEVICE2 -serial file:output.txt -cpu cortex-m4 -nographic -kernel $kernel --device loader,file=$module -d int,exec,guest_errors -s -S -D $output
    expect "*(qemu)*" { send "c\r" } 
    after 300  
    send "q\r"
    expect eof
EOF

    echo "Finished running QEMU on $DEVICE2 $output"
    echo "Grep Fault_Handler"
    grep "Fault_Handler" $output
    echo "Press Enter to continue..."
    read
done


echo "Enter ./run_gdb.sh <base_path> $DEVICE3 in another terminal"
qemu-system-arm -M $DEVICE3 -serial file:output.txt -cpu cortex-m4 -nographic -kernel ${STM32F405_PATHS[2]} --device loader,file=${STM32F405_PATHS[3]} -s -S 
wait
echo "Finished running QEMU on $DEVICE3 with MPU disabled"
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
    expect "*(qemu)*" { send "c\r" }                   
    after 300  
    send "q\r"
    expect eof
EOF

    echo "Finished running QEMU on $DEVICE3 $output"
    echo "Grep Fault_Handler"
    grep "Fault_Handler" $output 
    echo "Press Enter to continue..."
    read
done

cd ..
