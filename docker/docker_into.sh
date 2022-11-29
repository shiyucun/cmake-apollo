#! /usr/bin/env bash

DOCKER_EXEC=$(which docker)
if [[ $? && -z "${DOCKER_EXEC}" ]]; then
  echo "docker not found"
  exit 1
fi

DOCKER_PS=$(docker ps)
if [[ $? ]]; then
  if [[ ! "${DOCKER_PS}" =~ "cmake-apollo" ]]; then
    echo "please run docker first"
    exit 1
  fi
fi

docker exec -it cmake-apollo /bin/bash
