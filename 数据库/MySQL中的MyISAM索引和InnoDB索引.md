# MySQL中的MyISAM索引和InnoDB索引

MyISAM引擎使用B+Tree作为索引结构，叶节点的data域存放的是数据记录。

## MyISAM索引

MyISAM引擎使用B+Tree作为索引结构，叶节点的data域存放的是数据记录的地址。下图是MyISAM索引的原理图：

![8-a](https://github.com/enpeizhao/duck_db/raw/master/md_image/8-a.png)

这里设表一共有三列，假设我们以Col1为主键，则上图是一个MyISAM表的主索引（Primary key）示意。可以看出MyISAM的索引文件仅仅保存数据记录的地址。

## **InnoDB索引**

虽然InnoDB也使用B+Tree作为索引结构，但具体实现方式却与MyISAM截然不同。

第一个重大区别是InnoDB的数据文件本身就是索引文件。从上文知道，MyISAM索引文件和数据文件是分离的，索引文件仅保存数据记录的地址。而在InnoDB中，表数据文件本身就是按B+Tree组织的一个索引结构，这棵树的叶节点data域保存了完整的数据记录。这个索引的key是数据表的主键，因此InnoDB表数据文件本身就是主索引。

[![10](https://github.com/enpeizhao/duck_db/raw/master/md_image/10.png)](https://github.com/enpeizhao/duck_db/blob/master/md_image/10.png)