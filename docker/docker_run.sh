#! /usr/bin/env bash

DOCKER_EXEC=$(which docker)
if [[ $? && -z "${DOCKER_EXEC}" ]]; then
  echo "docker not found"
  exit 1
fi

IMAGES=$(docker images)
if [[ $? ]]; then
  if [[ ! "${IMAGES}" =~ "cmake-apollo" ]]; then
    echo "no cmake-apollo image found"
    exit 1
  fi
fi

DOCKER_PS=$(docker ps)
if [[ $? ]]; then
  if [[ "${DOCKER_PS}" =~ "cmake-apollo" ]]; then
    docker stop cmake-apollo
  fi
fi

DOCKER_PS=$(docker ps -a)
if [[ $? ]]; then
  if [[ "${DOCKER_PS}" =~ "cmake-apollo" ]]; then
    docker rm cmake-apollo
  fi
fi

SCRIPTS_DIR=$(cd $(dirname $0); pwd)

docker run -it -d \
  -v "${SCRIPTS_DIR}/..:/cmake-apollo" \
  --hostname="$(whoami)-cmake-apollo" \
  --name cmake-apollo \
  cmake-apollo:v1.0
