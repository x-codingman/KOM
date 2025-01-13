We provide the source code for the symbolic execution engine. It is recommended to build the engine using Docker for easier setup and environment management. Please note that the Docker container will consume approximately 30GB of memory to store the experiment results.

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
In case you cannot build a image, we provide a [pre-built docker image on Docker Hub](TODO) Execute the following command to use it:

```
docker rmi perry:latest
docker pull ray999/perry
docker tag ray999/perry perry:latest
cd perry
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

#### Perform Symbolic Execution
To run symbolic execution for ThreadX system calls, navigate to the **symbolic-execution-experiment** folder and execute the Python script. Most system calls will complete normally within 5 minutes, except for mutex_delete and mutex_put. Note that these two system calls may take up to 9 hours to finish, depending on the host machine’s performance.

```
cd ~/klee_src/symbolic-execution-experiment/scripts
python3 run_test_system_calls.py
```

The symbolic execution results will be stored in the *results/output* and *results/test-info-output* folders. 

#### Result Evaluation
To further evaluate the runtime overhead and analyze the modifiable fields, run the following:

```
python3 run_analysis.py
```

This command will generate four Excel files in the results folder, containing runtime evaluation data (E1) and information on the modifiable fields (M1, M2, and M3), as shown in Tables 2 and 3 in our paper (E2). The files will be named as follows:
```
M1_vulnerable_system_calls.xlsx
M2_vulnerable_system_calls.xlsx
M3_vlnerable_system_calls.xlsx
symbolic-execution-run-time-evaluation.xlsx
```