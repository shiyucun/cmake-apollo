
# 基于 ubuntu-20.04 构建新镜像
FROM ubuntu:20.04

ARG DEBIAN_FRONTED="noninteractive"

# 时区
ENV TZ=Asia/Shanghai

# UTF-8编码，避免docker内中文显示乱码
ENV LANG C.UTF-8

RUN sed -i s@/ports.ubuntu.com/@/mirrors.aliyun.com/@g /etc/apt/sources.list && \
    apt-get update -y && \
    # 设置时区
    ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone && \
    # 安装 c/c++ 环境
    apt-get install -y gcc g++ cmake && \
    # 安装 glog、gflags、gtest
    apt-get install -y libgoogle-glog* libgflags* libxorg-gtest* python3-gflags && \
    # 安装 opencv
    apt-get install -y libopencv-dev python3-opencv && \
    # 安装 yaml
    apt-get install -y libyaml-cpp-dev && \
    # 安装vim
    apt-get install -y vim && \
    # 删除安装过程中产生的各种非必要文件
    apt clean && \
    rm -rf /tmp/* /var/cache/* /usr/share/doc/* /usr/share/man/* /var/lib/apt/lists/*


LABEL "created"="2022-09-18"
LABEL "authors"="shiyucun"
LABEL "title"="cmake-apollo"
LABEL "description"="ubuntu-20.04 base image for testing"
