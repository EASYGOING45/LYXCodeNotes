# 计网归档-Pt6

## 40、使用Session的过程是怎样的？

过程如下：

- 用户进行登录时，用户提交包含用户名和密码的表单，放入 HTTP 请求报文中；
- 服务器验证该用户名和密码，如果正确则把用户信息存储到 Redis 中，它在 Redis 中的 Key 称为 Session ID；
- 服务器返回的响应报文的 Set-Cookie 首部字段包含了这个 Session ID，客户端收到响应报文之后将该 Cookie 值存入浏览器中；
- 客户端之后对同一个服务器进行请求时会包含该 Cookie 值，服务器收到之后提取出 Session ID，从 Redis 中取出用户信息，继续之前的业务操作。

> Session ID 的安全性问题，不能让它被恶意攻击者轻易获取，那么就不能产生一个容易被猜到的 Session ID 值。此外，还需要经常重新生成 Session ID。在对安全性要求极高的场景下，例如转账等操作，除了使用 Session 管理用户状态之外，还需要对用户进行重新验证，比如重新输入密码，或者使用短信验证码等方式。

## 41、Session和Cookie应该如何选择（使用场景）

- Cookie只能存储ASCII码字符串，而Session则可以存储任何类型的数据，因此在考虑数据复杂性时首选Session
- Cookie存储在浏览器中，容易被恶意查看。如果非要将一些隐私数据存储在Cookie中，可以将Cookie值进行加密，然后在服务器进行解密。
- 对于大型网站，如果用户所有的信息都存储在Session中，那么开销是非常大的，因此不建议将所有的用户信息都存储到Session中

## 42、Cookies和Session的区别

Cookie和Session都是客户端与服务器之间保持状态的解决方案 

1，存储的位置不同，cookie：存放在客户端，session：存放在服务端。Session存储的数据比较安全 

2，存储的数据类型不同 两者都是key-value的结构，但针对value的类型是有差异的 cookie：value只能是字符串类型，session：value是Object类型 

3，存储的数据大小限制不同 cookie：大小受浏览器的限制，很多是是4K的大小， session：理论上受当前内存的限制， 

4，生命周期的控制 cookie的生命周期当浏览器关闭的时候，就消亡了 

(1)cookie的生命周期是累计的，从创建时，就开始计时，20分钟后，cookie生命周期结束，

 (2)session的生命周期是间隔的，从创建时，开始计时如在20分钟，没有访问session，那么session生命周期被销毁

## 43、DDos攻击了解吗？

客户端向服务端发送请求链接数据包，服务端向客户端发送确认数据包，客户端不向服务端发送确认数据包，服务器一直等待来自客户端的确认，没有彻底根治的方法，除非不适用TCP。

DDOS的预防：

- 限制同时打开SYN半链接的数目
- 缩短SYN半链接的Time Out时间
- 关闭不必要的服务

## 44、MTU和MSS分别是什么？

MTU：maximum transmission unit，最大传输单元，由硬件规定，如以太网的MTU为1500字节。

MSS：maximum segment size ，最大分节大小，为TCP数据包每次传输的最大数据分段大小，一般由发送端向对端TCP通知对端在每个分节中能发送的最大TCP数据。MSS值为MTU值减去IPv4 Header（20 Byte）和TCP Header（20 Byte）得到。                                                                                                       

## 45、HTTP中有个缓存机制，但如何保证缓存是最新的呢？（缓存过期机制）

max-age指令出现在请求报文，并且缓存资源的缓存时间小于该指令指定的时间，那么就能接受该缓存。

max-age指令出现在响应报文，表示缓存资源在缓存服务器中保存的时间。

```C
Cache-Control: max-age=31536000
```

Expires首部字段也可以用于告知缓存服务器该资源什么时候会过期。 

```C
Expires: Wed, 04 Jul 2012 08:26:05 GMT
```

- 在 HTTP/1.1 中，会优先处理 max-age 指令；
- 在 HTTP/1.0 中，max-age 指令会被忽略掉。