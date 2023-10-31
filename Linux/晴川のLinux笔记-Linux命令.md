# 晴川のLinux笔记-Linux命令

## 系统命令

### 系统信息

| 命令                   | 说明                              |
| ---------------------- | --------------------------------- |
| # arch                 | 显示机器的处理器架构              |
| # cal 2016             | 显示 2016 年的日历表              |
| # cat /proc/cpuinfo    | 查看 CPU 信息                     |
| # cat /proc/interrupts | 显示中断                          |
| # cat /proc/meminfo    | 校验内存使用                      |
| # cat /proc/swaps      | 显示哪些 swap 被使用              |
| # cat /proc/version    | 显示内核版本                      |
| # cat /proc/net/dev    | 显示网络适配器及统计              |
| # cat /proc/mounts     | 显示已加载的文件系统              |
| # clock -w             | 将时间修改保存到 BIOS             |
| # date                 | 显示系统日期                      |
| # date 072308302016.00 | 设置日期和时间 - 月日时分年、. 秒 |
| # dmidecode -q         | 显示硬件系统部件 - (SMBIOS / DMI) |
| # hdparm -i /dev/hda   | 罗列一个磁盘的架构特性            |
| # hdparm -tT /dev/sda  | 在磁盘上执行测试性读取操作        |
| # lspci -tv            | 罗列 PCI 设备                     |
| # lsusb -tv            | 显示 USB 设备                     |
| # uname -m             | 显示机器的处理器架构              |
| # uname -r             | 显示正在使用的内核版本            |

### 关机

| 命令                  | 说明                   |
| --------------------- | ---------------------- |
| # init 0              | 关闭系统               |
| # logout              | 注销                   |
| # reboot              | 重启                   |
| # shutdown -h now     | 关闭系统               |
| # shutdown -h 16:30 & | 按预定时间关闭系统     |
| # shutdown -c         | 取消按预定时间关闭系统 |
| # shutdown -r now     | 重启                   |

### 监视和调试

| 命令                               | 说明                                 |
| ---------------------------------- | ------------------------------------ |
| # free -m                          | 以兆为单位罗列 RAM 状态              |
| # kill -9 process_id               | 强行关闭进程并结束它                 |
| # kill -1 process_id               | 强制一个进程重载其配置               |
| # last reboot                      | 显示重启历史                         |
| # lsmod                            | 罗列装载的内核模块                   |
| # lsof -p process_id               | 罗列一个由进程打开的文件列表         |
| # lsof /home/user1                 | 罗列所给系统路径中所打开的文件的列表 |
| # ps -eafw                         | 罗列 linux 任务                      |
| # ps -e -o pid,args --forest       | 以分级的方式罗列 linux 任务          |
| # pstree                           | 以树状图显示程序                     |
| # smartctl -A /dev/hda             | 通过启用 SMART 监控硬盘设备的可靠性  |
| # smartctl -i /dev/hda             | 检查一个硬盘设备的 SMART 是否启用    |
| # strace -c ls >/dev/null          | 罗列系统 calls made 并用一个进程接收 |
| # strace -f -e open ls >/dev/null  | 罗列库调用                           |
| # tail /var/log/dmesg              | 显示内核引导过程中的内部事件         |
| # tail /var/log/messages           | 显示系统事件                         |
| # top                              | 罗列使用 CPU 资源最多的 linux 任务   |
| # watch -n1 'cat /proc/interrupts' | 罗列实时中断                         |

### 公钥私钥

| 命令                                                | 说明                                                         |
| --------------------------------------------------- | ------------------------------------------------------------ |
| # ssh-keygen -t rsa -C "邮箱地址"                   | 产生公钥私钥对                                               |
| # ssh-copy-id -i ~/.ssh/id_rsa.pub root@192.168.0.2 | 将本地机器的公钥复制到远程机器的 root 用户的 authorized_keys 文件中 |
| # ssh-keygen -p -f ~/.ssh/id_rsa                    | 添加或修改 SSH-key 的私钥密码                                |
| # ssh-keygen -y -f ~/.ssh/id_rsa > id_rsa.pub       | 从私钥中生成公钥                                             |

### 其他

| 命令                                                   | 说明                                                         |
| ------------------------------------------------------ | ------------------------------------------------------------ |
| # alias hh='history'                                   | 为命令 history\（历史、) 设置一个别名                        |
| # gpg -c file1                                         | 用 GNU Privacy Guard 加密一个文件                            |
| # gpg file1.gpg                                        | 用 GNU Privacy Guard 解密一个文件                            |
| # ldd /usr/bin/ssh                                     | 显示 ssh 程序所依赖的共享库                                  |
| # man ping                                             | 罗列在线手册页（例如 ping 命令）                             |
| # mkbootdisk --device /dev/fd0 `uname -r`              | 创建一个引导软盘                                             |
| # wget -r www.example.com                              | 下载一个完整的 web 站点                                      |
| # wget -c www.example.com/file.iso                     | 以支持断点续传的方式下载一个文件                             |
| # echo 'wget -c www.example.com/files.iso' \| at 09:00 | 在任何给定的时间开始一次下载                                 |
| # whatis ...keyword                                    | 罗列该程序功能的说明                                         |
| # who -a                                               | 显示谁正登录在线，并打印出：系统最后引导的时间，关机进程，系统登录进程以及由 init 启动的进程，当前运行级和最后一次系统时钟的变化 |

## 资源

### 磁盘空间

| 命令                                                 | 说明                                                         |
| ---------------------------------------------------- | ------------------------------------------------------------ |
| # df -h                                              | 显示已经挂载的分区列表                                       |
| # du -sh dir1                                        | 估算目录 'dir1' 已经使用的磁盘空间                           |
| # du -sk * \| sort -rn                               | 以容量大小为依据依次显示文件和目录的大小                     |
| # ls -lSr \| more                                    | 以尺寸大小排列文件和目录                                     |
| # rpm -q -a --qf '%10{SIZE}t%{NAME}n' \| sort -k1,1n | 以大小为依据依次显示已安装的 rpm 包所使用的空间 (centos, redhat, fedora 类系统、) |

## 文件及文本处理

### 文件和目录

| 命令                                                         | 说明                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| # cd /home                                                   | 进入 '/home' 目录                                            |
| # cd ..                                                      | 返回上一级目录                                               |
| # cd ../..                                                   | 返回上两级目录                                               |
| # cd                                                         | 进入个人的主目录                                             |
| # cd ~user1                                                  | 进入个人的主目录                                             |
| # cd -                                                       | 返回上次所在的目录                                           |
| # cp file1 file2                                             | 复制一个文件                                                 |
| # cp dir/* .                                                 | 复制一个目录下的所有文件到当前工作目录                       |
| # cp -a /tmp/dir1 .                                          | 复制一个目录到当前工作目录                                   |
| # cp -a dir1 dir2                                            | 复制一个目录                                                 |
| # cp file file1                                              | 将 file 复制为 file1                                         |
| # iconv -l                                                   | 列出已知的编码                                               |
| # iconv -f fromEncoding -t toEncoding inputFile > outputFile | 改变字符的编码                                               |
| # find . -maxdepth 1 -name *.jpg -print -exec convert        | batch resize files in the current directory and send them to a thumbnails directory (requires convert from Imagemagick) |
| # ln -s file1 lnk1                                           | 创建一个指向文件或目录的软链接                               |
| # ln file1 lnk1                                              | 创建一个指向文件或目录的物理链接                             |
| # ls                                                         | 查看目录中的文件                                             |
| # ls -F                                                      | 查看目录中的文件                                             |
| # ls -l                                                      | 显示文件和目录的详细资料                                     |
| # ls -a                                                      | 显示隐藏文件                                                 |
| # ls *[0-9]*                                                 | 显示包含数字的文件名和目录名                                 |
| # lstree                                                     | 显示文件和目录由根目录开始的树形结构                         |
| # mkdir dir1                                                 | 创建一个叫做 'dir1' 的目录                                   |
| # mkdir dir1 dir2                                            | 同时创建两个目录                                             |
| # mkdir -p /tmp/dir1/dir2                                    | 创建一个目录树                                               |
| # mv dir1 new_dir                                            | 重命名 / 移动 一个目录                                       |
| # pwd                                                        | 显示工作路径                                                 |
| # rm -f file1                                                | 删除一个叫做 'file1' 的文件                                  |
| # rm -rf dir1                                                | 删除一个叫做 'dir1' 的目录并同时删除其内容                   |
| # rm -rf dir1 dir2                                           | 同时删除两个目录及它们的内容                                 |
| # rmdir dir1                                                 | 删除一个叫做 'dir1' 的目录                                   |
| # touch -t 1607230000 file1                                  | 修改一个文件或目录的时间戳 - (YYMMDDhhmm)                    |
| # tree                                                       | 显示文件和目录由根目录开始的树形结构                         |

### 文件搜索

| 命令                                         | 说明                                                 |
| -------------------------------------------- | ---------------------------------------------------- |
| # find / -name file1                         | 从 '/' 开始进入根文件系统搜索文件和目录              |
| # find / -user user1                         | 搜索属于用户 'user1' 的文件和目录                    |
| # find /home/user1 -name \*.bin              | 在目录 '/ home/user1' 中搜索带有'.bin' 结尾的文件    |
| # find /usr/bin -type f -atime +100          | 搜索在过去 100 天内未被使用过的执行文件              |
| # find /usr/bin -type f -mtime -10           | 搜索在 10 天内被创建或者修改过的文件                 |
| # find / -name *.rpm -exec chmod 755 '{}' \; | 搜索以 '.rpm' 结尾的文件并定义其权限                 |
| # find / -xdev -name \*.rpm                  | 搜索以 '.rpm' 结尾的文件，忽略光驱、捷盘等可移动设备 |
| # locate \*.ps                               | 寻找以 '.ps' 结尾的文件 - 先运行 'updatedb' 命令     |
| # whereis halt                               | 显示一个二进制文件、源码或 man 的位置                |
| # which halt                                 | 显示一个二进制文件或可执行文件的完整路径             |

### 文件的权限

| 命令                           | 说明                                                         |
| ------------------------------ | ------------------------------------------------------------ |
| # chgrp group1 file1           | 改变文件的群组                                               |
| # chmod ugo+rwx directory1     | 设置目录的所有人、(u)、群组、(g) 以及其他人、(o) 以读、(r)、写、(w) 和执行、(x) 的权限 |
| # chmod go-rwx directory1      | 删除群组、(g) 与其他人、(o) 对目录的读写执行权限             |
| # chmod u+s /bin/file1         | 设置一个二进制文件的 SUID 位 - 运行该文件的用户也被赋予和所有者同样的权限 |
| # chmod u-s /bin/file1         | 禁用一个二进制文件的 SUID 位                                 |
| # chmod g+s /home/public       | 设置一个目录的 SGID 位 - 类似 SUID，不过这是针对目录的       |
| # chmod g-s /home/public       | 禁用一个目录的 SGID 位                                       |
| # chmod o+t /home/public       | 设置一个文件的 STIKY 位 - 只允许合法所有人删除文件           |
| # chmod o-t /home/public       | 禁用一个目录的 STIKY 位                                      |
| # chown user1 file1            | 改变一个文件的所有人属性                                     |
| # chown -R user1 directory1    | 改变一个目录的所有人属性并同时改变改目录下所有文件的属性     |
| # chown user1:group1 file1     | 改变一个文件的所有人和群组属性                               |
| # find / -perm -u+s            | 罗列一个系统中所有使用了 SUID 控制的文件                     |
| # ls -lh                       | 显示权限                                                     |
| # ls /tmp \| pr -T5 -W$COLUMNS | 将终端划分成 5 栏显示                                        |

### 文件的特殊属性

| 命令              | 说明                                                         |
| ----------------- | ------------------------------------------------------------ |
| # chattr +a file1 | 只允许以追加方式读写文件                                     |
| # chattr +c file1 | 允许这个文件能被内核自动压缩 / 解压                          |
| # chattr +d file1 | 在进行文件系统备份时，dump 程序将忽略这个文件                |
| # chattr +i file1 | 设置成不可变的文件，不能被删除、修改、重命名或者链接         |
| # chattr +s file1 | 允许一个文件被安全地删除                                     |
| # chattr +S file1 | 一旦应用程序对这个文件执行了写操作，使系统立刻把修改的结果写到磁盘 |
| # chattr +u file1 | 若文件被删除，系统会允许你在以后恢复这个被删除的文件         |
| # lsattr          | 显示特殊的属性                                               |

### 查看文件内容

| 命令                        | 说明                                                         |
| --------------------------- | ------------------------------------------------------------ |
| # cat file1                 | 从第一个字节开始正向查看文件的内容                           |
| # head -2 file1             | 查看一个文件的前两行                                         |
| # less file1                | 类似于 'more' 命令，但是它允许在文件中和正向操作一样的反向操作 |
| # more file1                | 查看一个长文件的内容                                         |
| # tac file1                 | 从最后一行开始反向查看一个文件的内容                         |
| # tail -2 file1             | 查看一个文件的最后两行                                       |
| # tail -f /var/log/messages | 实时查看被添加到一个文件中的内容                             |

### 文本处理

| 命令                                        | 说明                                                      |
| ------------------------------------------- | --------------------------------------------------------- |
| # cat example.txt \| awk 'NR%2==1'          | 删除 example.txt 文件中的所有偶数行                       |
| # echo a b c \| awk '{print $1}'            | 查看一行第一栏                                            |
| # echo a b c \| awk '{print $1,$3}'         | 查看一行的第一和第三栏                                    |
| # cat -n file1                              | 标示文件的行数                                            |
| # comm -1 file1 file2                       | 比较两个文件的内容只删除 'file1' 所包含的内容             |
| # comm -2 file1 file2                       | 比较两个文件的内容只删除 'file2' 所包含的内容             |
| # comm -3 file1 file2                       | 比较两个文件的内容只删除两个文件共有的部分                |
| # diff file1 file2                          | 找出两个文件内容的不同处                                  |
| # grep Aug /var/log/messages                | 在文件 '/var/log/messages'中查找关键词"Aug"               |
| # grep ^Aug /var/log/messages               | 在文件 '/var/log/messages'中查找以"Aug"开始的词汇         |
| # grep [0-9] /var/log/messages              | 选择 '/var/log/messages' 文件中所有包含数字的行           |
| # grep Aug -R /var/log/*                    | 在目录 '/var/log' 及随后的目录中搜索字符串"Aug"           |
| # paste file1 file2                         | 合并两个文件或两栏的内容                                  |
| # paste -d '+' file1 file2                  | 合并两个文件或两栏的内容，中间用"+"区分                   |
| # sdiff file1 file2                         | 以对比的方式显示两个文件的不同                            |
| # sed 's/string1/string2/g' example.txt     | 将 example.txt 文件中的 "string1" 替换成 "string2"        |
| # sed '/^$/d' example.txt                   | 从 example.txt 文件中删除所有空白行                       |
| # sed '/ *\|#/d; /^$/d' example.txt         | 去除文件 example.txt 中的注释与空行                       |
| # sed -e '1d' exampe.txt                    | 从文件 example.txt 中排除第一行                           |
| # sed -n '/string1/p'                       | 查看只包含词汇 "string1"的行                              |
| # sed -e 's/ *$//' example.txt              | 删除每一行最后的空白字符                                  |
| # sed -e 's/string1//g' example.txt         | 从文档中只删除词汇 "string1" 并保留剩余全部               |
| # sed -n '1,5p' example.txt                 | 显示文件 1 至 5 行的内容                                  |
| # sed -n '5p;5q' example.txt                | 显示 example.txt 文件的第 5 行内容                        |
| # sed -e 's/00*/0/g' example.txt            | 用单个零替换多个零                                        |
| # sort file1 file2                          | 排序两个文件的内容                                        |
| # sort file1 file2 \| uniq                  | 取出两个文件的并集、（重复的行只保留一份、)               |
| # sort file1 file2 \| uniq -u               | 删除交集，留下其他的行                                    |
| # sort file1 file2 \| uniq -d               | 取出两个文件的交集、（只留下同时存在于两个文件中的文件、) |
| # echo 'word' \| tr '[:lower:]' '[:upper:]' | 合并上下单元格内容                                        |

### 字符设置和文件格式

| 命令                                   | 说明                                     |
| -------------------------------------- | ---------------------------------------- |
| # dos2unix filedos.txt fileunix.txt    | 将一个文本文件的格式从 MSDOS 转换成 UNIX |
| # recode ..HTML < page.txt > page.html | 将一个文本文件转换成 html                |
| # recode -l \| more                    | 显示所有允许的转换格式                   |
| # unix2dos fileunix.txt filedos.txt    | 将一个文本文件的格式从 UNIX 转换成 MSDOS |

## 挂载

### 挂载一个文件系统

| 命令                                                         | 说明                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| # fuser -km /mnt/hda2                                        | 当设备繁忙时强制卸载                                         |
| # mount /dev/hda2 /mnt/hda2                                  | 挂载一个叫做 hda2 的盘 - 确保目录 '/mnt/hda2' 已经存在       |
| # mount /dev/fd0 /mnt/floppy                                 | 挂载一个软盘                                                 |
| # mount /dev/cdrom /mnt/cdrom                                | 挂载一个 cdrom 或 dvdrom                                     |
| # mount /dev/hdc /mnt/cdrecorder                             | 挂载一个 cdrw 或 dvdrom                                      |
| # mount /dev/hdb /mnt/cdrecorder                             | 挂载一个 cdrw 或 dvdrom                                      |
| # mount -o loop file.iso /mnt/cdrom                          | 挂载一个文件或 ISO 镜像文件                                  |
| # mount -t vfat /dev/hda5 /mnt/hda5                          | 挂载一个 Windows FAT32 文件系统                              |
| # mount /dev/sda1 /mnt/usbdisk                               | 挂载一个 U 盘或闪存设备                                      |
| # mount -t smbfs -o username=user,password=pass //WinClient/share /mnt/share | 挂载一个 windows 网络共享                                    |
| # umount /dev/hda2                                           | 卸载一个叫做 hda2 的盘 - 先从挂载点 '/mnt/hda2' 退出         |
| # umount -n /mnt/hda2                                        | 运行卸载操作而不写入 /etc/mtab 文件、- 当文件为只读或当磁盘写满时非常有用 |

### 光盘

| 命令                                                         | 说明                                            |
| ------------------------------------------------------------ | ----------------------------------------------- |
| # cd-paranoia -B                                             | 从一个 CD 光盘转录音轨到 wav 文件中             |
| # cd-paranoia --                                             | 从一个 CD 光盘转录音轨到 wav 文件中（参数、-3） |
| # cdrecord -v gracetime=2 dev=/dev/cdrom -eject blank=fast -force | 清空一个可复写的光盘内容                        |
| # cdrecord -v dev=/dev/cdrom cd.iso                          | 刻录一个 ISO 镜像文件                           |
| # gzip -dc cd_iso.gz \| cdrecord dev=/dev/cdrom -            | 刻录一个压缩了的 ISO 镜像文件                   |
| # cdrecord --scanbus                                         | 扫描总线以识别 scsi 通道                        |
| # dd if=/dev/hdc \| md5sum                                   | 校验一个设备的 md5sum 编码，例如一张 CD         |
| # mkisofs /dev/cdrom > cd.iso                                | 在磁盘上创建一个光盘的 iso 镜像文件             |
| # mkisofs /dev/cdrom \| gzip > cd_iso.gz                     | 在磁盘上创建一个压缩了的光盘 iso 镜像文件       |
| # mkisofs -J -allow-leading-dots -R -V                       | 创建一个目录的 iso 镜像文件                     |
| # mount -o loop cd.iso /mnt/iso                              | 挂载一个 ISO 镜像文件                           |

## 用户管理

### 用户和群组

| 命令                                                         | 说明                                                  |
| ------------------------------------------------------------ | ----------------------------------------------------- |
| # chage -E 2016-12-31 user1                                  | 设置用户口令的失效期限                                |
| # groupadd [group]                                           | 创建一个新用户组                                      |
| # groupdel [group]                                           | 删除一个用户组                                        |
| # groupmod -n moon sun                                       | 重命名一个用户组                                      |
| # grpck                                                      | 检查 '/etc/passwd' 的文件格式和语法修正以及存在的群组 |
| # newgrp - [group]                                           | 登陆进一个新的群组以改变新创建文件的预设群组          |
| # passwd                                                     | 修改口令                                              |
| # passwd user1                                               | 修改一个用户的口令 \（只允许 root 执行、)             |
| # pwck                                                       | 检查 '/etc/passwd' 的文件格式和语法修正以及存在的用户 |
| # useradd -c "User Linux" -g admin -d /home/user1 -s /bin/bash user1 | 创建一个属于 "admin" 用户组的用户                     |
| # useradd user1                                              | 创建一个新用户                                        |
| # userdel -r user1                                           | 删除一个用户 ( '-r' 排除主目录、)                     |
| # usermod -c "User FTP" -g system -d /ftp/user1 -s /bin/nologin user1 | 修改用户属性                                          |

## 包管理

### 打包和压缩文件

| 命令                                    | 说明                                                  |
| --------------------------------------- | ----------------------------------------------------- |
| # bunzip2 file1.bz2                     | 解压一个叫做 'file1.bz2'的文件                        |
| # bzip2 file1                           | 压缩一个叫做 'file1' 的文件                           |
| # gunzip file1.gz                       | 解压一个叫做 'file1.gz'的文件                         |
| # gzip file1                            | 压缩一个叫做 'file1'的文件                            |
| # gzip -9 file1                         | 最大程度压缩                                          |
| # rar a file1.rar test_file             | 创建一个叫做 'file1.rar' 的包                         |
| # rar a file1.rar file1 file2 dir1      | 同时压缩 'file1', 'file2' 以及目录 'dir1'             |
| # rar x file1.rar                       | 解压 rar 包                                           |
| # tar -cvf archive.tar file1            | 创建一个非压缩的 tarball                              |
| # tar -cvf archive.tar file1 file2 dir1 | 创建一个包含了 'file1', 'file2' 以及 'dir1'的档案文件 |
| # tar -tf archive.tar                   | 显示一个包中的内容                                    |
| # tar -xvf archive.tar                  | 释放一个包                                            |
| # tar -xvf archive.tar -C /tmp          | 将压缩包释放到 /tmp 目录下                            |
| # tar -cvfj archive.tar.bz2 dir1        | 创建一个 bzip2 格式的压缩包                           |
| # tar -xvfj archive.tar.bz2             | 解压一个 bzip2 格式的压缩包                           |
| # tar -cvfz archive.tar.gz dir1         | 创建一个 gzip 格式的压缩包                            |
| # tar -xvfz archive.tar.gz              | 解压一个 gzip 格式的压缩包                            |
| # unrar x file1.rar                     | 解压 rar 包                                           |
| # unzip file1.zip                       | 解压一个 zip 格式压缩包                               |
| # zip file1.zip file1                   | 创建一个 zip 格式的压缩包                             |
| # zip -r file1.zip file1 file2 dir1     | 将几个文件和目录同时压缩成一个 zip 格式的压缩包       |

### RPM 包 (Fedora,RedHat and alike)

| 命令                                                         | 说明                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| # rpm -ivh [package.rpm]                                     | 安装一个 rpm 包                                              |
| # rpm -ivh --nodeeps [package.rpm]                           | 安装一个 rpm 包而忽略依赖关系警告                            |
| # rpm -U [package.rpm]                                       | 更新一个 rpm 包但不改变其配置文件                            |
| # rpm -F [package.rpm]                                       | 更新一个确定已经安装的 rpm 包                                |
| # rpm -e [package]                                           | 删除一个 rpm 包                                              |
| # rpm -qa                                                    | 显示系统中所有已经安装的 rpm 包                              |
| # rpm -qa \| grep httpd                                      | 显示所有名称中包含 "httpd" 字样的 rpm 包                     |
| # rpm -qi [package]                                          | 获取一个已安装包的特殊信息                                   |
| # rpm -qg "System Environment/Daemons"                       | 显示一个组件的 rpm 包                                        |
| # rpm -ql [package]                                          | 显示一个已经安装的 rpm 包提供的文件列表                      |
| # rpm -qc [package]                                          | 显示一个已经安装的 rpm 包提供的配置文件列表                  |
| # rpm -q [package] --whatrequires                            | 显示与一个 rpm 包存在依赖关系的列表                          |
| # rpm -q [package] --whatprovides                            | 显示一个 rpm 包所占的体积                                    |
| # rpm -q [package] --scripts                                 | 显示在安装 / 删除期间所执行的脚本 l                          |
| # rpm -q [package] --changelog                               | 显示一个 rpm 包的修改历史                                    |
| # rpm -qf /etc/httpd/conf/httpd.conf                         | 确认所给的文件由哪个 rpm 包所提供                            |
| # rpm -qp [package.rpm] -l                                   | 显示由一个尚未安装的 rpm 包提供的文件列表                    |
| # rpm --import /media/cdrom/RPM-GPG-KEY                      | 导入公钥数字证书                                             |
| # rpm --checksig [package.rpm]                               | 确认一个 rpm 包的完整性                                      |
| # rpm -qa gpg-pubkey                                         | 确认已安装的所有 rpm 包的完整性                              |
| # rpm -V [package]                                           | 检查文件尺寸、 许可、类型、所有者、群组、MD5 检查以及最后修改时间 |
| # rpm -Va                                                    | 检查系统中所有已安装的 rpm 包、- 小心使用                    |
| # rpm -Vp [package.rpm]                                      | 确认一个 rpm 包还未安装                                      |
| # rpm -ivh /usr/src/redhat/RPMS/`arch`/[package.rpm]         | 从一个 rpm 源码安装一个构建好的包                            |
| # rpm2cpio [package.rpm] \| cpio --extract --make-directories *bin* | 从一个 rpm 包运行可执行文件                                  |
| # rpmbuild --rebuild [package.src.rpm]                       | 从一个 rpm 源码构建一个 rpm 包                               |

### YUM 软件工具 (Fedora,RedHat and alike)

| 命令                             | 说明                                                        |
| -------------------------------- | ----------------------------------------------------------- |
| # yum -y install [package]       | 下载并安装一个 rpm 包                                       |
| # yum localinstall [package.rpm] | 将安装一个 rpm 包，使用你自己的软件仓库为你解决所有依赖关系 |
| # yum -y update                  | 更新当前系统中所有安装的 rpm 包                             |
| # yum update [package]           | 更新一个 rpm 包                                             |
| # yum remove [package]           | 删除一个 rpm 包                                             |
| # yum list                       | 列出当前系统中安装的所有包                                  |
| # yum repolist                   | 显示可用的仓库                                              |
| # yum search [package]           | 在 rpm 仓库中搜寻软件包                                     |
| # yum clean [package]            | 清理 rpm 缓存删除下载的包                                   |
| # yum clean headers              | 删除所有头文件                                              |
| # yum clean all                  | 删除所有缓存的包和头文件                                    |

### 备份

| 命令                                                         | 说明                                                     |
| ------------------------------------------------------------ | -------------------------------------------------------- |
| # find /var/log -name '*.log' \| tar cv --files-from=- \| bzip2 > log.tar.bz2 | 查找所有以 '.log' 结尾的文件并做成一个 bzip 包           |
| # find /home/user1 -name '*.txt' \| xargs cp -av --target-directory=/home/backup/ --parents | 从一个目录查找并复制所有以 '.txt' 结尾的文件到另一个目录 |
| # dd bs=1M if=/dev/hda \| gzip \| ssh user@ip_addr 'dd of=hda.gz' | 通过 ssh 在远程主机上执行一次备份本地磁盘的操作          |
| # dd if=/dev/sda of=/tmp/file1                               | 备份磁盘内容到一个文件                                   |
| # dd if=/dev/hda of=/dev/fd0 bs=512 count=1                  | 做一个将 MBR (Master Boot Record) 内容复制到软盘的动作   |
| # dd if=/dev/fd0 of=/dev/hda bs=512 count=1                  | 从已经保存到软盘的备份中恢复 MBR 内容                    |
| # dump -0aj -f /tmp/home0.bak /home                          | 制作一个 '/home' 目录的完整备份                          |
| # dump -1aj -f /tmp/home0.bak /home                          | 制作一个 '/home' 目录的交互式备份                        |
| # restore -if /tmp/home0.bak                                 | 还原一个交互式备份                                       |
| # rsync -rogpav --delete /home /tmp                          | 同步两边的目录                                           |
| # rsync -rogpav -e ssh --delete /home ip_address:/tmp        | 通过 SSH 通道 rsync                                      |
| # rsync -az -e ssh --delete ip_addr:/home/public /home/local | 通过 ssh 和压缩将一个远程目录同步到本地目录              |
| # rsync -az -e ssh --delete /home/local ip_addr:/home/public | 通过 ssh 和压缩将本地目录同步到远程目录                  |
| # tar -Puf backup.tar /home/user                             | 执行一次对 '/home/user' 目录的交互式备份操作             |
| # ( cd /tmp/local/ && tar c . ) \| ssh -C user@ip_addr 'cd /home/share/ && tar x -p' | 通过 ssh 在远程目录中复制一个目录内容                    |
| # ( tar c /home ) \| ssh -C user@ip_addr 'cd /home/backup-home && tar x -p' | 通过 ssh 在远程目录中复制一个本地目录                    |
| # tar cf - . \| (cd /tmp/backup ; tar xf - )                 | 本地将一个目录复制到另一个地方，保留原有权限及链接       |

## 磁盘和分区

### 文件系统分析

| 命令                     | 说明                                           |
| ------------------------ | ---------------------------------------------- |
| # badblocks -v /dev/hda1 | 检查磁盘 hda1 上的坏磁块                       |
| # dosfsck /dev/hda1      | 修复 / 检查 hda1 磁盘上 dos 文件系统的完整性   |
| # e2fsck /dev/hda1       | 修复 / 检查 hda1 磁盘上 ext2 文件系统的完整性  |
| # e2fsck -j /dev/hda1    | 修复 / 检查 hda1 磁盘上 ext3 文件系统的完整性  |
| # fsck /dev/hda1         | 修复 / 检查 hda1 磁盘上 linux 文件系统的完整性 |
| # fsck.ext2 /dev/hda1    | 修复 / 检查 hda1 磁盘上 ext2 文件系统的完整性  |
| # fsck.ext3 /dev/hda1    | 修复 / 检查 hda1 磁盘上 ext3 文件系统的完整性  |
| # fsck.vfat /dev/hda1    | 修复 / 检查 hda1 磁盘上 fat 文件系统的完整性   |
| # fsck.msdos /dev/hda1   | 修复 / 检查 hda1 磁盘上 dos 文件系统的完整性   |

### 初始化一个文件系统

| 命令                           | 说明                                                   |
| ------------------------------ | ------------------------------------------------------ |
| # fdformat -n /dev/fd0         | 格式化一个软盘                                         |
| # mke2fs /dev/hda1             | 在 hda1 分区创建一个 linux ext2 的文件系统             |
| # mke2fs -j /dev/hda1          | 在 hda1 分区创建一个 linux ext3\（日志型、) 的文件系统 |
| # mkfs /dev/hda1               | 在 hda1 分区创建一个文件系统                           |
| # mkfs -t vfat 32 -F /dev/hda1 | 创建一个 FAT32 文件系统                                |
| # mkswap /dev/hda3             | 创建一个 swap 文件系统                                 |

### SWAP 文件系统

| 命令                         | 说明                       |
| ---------------------------- | -------------------------- |
| # mkswap /dev/hda3           | 创建一个 swap 文件系统     |
| # swapon /dev/hda3           | 启用一个新的 swap 文件系统 |
| # swapon /dev/hda2 /dev/hdb3 | 启用两个 swap 分区         |