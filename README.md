# KOM Experiments

This directory contains the data required to reproduce the experiments described in our USENIX 2025 paper: The Cost of Performance: Breaking ThreadX with Kernel Object Masquerading Attacks.

For driver source code we used in our experiments, please refer to [this repo](https://github.com/VoodooChild99/perry-drivers).

## Requirements
### Hardware Dependencies
* **Processor**: We recommend using a machine with two Intel Xeon E5-2620 v2 CPUs (12 cores, 24 threads) to reproduce the experiment. However, comparable hardware may also suffice.
* **Memory**: At least 64GB of RAM
* **Storage**: At least 256GB.
* **Board**: NUCLEO-U575ZI-Q is used as one of the platform in the PoC experiment.
### Software Dependencies
* **OS**: We used Ubuntu 24.04. Other systems are not tested.
* **Misc**: git, qemu and Docker

## Preparations
It is assumed that you have built the experiment platform with Docker as described [here](https://github.com/VoodooChild99/perry?tab=readme-ov-file#build-with-docker).
All experiments should be conducted within the built container (execute `run_docker.sh` to launch a shell). 

## Directory Layout
| Directories/Files                                        | Experiment                                                   |
| :------------------------------------------------------- | :----------------------------------------------------------- |
| [symbolic-execution-engine](./symbolic-execution-engine) | Symbolic execution for ThreadX system calls as described in Section 6.2 (Vulnerable System Call" and "Performance of Symbolic Execution Engine"). |
| [Proof-of-Concept](./Proof-of-Concept)                   | Proof of Concept for KOM attacks as described in Section 6.2 ("Implications of Attacks") and A.2 (Proof of Concept). |
| [modification-ThreadX.md](./modification-ThreadX.md)     | The modifications we made to the ThreadX source code.        |

## Running the Experiments
Please refer to the `README` files in [symbolic-execution-engine](./symbolic-execution-engine), [Proof-of-Concept](./Proof-of-Concept) for detailed instructions.

Note that the symbolic execution takes ~10 hours. 

## (TODO)Badges
<p float="left">
<img src="./assets/usenixbadges-available.svg" width="15%">
<img src="./assets/usenixbadges-functional.svg" width="15%">
<img src="./assets/usenixbadges-reproduced.svg" width="15%">
</p>