#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

//定义全局变量
char time_string[100];
//定义互斥锁
pthread_mutex_t mutex;
int ll = 0;
//定义全局消费品结构体
struct consumer
{
  int number;
};

//定义字符串返回函数
char *get_time_string() {
  // 获取当前时间（以秒为单位，相对于1970年1月1日）
  time_t current_time = time(NULL);
  // 将时间转换为本地时间结构体
  struct tm* local_time = localtime(&current_time);
  // 将时间结构体转换为可读的字符串格式
  strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", local_time);
  return time_string;
}

//定义线程函数1作为消费者
void *consumer(void *arg) {
  while (1)
  {
    pthread_mutex_lock(&mutex);
    printf("Consumer: %s Consuming...\n",get_time_string());
    sleep(1);
    //检查库存
    if (((struct consumer *)arg)->number > 0) {
      ((struct consumer *)arg)->number--;
      printf("Consumer: %s Freight -1\n",get_time_string());
    } else {
      printf("Consumer: %s No more Freight wait producer...\n",get_time_string());
      ll++;
      if (ll == 10)
      {
        return NULL;
      }
      
    }
    printf("Consumer: %s Freight nuber is %d\n",get_time_string(), ((struct consumer *)arg)->number);
    pthread_mutex_unlock(&mutex);
    //生成0-10的随机数
    srand(time(NULL));  
    int sleep_time = rand() % 10 + 1;
    sleep(sleep_time);
  }
  return NULL;
}

//定义线程函数2作为生产者
void *producer(void *arg) {
  while (1)
  {
    pthread_mutex_lock(&mutex);
    printf("Producer: %s Producing...\n", get_time_string());
    sleep(1);
    ((struct consumer *)arg)->number++;
    printf("Producer: %s Freight +1\n", get_time_string());
    printf("Producer: %s Freight nuber is %d\n",get_time_string() ,((struct consumer *)arg)->number);
    pthread_mutex_unlock(&mutex);
    //睡眠2s
    sleep(2);
    if (((struct consumer *)arg)->number == 20)
    {
      return NULL;
    }
  }
  return NULL;
}


int main() {
  pthread_t thread1, thread2, thread3, thread4;
  
  //初始化互斥锁
  pthread_mutex_init(&mutex, NULL);
  
  struct consumer cons = {0};
  pthread_create(&thread1, NULL, producer, &cons);
  pthread_create(&thread2, NULL, consumer, &cons);
  pthread_create(&thread3, NULL, consumer, &cons);
  //pthread_create(&thread4, NULL, consumer, &cons);
  
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
  //pthread_join(thread4, NULL);
  
  pthread_mutex_destroy(&mutex);

  printf("All threads have finished.\n");

  return 0;
}
