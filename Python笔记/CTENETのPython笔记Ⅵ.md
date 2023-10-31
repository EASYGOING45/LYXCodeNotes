# CTENETのPython笔记Ⅵ

## Python模块

## Python 模块常用的几种安装方式

### 单文件模块

直接把文件拷贝到 `$python_dir/Lib`

### 多文件模块，带setup.py

下载模块包，进行解压，进入模块文件夹，执行：

```bash
python setup.py install
```

### easy_install 方式

先下载 ez_setup.py，运行 python ez_setup 进行 easy_install 工具的安装，之后就可以使用 easy_install 进行安装 package 了。

```bash
easy_install  packageNameeasy_install  package.egg
```

### pip 方式

先进行pip工具的安裝：easy_install pip（pip 可以通过easy_install 安裝，而且也会装到 Scripts 文件夹下。）

```bash
pip install PackageName # 安裝
pip install -U PackageName # 更新
pip uninstall PackageName # 移除
pip search PackageName # 搜索
pip help # 帮助
```

注：虽然Python的模块可以拷贝安装，但是一般情况下推荐制作一个安装包，即写一个setup.py文件来安装。setup.py文件的使用如下:

```bash
python setup.py build     #编译
python setup.py install   #安装
python setup.py sdist     #制作分发包
python setup.py bdist_wininst    #制作windows下的分发包
python setup.py bdist_rpm
```

------

## Python中的setup.py详解

### 1.为什么需要对项目分发打包？

平常我们习惯了使用 pip 来安装一些第三方模块，这个安装过程之所以简单，是因为模块开发者为我们默默地为我们做了所有繁杂的工作，而这个过程就是 `打包`。

打包，就是将你的源代码进一步封装，并且将所有的项目部署工作都事先安排好，这样使用者拿到后即装即用，不用再操心如何部署的问题（如果你不想对照着一堆部署文档手工操作的话）。

不管你是在工作中，还是业余准备自己写一个可以上传到 PyPI 的项目，你都要学会如何打包你的项目。

Python 发展了这么些年了，项目打包工具也已经很成熟了。他们都有哪些呢？

你可能听过 `disutils`、 `distutils` 、`distutils2`、`setuptools`等等，好像很熟悉，却又很陌生，他们都是什么关系呢？

### 2. 包分发的始祖：distutils

`distutils` 是 Python 的一个标准库，从命名上很容易看出它是一个分发（distribute）工具（utlis），它是 Python 官方开发的一个分发打包工具，所有后续的打包工具，全部都是基于它进行开发的。

`distutils` 的精髓在于编写 setup.py，它是模块分发与安装的指导文件。

那么如何编写 setup.py 呢？这里面的内容非常多，我会在后面进行详细的解析，请你耐心往下看。

你有可能没写过 setup.py ，但你绝对使用过 setup.py 来做一些事情，比如下面这条命令，我们经常用它来进行模块的安装。

```text
$ python setup.py install
```

这样的安装方法是通过源码安装，与之对应的是通过二进制软件包的安装，同样我也会在后面进行介绍。

### 3. 分发工具升级：setuptools

`setuptools` 是 distutils 增强版，不包括在标准库中。其扩展了很多功能，能够帮助开发者更好的创建和分发 Python 包。大部分 Python 用户都会使用更先进的 setuptools 模块。

**distribute**，或许你在其他地方也见过它，这里也提一下。

distribute 是 setuptools 有一个分支版本，分支的原因可能是有一部分开发者认为 setuptools 开发太慢了。但现在，distribute 又合并回了 setuptools 中。因此，我们可以认为它们是同一个东西。

还有一个大包分发工具是 **distutils2**，其试图尝试充分利用distutils，detuptools 和 distribute 并成为 Python 标准库中的标准工具。但该计划并没有达到预期的目的，且已经是一个废弃的项目。

因此，setuptools 是一个优秀的，可靠的 Python 包安装与分发工具。

那么如何在一个干净的环境中安装 setuptools 呢？

主要有两种方法：

- 源码安装：在 [https://pypi.org/project/setuptools/#filesopen in new window](https://link.zhihu.com/?target=https%3A//pypi.org/project/setuptools/%23files) 中下载 zip 包 解压执行 `python setup.py install` 安装
- 通过引导程序安装：下载引导程序，它可以用来下载或者更新最新版本的 setuptools

```text
$ wget http://peak.telecommunity.com/dist/ez_setup.py

# 安装
$ python ez_setup.py

# 更新，以下两种任选
$ python ez_setup.py –U setuptools
$ pip install -U setuptools
```

### 4. easy_install 使用指南

当你安装完 setuptools 后，就拥有了一个叫做 `easy_install` 的第三方管理工具，这也是它区分于 distutils 的一大改进。

这里简单介绍一下它的用法，虽然它已经用得非常少了。

先是包的安装

```text
# 通过包名，从PyPI寻找最新版本，自动下载、编译、安装
$ easy_install pkg_name

# 通过包名从指定下载页寻找链接来安装或升级包
$ easy_install -f http://pythonpaste.org/package_index.html 

# 指定线上的包地址安装
$ easy_install http://example.com/path/to/MyPackage-1.2.3.tgz

# 从本地的 .egg 文件安装
$ easy_install xxx.egg

# 在安装时你可以添加额外的参数
指定安装目录：--install-dir=DIR, -d DIR
指定用户安装：--user
```

再者是包的升级

```text
# 从 pypi 中搜索并升级包
$ easy_install --upgrade pkg_name

# 指定版本进行升级
$ easy_install "SomePackage==2.0"
```

最后是包的删除

```text
$ easy_install -m pkg_name
```

需要注意的是，这样的删除，仅是在 easy-install.pth 文件中删除，使其不能在 python 中使用 这个模块，但实际的包还在你的电脑中，若要删除彻底，需要你手动删除相关的 .egg 及 其他文件。

默认情况下，easy_install 只会从 pypi 上下载相关软件包，由于这个源在国外，下载包的速度并不理想，使用过pip的朋友自然会想，easy_install 是否能指定源进行安装呢？

答案是，可以的。

编辑配置文件 `/root/.pydistutils.cfg`

```text
[easy_install]
index-url=http://mirrors.aliyun.com/pypi/simple/
find-links=http://mirrors.aliyun.com/pypi/simple/
```

以上仅介绍了 easy_install 的一些常用的方法，想要了解更多，你可以点击官方文档：[https://setuptools.readthedocs.io/en/latest/easy_install.htmlopen in new window](https://link.zhihu.com/?target=https%3A//setuptools.readthedocs.io/en/latest/easy_install.html)

总结一句：setuptools 是官方提供的一个专业用于包分发的工具，若只从安装的角度来看，它的功能确实简单。它更大的意义是对包的分发很有用，定制化程序非常高，我们现在也还在用它进行版本包的发布。

### 5. 源码包与二进制包什么区别？

Python 包的分发可以分为两种：

1、以源码包的方式发布

源码包安装的过程，是先解压，再编译，最后才安装，所以它是跨平台的，由于每次安装都要进行编译，相对二进包安装方式来说安装速度较慢。

源码包的本质是一个压缩包，其常见的格式有：

![img](https://pic1.zhimg.com/80/v2-dffd77a245997a841eb426d9c0ce5184_720w.jpg)

2、以二进制包形式发布

二进制包的安装过程省去了编译的过程，直接进行解压安装，所以安装速度较源码包来说更快。

由于不同平台的编译出来的包无法通用，所以在发布时，需事先编译好多个平台的包。

二进制包的常见格式有：

![img](https://pic4.zhimg.com/80/v2-b0a22d8b82eac1f25bc6a1b95f6e0c2f_720w.jpg)

### 6. eggs 与 wheels 有什么区别？

Egg 格式是由 setuptools 在 2004 年引入，而 Wheel 格式是由 PEP427 在 2012 年定义。Wheel 的出现是为了替代 Egg，它的本质是一个zip包，其现在被认为是 Python 的二进制包的标准格式。

以下是 Wheel 和 Egg 的主要区别：

- Wheel 有一个官方的 PEP427 来定义，而 Egg 没有 PEP 定义
- Wheel 是一种分发格式，即打包格式。而 Egg 既是一种分发格式，也是一种运行时安装的格式，并且是可以被直接 import
- Wheel 文件不会包含 .pyc 文件
- Wheel 使用和 PEP376 兼容的 .dist-info 目录，而 Egg 使用 .egg-info 目录
- Wheel 有着更丰富的命名规则。
- Wheel 是有版本的。每个 Wheel 文件都包含 wheel 规范的版本和打包的实现
- Wheel 在内部被 sysconfig path type 管理，因此转向其他格式也更容易

wheel 包可以通过 pip 来安装，只不过需要先安装 wheel 模块，然后再使用 pip 的命令。

```text
$ pip install wheel
$ pip wheel --wheel-dir=/local/wheels pkg
```

### 7. 超详细讲解 setup.py 的编写？

打包分发最关键的一步是编写 `setup.py` 文件。

以下是一个 setup.py 简单的使用示例

```text
from setuptools import setup, find_packages

setup(
    name="mytest",
    version="1.0",
    author="wangbm",
    author_email="wongbingming@163.com",
    description="Learn to Pack Python Module  -->公众号：Python编程时光",

    # 项目主页
    url="http://iswbm.com/", 

    # 你要安装的包，通过 setuptools.find_packages 找到当前目录下有哪些包
    packages=find_packages()
)
```

接下来，我将慢慢扩充这个setup函数，增加更多的参数，以便你能理解setup函数能做哪些事情。

**程序分类信息**

`classifiers` 参数说明包的分类信息。所有支持的分类列表见：[https://pypi.org/pypi?%3Aaction=list_classifiersopen in new window](https://link.zhihu.com/?target=https%3A//pypi.org/pypi%3F%3Aaction%3Dlist_classifiers)

示例：

```text
from setuptools import setup, find_packages

setup(
    classifiers = [
        # 发展时期,常见的如下
        #   3 - Alpha
        #   4 - Beta
        #   5 - Production/Stable
        'Development Status :: 3 - Alpha',

        # 开发的目标用户
        'Intended Audience :: Developers',

        # 属于什么类型
        'Topic :: Software Development :: Build Tools',

        # 许可证信息
        'License :: OSI Approved :: MIT License',

        # 目标 Python 版本
        'Programming Language :: Python :: 2',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.3',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
    ]
)
```

**关于文件的分发**

```text
from setuptools import setup, find_packages


setup(
    name="mytest",
    version="1.0",
    author="wangbm",
    author_email="wongbingming@163.com",
    description="Learn to Pack Python Module",
    url="http://iswbm.com/", 
    packages=find_packages(),

    # 安装过程中，需要安装的静态文件，如配置文件、service文件、图片等
    data_files=[
        ('', ['conf/*.conf']),
        ('/usr/lib/systemd/system/', ['bin/*.service']),
               ],

    # 希望被打包的文件
    package_data={
        '':['*.txt'],
        'bandwidth_reporter':['*.txt']
               },
    # 不打包某些文件
    exclude_package_data={
        'bandwidth_reporter':['*.txt']
               }
)
```

除了以上的参数配置之外，还可以使用一个叫做 `MANIFEST.in` 的文件，来控制文件的分发。

如下这是一个 `MANIFEST.in` 的样例：

```text
include *.txt
recursive-include examples *.txt *.py
prune examples/sample?/build
```

这些配置，规定了如下几点

- 所有根目录下的以 txt 为后缀名的文件，都会分发
- 根目录下的 examples 目录 和 txt、py文件都会分发
- 路径匹配上 examples/sample?/build 不会分发

`MANIFEST.in` 需要放在和 setup.py 同级的顶级目录下，setuptools 会自动读取该文件。

**关于依赖包下载安装**

```text
from setuptools import setup, find_packages


setup(
    ...

    # 表明当前模块依赖哪些包，若环境中没有，则会从pypi中下载安装
    install_requires=['docutils>=0.3'],

    # setup.py 本身要依赖的包，这通常是为一些setuptools的插件准备的配置
    # 这里列出的包，不会自动安装。
    setup_requires=['pbr'],

    # 仅在测试时需要使用的依赖，在正常发布的代码中是没有用的。
    # 在执行python setup.py test时，可以自动安装这三个库，确保测试的正常运行。
    tests_require=[
        'pytest>=3.3.1',
        'pytest-cov>=2.5.1',
    ],

    # 用于安装setup_requires或tests_require里的软件包
    # 这些信息会写入egg的 metadata 信息中
    dependency_links=[
        "http://example2.com/p/foobar-1.0.tar.gz",
    ],

    # install_requires 在安装模块时会自动安装依赖包
    # 而 extras_require 不会，这里仅表示该模块会依赖这些包
    # 但是这些包通常不会使用到，只有当你深度使用模块时，才会用到，这里需要你手动安装
    extras_require={
        'PDF':  ["ReportLab>=1.2", "RXP"],
        'reST': ["docutils>=0.3"],
    }
)
```

关于 `install_requires`， 有以下五种常用的表示方法：

1. `'argparse'`，只包含包名。 这种形式只检查包的存在性，不检查版本。 方便，但不利于控制风险。
2. `'setuptools==38.2.4'`，指定版本。 这种形式把风险降到了最低，确保了开发、测试与部署的版本一致，不会出现意外。 缺点是不利于更新，每次更新都需要改动代码。
3. `'docutils >= 0.3'`，这是比较常用的形式。 当对某个库比较信任时，这种形式可以自动保持版本为最新。
4. `'Django >= 1.11, != 1.11.1, <= 2'`，这是比较复杂的形式。 如这个例子，保证了Django的大版本在1.11和2之间，也即1.11.x；并且，排除了已知有问题的版本1.11.1（仅举例）。 对于一些大型、复杂的库，这种形式是最合适的。
5. `'requests[security, socks] >= 2.18.4'`，这是包含了额外的可选依赖的形式。 正常安装requests会自动安装它的`install_requires`中指定的依赖，而不会安装`security`和`socks`这两组依赖。 这两组依赖是定义在它的`extras_require`中。 这种形式，用在深度使用某些库时。

**关于安装环境的限制**

有些库并不是在所以的 Python 版本中都适用的，若一个库安装在一个未兼容的 Python 环境中，理论上不应该在使用时才报错，而应该在安装过程就使其失败，提示禁止安装。

这样的功能，可以使用 `python_requires` 来实现。

```text
setup(
    ...
    python_requires='>=2.7, <=3',
)
```

**生成可执行文件的分发**

```text
from setuptools import setup, find_packages


setup(
    name="mytest",
    version="1.0",
    author="wangbm",
    author_email="wongbingming@163.com",
    description="Learn to Pack Python Module",
    url="http://iswbm.com/", 
    packages=find_packages(),

    # 用来支持自动生成脚本，安装后会自动生成 /usr/bin/foo 的可执行文件
    # 该文件入口指向 foo/main.py 的main 函数
    entry_points={
        'console_scripts': [
            'foo = foo.main:main'
        ]
    },

    # 将 bin/foo.sh 和 bar.py 脚本，生成到系统 PATH中
    # 执行 python setup.py install 后
    # 会生成 如 /usr/bin/foo.sh 和 如 /usr/bin/bar.py
    scripts=['bin/foo.sh', 'bar.py']
)
```

上面的 scripts 里有的脚本中有 `sh` 和 `py` 后缀，那么安装后，setuptools 会原封不动的移动到 /usr/bin 中，并添加可执行权限。

若你想对这些文件再作一些更改，比如去掉多余的后缀，可以这样做

```text
from setuptools.command.install_scripts import install_scripts

class InstallScripts(install_scripts):

    def run(self):
        setuptools.command.install_scripts.install_scripts.run(self)

        # Rename some script files
        for script in self.get_outputs():
            if basename.endswith(".py") or basename.endswith(".sh"):
                dest = script[:-3]
            else:
                continue
            print("moving %s to %s" % (script, dest))
            shutil.move(script, dest)

setup(
    ...
    scripts=['bin/foo.sh', 'bar.py'],

    cmdclass={
        "install_scripts": InstallScripts
    }
)
```

**ext_modules**

`ext_modules` 参数用于构建 C 和 C++ 扩展扩展包。其是 Extension 实例的列表，每一个 Extension 实例描述了一个独立的扩展模块，扩展模块可以设置扩展包名，头文件、源文件、链接库及其路径、宏定义和编辑参数等。如：

```text
setup(
    # other arguments here...
    ext_modules=[
        Extension('foo',
                  glob(path.join(here, 'src', '*.c')),
                  libraries = [ 'rt' ],
                  include_dirs=[numpy.get_include()])
    ]
)
```

详细了解可参考：[https://docs.python.org/3.6/distutils/setupscript.html#preprocessor-optionsopen in new window](https://link.zhihu.com/?target=https%3A//docs.python.org/3.6/distutils/setupscript.html%23preprocessor-options)

**指定release**

setup.py 里只能指定 version，而不能指定 release，如果你需要变更版本号，可以使用 `--release` 参数进行指定

```text
python setup.py bdist_rpm --release=20200617
```

setup.py 的参数非常多，能够不借助文档写好一个setup.py好像没那么简单。为了备忘，我整理了 setup 函数常用的一些参数：

![img](https://pic3.zhimg.com/80/v2-4563e810d05ec25ce283c7f54a271e2e_720w.jpg)

更多参数可见：[https://setuptools.readthedocs.io/en/latest/setuptools.htmlopen in new window](https://link.zhihu.com/?target=https%3A//setuptools.readthedocs.io/en/latest/setuptools.html)

### 8. 打包辅助神器PBR 是什么？

`pbr` 是 setuptools 的辅助工具，最初是为 OpenStack 开发([https://launchpad.net/pbr)，基于`d2to1`。open in new window](https://link.zhihu.com/?target=https%3A//launchpad.net/pbr)%EF%BC%8C%E5%9F%BA%E4%BA%8E%60d2to1%60%E3%80%82)

`pbr` 会读取和过滤setup.cfg中的数据，然后将解析后的数据提供给 `setup.py` 作为参数。包含如下功能：

1. 从git中获取Version、AUTHORS and ChangeLog信息
2. Sphinx Autodoc。pbr 会扫描project，找到所有模块，生成stub files
3. Requirements。pbr会读取requirements.txt，生成setup函数需要的`install_requires/tests_require/dependency_links`

这里需要注意，在 `requirements.txt` 文件的头部可以使用：`--index https://pypi.python.org/simple/`，这一行把一个抽象的依赖声明如 requests==1.2.0 转变为一个具体的依赖声明 requests 1.2.0 from pypi.python.org/simple/

1. long_description。从README.rst, README.txt or README file中生成`long_description`参数

使用pbr很简单：

```text
from setuptools import setup

setup(
    setup_requires=['pbr'],
    pbr=True,
)
```

使用pbr时，setup.cfg中有一些配置。在[files]中，有三个key： `packages`:指定需要包含的包，行为类似于setuptools.find_packages `namespace_packages`:指定namespace packages `data_files`: 指定目的目录和源文件路径，一个示例：

```text
[files]
data_files =
    etc/pbr = etc/pbr/*
    etc/neutron =
        etc/api-paste.ini
        etc/dhcp-agent.ini
    etc/init.d = neutron.init
```

`[entry_points]` 段跟 setuptools 的方式相同。

到此，我讲了三种编写使用 setup.py 的方法

- 使用命令行参数指定，一个一个将参数传递进去（极不推荐）
- 在 setup.py 中的setup函数中指定（推荐使用）
- 使用 pbr ，在 setup.cfg 中指定（易于管理，更推荐）

### 9. 如何使用 setup.py 构建包

1、构建源码发布包。

用于发布一个 Python 模块或项目，将源码打包成 tar.gz （用于 Linux 环境中）或者 zip 压缩包（用于 Windows 环境中）

```text
$ python setup.py sdist
```

那这种包如何安装呢

答案是，使用下一节即将介绍的 `setuptools` 中提供的 `easy_install` 工具。

```text
$ easy_install xxx.tar.gz
```

使用 sdist 将根据当前平台创建默认格式的存档。在类 Unix 平台上，将创建后缀后为 `.tar.gz` 的 gzip 压缩的tar文件分发包，而在Windows上为 ZIP 文件。

当然，你也可以通过指定你要的发布包格式来打破这个默认行为

```text
$ python setup.py sdist --formats=gztar,zip
```

你可以指定的格式有哪些呢？

创建一个压缩的tarball和一个zip文件。可用格式为：

![img](https://pic2.zhimg.com/80/v2-7416d2c5ffd4fde928d7bd214ea59d39_720w.jpg)

对以上的格式，有几点需要注意一下：

- 在版本3.5中才添加了对 `xztar` 格式的支持
- zip 格式需要你事先已安装相应的模块：zip程序或zipfile模块（已成为Python的标准库）
- ztar 格式正在弃用，请尽量不要使用

另外，如果您希望归档文件的所有文件归root拥有，可以这样指定

```text
python setup.py sdist --owner=root --group=root
```

2、构建二进制分发包。

在windows中我们习惯了双击 exe 进行软件的安装，Python 模块的安装也同样支持 打包成 exe 这样的二进制软件包。

```text
$ python setup.py bdist_wininst
```

而在 Linux 中，大家也习惯了使用 rpm 来安装包，对此你可以使用这条命令实现 rpm 包的构建

```text
$ python setup.py bdist_rpm
```

若你喜欢使用 easy_install 或者 pip 来安装离线包。你可以将其打包成 egg 包

```text
$ python setup.py bdist_egg
```

若你的项目，需要安装多个平台下，既有 Windows 也有 Linux，按照上面的方法，多种格式我们要执行多次命令，为了方便，你可以一步到位，执行如下这条命令，即可生成多个格式的进制

```text
$ python setup.py bdist
```

### 10. 如何使用 setup.py 安装包

正常情况下，我们都是通过以上构建的源码包或者二进制包进行模块的安装。

但在编写 setup.py 的过程中，可能不能一步到位，需要多次调试，这时候如何测试自己写的 setup.py 文件是可用的呢？

这时候你可以使用这条命令，它会将你的模块安装至系统全局环境中

```text
$ python setup.py install
```

如若你的项目还处于开发阶段，频繁的安装模块，也是一个麻烦事。

这时候你可以使用这条命令安装，该方法不会真正的安装包，而是在系统环境中创建一个软链接指向包实际所在目录。这边在修改包之后不用再安装就能生效，便于调试。

```text
$ python setup.py develop
```

### 11. 如何发布包到 PyPi？

通过上面的学习，你一定已经学会了如何打包自己的项目，若你觉得自己开发的模块非常不错，想要 share 给其他人使用，你可以将其上传到 PyPi （Python Package Index）上，它是 Python 官方维护的第三方包仓库，用于统一存储和管理开发者发布的 Python 包。

如果要发布自己的包，需要先到 pypi 上注册账号。然后创建 `~/.pypirc` 文件，此文件中配置 PyPI 访问地址和账号。如的.pypirc文件内容请根据自己的账号来修改。

典型的 .pypirc 文件

```text
[distutils]
index-servers = pypi

[pypi]
username:xxx
password:xxx
```

然后使用这条命令进行信息注册，完成后，你可以在 PyPi 上看到项目信息。

```text
$ python setup.py register
```

注册完了后，你还要上传源码包，别人才使用下载安装

```text
$ python setup.py upload
```

或者也可以使用 `twine` 工具注册上传，它是一个专门用于与 pypi 进行交互的工具，详情可以参考官网：[https://www.ctolib.com/twine.html，这里不详细讲了。](https://link.zhihu.com/?target=https%3A//www.ctolib.com/twine.html，这里不详细讲了。)

