#include <unistd.h>
#include <sys/inotify.h>
#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include "json/json.h"
#include <set>  
#include <mysql/mysql.h>
#include <pthread.h>  
#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/msg.h>  

#define MSGKEY 1024  
#define MAX_BUF_SIZE 1024 // 缓冲区最大字节数

using namespace std;

string line;
string result[18]={"0"}; //save json data;
set<string> mm, nn; 
set<string>::iterator it_w, it_b;

MYSQL 		*g_conn; // mysql 连接
MYSQL_RES 	*g_res; // mysql 记录集
MYSQL_ROW 	g_row; // 字符串数组，mysql 记录行

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


void print_mysql_error(const char *msg)
{ // 打印最后一次错误
    if (msg)
        printf("%s: %s\n", msg, mysql_error(g_conn));
    else
        puts(mysql_error(g_conn));
}

int executesql(const char * sql)
{
    /*query the database according the sql*/
    if (mysql_real_query(g_conn, sql, strlen(sql))) // 如果失败
        return -1; // 表示失败

    return 0; // 成功执行
}

int init_mysql()
{
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

int load_msg()
{
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

void msg_format(){

	printf("msg format working here !\n");	
	printf("---------------------------\n");

}

int check_md5()
{
	cout<<">>>  MD5  CHECK   <<<"<<endl;
	return -1;
	cout<<">>> MD5 CHECK END <<<"<<endl;
}
int check_url()
{
	cout<<">>>  URL  CHECK   <<<"<<endl;
	return -1;
	cout<<">>> RUL CHECK END <<<"<<endl;
}
int check_dns()
{
	cout<<">>>  DNS  CHECK   <<<"<<endl;
	return -1;
	cout<<">>> DNS CHECK END <<<"<<endl;
}
int check_av(const char *file);
int check_ip(string ip);

string check_dir="/home/SD/Data/DataDIR/"; //the path for clamAV check

int check_ip(string ip) 
{
	cout<<">>>   IP  CHECK   <<<"<<endl;
	string strin = ip;

	it_w=mm.begin();                                                                             
	cout<<"___________white________________"<<endl;
	while(it_w!=mm.end()){                                                                                                                
      cout<< *it_w <<endl;
      ++it_w;
    }

	it_b=nn.begin();                                                                             
	cout<<"___________black________________"<<endl;
 	while(it_b!=nn.end()){                                                                                                                                                                          
      cout<< *it_b <<endl;
      ++it_b;
    }

	it_w = mm.find(strin);
	if(mm.end() != it_w)  // in white list
	{
		cout<<"match white_list"<<endl;
		cout<<">>>   IP CHECK END   <<<"<<endl;
		return 1;
	}
	else if(mm.end() == it_w)  // not in white list
	{
		cout << "not in white_list"<<endl;
		
		it_b = nn.find(strin);
		if(nn.end() != it_b) // in black list 
		{
			cout<<"match black_list"<<endl;
			cout<<">>>   IP CHECK END   <<<"<<endl;
			return 2;
		}
		else if(nn.end() == it_b) // not in black list
		{
			cout << "not in black_list yet" << endl;
			cout<<">>>   IP CHECK END   <<<"<<endl;
			return -1;
		}
	}

	return 0;
}

int check_av(const char *file)
{
	cout<<">>>   AV  CHECK   <<<"<<endl;

    FILE *fstream=NULL;     
    char buff[1024];   
	char *p;
	char *q;
	char *t;
    memset(buff,0,sizeof(buff));   
	//printf("%s", file);
	char cmd[1024]={0};

	strcpy(cmd, "/usr/bin/clamscan ");
	strcat(cmd, file);
	printf("cmd is => [%s]\n", cmd);
    //if(NULL==(fstream=popen("/usr/bin/clamscan /tmp/a.out","r")))     
    if(NULL==(fstream=popen(cmd,"r")))     
    {    
        fprintf(stderr,"execute command failed:");     
        return -1;     
    }    
    fgets(buff, sizeof(buff), fstream); 
	p=buff;
	t=strchr(p, '\n');
	if(t)
		*t='\0';
    printf("[%s]\n",buff);   
	q=strtok(p," ");
    q=strtok(NULL," ");
    //printf("[%s]---\n",q);
	if(!strcmp(q,"OK"))
	{
    	pclose(fstream);   
		cout<<">>>   AV CHECK END   <<<"<<endl;
		return 2;
	}else{
    	pclose(fstream);   
		cout<<">>>   AV CHECK END   <<<"<<endl;
		return 1;
	}
}

void writejsonfile(int tag, const char * file)
{
	char write_path[1024]={0};
	if(tag==1)
		strcpy(write_path, "/home/SD/Data/ResDIR/");
	if(tag == 2)
		strcpy(write_path, "/home/SD/Data/DetectDIR/");
	
	strcat(write_path, file);
	//根节点
    Json::Value root; 
    //根节点属性

	root["sip"]			=	Json::Value(result[0]);
	root["sport"]		=	Json::Value(result[1]);
	root["dip"]			=	Json::Value(result[2]);
	root["dport"]		=	Json::Value(result[3]);
	root["protocol"]	=	Json::Value(result[4]);
	root["app_type"]	=	Json::Value(result[5]);
	root["name"]		=	Json::Value(result[6]);
	root["from"]		=	Json::Value(result[7]);
	root["session_id"]	=	Json::Value(result[8]);
	root["sender"]		=	Json::Value(result[9]);
 	root["receiver"]	=	Json::Value(result[10]);
 	root["url"]			=	Json::Value(result[11]);
 	root["dns"]			=	Json::Value(result[12]);
 	root["ip"]			=	Json::Value(result[13]);
 	root["md5"]			=	Json::Value(result[14]);
 	root["c_time"]		=	Json::Value(result[15]);
 	root["virus_name"]	=	Json::Value(result[16]);
 	root["detect_type"]	=	Json::Value(result[17]);

    //缩进输出
    cout << "StyledWriter:" << endl;
    Json::StyledWriter sw;
    cout << sw.write(root) << endl << endl;
     
    //输出到文件

    ofstream os;
    os.open(write_path);
    os << sw.write(root);
    os.close();
 
    return ;
}

int readjsonfile(const char *dir, const char *file)
{	
	string member[16];
	Json::Reader reader;
	Json::Value root;
	char tmp_path[1024]={0};

	strcpy(tmp_path, dir);
	printf("json file dir is  %s--\n", tmp_path);
	printf("json file name is %s--\n", file);
	strcat(tmp_path,file);
	printf("absolute path is --[%s]--\n", tmp_path);
	 
    //从文件中读取
    ifstream is;
    //is.open("/home/SD/Data/InfoDIR/a.json", ios::binary);
    is.open(tmp_path, ios::binary);
	if(!is.is_open())
	{
		cout<<"open error!"<<endl;
		is.close();
		return -1;
	}
 
    if(reader.parse(is,root))
    {
        //读取根节点信息
		member[0] = 	root["sip"].asString();
		member[1] = 	root["sport"].asString();
		member[2] = 	root["dip"].asString();
		member[3] = 	root["dport"].asString();
		member[4] = 	root["protocol"].asString();
		member[5] = 	root["app_type"].asString();
		member[6] = 	root["name"].asString();
		member[7] = 	root["from"].asString();
		member[8] = 	root["session_id"].asString();
		member[9] = 	root["sender"].asString();
		member[10] = 	root["receiver"].asString();
		member[11] = 	root["url"].asString();
		member[12] = 	root["dns"].asString();
		member[13] = 	root["ip"].asString();
		member[14] = 	root["md5"].asString();
		member[15] = 	root["c_time"].asString();

		cout<<"====Print Json Key and Value!============="<<endl;	
		cout<<member[0]<<endl;
		cout<<member[1]<<endl;
		cout<<member[2]<<endl;
		cout<<member[3]<<endl;
		cout<<member[4]<<endl;
		cout<<member[5]<<endl;
		cout<<member[6]<<endl;
		cout<<member[7]<<endl;
		cout<<member[8]<<endl;
		cout<<member[9]<<endl;
		cout<<member[10]<<endl;
		cout<<member[11]<<endl;
		cout<<member[12]<<endl;
		cout<<member[13]<<endl;
		cout<<member[14]<<endl;
		cout<<member[15]<<endl;

		cout<<"====Reading Comlete!======================"<<endl;	
    }
 
    is.close();

	int i=0;
	for(i=0; i<16; i++)		
	{
		cout<<member[i]<<endl;
		result[i]=member[i];
	}
	result[16] = "0";
	result[17] = "1";
 
	cout<<">>>   DO CHECK HERE   <<<"<<endl;
	int ret;
		
	ret=check_md5();	
	if(ret == 1){
		printf("match md5 white list here!\n");
		result[17] = "2";
		return 1;
	}
	else if(ret == 2){
		printf("match md5 black list here!\n");
		result[17] = "2";
		return 2;
	}
	printf("unknow result and go to the next check!\n");


	ret=check_ip(member[13]);
	if(ret == 1){
		printf("match ip white list here!\n");
		writejsonfile(1, file);
		return 1;
	}
	else if(ret == 2){
		printf("match ip black list here!\n");
		writejsonfile(1, file);
		return 2;
	}
	printf("unknow result and go to the next check!\n");
	

	ret=check_url();
	if(ret == 1){
		printf("match white list here!\n");
		return 1;
	}
	else if(ret == 2){
		printf("match black list here!\n");
		return 2;
	}
	printf("unknow result and go to the next check!\n");


	ret=check_dns();
	if(ret == 1){
		printf("match white list here!\n");
		return 1;
	}
	else if(ret == 2){
		printf("match black list here!\n");
		return 2;
	}
	printf("unknow result and go to the next check!\n");


	string check_file = member[6];
	string check_path = check_dir + check_file;
	ret=check_av(check_path.c_str());
	if(ret == 1){
		printf("the file is infected!\n");
		result[16] = "virus";
		result[17] = "3";
		printf("put the file info into the result dir\n");
		writejsonfile(1, file);
		return 1;
	}
	else if(ret == 2){
		printf("the file is not sure !\n");
		result[16] = "0";
		result[17] = "4";
		printf("put the file info into the suspicious dir\n");
		writejsonfile(2, file);
		return 2;
	}

    return 0;
}

int freadsome(void *dest, size_t remain, FILE *file)  
{
    char *offset = (char*)dest;
    while (remain) {
        int n = fread(offset, 1, remain, file);
        if (n==0) {
            return -1;
        }
  
        remain -= n;
        offset += n;
    }
    return 1;
}

int callback(const char* dir, const char* file)
{
	const char* ch = strrchr(file, '.'), *suffix;
	if (!ch) {
		return -1;
	}
	printf("DIR------------%s\n", dir);
	printf("FILE-----------%s\n", file);

	suffix = ch+1;
	printf("SUFFIX---------%s\n", suffix);
	
	if (!strcmp(suffix, "json")) {
		printf("suffix is json !\n");
	}
	else{
		printf("suffix not json !\n");
		return 0;
	}
	
	return 1;
}

void monitor()
{
	string path="/home/SD/Data/InfoDIR/";
    int monitor = inotify_init();
    if ( -1 == monitor ) {
        perror("monitor");
    }

    int watcher = inotify_add_watch(monitor, path.c_str(), IN_CLOSE_WRITE);
    if ( -1 == watcher  ) {
        perror("inotify_add_watch");
    }

    FILE *monitor_file = fdopen(monitor, "r");
    char name[1024];

    while (1) {
        struct inotify_event event;
        if ( -1 == freadsome(&event, sizeof(event), monitor_file) ) {
            perror("fread monitor");
        }
        if (event.len) {
            freadsome(name, event.len, monitor_file);
        } else {
            sprintf(name, "FD: %d\n", event.wd);
        }

        if (!callback(path.c_str(), name)) {
			printf("callback func false!\n");
        }
		readjsonfile(path.c_str(), name);
    }
    return ;
}


void * func1(void* args)  
{  
	imsgID=msgget(MSGKEY,IPC_EXCL );//检查消息队列是否存在  
	if(imsgID < 0){  
	      printf("消息不存在! errno=%d [%s]\n",errno,strerror(errno));  
	      exit(-1);  
	  }  
	
	while(1)
	{	
		//pthread_mutex_lock(&mutex);  
		 ilrc = msgrcv(imsgID,&slRcvMsg,sizeof(struct msgstru),0,0);/*接收消息队列*/  
		
		if ( ilrc < 0 )
		{  
			printf("msgsnd()读消息队列失败,errno=%d[%s]\n",errno,strerror(errno));  
			exit(-1);  
		}
		else
		{
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
			monitor();
        	pthread_mutex_unlock(&mutex);  
    }  
}  

int main()
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
