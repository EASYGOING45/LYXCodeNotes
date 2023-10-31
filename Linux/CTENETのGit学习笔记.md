# CTENETのGit学习笔记

##  vim IDE 工具

- [VIM 一键 IDE](https://github.com/meetbill/Vim)

## 1.2 Git 分布式管理系统

### 1.2.1 Git 基础

**环境配置**

- `git config --global user.name your_name` : 设置你的用户名，提交会显示
- `git config --global user.email your_email` : 设置你的邮箱
- `git config core.quotepath false` : 解决中文文件名显示为数字问题

**基本操作**

- `git init` : 初始化一个 git 仓库
- `git add <filename>` : 添加一个文件到 git 仓库中
- `git commit -m "commit message"`: 提交到本地
- `git push [remote-name] [branch-name]` : 把本地的提交记录推送到远端分支
- `git pull`: 更新仓库 `git pull` = `git fetch` + `git merge`
- `git checkout -- <file>` : 还原未暂存 (staged) 的文件
- `git reset HEAD <file>...` : 取消暂存，那么还原一个暂存文件，应该是先 `reset` 后 `checkout`
- `git stash` : 隐藏本地提交记录，恢复的时候 `git stash pop`。这样可以在本地和远程有冲突的情况下，更新其他文件

**分支**

- `git branch <branch-name>` : 基于当前 commit 新建一个分支，但是不切换到新分支
- `git branch -r` : 查看远程的所有分支（常用）
- `git checkout -b <branch-name>` : 新建并切换分支
- `git checkout <branch-name>` : 切换分支(常用)
- `git branch -d <branch-name>` : 删除分支
- `git push origin <branch-name>` : 推送本地分支
- `git checkout -b <local-branch-name> origin/<origin-branch-name>` : 基于某个远程分支新建一个分支开发
- `git checkout --track origin/<origin-branch-name>` : 跟踪远程分支（创建跟踪远程分支，Git 在 `git push` 的时候不需要指定 `origin` 和 `branch-name` ，其实当我们 `clone` 一个 repo 到本地的时候，`master` 分支就是 origin/master 的跟踪分支，所以提交的时候直接 `git push`)。
- `git push origin :<origin-branch-name>` : 删除远程分支

实践 --- 主分支 Master/ 开发分支 Develop

```
主分支只用来分布重大版本，日常开发应该在另一条分支上完成。我们把开发用的分支，叫做 Develop。

# Git 创建 Develop 分支
git checkout -b develop master

# 将 Develop 分支发布到 Master 分支

# 切换到 Master 分支
git checkout master

# 对 Develop 分支进行合并
git merge --no-ff develop
上一条命令的 --no-ff 参数是什么意思。默认情况下，Git 执行"快进式合并"（fast-farward merge），会直接将 Master 分支指向 Develop 分支。

# 删除本地分支
git branch -d develop
```

**标签**

- `git tag -a <tagname> -m <message>` : 创建一个标签（用 -a 指定标签名，-m 指定说明文字） 如 `git tag -a v1.0 -m "version 1.0 released mitaka"`
- `git tag` : 显示已有的标签
- `git show tagname`: 显示某个标签的详细信息
- `git push origin v1.0` push 到远端仓库 如`git push -u ${PWD##*/} master v1.0`
- `git checkout -b <tag-name>` : 基于某个 tag 创建一个新的分支

**Git shortcuts/aliases**

```
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.st status
```

### 1.2.2 知识点

基本命令让你快速的上手使用 Git，知识点能让你更好的理解 Git。

**文件的几种状态**

- untracked: 未被跟踪的，没有纳入 Git 版本控制，使用 `git add <filename>` 纳入版本控制
- unmodified: 未修改的，已经纳入版本控制，但是没有修改过的文件
- modified: 对纳入版本控制的文件做了修改，git 将标记为 modified
- staged: 暂存的文件，简单理解：暂存文件就是 add 之后，commit 之前的文件状态

理解这几种文件状态对于理解 Git 是非常关键的（至少可以看懂一些错误提示了）。

**快照和差异**

详细可看：[Pro Git: Git 基础](http://iissnan.com/progit/html/zh/ch1_3.html) 中有讲到 *直接记录快照，而非差异比较*，这里只讲我个人的理解。

Git 关心的是文件数据整体的变化，其他版本管理系统（以 svn 为例）关心的某个具体文件的*差异*。这个差异是好理解的，也就是两个版本具体文件的不同点，比如某一行的某个字符发生了改变。

Git 不保存文件提交前后的差异，不变的文件不会发生任何改变，对于变化的文件，前后两次提交则保存两个文件。举个例子：

SVN:

1. 新建 3 个文件 a, b, c，做第一次提交 -> `version1 : file_a file_b file_c`
2. 修改文件 b， 做第二次提交（真正提交的是 修改后的文件 b 和修改前的 `file_b` 的 diff) -> `version2: diff_b_2_1`
3. 当我要 checkout version2 的时候，实际上得到的是 `file_a file_b+diff_b_2_1 file_c`

Git:

1. 新建 3 个文件 a, b, c，做第一次提交 -> `version1 : file_a file_b file_c`
2. 修改文件 b （得到`file_b1`), 做第二次提交 -> `version2: file_a file_b1 file_c`
3. 当我要用 version2 的时候，实际上得到的是 `file_a file_b1 file_c`

上面的 `file_a file_b1 file_c` 就是 version2 的 *快照*。

**Git 数据结构**

Git 的核心数是很简单的，就是一个链表（或者一棵树更准确一些？无所谓了），一旦你理解了它的基本数据结构，再去看 Git，相信你有不同的感受。继续用上面的例子（所有的物理文件都对应一个 SHA-1 的值）

当我们做第一次提交时，数据结构是这样的：

```
sha1_2_file_map:
    28415f07ca9281d0ed86cdc766629fb4ea35ea38 => file_a
    ed5cfa40b80da97b56698466d03ab126c5eec5a9 => file_b
    1b5ca12a6cf11a9b89dbeee2e5431a1a98ea5e39 => file_c

commit_26b985d269d3a617af4064489199c3e0d4791bb5:
    base_info:
        Auther: "JerryZhang(chinajiezhang@gmail.com)"
        Date: "Tue Jul 15 19:19:22 2014 +0800"
        commit_content: "第一次提交"
    file_list:
        [1]: 28415f07ca9281d0ed86cdc766629fb4ea35ea38
        [2]: ed5cfa40b80da97b56698466d03ab126c5eec5a9
        [3]: 1b5ca12a6cf11a9b89dbeee2e5431a1a98ea5e39
        pre_commit: null
    next_commit: null
```

当修改了 `file_b`, 再提交一次时，数据结构应该是这样的：

```
sha1_2_file_map:
    28415f07ca9281d0ed86cdc766629fb4ea35ea38 => file_a
    ed5cfa40b80da97b56698466d03ab126c5eec5a9 => file_b
    1b5ca12a6cf11a9b89dbeee2e5431a1a98ea5e39 => file_c
    39015ba6f80eb9e7fdad3602ef2b1af0521eba89 => file_b1

commit_26b985d269d3a617af4064489199c3e0d4791bb5:
    base_info:
        Auther: "JerryZhang(chinajiezhang@gmail.com)"
        Date: "Tue Jul 15 19:19:22 2014 +0800"
        commit_content: "第一次提交"
    file_list:
        [1]: 28415f07ca9281d0ed86cdc766629fb4ea35ea38
        [2]: ed5cfa40b80da97b56698466d03ab126c5eec5a9
        [3]: 1b5ca12a6cf11a9b89dbeee2e5431a1a98ea5e39
    pre_commit: commit_a08a57561b5c30b9c0bf33829349e14fad1f5cff
    next_commit: null

commit_a08a57561b5c30b9c0bf33829349e14fad1f5cff:
    base_info:
        Auther: "JerryZhang(chinajiezhang@gmail.com)"
        Date: "Tue Jul 15 22:19:22 2014 +0800"
        commit_content: "更新文件 b"
    file_list:
        [1]: 28415f07ca9281d0ed86cdc766629fb4ea35ea38
        [2]: 39015ba6f80eb9e7fdad3602ef2b1af0521eba89
        [3]: 1b5ca12a6cf11a9b89dbeee2e5431a1a98ea5e39
    pre_commit: null
    next_commit: commit_26b985d269d3a617af4064489199c3e0d4791bb5
```

当提交完第二次的时候，执行 `git log`，实际上就是从 `commit_a08a57561b5c30b9c0bf33829349e14fad1f5cff` 开始遍历然后打印 `base_info` 而已。

实际的 git 实际肯定要比上面的结构 (（的信息）的）要复杂的多，但是它的核心思想应该是就是，每一次提交就是一个新的结点。通过这个结点，我可以找到所有的快照文件。再思考一下，什么是分支？什么是 Tags，其实他们可能只是某次提交的引用而已（一个 `tag_head_node` 指向了某一次提交的 node)。再思考怎么回退一个版本呢？指针偏移！依次类推，上面的基本命令都可以得到一个合理的解释。

**理解 git fetch 和 git pull 的差异**

上面我们说过 `git pull` 等价于 `git fetch` 和 `git merge` 两条命令。当我们 `clone` 一个 repo 到本地时，就有了本地分支和远端分支的概念（假定我们只有一个主分支），本地分支是 `master`，远端分支是 `origin/master`。通过上面我们对 Git 数据结构的理解，`master` 和 `origin/master` 可以想成是指向最新 commit 结点的两个指针。刚 `clone` 下来的 repo，`master` 和 `origin/master` 指针指向同一个结点，我们在本地提交一次，`origin` 结点就更新一次，此时 `master` 和 `orgin/master` 就不再相同了。很有可能别人已经 commit 改 repo 很多次了，并且进行了提交。那么我们的本地的 `origin/master` 就不再是远程服务器上的最新的位置了。 `git fetch` 干的就是从服务器上同步服务器上最新的 `origin/master` 和一些服务器上新的记录 / 文件到本地。而 `git merge` 就是合并操作了（解决文件冲突）。`git push` 是把本地的 `origin/master` 和 `master` 指向相同的位置，并且推送到远程的服务器。

### 1.2.3 其他操作

#### **解决 GitHub commit 次数过多.git 文件过大**

完全重建版本库

```
# rm -rf .git
# git init
# git add .
# git commit -a -m "[Update] 合并之前所有 commit"
# git remote add origin <your_github_repo_url>
# git push -f -u origin master
```

#### **HTTP request failed**

使用 git clone 失败

```
[root@localhost ~]# git clone https://github.com/meetbill/Vim.git
Initialized empty Git repository in /root/Vim/.git/
error:  while accessing https://github.com/meetbill/Vim.git/info/refs

fatal: HTTP request failed
```

解决方法

```
#git config --global http.sslVerify false
```

#### 设置 Wiki 只能自己编写，其他人员只读

在项目中的设置中勾选`Restrict editing to collaborators only`

#### 修改最后一次 commit 操作

有时候我们提交完了才发现漏掉了几个文件没有加，或者提交信息写错了。想要撤消刚才的提交操作，可以使用 --amend 选项重新提交：

```
$ git commit -a -m 'initial commit'
$ git add forgotten_file
$ git commit --amend -m 'new commit'
```

### 1.2.4 Git tips

(1) 命令简化

```
cd git_repo（替换为项目名字）
git remote add ${PWD##*/} git@github.com:meetbill/${PWD##*/}.git
git push -u ${PWD##*/} master
```

(2) 提升 git 使用体验

> - [git 命令自动补全](https://github.com/meetbill/op_practice_code/tree/master/Linux/tools/git/git-completion)
> - [命令行显示 git 信息](https://github.com/meetbill/op_practice_code/tree/master/Linux/tools/git/git-ps1)