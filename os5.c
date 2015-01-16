#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<unistd.h>
#include<queue>
#include <iostream>
#include<pwd.h>
#include<grp.h>
 
using namespace std; 

int main()
{
  string a;
  string b;
  DIR* dir;
  struct dirent *read;
  struct stat buf;
  queue<string>q;
  cout<<"请输入路径："<<endl;
  cin>>a;
  q.push(a);
  while(q.size()!=0)
  {
    b=q.front();
    q.pop();
    if((dir=opendir(b.c_str()))==NULL)printf("打开目录失败！");
    while(read=readdir(dir))
      {
        if(((strcmp(read->d_name,"."))&&(strcmp(read->d_name,".."))))
        {
        string bb = b + "/" + read->d_name;
        stat(bb.c_str(),&buf);
        struct group* gid=getgrgid(buf.st_gid);
        struct passwd* wd=getpwuid(buf.st_uid);
        char* time=ctime(&(buf.st_ctime));
        time[strlen(time)-1] = '\0';
        cout<<buf.st_mode<<" "<<buf.st_nlink<<" "<<gid->gr_name<<" "<<wd->pw_name<<" "<<buf.st_size<<" "<<time<<" "<<read->d_name<<endl;
        if(read->d_type==4)q.push(bb);
        }
      }
   } 
 return 0; 
}

