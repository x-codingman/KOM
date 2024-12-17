## How to run symbolic execution on zephyr os
### Challenges
* build system, we customize the build system to only focus on the zephyr os API.
* under-constraint parameters check, e.g., we need initialize the necessary kernel objects before the checking.

### Solutions




## zephyr-os modification

* mark MACRO LOG_ERR as empty at $(ZEPHYR_DIR)/zephyr/include/zephyr/logging/log.h:line 42
* modify the Z_OOPS() at /home/klee/zephyr-os/zephyr/include/zephyr/syscall_handler.h:line 291
