## 前端->npm管理Vue

### Vue？

前端框架

.vue文件

传统前端是.html文件 类比去年数据库课设

今年改用前后端分离架构，前端使用Vue框架 每一个网页都是一个组件（Component)，每一个网页文件都是一个.vue文件。

前端：HTML+CSS+JavaScript

基本三件套->前端框架（BootStrap、Uniapp、Vue）

Vue->组件式、多渲染的前端框架，基于WebPack（迅速的将前端环境打包部署），每一个网站都是一个.vue的组件

xxx.html  一个网页

在Vue中就是一个xxx.vue

## 后端：Python(Conda管理)

### 后端框架:Python->Django2.2.12

Django框架：

如何新建一个Django项目： `django-admin startproject xxx(项目名称)`

Django项目组成：Django里面，每一个组成都是以应用(app)来划分，数据库博客项目里面，核心app就是kblog，每一个Django项目至少包含一个应用，该应用和项目同名，里面主要存储一些配置文件(settings.py )，配置如数据库、中间件等信息。

Django程序的入口文件：`manage.py`

Django程序如何启动（如何启动Django服务器）：`python manage.py runserver`

1. 

Django->MVC架构 数据模型对应的是M，就是每一个子应用的models.py

1. `python manage.py  makemigrations`
2. `python manage.py migrate`  数据模型迁移落地到数据库里面 目的地（数据库），由全局的settings.py所决定

## SSH Channels

GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' IDENTIFIED BY 'huan0912' WITH GRANT OPTION;