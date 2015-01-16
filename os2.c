#include <stdio.h>    
#include <stdlib.h>
#include <sys/sem.h>
#include <unistd.h>
#include <pthread.h>
#define WINDOWS_NUM 5   /*窗口数目*/
#define TICKETS_NUM 35  /*飞机票总数*/

static int sem_id;         /*全局变量，信号灯集ID*/
static int sold_tickets;   /*全局变量，已售出票数*/
union semun
{
  int val;
};
int InitSem();
int DelSem();
void P();
void V();
void SellTickets();

int main()
{
  pthread_t m[WINDOWS_NUM];
  int n;
 /*创建信号灯集*/
  sem_id=semget((key_t)1234,1,IPC_CREAT|0666);
  if(sem_id==-1)
  {
    printf("创建信号灯集失败！\n");
    exit(EXIT_FAILURE);
  }
  if(InitSem()!=0)
  {
    printf("初始化信号灯集失败！\n");
    exit(EXIT_FAILURE);
  }
  printf("start...\n");
  sold_tickets=0;
  srand(time(NULL));
  /*创建售票进程*/
  for(n=0;n<WINDOWS_NUM;n++)
  {
    if(pthread_create(m+n,NULL,(void *)SellTickets,NULL)!=0)
    {
      printf("创建线程失败！\n");
      exit(EXIT_FAILURE);
    }
  }
  /*线程等待*/
  for(n=0;n<WINDOWS_NUM;n++)
  {
    if(pthread_join(m[n],NULL)!=0)
    {
      perror("线程加入等待队列失败！\n");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
  }
}
int InitSem()
{
  union semun arg;
  arg.val=1;        /*默认信号灯初值为1*/
  if(semctl(sem_id,0,SETVAL,arg)==-1)
  {
    printf("初始化失败！\n");
    exit(EXIT_FAILURE);
  }
  return 0;
}

int DelSem()
{
  union semun arg;
  if(semctl(sem_id,0,IPC_RMID,arg)==-1)
  {
    printf("删除信号灯集失败！\n");
    exit(EXIT_FAILURE);
  }
  return 0;
}
void P()
{
  struct sembuf sop;
  sop.sem_num=0;
  sop.sem_op=-1;
  sop.sem_flg=0;
  semop(sem_id,&sop,1);
}

void  V()
{
  struct sembuf sop;
  sop.sem_num=0;
  sop.sem_op=1;
  sop.sem_flg=0;
  semop(sem_id,&sop,1);
}
void SellTickets()
{
  while(1)
  {
    usleep(400);
    P();
    printf("第%ld售票线程正售出第%d张机票。\n",pthread_self(),++sold_tickets);
    if(sold_tickets==TICKETS_NUM)
    {
      DelSem();
      printf("机票已售完。\n");
      exit(EXIT_SUCCESS);
    }
    V();
  }
}

