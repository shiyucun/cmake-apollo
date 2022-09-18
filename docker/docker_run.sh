#! /usr/bin/env bash

docker stop cmake-apollo

docker rm cmake-apollo

docker run -it -d -v /Users/shiyucun/workspace/github_repos/repos/cmake-apollo:/cmake-apollo --hostname=$(hostname)-apollo --name cmake-apollo cmake-apollo:v1.0
