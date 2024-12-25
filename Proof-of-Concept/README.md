### Preparation

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

### Reproduce the PoC Experiments on Qemu

We now demonstrate that the KOM attack can be successfully executed on three devices simulated using QEMU. The experiment involving the NUCLEO-U575ZI-Q board is optional for the reproducer, as it requires a physical board. Building upon the KOM attack, we can achieve:

​	•	**MPU Disabling**

​	•	**Arbitrary Memory Read**

​	•	**Arbitrary Memory Write**

To launch the qemu, execute the following command.

```shell
./run_qemu.sh
```

1. **MPU Disabling**

After launching the qemu, open another terminal and start the gdb so that we can inspect the memory operations during the KOM attacks.

```shell
docker exec -it KOM-PoC /bin/bash
./run_gdb.sh
```

We can then see the output, which shows that the MPU control registers (the address is 0xe000ed94) has been modified. This means the MPU is disabled successfully.

```

```

2. **Arbitrary Memory Read**

Move to the terminal of run_qemu.sh and press **Enter**. We will execute the test program twice:

​	•	The first run attempts to read privileged memory from an unprivileged thread **without** the KOM attack.

​	•	The second run performs the same operation, but **with** the KOM attack.

The results can be observed in the output files (i.e., TODO) from both executions. For the first execution, we can find the memmange fault from the TODO. For the second execution, we can see the execution is performed without any exception.

3. **Arbitrary Memory Write**

This PoC can be reproduced as the same as the **Arbitrary Memory Write** by pressing **Enter** in the terminal and verify the two output files.

### Optional Experiment

We demonstrate the PoC on a real board. The reproducer can get the board of NUCLEO-U575ZI-Q board from the link:

We provide a youtube vedio so that the reproducer can reproduce this experiment step by step. This vedio have been shared with Microsoft and they have confirmed this PoC experiment.





