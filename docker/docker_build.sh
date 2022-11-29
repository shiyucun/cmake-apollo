#! /usr/bin/env bash

DIR=$(cd $(dirname $0); pwd)

DOCKERFILE=${DIR}/cmake-apollo.dockerfile

docker build -f ${DOCKERFILE} -t cmake-apollo:v1.0 ${DIR}
