
/*
 * Copyright (C) Zhu Jiashun
 * Copyright (C) Zaver
 */

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "dbg.h"
#include "error.h"

#define ZV_PQ_DEFAULT_SIZE 10

typedef int (*zv_pq_comparator_pt)(void *pi, void *pj);

typedef struct {
    void **pq;//数组 元素是请求
    size_t nalloc;//实际使用的
    size_t size;//已经分配的 不包括位置0 使用从1开始 因此实际能用的是size-1
    zv_pq_comparator_pt comp;
} zv_pq_t;
//comp比较函数   size为初始数组大小 不包括位置0
int zv_pq_init(zv_pq_t *zv_pq, zv_pq_comparator_pt comp, size_t size);
int zv_pq_is_empty(zv_pq_t *zv_pq);
size_t zv_pq_size(zv_pq_t *zv_pq);
void *zv_pq_min(zv_pq_t *zv_pq);
int zv_pq_delmin(zv_pq_t *zv_pq);
int zv_pq_insert(zv_pq_t *zv_pq, void *item);

int zv_pq_sink(zv_pq_t *zv_pq, size_t i);
#endif 
