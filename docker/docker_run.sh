docker stop JustFollow
# docker rm JustFollow
# docker run -it -d -v /Users/shiyucun/workspace/github_repos/repos/data_flow:/JustFollow --hostname=$(hostname)-docker --name JustFollow eb574ad4e57c

docker start JustFollow
echo "$(tput setaf 3)"yellow text"$(tput sgr0)"

# sed -i s@/archive.ubuntu.com/@/mirrors.aliyun.com/@g /etc/apt/sources.list
# sed -i s@/security.ubuntu.com/@/mirrors.aliyun.com/@g /etc/apt/sources.list
# apt clean
# apt-get update -y
# apt-get install gcc g++ cmake git vim libopencv-dev python3-opencv libgoogle-glog* libgflags* python3-gflags  libxorg-gtest* libyaml-cpp-dev
