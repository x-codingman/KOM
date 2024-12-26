## Preparation

We provide the experimental material for the Proof of Concept experiments. It is recommended to build the engine using Docker for easier setup and environment management. 

```
docker build -t poc-image .
```

This will build a docker image `"my-poc-image"` which contains all the necessary materials to reproduce our experiments.

To launch the container:

```
./run_docker.sh
```

In case you cannot build a image, we provide a [pre-built docker image on Docker Hub](TODO) Execute the following command to use it:

```
TODO
```

We check if the qemu is installed correctly.

```
qemu-system-arm --version
```

## Reproduce the PoC Experiments on Qemu

We now demonstrate that the KOM attack can be successfully executed on three devices simulated using QEMU. The experiment involving the NUCLEO-U575ZI-Q board is optional for the reproducer, as it requires a physical board. Building upon the KOM attack, we can achieve:

​	•	**MPU Disabling**

​	•	**Arbitrary Memory Read**

​	•	**Arbitrary Memory Write**

In this experiment, we will demonstrate the effectiveness of the attack on three devices: **b-l475e-iot01a**, **netduinoplus2**, and **olimex-stm32-h405**, all simulated using QEMU. For each device, you can follow the instructions below to reproduce the experiments. As an example, we will use the **b-l475e-iot01a** device to illustrate the step-by-step process of reproducing the PoC experiment.

To start the QEMU simulation, execute the following command:

```shell
./run_qemu.sh
```

1. **MPU Disabling**

Once QEMU is running, open a second terminal and start GDB to inspect the memory operations during the KOM attacks. This will allow us to observe the changes in memory control registers.

```shell
docker exec -it KOM-PoC /bin/bash
./run_gdb.sh /workspace/threadx_exploitation b-l475e-iot01a
```

After running the above commands, you should observe the output showing that the MPU control register (at address `0xe000ed94`) has been modified. We print the value of the register before and after launching the KOM attack. Specifically, the value of the control register changes from `5` to `0`, indicating that the MPU has been successfully disabled.

```
(gdb) watch *0xe000ed94
Hardware watchpoint 2: *0xe000ed94
(gdb) continue
Continuing.

Hardware watchpoint 2: *0xe000ed94

Old value = 5
New value = 0 (SHAO: How to establish a connection between reading a control register and the use of watchpoints in GDB?)
```

2. **Arbitrary Memory Read**

In the terminal running `run_qemu.sh`, press **Enter** to initiate the test program. The program will be executed twice:

- The first run attempts to read privileged memory from an unprivileged thread **without** the KOM attack.
- The second run performs the same operation, but **with** the KOM attack.

The results of these runs can be found in the output files (`read_before_kom.txt` and `read_after_kom.txt`) generated from both executions.

- In the first execution, you should observe the `_txm_module_manager_memory_fault_handler` in `read_before_kom.txt` or `write_before_kom.txt`.
- In the second execution, no exception should occur, demonstrating that the operation was successfully executed without any faults in`read_after_kom.txt` and `write_after_kom.txt`.

3. **Arbitrary Memory Write**

This Proof of Concept (PoC) can be reproduced in the same manner as the **Arbitrary Memory Read** experiment. Simply press **Enter** in the terminal and verify the two output files to confirm the results.

### Optional Experiment

To further demonstrate the PoC, we conduct the experiment on a real board. Reproducers can obtain the **NUCLEO-U575ZI-Q** board from [this Amazon link](https://www.amazon.in/Robotism-NUCLEO-U575ZI-Q-Development-board/dp/B0BD1LTSSD).

Additionally, a [YouTube video](https://youtu.be/dr2qib8wsiA) is provided to guide reproducing the experiment step by step. This video has been shared with Microsoft, and they have confirmed the validity of this PoC experiment.





