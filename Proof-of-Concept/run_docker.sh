#!/bin/bash

IMAGE=kom-poc-image:latest
CONTAINER_NAME=KOM-PoC

RUN_FLAGS="
-dit \
--name $CONTAINER_NAME \
"
create_contrainter() {
    docker create -it --name $CONTAINER_NAME $IMAGE
}

run_docker() {
    docker run  $RUN_FLAGS $IMAGE
}

if [[ -n $(docker ps -a --filter name=$CONTAINER_NAME --format "{{.Names}}") ]]; then
    # container exists, check status
    if [[ -n $(docker ps -a --filter name=$CONTAINER_NAME --filter status=running --format "{{.Names}}") ]]; then
        # running, do nothing
        :
    elif [[ -n $(docker ps -a --filter name=$CONTAINER_NAME --filter status=created --format "{{.Names}}") ]]; then
        # created, never running, run it
        docker start $CONTAINER_NAME
    elif [[ -n $(docker ps -a --filter name=$CONTAINER_NAME --filter status=paused --format "{{.Names}}") ]]; then
        # paused, unpause it
        docker unpause $CONTAINER_NAME
    elif [[ -n $(docker ps -a --filter name=$CONTAINER_NAME --filter status=exited --format "{{.Names}}") ]]; then
        # exited, restart
        docker start $CONTAINER_NAME
    elif [[ -n $(docker ps -a --filter name=$CONTAINER_NAME --filter status=dead --format "{{.Names}}") ]]; then
        # dead, remove it then run a new one
        docker rm $CONTAINER_NAME
        run_docker
    elif [[ -n $(docker ps -a --filter name=$CONTAINER_NAME --filter status=restarting --format "{{.Names}}") ]]; then
        echo "[*] The container is restarting, please try later!"
    elif [[ -n $(docker ps -a --filter name=$CONTAINER_NAME --filter status=removing --format "{{.Names}}") ]]; then
        echo "[*] The container is being removed, please try later!"
    fi
else
    run_docker
fi

if [[ -n $(docker ps -a --filter name=$CONTAINER_NAME --format "{{.Names}}") ]]; then
    docker exec -it $CONTAINER_NAME /bin/bash
else
    echo "[x] Failed to run container :("
fi
