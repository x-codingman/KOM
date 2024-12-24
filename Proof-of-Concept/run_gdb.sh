#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <path> <device_name>"
    exit 1
fi

which expect || echo "expect not found"

PATH_PREFIX=$1
DEVICE=$2

FILE_PATHS=(
    "$PATH_PREFIX/qemu_stm32l475_m4_read_after_exploit/qemu_stm32l475_m4_read_after_exploit/STM32CubeIDE/Tx_Module_Manager_Debug/qemu_stm32l475_m4_read_after_exploit.elf"
    "$PATH_PREFIX/qemu_stm32f405_m4_read_after_exploit/qemu_stm32f405_m4_read_after_exploit/STM32CubeIDE/Tx_ModuleManager/Debug/Tx_ModuleManager.elf"
)

DEVICE1=b-l475e-iot01a
DEVICE2=netduinoplus2
DEVICE3=olimex-stm32-h405

DEVICE1_DIR=$(pwd)/$DEVICE1
DEVICE2_DIR=$(pwd)/$DEVICE2
DEVICE3_DIR=$(pwd)/$DEVICE3

case "$DEVICE" in
    "b-l475e-iot01a")
    FILE_PATH=${FILE_PATHS[0]}
    ;;
    "netduinoplus2"|"olimex-stm32-h405")
    FILE_PATH=${FILE_PATHS[1]}
    ;;
    *)
    echo "Error: Invalid device name. Valid names are 'b-l475e-iot01a', 'netduinoplus2', and 'olimex-stm32-h405'."
    exit 1
    ;;
esac
    
    expect <<EOF
    spawn gdb-multiarch $FILE_PATH
    expect "(gdb)" { send "set architecture arm\r"}
    after 100
    expect "(gdb)" { send "target remote localhost:1234\r"}
    after 100
    expect "(gdb)" { send "break _tx_queue_send\r"}
    after 100
    expect "(gdb)" { send "continue\r"}
    after 100
    expect "(gdb)" { send "watch *0xe000ed94\r"}
    after 100
    expect "(gdb)" { send "continue\r"}
    sleep 1
    expect "(gdb)" { send "kill\r"}
    expect "(y or n)" { send "y\r"}
    expect "(gdb)" { send "quit\r"}
    expect eof
EOF
echo "Finished running QEMU on $DEVICE with MPU disabled"

