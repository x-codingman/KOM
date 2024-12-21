#### Get ready

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

#### Reproduce the PoC on Qemu

```
qemu-system-arm -M b-l475e-iot01a -cpu cortex-m4 -nographic -kernel Tx_ModuleManager.elf --device loader,file=TX_Module_MemManage_Fault.elf -d int,exec,guest_errors -s -S 2> output.txt
c // continue
q // quit
```

