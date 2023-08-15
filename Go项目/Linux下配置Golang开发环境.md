# Linux下配置Golang开发环境

## 配置安装Golang语言环境

1. 切换至目录 `/usr/local`下

   `cd /usr/local/`

2. 使用wget下载golang1.19包

   `wget https://studygolang.com/dl/golang/go1.19.linux-amd64.tar.gz`

3. 解压安装

   `tar -zxvf go1.19.linux-amd64.tar.gz`

4. 查看版本

   `go verison`

   ![image-20230815110616723](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230815110616723.png)

从 `Go 1.11` 版本开始，Go 提供了 [Go Modules](https://github.com/golang/go/wiki/Modules) 的机制，推荐设置以下环境变量，第三方包的下载将通过国内镜像，避免出现官方网址被屏蔽的问题。

```shell
go env -w GOPROXY=https://goproxy.cn,direct
```

或在 `~/.profile` 中设置环境变量

```shell
export GOPROXY=https://goproxy.cn
```

## 配置VSCODE中的Go工具

VSCODE会自动弹出提示框，询问是否要安装Go相关的插件工具，点击 `Install All`后，可能会无法安装，按照以下步骤修改即可正常安装使用

键入以下命令后，重新打开窗口，再次`Install All`即可成功

```shell
[root@VM-24-4-centos GoingCache]# go env -w GO111MODULE=on
[root@VM-24-4-centos GoingCache]# go env -w GOPROXY=https://goproxy.cn,direct
[root@VM-24-4-centos GoingCache]# go env
```

![image-20230815110825713](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230815110825713.png)

![image-20230815110734648](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230815110734648.png)