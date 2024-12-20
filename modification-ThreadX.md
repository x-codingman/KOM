**Code Modifications on ThreadX**

​	•	**System Call Name Change**:

We modified the system call names in the common_modules/module_lib/src directory to facilitate compilation. Specifically, we added a prefix m_ to the original system call wrapper names. This change is necessary because **ThreadX** uses the same system call names in both the user interface and kernel directories but compiles them separately. For example, the system call txe_block_pool_create was changed to m_txe_block_pool_create to ensure consistency and avoid conflicts during the compilation process.

​	•	**Interrupt Disable/Enable Macros**:

We commented out the macros related to interrupt disable and interrupt enable. These macros are typically used to prevent concurrency issues but are not required for the system call execution in our case. By commenting them out, we eliminate unnecessary interrupt handling, ensuring that system calls execute as expected without affecting functionality.

​	•	**Parameter Checking Intrinsic Functions**:

We rewrote the parameter-checking intrinsic functions to bypass hardware dependencies, specifically the **Memory Protection Unit (MPU)**. This modification ensures that the system call can be executed correctly from the system call wrapper, independent of the hardware configuration.