# KOM Experiments

This repository contains the data required to reproduce the experiments described in our USENIX 2025 paper: The Cost of Performance: Breaking ThreadX with Kernel Object Masquerading Attacks. 

In this repository, we give the intructions to reproduce the experiments of symbolic exeucution and Proof of Concept(PoC) mentioned in the paper. 

## Requirements

### Hardware Dependencies

* **Processor**: We recommend using a machine with two Intel Xeon E5-2620 v2 CPUs (12 cores, 24 threads) to reproduce the experiment. However, comparable hardware may also suffice.
* **Memory**: At least 64GB of RAM
* **Storage**: At least 256GB.
* **Board**: NUCLEO-U575ZI-Q is used as one of the platform in the PoC experiment (optional).

### Software Dependencies

* **OS**: We used Ubuntu 24.04. Other systems are not tested.
* **Misc**: Git, QEMU and Docker

## Directory Layout

| Directories/Files                                     | Experiment                                                                                                                                        |
| :---------------------------------------------------- | :------------------------------------------------------------------------------------------------------------------------------------------------ |
| [symbolic-execution-engine](./symbolic-execution-engine) | Symbolic execution for ThreadX system calls as described in Section 6.2 (Vulnerable System Call" and "Performance of Symbolic Execution Engine"). |
| [Proof-of-Concept](./Proof-of-Concept)                   | Proof of Concept for KOM attacks as described in Section 6.2 ("Implications of Attacks") and A.2 (Proof of Concept).                              |
| [modification-ThreadX.md](./modification-ThreadX.md)     | The modifications we made to the ThreadX source code.                                                                                             |

## Running the Experiments

Please refer to the `README` files in [symbolic-execution-engine](./symbolic-execution-engine), [Proof-of-Concept](./Proof-of-Concept) for detailed instructions. All experiments should be conducted within the built container (execute `run_docker.sh` to launch a shell). Please note that if you are unable to obtain the image from Docker Hub as described in the README, you can alternatively download the corresponding images from [Zenodo](https://zenodo.org/records/14754680).

<!-- ## (TODO)Badges
<p float="left">
<img src="./assets/usenixbadges-available.svg" width="15%">
<img src="./assets/usenixbadges-functional.svg" width="15%">
<img src="./assets/usenixbadges-reproduced.svg" width="15%">
</p> -->
