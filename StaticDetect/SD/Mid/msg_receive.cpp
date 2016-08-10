#include <stdio.h>  
#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/msg.h>  
#include <errno.h>  
#include <stdlib.h>
#include <string.h>

#include <pthread.h>  

#include <stdio.h>                                                                                            
#include <stdlib.h>

#define MSGKEY 1024  

#include <set>  
#include <mysql/mysql.h>
#include <iostream>
using namespace std;
//MYSQL

string line;
set<string> mm, nn; 
set<string>::iterator it_w, it_b;


MYSQL 		*g_conn; // mysql 连接
MYSQL_RES 	*g_res; // mysql 记录集
MYSQL_ROW 	g_row; // 字符串数组，mysql 记录行
 
#define MAX_BUF_SIZE 1024 // 缓冲区最大字节数

const char *g_host_name = "192.168.10.118";
const char *g_user_name = "root";
const char *g_password = "123456";
const char *g_db_name = "test_c";
const unsigned int g_db_port = 3306;


struct msgstru  
{  
   int  categary; 
   char version[2048];  
  
};  

int imsgID;  
struct msgstru slQMsg,slRcvMsg;  
int ilrc;  

pthread_mutex_t mutex;  

void print_mysql_error(const char *msg) { // 打印最后一次错误
    if (msg)
        printf("%s: %s\n", msg, mysql_error(g_conn));
    else
        puts(mysql_error(g_conn));
}

int executesql(const char * sql) {
    /*query the database according the sql*/
    if (mysql_real_query(g_conn, sql, strlen(sql))) // 如果失败
        return -1; // 表示失败

    return 0; // 成功执行
}


int init_mysql() { // 初始化连接
    // init the database connection
    g_conn = mysql_init(NULL);

    /* connect the database */
    if(!mysql_real_connect(g_conn, g_host_name, g_user_name, g_password, g_db_name, g_db_port, NULL, 0)) // 如果失败
        return -1;

    // 是否连接已经可用
    if (executesql("set names utf8")) // 如果失败
        return -1;

    return 0; // 返回成功
}

//START_MYSQL
int load_msg(){

	printf("---------------------------\n");
    puts("       OOAD MYSQL         "); /* prints !!!Hello World!!! */
	printf("---------------------------\n");

    if (init_mysql());
        print_mysql_error(NULL);

    char sql[MAX_BUF_SIZE];
    sprintf(sql, "select * from `d_IP` order by id");

    if (executesql(sql)) // 句末没有分号
       {
		 print_mysql_error(NULL);
		}

	printf("it is here: 2!\n");
    g_res = mysql_store_result(g_conn); // 从服务器传送结果集至本地，mysql_use_result直接使用服务器上的记录集

    int iNum_rows = mysql_num_rows(g_res); // 得到记录的行数
    int iNum_fields = mysql_num_fields(g_res); // 得到记录的列数
	
	printf("---------------------------\n");
    printf("共 %d 个记录，每个记录 %d 字段\n", iNum_rows, iNum_fields);
	printf("---------------------------\n");

    while ((g_row=mysql_fetch_row(g_res))) // 打印结果集
	{
        printf("%s\t%s\t%s\t%s\n", g_row[0], g_row[1], g_row[2], g_row[3]); // 第一，第二字段
		line=g_row[2];
		cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
		printf("deal the mysql result here!\n");
		if(strcmp(g_row[1],"1")){
			printf("insert into ip white list  here!\n");
			cout << line <<endl;                                                                                                                                                                                              
        	mm.insert(line);
		}else if(!strcmp(g_row[1],"1")){
			printf("insert into ip black list  here!\n");
			cout << line <<endl;                                                                                                                                                                                               
        	nn.insert(line);
		}
	}

	printf("---------------------------\n");
    mysql_free_result(g_res); // 释放结果集
    mysql_close(g_conn); // 关闭链接

	//show alll white list and black list
  it_w=mm.begin();                                                                             
	  cout<<"###########white################"<<endl;
  while(it_w!=mm.end()){                                                                                                                                                                                                      
      cout<< *it_w <<endl;
      ++it_w;
    }
	  cout<<"###########end###################"<<endl;
  
  
  it_b=nn.begin();                                                                             
	  cout<<"###########black################"<<endl;
  while(it_b!=nn.end()){                                                                                                                                                                                                      
      cout<< *it_b <<endl;
      ++it_b;
    }
	  cout<<"###########end###################"<<endl;
  cout << "do business logic" << endl;

	return 0;
}
//END_MYSQL

void msg_format(){

	printf("msg format working here !\n");	
	printf("---------------------------\n");

}


int check_md5() 
{
	cout<<"enter the key you want to find"<<endl;
	string strin;
	cin >> strin;

	cout<<"DEBUG"<<endl;

  it_w=mm.begin();                                                                             
	  cout<<"###########white################"<<endl;
  while(it_w!=mm.end()){                                                                                                                                                                                                      
      cout<< *it_w <<endl;
      ++it_w;
    }
	  cout<<"###########end###################"<<endl;
  
  
  it_b=nn.begin();                                                                             
	  cout<<"###########black################"<<endl;
  while(it_b!=nn.end()){                                                                                                                                                                                                      
      cout<< *it_b <<endl;
      ++it_b;
    }
	  cout<<"###########end###################"<<endl;

	cout<<"DEBUG-end"<<endl;


	it_w = mm.find(strin);
	if(mm.end() != it_w)  // 在白名单中
	{
		cout<<"----------------------------------"<<endl;
		cout<<"match the white_list here!"<<endl;
		return 1;
	}
	else if(mm.end() == it_w)  // 不在白名单中
	{
		cout<<"----------------------------------"<<endl;
		cout << "not in the white_list" << endl;
		
		it_b = nn.find(strin);
		if(nn.end() != it_b) // in black list 
		{
			cout<<"----------------------------------"<<endl;
			cout<<"match the black_list here!"<<endl;
			return 2;
		}
		else if(nn.end() == it_b) // not in black list
		{
			cout<<"----------------------------------"<<endl;
			cout << "not in the black_list" << endl;
			cout <<"do other bussiness!"<<endl;
			return -1;
		}
			
	}

	return 0;
}


  
void * func1(void* args)  
{  
	imsgID=msgget(MSGKEY,IPC_EXCL );//检查消息队列是否存在  
	if(imsgID < 0){  
	      printf("消息不存在! errno=%d [%s]\n",errno,strerror(errno));  
	      exit(-1);  
	  }  
	
	while(1){	
        	//pthread_mutex_lock(&mutex);  
			 ilrc = msgrcv(imsgID,&slRcvMsg,sizeof(struct msgstru),0,0);/*接收消息队列*/  
	
			  if ( ilrc < 0 ) {  
			       printf("msgsnd()读消息队列失败,errno=%d[%s]\n",errno,strerror(errno));  
			       exit(-1);  
			  
			  }else{
				   printf("消息队列read成功\n");
				  
			  }
			//free(MSG_R);
			printf("TYPE	=	[%d]\n",slRcvMsg.categary);  
			printf("VERSION	=	[%s]\n",slRcvMsg.version);  
			
			//	 msgctl(imsgID,IPC_RMID,0); //删除消息队列  
		
			//mysql
			printf("---------------------------\n");
		    puts("        UPDATE        "); /* prints !!!Hello World!!! */
			printf("---------------------------\n");
			load_msg();
			//end-mysql
		
			msg_format();
        	//pthread_mutex_unlock(&mutex);  
	}
}  

void * func2(void* args)  
{  
    while(1)  
    {
        	pthread_mutex_lock(&mutex);  
			check_md5();  
        	pthread_mutex_unlock(&mutex);  
    }  
}  

main()  
{  
	
	int  cat;
	char str[2048];  

    pthread_t pid1, pid2;  
    pthread_mutex_init(&mutex, NULL);  


	//mysq-start
	printf("---------------------------\n");
    puts("        START         "); 
	printf("---------------------------\n");
	load_msg();
	//mysq-end

	msg_format();
	

    if(pthread_create(&pid1, NULL, func1, NULL))  
    {  
        return -1;  
    }  
  
    if(pthread_create(&pid2, NULL, func2, NULL))  
    {  
        return -1;  
    }  
	
	while(1)
		sleep(0);

	return 0;
}  
