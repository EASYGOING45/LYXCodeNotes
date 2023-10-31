# CTENETのDjango笔记Ⅰ

## Centos7配置安装miniconda、虚拟环境、Django2

- 创建虚拟环境并指定Python版本号 `conda create -n py36 python=3.6`
- 安装Django2`pip3 install Django==2.2.12`

![image-20231025154753558](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20231025154753558.png)

- 检查

  ```Python
  import django
  
  print(django.get_version()) # 查看当前Django版本
  print(django.VERSION) # 查看当前Django版本
  
  # 查看当前使用的Python版本及conda环境
  import sys
  print(sys.version)
  print(sys.version_info)
  print(sys.executable)
  # 查看conda环境 
  # conda env list
  # conda 创建环境并指定python版本号为3.6
  # conda create -n py36 python=3.6
  ```

  

  ![image-20231025154915775](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20231025154915775.png)