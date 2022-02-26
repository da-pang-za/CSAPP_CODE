/* $begin sbufc */
#include "csapp.h"
#include "sbuf.h"
//生产者消费者模型
/* Create an empty, bounded, shared FIFO buffer with n slots */
/* $begin sbuf_init */
void sbuf_init(sbuf_t *sp, int n)
{
    sp->buf = Calloc(n, sizeof(int));
    sp->n = n;                       /* Buffer holds max of n items */
    sp->front = sp->rear = 0;        /* Empty buffer iff front == rear */
    //mutex操作锁  slots item 容量锁
    Sem_init(&sp->mutex, 0, 1);      /* Binary semaphore for locking 互斥 生产生产 生产消费 消费消费 */
    Sem_init(&sp->slots, 0, n);      /* Initially, buf has n empty slots 空位 */
    Sem_init(&sp->items, 0, 0);      /* Initially, buf has zero data items 已经使用的*/
}
/* $end sbuf_init */

/* Clean up buffer sp */
/* $begin sbuf_deinit */
void sbuf_deinit(sbuf_t *sp)
{
    Free(sp->buf);
}
/* $end sbuf_deinit */

/* Insert item onto the rear of shared buffer sp */
/* $begin sbuf_insert */
void sbuf_insert(sbuf_t *sp, int item)
{

    //如果先mutex：获取到mutex之后发现获取不到slots 需要等待其他线程增加slots 但是其他线程没有mutex 死锁
    //如果先slots：获取到slots之后发现获取不到mutex 此时其他线程可以获得item锁和mutex来增加slots
    P(&sp->slots);                          /* Wait for available slot */
    P(&sp->mutex);                          /* Lock the buffer */
    sp->buf[(++sp->rear)%(sp->n)] = item;   /* Insert the item */
    //解锁顺序和加锁相反
    V(&sp->mutex);                          /* Unlock the buffer */
    V(&sp->items);                          /* Announce available item */
}
/* $end sbuf_insert */

/* Remove and return the first item from buffer sp */
/* $begin sbuf_remove */
int sbuf_remove(sbuf_t *sp)
{
    int item;
    P(&sp->items);                          /* Wait for available item */
    P(&sp->mutex);                          /* Lock the buffer */
    item = sp->buf[(++sp->front)%(sp->n)];  /* Remove the item */
    V(&sp->mutex);                          /* Unlock the buffer */
    V(&sp->slots);                          /* Announce available slot */
    return item;
}
/* $end sbuf_remove */
/* $end sbufc */


