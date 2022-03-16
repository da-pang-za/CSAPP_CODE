## 介绍  

前辈实现的基于epoll的web server  nginx核心
## 学习进度
todo:HTTP
### non-blocking好处/blocking IO缺点：
* BIO占用线程多(线程数=连接数) 上下文切换开销大 创建销毁线程开销大(可用线程池优化)
* BIO无法配合事件驱动  因为阻塞了
* 参考阿里知乎 https://www.zhihu.com/question/382972191

### 单线程处理所有handler缺点：
* 可能会有某个事件处理占用时间太长，其他事件得不到执行(饥饿)
阻塞是什么：CSAPP p511

fd饥饿
* p1123

Zaver
=====

Yet another fast and efficient HTTP server.

## purpose

The purpose of Zaver is to help developers understand how to write a high performance server based on epoll. Although Nginx is a good learning example, its complexity and huge code base make people discouraged. Zaver uses as few codes as possible to demonstrate the core structure of high performance server like Nginx. Developers can lay a solid foundation by learning Zaver for further study in network programming.

## programming model

* epoll
* non-blocking I/O
* thread-pool

## compile and run (for now only support Linux2.6+)

please make sure you have [cmake](https://cmake.org/) installed.
```
mkdir build && cd build
cmake .. && make
cd .. && ./build/zaver -c zaver.conf
```

## support

* HTTP persistent connection
* browser cache
* timer(use binary heap instead of rbtree used in Nginx)

## todo

* sendfile
* proxy
* FastCGI
* other HTTP/1.1 features
* memory pool
* WebDAV?

## more details

https://zyearn.github.io/blog/2015/05/16/how-to-write-a-server/

