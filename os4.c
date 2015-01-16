#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 20
#define PRODUCERS 4
#define CONSUMERS 4
#define NUM_PRO 40

int InitSem();    //信号灯集初始化
int DelSem();     //删除信号灯集
void P(int semno); //P操作
void V(int semno); //V操作
void Producer();   //生产者函数
void Consumer();   //消费者函数   

static int sem_id,shm_id;  /*信号灯集ID,共享存储区ID*/
union semun
{
  int val;
};
int main()
{
  int i,shm_id;
  int n=NUM_PRO;
  int*  addr;
  sem_id=semget((key_t)1234,3,IPC_CREAT|0666);
  if(sem_id==-1)
  {
    printf("创建信号灯集失败！\n");
    exit(EXIT_FAILURE);
  }
  /*初始化信号灯集*/
  if(InitSem()!=0)
  {
    printf("初始化信号灯集失败！\n");
    exit(EXIT_FAILURE);
  }
  /*创建共享内存区*/
  shm_id=shmget((key_t)4444,SHM_SIZE,0666|IPC_CREAT);
  if(shm_id==-1)
  {
    printf("创建缓冲区失败！\n");
    exit(EXIT_FAILURE);
  }
  addr=shmat(shm_id,0,0);
  if(addr==NULL)
  {
    printf("得到虚地址失败！\n");
    exit(EXIT_FAILURE);
  }
  /*共享内存区初始化*/
  for(i=0;i<SHM_SIZE+3;i++)addr[i]=0;   /* */
  /*创建子进程*/
  for(i=0;i<PRODUCERS;i++)if(fork()==0)Producer();
  for(i=0;i<CONSUMERS;i++)if(fork()==0)Consumer();
  for( i=0; i<PRODUCERS+CONSUMERS; i++ ) wait();
  return 1;
}

/*初始化信号灯集*/
/*第一个信号灯full，表示满缓冲区的数目，初值为0*/
/*第二个信号灯empty，表示空缓冲区的数目，初值为共享缓冲区大小*/
/*第三个信号灯mutex，表示对缓冲区进行操作的互斥,初值为1*/
int InitSem()
{
  union semun arg;
  arg.val=0;
  if(semctl(sem_id,0,SETVAL,arg)==-1)
  {
    printf("信号灯1初始化失败！\n");
    exit(EXIT_FAILURE);
  }
  arg.val=SHM_SIZE;
  if(semctl(sem_id,1,SETVAL,arg)==-1)
  {
    printf("信号灯2初始化失败！\n");
    exit(EXIT_FAILURE);
  }
  arg.val=1;
  if(semctl(sem_id,2,SETVAL,arg)==-1)
  {
    printf("信号灯3初始化失败！\n");
    exit(EXIT_FAILURE);
  }
  return 0;
}

/*删除信号灯集*/
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

void Producer()
{
  int shm_id,x,i,n;
  int* addr;

  shm_id=shmget((key_t)4444,SHM_SIZE,0666);
  addr=shmat(shm_id,0,0);
  for(i=0;i<10;i++)
  {
    x=rand()%10;
    P(1);
    P(2);
    for(n=0;addr[n]!=0;n++);
    addr[n]=x;
    printf("%d生产：%d\n",getpid(),addr[n]);
    V(2);
    V(0);
  }
   exit( EXIT_SUCCESS );    
}

void Consumer()
{
  int shm_id,i,n;
  int* addr;
  shm_id=shmget((key_t)4444,SHM_SIZE,0666);
  addr=shmat(shm_id,0,0);
  for(i=0;i<10;i++)
  {
    P(0);
    P(2);
    for(n=0;addr[n]==0;n++);
    printf("%d消费：%d\n",getpid(),addr[n]);
    V(2);
    V(1);
  }
   exit( EXIT_SUCCESS );
}

