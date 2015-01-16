#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <unistd.h>
#include <pthread.h>

#define CAL_NUM 5            /*运算次数*/
int x, y ;
static int z[CAL_NUM];     /*全局变量定义缓冲区*/
static int sem_id;         /*全局变量，信号灯集ID*/

union semun
{
  int val;
};

int InitSem(); // 信号灯集初始化
int DelSem(); //删除信号灯
void P(int semno); // p 操作
void V(int semno); // v 操作
void Add();  //计算数据
void Printf(); //输出数据

int main()
{
  pthread_t m,n;
  /*创建信号灯集,该信号灯集中有两个信号灯*/
  /*第一个信号灯表示缓冲区是否为空，第二个信号灯表示缓冲区内是否有数据*/
  sem_id=semget((key_t)1234,2,IPC_CREAT|0666);
  if(sem_id==-1)
  {
    printf("创建信号灯集失败！\n");
    exit(EXIT_FAILURE);
  }
/*初始化信号灯集，第一个信号灯初始值为1,第二个信号灯初始值为0*/
  if(InitSem()!=0)
  {
    printf("初始化信号灯集失败！\n");
    exit(EXIT_FAILURE);
  }
  /*创建计算线程*/
  if(pthread_create(&m,NULL,(void *)Add,NULL)!=0)
  {
    printf("创建计算线程失败！\n");
    exit(EXIT_FAILURE);
  }
  if(pthread_create(&n,NULL,(void *)Printf,NULL)!=0)
  {
    printf("创建输出线程失败！\n");
    exit(EXIT_FAILURE);
  }
  /*计算线程等待*/
  if(pthread_join(m,NULL)!=0)
  {
      perror("计算线程加入等待队列失败！\n");
      exit(EXIT_FAILURE);
  }
/*输出线程等待*/
  if(pthread_join(n,NULL)!=0)
  {
      perror("输出线程加入等待队列失败！\n");
      exit(EXIT_FAILURE);
  }
  if(DelSem()!=0)
  {
    printf("删除信号灯失败！\n");
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}

int InitSem()
{
  union semun arg;
  arg.val=1;        /*默认信号灯1初值为1*/
  if(semctl(sem_id,0,SETVAL,arg)==-1)
  {
    printf("信号灯1初始化失败！\n");
    exit(EXIT_FAILURE);
  }
arg.val=0;
  if(semctl(sem_id,1,SETVAL,arg)==-1)
  {
    printf("信号灯2初始化失败！\n");
    exit(EXIT_FAILURE);
  }
  return 0;
}

int DelSem()
{
  union semun arg;
  int i;
  for(i=0;i<2;i++)
  {
    if(semctl(sem_id,i,IPC_RMID,arg)==-1)
    {
      printf("删除信号灯%d失败！\n",(i+1));
      exit(EXIT_FAILURE);
    }
  }
  return 0;
}
void P(int semno)
{
  struct sembuf sop;
  sop.sem_num=semno;
  sop.sem_op=-1;
  sop.sem_flg=0;
  semop(sem_id,&sop,1);
}

void V(int semno)
{
  struct sembuf sop;
  sop.sem_num=semno;
  sop.sem_op=1;
  sop.sem_flg=0;
  semop(sem_id,&sop,1);
}

void Add()
{
  int i;
  for(i=0;i<CAL_NUM;i++)
  {
     P(0);
     x=rand()%10;
     y=rand()%10;
     z[i]=x+y;
     printf("计算 %ld: x=%d,y=%d",pthread_self(),x,y);
     V(1);
     usleep(400);
  }
}

void Printf()
{
  int i;
  for(i=0;i<CAL_NUM;i++)
  {
    P(1);
    printf("输出 %d+%d=%d\n",x,y,z[i]);
    V(0);
  }
}

