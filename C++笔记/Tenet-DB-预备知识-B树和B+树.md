# Tenet-DB-预备知识-B树和B+树

https://github.com/enpeizhao/duck_db

https://segmentfault.com/a/1190000020416577

## 索引

数据库一般会操作海量的数据，这些数据都是存在磁盘上的。查询是数据库的最主要功能之一，我们可以将查询的过程类比在词典中查单词，显然，我们都希望查询数据的速度尽可能的快。

![image-20230816163107892](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230816163107892.png)

假设我们在词典中查询`hash`这个单词，有两种方式可以选择：第一种是从`A->H`一个个遍历；二是按照上图中圈红的方式，先找到H，再看单词第二个字母，再看第三个....显然，通常使用的是第二种方式，圈红的字母即为`索引(index)`。

> MySQL官方对索引的定义为：索引（index）是帮助MySQL高效获取数据的数据结构。提取句子主干，就可以得到索引的本质：索引是一种数据结构！

最基本的查询算法当然是[顺序查找](http://en.wikipedia.org/wiki/Linear_search)（linear search），这种复杂度为`O(n)`的算法在数据量很大时显然是糟糕的，随着计算机科学的发展，我们先后发明了[二分查找](http://en.wikipedia.org/wiki/Binary_search_algorithm)（binary search）、[二叉树查找](http://en.wikipedia.org/wiki/Binary_search_tree)（binary tree search）等算法。每种查找算法都只能应用于特定的数据结构之上，例如二分查找要求被检索数据有序，而二叉树查找只能应用于[二叉查找树](http://en.wikipedia.org/wiki/Binary_search_tree)上，但是数据本身的组织结构不可能完全满足各种数据结构（例如，理论上不可能同时将两列都按顺序进行组织），所以，在数据之外，数据库系统还维护着满足特定查找算法的数据结构，这些数据结构以某种方式引用（指向）数据，这样就可以在这些数据结构上实现高级查找算法，这种数据结构即为索引。

![img](https://happygoing.oss-cn-beijing.aliyuncs.com/img/6.png)

上图展示了一种可能的索引方式。左边是数据表，共有两列七条记录，最左边的是数据记录的物理地址（注意逻辑上相邻的记录在磁盘上并不是一定物理相邻的）。为了加快`Col2`的查找，可以维护一个右边所示二叉查找树，每个节点分别包含索引键值和一个指向对应数据记录物理地址的指针，这样就可以运用二叉查找在低复杂度内获取到响应数据。

| Unsorted Array of rows | Sorted Array of rows | Tree of nodes |                                  |
| ---------------------- | -------------------- | ------------- | -------------------------------- |
| Pages contain          | only data            | only data     | metadata, primary keys, and data |
| Rows per page          | more                 | more          | fewer                            |
| Insertion              | O(1)                 | O(n)          | O(log(n))                        |
| Deletion               | O(n)                 | O(n)          | O(log(n))                        |
| Lookup by id           | O(n)                 | O(log(n))     | O(log(n)                         |

目前大部分数据库系统及文件系统都采用B-Tree或其变种B+Tree作为索引结构，没有使用二叉查找树或其进化品种[红黑树](http://en.wikipedia.org/wiki/Red-black_tree)（red-black tree）的原因请参见这篇文章：http://www.cnblogs.com/serendipity-fly/p/9300360.html

## B树与B+树

维基百科对B树的定义为“在计算机科学中，B树（B-tree）是一种树状数据结构，它能够存储数据、对其进行排序并允许以O(log n)的时间复杂度运行进行查找、顺序读取、插入和删除的数据结构。B树，概括来说是一个节点可以拥有多于2个子节点的二叉查找树。与自平衡二叉查找树不同，B-树为系统最优化**大块数据的读和写操作**。B-tree算法减少定位记录时所经历的中间过程，从而加快存取速度。普遍运用在**数据库**和**文件系统**。”

**B树**

**B 树**可以看作是对2-3查找树的一种扩展，即他允许每个节点有M-1个子节点。

- 根节点至少有两个子节点；
- 每个节点有M-1个key，并且以升序排列；
- 位于M-1和M key的子节点的值位于M-1 和M key对应的Value之间；
- 其它节点至少有M/2个子节点；

下图是一个M=4 阶的B树：

![7](https://happygoing.oss-cn-beijing.aliyuncs.com/img/7.png)

下面是往B树中依次插入

**6 10 4 14 5 11 15 3 2 12 1 7 8 8 6 3 6 21 5 15 15 6 32 23 45 65 7 8 6 5 4**

的演示动画：

![bb](https://happygoing.oss-cn-beijing.aliyuncs.com/img/bb.gif)

**B+树**

**B+**树是对B树的一种变形树，它与B树的差异在于：

- 有k个子结点的结点必然有k个关键码；
- 非叶结点仅具有索引作用，跟记录有关的信息均存放在叶结点中。
- 树的所有叶结点构成一个有序链表，可以按照关键码排序的次序遍历全部记录。

如下图，是一个B+树：

![9](https://happygoing.oss-cn-beijing.aliyuncs.com/img/9.png)

下面是往B+树中依次插入

**6 10 4 14 5 11 15 3 2 12 1 7 8 8 6 3 6 21 5 15 15 6 32 23 45 65 7 8 6 5 4**

的演示动画：

![b+](U:\duck_db-master\md_image\b+.gif)

B和B+树的区别在于，B+树的非叶子结点只包含导航信息，不包含实际的值，所有的叶子结点和相连的节点使用链表相连，便于区间查找和遍历。

**B+ 树的优点在于：**

- 由于B+树在内部节点上不包含数据信息，因此在内存页中能够存放更多的key。 数据存放的更加紧密，具有更好的空间局部性。因此访问叶子节点上关联的数据也具有更好的缓存命中率。
- B+树的叶子结点都是相链的，因此对整棵树的便利只需要一次线性遍历叶子结点即可。而且由于数据顺序排列并且相连，所以便于区间查找和搜索。而B树则需要进行每一层的递归遍历。相邻的元素可能在内存中不相邻，所以缓存命中性没有B+树好。

但是B树也有优点，其优点在于，由于B树的每一个节点都包含key和value，因此经常访问的元素可能离根节点更近，因此访问也更迅速。下面是B 树和B+树的区别图：

![8](https://happygoing.oss-cn-beijing.aliyuncs.com/img/8.png)
