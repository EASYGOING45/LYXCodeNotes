# CTENETのDocker学习笔记Ⅰ

## 什么是Docker

[Docker](https://www.docker.com/) 是一个开源的应用容器引擎，而一个容器containers其实是一个虚拟化的独立的环境，让开发者可以打包他们的应用以及依赖包到一个可移植的容器中，然后发布到任何流行的 Linux 机器上，也可以实现虚拟化。容器是完全使用沙箱机制，相互之间不会有任何接口。

> Docker 的局限性之一，它只能用在 64 位的操作系统上。

Docker 从 `1.13` 版本之后采用时间线的方式作为版本号，分为社区版 `CE` 和企业版 `EE`，社区版是免费提供给个人开发者和小型团体使用的，企业版会提供额外的收费服务，比如经过官方测试认证过的基础设施、容器、插件等。

社区版按照 `stable` 和 `edge` 两种方式发布，每个季度更新 `stable` 版本，如 `17.06`，`17.09`；每个月份更新 `edge` 版本，如`17.09`，`17.10`。

该笔记基于CentOS系统撰写。

## Docker新版本安装与测试

Docker 官方的安装教程，[在这里](https://docs.docker.com/install/linux/docker-ce/centos/)。

我安装在了我的腾讯云服务器中：

### 设置存储库

安装`yum-utils`软件包（提供`yum-config-manager` 实用程序）并设置存储库。

```console
$ sudo yum install -y yum-utils
$ sudo yum-config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo
```

安装Docker引擎、containerd和Docker Compose

```shell
sudo yum install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```

如果提示接受 GPG 密钥，请验证指纹是否匹配 `060A 61C5 1B55 8A7F 742B 77AA C52F EB6B 621E 9F35`，如果匹配，则接受。

此命令会安装 Docker，但不会启动 Docker。它还创建一个 `docker`组，但是默认情况下不会将任何用户添加到该组。

```
yum-config-manager --add-repo http://mirrors.aliyun.com/docker-ce/linux/centos/docker-ce.repo
```

![image-20231017182037326](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20231017182037326.png)

![image-20231017182206247](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20231017182206247.png)

### 启动Docker

```
sudo systemctl start docker
```

通过运行镜像来验证Docker Engine安装是否成功 `hello-world`。

```shell
sudo docker run hello-world
```

此命令下载测试映像并在容器中运行它。当容器运行时，它会打印一条确认消息并退出。

您现在已经成功安装并启动了 Docker Engine。

![image-20231017183141978](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20231017183141978.png)

### Unable to find image 'hello-world:latest' locally的问题

我在[CentOS7](https://so.csdn.net/so/search?q=CentOS7&spm=1001.2101.3001.7020)中安装了docker之后，然后运行docker run hello-world，拉取docker的hello-world测试镜像，结果在终端中提示：Unable to find image 'hello-world:latest' locally！

意思是docker在本地没有找到hello-world镜像，也没有从docker仓库中拉取到镜像。

这是因为docker服务器在国外，基于网速与“和谐墙”的问题，所以我们在国内操作国外镜像可能无法正常拉取，这需要我们为docker设置国内的阿里云镜像加速器。

#### 创建文件daemon.json文件

```
#touch  /etc/docker/daemon.json
```

#### 配置文件/etc/docker/daemon.json,添加阿里云镜像

```
{ 
"registry-mirrors": ["https://alzgoonw.mirror.aliyuncs.com"] 
}
```

#### 重启docker服务

```
#systemctl restart docker
#sudo systemctl status docker
```

此时我们再重新拉取hello-world镜像，就可以成功了。