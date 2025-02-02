#ifndef __TPOOL_H__
#define __TPOOL_H__

#include <stdio.h>
#include <stddef.h>
#ifdef __linux__
#include <pthread.h>
#else
#include <Windows.h>

#endif

struct tpool;
typedef struct tpool tpool_t;
typedef void (*thread_func_t)(void *arg);
tpool_t *tpool_create(size_t num);
void tpool_destroy(tpool_t* tm);

bool tpool_add_work(tpool_t* tm, thread_func_t func, void* arg);
void tpool_wait(tpool_t* tm);


struct tpool_work {
  thread_func_t func;
  void *arg;
  struct tpool_work *next;
};

typedef struct tpool_work tpool_work_t;


// TODO: FIND A WAY TO IMPLEMENT pthread types

// struct tpool {
//   tpool_work_t *work_first;
//   tpool_work_t *work_last;
//   pthread_mutex_t work_mutex;
//   pthread_cond_t work_cond;
//   pthread_cond_t working_cond;
//   size_t working_cnt;
//   size_t thread_cnt;
//   bool stop;
// };

#endif