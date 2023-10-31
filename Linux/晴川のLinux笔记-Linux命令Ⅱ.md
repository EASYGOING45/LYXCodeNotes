# 晴川のLinux笔记-Linux命令Ⅱ

## 网络（LAN/WiFi）

| 命令                                                         | 说明                                          |
| ------------------------------------------------------------ | --------------------------------------------- |
| # dhclient eth0                                              | 以 dhcp 模式启用 'eth0' 网络设备              |
| # ethtool eth0                                               | 显示网卡 'eth0' 的流量统计                    |
| # host www.example.com                                       | 查找主机名以解析名称与 IP 地址及镜像          |
| # hostname                                                   | 显示主机名                                    |
| # ifconfig eth0                                              | 显示一个以太网卡的配置                        |
| # ifconfig eth0 192.168.1.1 netmask 255.255.255.0            | 控制 IP 地址                                  |
| # ifconfig eth0 promisc                                      | 设置 'eth0' 成混杂模式以嗅探数据包 (sniffing) |
| # ifdown eth0                                                | 禁用一个 'eth0' 网络设备                      |
| # ifup eth0                                                  | 启用一个 'eth0' 网络设备                      |
| # ip link show                                               | 显示所有网络设备的连接状态                    |
| # iwconfig eth1                                              | 显示一个无线网卡的配置                        |
| # iwlist scan                                                | 显示无线网络                                  |
| # mii-tool eth0                                              | 显示 'eth0'的连接状态                         |
| # netstat -tup                                               | 显示所有启用的网络连接和它们的 PID            |
| # netstat -tupl                                              | 显示系统中所有监听的网络服务和它们的 PID      |
| # netstat -rn                                                | 显示路由表，类似于“route -n”命令              |
| # nslookup www.example.com                                   | 查找主机名以解析名称与 IP 地址及镜像          |
| # route -n                                                   | 显示路由表                                    |
| # route add -net 0/0 gw IP_Gateway                           | 控制预设网关                                  |
| # route add -net 192.168.0.0 netmask 255.255.0.0 gw 192.168.1.1 | 控制通向网络 '192.168.0.0/16' 的静态路由      |
| # route del 0/0 gw IP_gateway                                | 删除静态路由                                  |
| # echo "1" > /proc/sys/net/ipv4/ip_forward                   | 激活 IP 转发                                  |
| # tcpdump tcp port 80                                        | 显示所有 HTTP 回环                            |
| # whois www.example.com                                      | 在 Whois 数据库中查找                         |

## route 设置

### 基本使用

添加到主机的路由（就是一个 IP 一个 IP 添加）

```
 route add -host 146.148.149.202 dev eno16777984
 route add -host 146.148.149.202 gw 146.148.149.193
```

添加到网络的路由（批量）

```
route add -net 146.148.149.0 netmask 255.255.255.0 dev eno16777984
route add -net 146.148.149.0 netmask 255.255.255.0 gw 146.148.149.193
```

简洁写法

```
route add -net 146.148.150.0/24 dev eno16777984
route add -net 146.148.150.0/24 gw 146.148.150.193
```

添加默认网关

```
route add default gw 146.148.149.193
```

删除主机路由：

```
route del -host 146.148.149.202 dev eno16777984
```

删除网络路由：

```
 route del -net 146.148.149.0 netmask 255.255.255.0
 route del -net 146.148.150.0/24
```

删除默认路由

```
route del default gw 146.148.149.193
```

### 在 linux 下设置永久路由的方法

服务器启动时自动设置路由，第一想到的可能时 `rc.local`

按照 linux 启动的顺序，rc.local 里面的内容是在 linux 所有服务都启动完毕，最后才被执行的，也就是说，这里面的内容是在 NFS 之后才被执行的，那也就是说在 NFS 启动的时候，服务器上的静态路由是没有被添加的，所以 NFS 挂载不能成功。

/etc/sysconfig/static-routes

```
any net 192.168.3.0/24 gw 192.168.3.254
any net 10.250.228.128 netmask 255.255.255.192 gw 10.250.228.129
```

使用 static-routes 的方法是最好的。无论重启系统和 service network restart 都会生效

static-routes 文件又是什么呢，这个是 network 脚本 (/etc/init.d/network) 调用的，大致的程序如下

```
if [ -f /etc/sysconfig/static-routes  ]; then
    grep "^any" /etc/sysconfig/static-routes | while read ignore args ; do
        /sbin/route add -$args
    done
fi
```

从这段脚本可以看到，这个就是添加静态路由的方法，static-routes 的写法是

any net 192.168.0.0/16 gw 网关 ip

### Microsoft windows 网络 (samba)

| 命令                                                         | 说明                                                   |
| ------------------------------------------------------------ | ------------------------------------------------------ |
| # mount -t smbfs -o username=user,password=pass //WinClient/share /mnt/share | 挂载一个 windows 网络共享                              |
| # nbtscan ip_addr                                            | netbios 名解析                                         |
| # nmblookup -A ip_addr                                       | netbios 名解析                                         |
| # smbclient -L ip_addr/hostname                              | 显示一台 windows 主机的远程共享                        |
| # smbget -Rr smb://ip_addr/share                             | 像 wget 一样能够通过 smb 从一台 windows 主机上下载文件 |

### IPTABLES (firewall)

| 命令                                                         | 说明                                               |
| ------------------------------------------------------------ | -------------------------------------------------- |
| # iptables -t filter -L                                      | 显示过滤表的所有链路                               |
| # iptables -t nat -L                                         | 显示 nat 表的所有链路                              |
| # iptables -t filter -F                                      | 以过滤表为依据清理所有规则                         |
| # iptables -t nat -F                                         | 以 nat 表为依据清理所有规则                        |
| # iptables -t filter -X                                      | 删除所有由用户创建的链路                           |
| # iptables -t filter -A INPUT -p tcp --dport telnet -j ACCEPT | 允许 telnet 接入                                   |
| # iptables -t filter -A OUTPUT -p tcp --dport http -j DROP   | 阻止 HTTP 连出                                     |
| # iptables -t filter -A FORWARD -p tcp --dport pop3 -j ACCEPT | 允许转发链路上的 POP3 连接                         |
| # iptables -t filter -A INPUT -j LOG --log-prefix            | 记录所有链路中被查封的包                           |
| # iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE       | 设置一个 PAT \（端口地址转换、) 在 eth0 掩盖发出包 |
| # iptables -t nat -A PREROUTING -d 192.168.0.1 -p tcp -m tcp --dport 22 -j DNAT --to-destination 10.0.0.2:22 | 将发往一个主机地址的包转向到其他主机               |