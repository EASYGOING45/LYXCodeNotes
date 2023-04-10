# Linux下的I/O多路复用机制

I/O多路复用机制，重点讲解`select、poll、epoll`这几个关键字。

## select、poll、epoll

select、poll、epoll都是IO多路复用的机制。I/O多路复用就是通过一种控制机制，一个进程可以监视多个描述符，一旦某个描述符就绪（一般是读就绪或者写就绪），能够通知程序进行相应的读写操作。

但select、poll、epoll本质上都是同步I/O，因为他们都需要在读写事件就绪后，自己负责进行读写，也就是说这个读写过程是阻塞的，而异步I/O则无需自己负责进行读写，异步I/O的实现会负责把数据从内核拷贝到用户空间。

## select

缺点：

- fd_set数组实现
  - fd_size有限制，1024bitmap，默认就是1024个线程fd[i]=accept()
  - fdset不可重用，新的fd进来，需要重新创建
  - 用户态和内核态拷贝产生开销
  - O(n)时间复杂度的轮询成功调用返回结果大于0，出错返回结果为-1，超时返回结果为0，具有超时时间

## poll

基于结构体存储pollfd，改进也是基于这个结构体，用的是链表而不再是数组了

```C
struct pollfd
{
	int fd;
	short events;	//在意的事件
	poolin poolout;
	short revents;	//可重用
};
```

解决了select的1,2两点缺点

有数据；置位revents 再返回，然后再恢复为0，也就是说poolfd又恢复成了最初的样子

## epoll

解决select的1，2，3，4不需要轮询，时间复杂度为O(1)epoll_create 创建一个白板 存放fd_eventsepoll_ctl 用于向内核注册新的描述符或者是改变某个文件描述符的状态。已注册的描述符在内核中会被维护在一棵红黑树上epoll_wait 通过回调函数内核会将 I/O 准备好的描述符加入到一个链表中管理，进程调用 epoll_wait() 便可以得到事件完成的描述符