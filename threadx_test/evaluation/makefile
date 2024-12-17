CC                    := clang

BUILD_DIR             := ./build
BUILD_EXTRA_DIR       := ./build_extra
BUILD_COMMON_MODULES_LIB_DIR := $(BUILD_DIR)/common_modules_lib


KERNEL_DIR            := /home/klee/threadx/threadx/

evaluation_files_DIR            := /home/klee/klee_test/threadx_test/evaluation/evaluation_files

COMMON_DIR                     := /home/klee/threadx/threadx/common
COMMON_MODULES_LIB_DIR         := /home/klee/threadx/threadx/common_modules/module_lib
COMMON_MODULES_MANAGER_DIR     := /home/klee/threadx/threadx/common_modules/module_manager

#TARGET_DIR            := /home/klee/FreeRTOS-kernel-revision/portable/GCC/ARM_CM33_NTZ/non_secure


KLEE_INCLUDE_DIR      := /home/klee/klee_test/include/


INCLUDE_DIRS          := -I.
# INCLUDE_DIRS          += -I/usr/lib/gcc/arm-none-eabi/6.3.1/include
# INCLUDE_DIRS          += -I/usr/lib/gcc/arm-none-eabi/6.3.1/include-fixed
#INCLUDE_DIRS          += -I/home/klee/threadx/threadx/ports_module/cortex_m33/gnu/inc
#INCLUDE_DIRS          += -I/home/klee/threadx/threadx/ports/cortex_m33/gnu/inc
INCLUDE_DIRS          += -I${KLEE_INCLUDE_DIR}
INCLUDE_COMMON_DIRS          += -I/home/klee/threadx/threadx/common/inc
INCLUDE_DIRS  += -I/home/klee/klee_test/threadx_test/evaluation/klee_help.h
INCLUDE_COMMON_MODULES_LIB_DIRS  += -I/home/klee/threadx/threadx/common_modules/inc

INCLUDE_DIRS  += -I/home/klee/threadx/threadx/ports_module/cortex_m33/gnu/inc
INCLUDE_COMMON_MODULES_MANAGER_DIRS  += -I/home/klee/threadx/threadx/common_modules/module_manager/inc
#INCLUDE_DIRS          += -I/home/klee/threadx/threadx/common_modules/inc

#INCLUDE_DIRS          += -I/home/klee/threadx/threadx/ports_module/cortex_m33/gnu/module_manager/inc

#SOURCE_FILES          := $(wildcard *.c)
SOURCE_COMMON_MODULES_LIB_FILES   := $(wildcard /home/klee/threadx/threadx/common_modules/module_lib/src/*.c)
SOURCE_COMMON_MODULES_MANAGER_FILES   := $(wildcard /home/klee/threadx/threadx/common_modules/module_manager/src/*.c)
SOURCE_COMMON_FILES           := $(wildcard /home/klee/threadx/threadx/common/src/*.c)
#NEW_SOURCE_COMMON_FILES := $(foreach file,$(SOURCE_COMMON_FILES),$(shell echo $(notdir $(file)) | sed 's/^[^_]*_//'))
#SOURCE_FILES           := $(wildcard /home/klee/threadx/threadx/common/src/*.c)
#SOURCE_FILES          += $(wildcard /home/klee/threadx/threadx/common/src/tx_thread_initialize.c)
#SOURCE_FILES          += $(wildcard /home/klee/threadx/threadx/ports_module/cortex_m33/gnu/module_lib/src/*.c)


SOURCE_evaluation_files      := $(wildcard /home/klee/klee_test/threadx_test/evaluation/evaluation_files/*.c)




BC_FILES              := $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.bc)
COMMON_BC_FILES       := $(SOURCE_COMMON_FILES:%.c=$(BUILD_DIR)/common/%.bc)
COMMON_MODULES_LIB_BC_FILES   := $(SOURCE_COMMON_MODULES_LIB_FILES:%.c=$(BUILD_DIR)/common_modules_lib/%.bc)
COMMON_MODULES_LIB_BC_LINKED_FILES := $(SOURCE_COMMON_MODULES_LIB_FILES:%.c=$(BUILD_DIR)/common_modules_lib/%.linked.bc)
COMMON_MODULES_MANAGER_BC_FILES := $(SOURCE_COMMON_MODULES_MANAGER_FILES:%.c=$(BUILD_DIR)/common_modules_manage/%.bc)
COMMON_MODULES_MANAGER_BC_LINKED_FILES := $(SOURCE_COMMON_MODULES_MANAGER_FILES:%.c=$(BUILD_DIR)/common_modules_manage/%.linked.bc)
TEST_BC_LINKED_FILES_DIR := $(BUILD_DIR)/evaluation_files/
TEST_BC_FILES         := $(SOURCE_evaluation_files:%.c=$(BUILD_DIR)/evaluation_files/%.bc)
TEST_BC_LINKED_FILES  := $(SOURCE_evaluation_files:%.c=$(BUILD_DIR)/evaluation_files/%.linked.bc)




CFLAGS                := -fno-asm -emit-llvm -c -g 



all: $(TEST_BC_FILES) rename_files $(COMMON_MODULES_LIB_BC_LINKED_FILES) $(COMMON_MODULES_MANAGER_BC_FILES) $(COMMON_MODULES_MANAGER_BC_LINKED_FILES)   $(COMMON_MODULES_LIB_BC_FILES) 

$(COMMON_MODULES_LIB_BC_LINKED_FILES): $(COMMON_MODULES_MANAGER_BC_LINKED_FILES) $(COMMON_MODULES_LIB_BC_FILES) 
$(COMMON_MODULES_MANAGER_BC_LINKED_FILES): $(COMMON_MODULES_MANAGER_BC_FILES)

rename_files : $(COMMON_MODULES_LIB_BC_LINKED_FILES)

target: $(TEST_BC_LINKED_FILES)
$(BUILD_DIR)/common_modules_manage/%.bc : %.c
	-mkdir -p $(@D)
	$(CC) $(INCLUDE_COMMON_MODULES_MANAGER_DIRS) $(INCLUDE_COMMON_MODULES_LIB_DIRS) $(INCLUDE_COMMON_MODULES_DIRS) $(INCLUDE_DIRS) $(INCLUDE_COMMON_DIRS) $(CFLAGS) $< -o $@

$(BUILD_DIR)/common/%.bc : %.c
	-mkdir -p $(@D)
	$(CC) $(INCLUDE_COMMON_DIRS) $(INCLUDE_DIRS) $(CFLAGS) $< -o $@

$(BUILD_DIR)/common/common_lib.bc : $(COMMON_BC_FILES)
	-mkdir -p ${@D}
	llvm-link $^ -o $@

$(BUILD_DIR)/common_modules_manage/common_modules_manage_lib.linked.bc : $(COMMON_MODULES_MANAGER_BC_FILES) $(BUILD_DIR)/common/common_lib.bc
	-mkdir -p ${@D}
	llvm-link $^  -o $@

$(BUILD_DIR)/common_modules_lib/%.bc : %.c
	-mkdir -p $(@D)
	$(CC) $(INCLUDE_COMMON_MODULES_LIB_DIRS) $(INCLUDE_COMMON_DIRS) $(INCLUDE_DIRS) $(CFLAGS) $< -o $@


$(BUILD_DIR)/common_modules_lib/%.linked.bc: $(BUILD_DIR)/common_modules_lib/%.bc $(BUILD_DIR)/common_modules_manage/common_modules_manage_lib.linked.bc 
	-mkdir -p ${@D}
	llvm-link $< $(BUILD_DIR)/common_modules_manage/common_modules_manage_lib.linked.bc -o $@

$(BUILD_DIR)/evaluation_files/%.bc : %.c
	-mkdir -p $(@D)
	$(CC) $(INCLUDE_COMMON_MODULES_LIB_DIRS) $(INCLUDE_DIRS) $(INCLUDE_COMMON_DIRS) $(CFLAGS) $< -o $@

# $(BUILD_DIR)/evaluation_files/%.linked.bc : %.bc /home/klee/threadx/symbolic_execution/build/common_modules_lib/home/klee/threadx/threadx/common_modules/module_lib/src/txm_block_allocate.linked.bc
# 	-mkdir -p ${@D}
# 	llvm-link $^ -o $@

rename_files: $(COMMON_MODULES_LIB_BC_LINKED_FILES)
	@for file in $(COMMON_MODULES_LIB_BC_LINKED_FILES); do \
        dir_name=$$(dirname $$file); \
        base_name=$$(basename $$file); \
        new_name=$$(echo $$base_name | sed 's/^[^_]*_//'); \
        mv $$file $$dir_name/$$new_name; \
    done


$(BUILD_DIR)/evaluation_files//home/klee/klee_test/threadx_test/evaluation/evaluation_files/%.linked.bc : $(BUILD_DIR)/evaluation_files/home/klee/klee_test/threadx_test/evaluation/evaluation_files/%.bc $(BUILD_DIR)/common_modules_lib//home/klee/threadx/threadx/common_modules/module_lib/src/%.linked.bc  #文件路径不一致
	-mkdir -p ${@D}
	llvm-link $^ -o $@


# $(BUILD_DIR) : %.c 
# 	-mkdir -p $(@D)
# 	$(CC) $(INCLUDE_DIRS) $(CFLAGS) $< -o $@

# $(COMMON_MODULE_LIB_BC_FILES) : $(COMMON_MODULES_FILES)
# 	-mkdir -p $(@D)
# 	$(CC) $(INCLUDE_MODULES_DIRS)  $(CFLAGS) $< -o $@

# $(COMMON_MODULE_LIB_BC_LINKED_FILES) : $(COMMON_MODULE_LIB_BC_FILES)
# 	llvm-link $^ -o $@

# %.bc : %.c 
# 	-mkdir -p $(@D)
# 	$(CC) $(INCLUDE_DIRS) $(CFLAGS) $< -o $@

# %.test.bc : $(BC_FILES) %.bc
# 	-mkdir -p ${@D}
# 	llvm-link $^ -o $@


clean_bc:
	rm -rf $(TEST_BC_FILES)

clean:
	rm -rf $(BUILD_DIR)   