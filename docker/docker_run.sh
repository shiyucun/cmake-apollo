docker stop cmake-apollo
docker rm cmake-apollo
docker run -it -d -v /Users/shiyucun/workspace/github_repos/repos/cmake-apollo:/cmake-apollo --hostname=$(hostname)-docker --name cmake-apollo eb574ad4e57c

docker start cmake-apollo
echo "$(tput setaf 3)"yellow text"$(tput sgr0)"

sed -i s@/archive.ubuntu.com/@/mirrors.aliyun.com/@g /etc/apt/sources.list
sed -i s@/security.ubuntu.com/@/mirrors.aliyun.com/@g /etc/apt/sources.list
apt clean
apt-get update -y
apt-get install gcc g++ cmake git vim libopencv-dev python3-opencv libgoogle-glog* libgflags* python3-gflags  libxorg-gtest* libyaml-cpp-dev
