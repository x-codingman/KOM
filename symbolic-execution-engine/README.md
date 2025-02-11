We provide the source code for the symbolic execution engine. It is recommended to build the engine using Docker for easier setup and environment management. Please note that the Docker container will consume approximately 30GB of memory to store the experiment results.

## Preparation

#### Building With Docker

```
docker build -t klee/klee .
```

This will build a docker image `"klee"` which contains all the necessary materials to reproduce our experiments.

To launch the container:

```
./run_docker.sh
```

#### Using the Pre-Built Docker Image

In case you cannot build a image, we provide a [pre-built docker image on Docker Hub](https://hub.docker.com/repository/docker/xcodingman/klee/general). Execute the following command to use it:

```
docker rmi xcodingman/klee
docker pull xcodingman/klee:latest
docker tag xcodingman/klee:latest klee/klee:latest
./run_docker.sh
```

To build KLEE, run the following commands:

```
cd /home/klee/klee_src
sudo apt-get update
sudo apt-get install google-perftools libgoogle-perftools-dev
mkdir build
cmake \
  -DCMAKE_CXX_FLAGS_DEBUG="-g" \
  -DCMAKE_C_FLAGS_DEBUG="-g" \
  -DCMAKE_CXX_FLAGS_RELEASE="-O3 -DNDEBUG" \
  -DCMAKE_C_FLAGS_RELEASE="-O3 -DNDEBUG" \
  -DCMAKE_CXX_FLAGS_RELWITHDEBINFO="-O2 -g -DNDEBUG" \
  -DCMAKE_C_FLAGS_RELWITHDEBINFO="-O2 -g -DNDEBUG" \
  -DENABLE_SOLVER_STP=ON \
  -DENABLE_POSIX_RUNTIME=ON \
  -DSTP_DIR=/tmp/stp-2.3.3-install/lib/cmake/STP/ \
  ..
make -j
```

## Execution

To run symbolic execution for ThreadX system calls, navigate to the **symbolic-execution-experiment** folder and execute the Python script. Most system calls will complete normally within 5 minutes, except for mutex_delete and mutex_put. Note that these two system calls may take up to 9 hours to finish, depending on the host machine’s performance.

```
cd ~/klee_src/symbolic-execution-experiment/scripts
python3 run_test_system_calls.py
```

The symbolic execution results will be stored in the *results/output* and *results/test-info-output* folders.

## Conduct Evaluation

#### (E1)Vulnerable System Call Detection

To identify the vulnerable system calls, run the following:

```
python3 modifiable_fields_analysis.py
```

This command will analyze the results of symbolic execution and generate three Excel files in the [symbolic-execution-experiment/result](https://github.com/x-codingman/KOM-experiments/tree/main/symbolic-execution-engine/symbolic-execution-experiment/results) folder, containing the information on the modifiable fields (M1, M2, and M3), as shown in Tables 2 and 3 in our paper. The files will be named as follows:

```
M1_vulnerable_system_calls.xlsx
M2_vulnerable_system_calls.xlsx
M3_vulnerable_system_calls.xlsx
```

#### (E2) Efficiency

To evaluate the efficiency of the symbolic execution, run the following:

python3 run-time-evaluation.py

This command will analyze the efficiency of symbolic execution and generate an Excel file in the [symbolic-execution-experiment/result](https://github.com/x-codingman/KOM-experiments/tree/main/symbolic-execution-engine/symbolic-execution-experiment/results) folder, containing the information of the runtime overhead of the symbolic execution process. This file will be named as follows:

```
symbolic-execution-run-time-evaluation.xlsx
```
