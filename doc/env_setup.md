# 安装依赖
使用apt安装qemu模拟器和aarch64工具链。

在ubuntu系统下，可以使用apt安装本实验需要的所有依赖。

本次实验需要使用Aarch64(arm64)工具链对我们编译器得到的汇编文件进行汇编和链接，生成可执行文件。然后，我们将使用qemu模拟器提供的arm64环境运行程序。

## 安装方式1：使用apt安装
对于使用linux系统的同学，建议使用系统的包管理工具安装实验相关工具，以Ubuntu系统下的apt工具为例，安装指令为：
```
sudo apt install qemu qemu-system qemu-user
sudo apt install gcc-aarch64-linux-gnu
```

## 安装方式2：从源码编译
对于使用Mac系统的同学，或无法从包管理工具直接安装的同学，请从elearning下载提供的安装包，并进行编译安装。

```shell
$ cd ~
$ tar xf arm-gnu-toolchain-13.2.rel1-x86_64-aarch64-none-linux-gnu.tar.xz
$ echo "export PATH=~/arm-gnu-toolchain-13.2.rel1-x86_64-aarch64-none-linux-gnu/bin:\$PATH" >> ~/.bashrc # or ~/.zshrc
```

qemu模拟器用于执行交叉编译出的arm机器码，同交叉编译器配套在后面的实验中使用。

从 elearning 上下载压缩包`qemu-6.2.0.tar.xz`，然后在 linux 环境里执行：

```shell
$ sudo apt install ninja-build
$ cd ~
$ tar xf qemu-6.2.0.tar.xz
$ cd qemu-6.2.0
$ mkdir build
$ cd build
$ ../configure
$ make -j4
$ sudo make install
```

## 验证安装
安装完毕后，运行
```
aarch64-linux-gnu-gcc --version
qemu-aarch64 -version
```
检查工具链和qemu安装状态，返回版本信息即说明安装成功。

# 汇编和链接

实验准备

```shell
$ aarch64-linux-gnu-gcc -c sylib.c -o ./sylib/sylib.o # 编译出sylib.o
```
之后make即可
