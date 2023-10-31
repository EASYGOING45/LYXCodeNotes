# Linux

Linux-操作系统内核 操作系统硬件架构有哪些？

Arm-Linux X86 X64 X32 Fixed

1. 如何查看操作系统内核信息：`uname -a`

2. 如何查看本机IP网络相关信息：`ifconfig`

3. 文件操作相关

4. 如何查看当前所处的绝对路径：`pwd`

   ![image-20231029153508862](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20231029153508862.png)

5. 如何切换路径： `cd 路径信息（如cd /Projects/BlueKing）`

   `cd ..` 即切换到上一级目录

   ![image-20231029153851638](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20231029153851638.png)

6. 如何查看当前路径下的文件信息： `ls`

7. 如何创建文件

   `touch 文件名.后缀` 创建文件，但不进行编辑

   `vim 文件名.后缀` 创建文件，并打开VIM编辑器，按`i`进入Insert模式可以进行编辑，编辑完后先按 `Esc`，再按 `:`,输入 `wq`，即Write&Quit 保存并推出

8. Python如何运行程序 `python 文件名`

   ![image-20231029154047254](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20231029154047254.png)

9. 语言环境相关

10. Python后端-使用Conda作为管理器

11. 查看当前主机下有哪些Conda虚拟环境 `conda env list`

12. 切换至指定Conda 环境 `conda activate 环境名`

13. 如何查看当前Conda环境下安装了哪些Python包 `conda list`

14. ![image-20231029154314780](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20231029154314780.png)

15. Django相关 

16. Django创建新项目：切换至拥有Django的Conda环境中 参考上文

17. 创建新项目： `django-admin startproject 项目名称`

18. 如何执行数据库迁移：`python manage.py makemigrations`

19. 迁移：`python manage.py migrate`

20. 如何启动Django服务器（项目）：`python manage.py runserver`

21. 如何在指定端口启动Django服务器：`python manage.py runserver 端口号`

GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' IDENTIFIED BY 'huan0912' WITH GRANT OPTION;
FLUSH PRIVILEGES;