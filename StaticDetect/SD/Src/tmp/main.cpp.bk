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

set<string> mm, nn;
set<string>::iterator it_w, it_b;

set<string> mm_md5, nn_md5;
set<string>::iterator it_w_md5, it_b_md5;

set<string> mm_url, nn_url;
set<string>::iterator it_w_url, it_b_url;

set<string> mm_dns, nn_dns;
set<string>::iterator it_w_dns, it_b_dns;

pthread_mutex_t mutex;


int load_msg_md5()
{
	string line;
	MYSQL_RES 	*g_res; // mysql 记录集
	MYSQL		*g_conn; // mysql 连接
	MYSQL_ROW 	g_row; // 字符串数组，mysql 记录行
	const char	*g_host_name = "192.168.10.118";
	const char	*g_user_name = "root";
	const char	*g_password = "123456";
	const char	*g_db_name = "test_c";
	const unsigned int g_db_port = 3306;
    char sql[MAX_BUF_SIZE];

	printf("---------------------------\n");
	printf("-        LOAD MYSQL       -\n");
	printf("---------------------------\n");

	mm_md5.clear();
	nn_md5.clear();
    // init the database connection
    g_conn = mysql_init(NULL);

    /* connect the database */
    if(!mysql_real_connect(g_conn, g_host_name, g_user_name, g_password, g_db_name, g_db_port, NULL, 0)) // 如果失败
    {
		perror("mysql connect: ");
		return -1;
	}

    // 是否连接已经可用

    sprintf(sql, "set names utf8");
    if (mysql_real_query(g_conn, sql, strlen(sql))) // 如果失败
    {
		perror("test error: ");
		return -1;
	}

    sprintf(sql, "select * from `d_MD5` order by id");
    if (mysql_real_query(g_conn, sql, strlen(sql))) // 如果失败
    {
		perror("execute error: ");
		return -1;
	}


    g_res = mysql_store_result(g_conn); // 从服务器传送结果集至本地，mysql_use_result直接使用服务器上的记录集

    int iNum_rows = mysql_num_rows(g_res); // 得到记录的行数
    int iNum_fields = mysql_num_fields(g_res); // 得到记录的列数
	
    while ((g_row=mysql_fetch_row(g_res))) // 打印结果集
	{
		line=g_row[2];
		if(strcmp(g_row[1],"1"))
		{
        	mm_md5.insert(line);
		}
		else if(!strcmp(g_row[1],"1"))
		{
        	nn_md5.insert(line);
		}
	}

    mysql_free_result(g_res); // 释放结果集
    mysql_close(g_conn); // 关闭链接

	//show alll white list and black list
	it_w_md5=mm_md5.begin();                                                                             
	printf("-----------white-----------\n");
	printf("---------------------------\n");
	while(it_w_md5!=mm_md5.end())
	{
      cout<< *it_w_md5 <<endl;
      ++it_w_md5;
	}
  
	it_b_md5=nn_md5.begin();                                                                             
	printf("-----------black-----------\n");
	printf("---------------------------\n");
	while(it_b_md5!=nn_md5.end())
	{
      cout<< *it_b_md5 <<endl;
      ++it_b_md5;
	}

	printf("---------------------------\n");
	printf("-     LOAD  MD5  END      -\n");
	printf("---------------------------\n");

	return 0;
}



int load_msg_ip()
{
	string line;
	MYSQL_RES 	*g_res; // mysql 记录集
	MYSQL		*g_conn; // mysql 连接
	MYSQL_ROW 	g_row; // 字符串数组，mysql 记录行
	const char	*g_host_name = "192.168.10.118";
	const char	*g_user_name = "root";
	const char	*g_password = "123456";
	const char	*g_db_name = "test_c";
	const unsigned int g_db_port = 3306;
    char sql[MAX_BUF_SIZE];

	printf("---------------------------\n");
	printf("-        LOAD MYSQL       -\n");
	printf("---------------------------\n");

	mm.clear();
	nn.clear();
    // init the database connection
    g_conn = mysql_init(NULL);

    /* connect the database */
    if(!mysql_real_connect(g_conn, g_host_name, g_user_name, g_password, g_db_name, g_db_port, NULL, 0)) // 如果失败
    {
		perror("mysql connect: ");
		return -1;
	}

    // 是否连接已经可用

    sprintf(sql, "set names utf8");
    if (mysql_real_query(g_conn, sql, strlen(sql))) // 如果失败
    {
		perror("test error: ");
		return -1;
	}

    sprintf(sql, "select * from `d_IP` order by id");
    if (mysql_real_query(g_conn, sql, strlen(sql))) // 如果失败
    {
		perror("execute error: ");
		return -1;
	}


    g_res = mysql_store_result(g_conn); // 从服务器传送结果集至本地，mysql_use_result直接使用服务器上的记录集

    int iNum_rows = mysql_num_rows(g_res); // 得到记录的行数
    int iNum_fields = mysql_num_fields(g_res); // 得到记录的列数
	
    while ((g_row=mysql_fetch_row(g_res))) // 打印结果集
	{
		line=g_row[2];
		if(strcmp(g_row[1],"1"))
		{
        	mm.insert(line);
		}
		else if(!strcmp(g_row[1],"1"))
		{
        	nn.insert(line);
		}
	}

    mysql_free_result(g_res); // 释放结果集
    mysql_close(g_conn); // 关闭链接

	//show alll white list and black list
	it_w=mm.begin();                                                                             
	printf("-----------white-----------\n");
	printf("---------------------------\n");
	while(it_w!=mm.end())
	{
      cout<< *it_w <<endl;
      ++it_w;
	}
  
	it_b=nn.begin();                                                                             
	printf("-----------black-----------\n");
	printf("---------------------------\n");
	while(it_b!=nn.end())
	{
      cout<< *it_b <<endl;
      ++it_b;
	}

	printf("---------------------------\n");
	printf("-       LOAD IP END       -\n");
	printf("---------------------------\n");

	return 0;
}

int load_msg_url()
{
	string line;
	MYSQL_RES 	*g_res; // mysql 记录集
	MYSQL		*g_conn; // mysql 连接
	MYSQL_ROW 	g_row; // 字符串数组，mysql 记录行
	const char	*g_host_name = "192.168.10.118";
	const char	*g_user_name = "root";
	const char	*g_password = "123456";
	const char	*g_db_name = "test_c";
	const unsigned int g_db_port = 3306;
    char sql[MAX_BUF_SIZE];

	printf("---------------------------\n");
	printf("-        LOAD MYSQL       -\n");
	printf("---------------------------\n");

	mm_url.clear();
	nn_url.clear();
    // init the database connection
    g_conn = mysql_init(NULL);

    /* connect the database */
    if(!mysql_real_connect(g_conn, g_host_name, g_user_name, g_password, g_db_name, g_db_port, NULL, 0)) // 如果失败
    {
		perror("mysql connect: ");
		return -1;
	}

    // 是否连接已经可用

    sprintf(sql, "set names utf8");
    if (mysql_real_query(g_conn, sql, strlen(sql))) // 如果失败
    {
		perror("test error: ");
		return -1;
	}

    sprintf(sql, "select * from `d_URL` order by id");
    if (mysql_real_query(g_conn, sql, strlen(sql))) // 如果失败
    {
		perror("execute error: ");
		return -1;
	}


    g_res = mysql_store_result(g_conn); // 从服务器传送结果集至本地，mysql_use_result直接使用服务器上的记录集

    int iNum_rows = mysql_num_rows(g_res); // 得到记录的行数
    int iNum_fields = mysql_num_fields(g_res); // 得到记录的列数
	
    while ((g_row=mysql_fetch_row(g_res))) // 打印结果集
	{
		line=g_row[2];
		if(strcmp(g_row[1],"1"))
		{
        	mm_url.insert(line);
		}
		else if(!strcmp(g_row[1],"1"))
		{
        	nn_url.insert(line);
		}
	}

    mysql_free_result(g_res); // 释放结果集
    mysql_close(g_conn); // 关闭链接

	//show alll white list and black list
	it_w_url=mm_url.begin();                                                                             
	printf("-----------white-----------\n");
	printf("---------------------------\n");
	while(it_w_url!=mm_url.end())
	{
      cout<< *it_w_url <<endl;
      ++it_w_url;
	}
  
	it_b_url=nn_url.begin();                                                                             
	printf("-----------black-----------\n");
	printf("---------------------------\n");
	while(it_b_url!=nn_url.end())
	{
      cout<< *it_b_url <<endl;
      ++it_b_url;
	}

	printf("---------------------------\n");
	printf("-       LOAD URL END      -\n");
	printf("---------------------------\n");

	return 0;
}


int load_msg_dns()
{
	string line;
	MYSQL_RES 	*g_res; // mysql 记录集
	MYSQL		*g_conn; // mysql 连接
	MYSQL_ROW 	g_row; // 字符串数组，mysql 记录行
	const char	*g_host_name = "192.168.10.118";
	const char	*g_user_name = "root";
	const char	*g_password = "123456";
	const char	*g_db_name = "test_c";
	const unsigned int g_db_port = 3306;
    char sql[MAX_BUF_SIZE];

	printf("---------------------------\n");
	printf("-        LOAD MYSQL       -\n");
	printf("---------------------------\n");

	mm_dns.clear();
	nn_dns.clear();
    // init the database connection
    g_conn = mysql_init(NULL);

    /* connect the database */
    if(!mysql_real_connect(g_conn, g_host_name, g_user_name, g_password, g_db_name, g_db_port, NULL, 0)) // 如果失败
    {
		perror("mysql connect: ");
		return -1;
	}

    // 是否连接已经可用

    sprintf(sql, "set names utf8");
    if (mysql_real_query(g_conn, sql, strlen(sql))) // 如果失败
    {
		perror("test error: ");
		return -1;
	}

    sprintf(sql, "select * from `d_DNS` order by id");
    if (mysql_real_query(g_conn, sql, strlen(sql))) // 如果失败
    {
		perror("execute error: ");
		return -1;
	}


    g_res = mysql_store_result(g_conn); // 从服务器传送结果集至本地，mysql_use_result直接使用服务器上的记录集

    int iNum_rows = mysql_num_rows(g_res); // 得到记录的行数
    int iNum_fields = mysql_num_fields(g_res); // 得到记录的列数
	
    while ((g_row=mysql_fetch_row(g_res))) // 打印结果集
	{
		line=g_row[2];
		if(strcmp(g_row[1],"1"))
		{
        	mm_dns.insert(line);
		}
		else if(!strcmp(g_row[1],"1"))
		{
        	nn_dns.insert(line);
		}
	}

    mysql_free_result(g_res); // 释放结果集
    mysql_close(g_conn); // 关闭链接

	//show alll white list and black list
	it_w_dns=mm_dns.begin();                                                                             
	printf("-----------white-----------\n");
	printf("---------------------------\n");
	while(it_w_dns!=mm_dns.end())
	{
      cout<< *it_w_dns <<endl;
      ++it_w_dns;
	}
  
	it_b_dns=nn_dns.begin();                                                                             
	printf("-----------black-----------\n");
	printf("---------------------------\n");
	while(it_b_dns!=nn_dns.end())
	{
      cout<< *it_b_dns <<endl;
      ++it_b_dns;
	}

	printf("---------------------------\n");
	printf("-       LOAD DNS END      -\n");
	printf("---------------------------\n");

	return 0;
}


int check_md5(string md5) 
{
	cout<<">>>   MD5 CHECK   <<<"<<endl;
	string strin = md5;

	it_w_md5 = mm_md5.find(strin);
	if(mm_md5.end() != it_w_md5)  // in white list
	{
		cout<<"match white"<<endl;
		return 1;
	}
	else if(mm_md5.end() == it_w_md5)  // not in white list
	{
		cout << "not in white"<<endl;
		
		it_b_md5 = nn_md5.find(strin);
		if(nn_md5.end() != it_b_md5) // in black list 
		{
			cout<<"match black"<<endl;
			return 2;
		}
		else if(nn_md5.end() == it_b_md5) // not in black list
		{
			cout << "not in black yet" << endl;
			cout<<">>>  MD5 CHECK END   <<<"<<endl;
			return -1;
		}
	}
}


int check_ip(string ip) 
{
	cout<<">>>   IP  CHECK   <<<"<<endl;
	string strin = ip;

	it_w = mm.find(strin);
	if(mm.end() != it_w)  // in white list
	{
		cout<<"match white"<<endl;
		return 1;
	}
	else if(mm.end() == it_w)  // not in white list
	{
		cout << "not in white"<<endl;
		
		it_b = nn.find(strin);
		if(nn.end() != it_b) // in black list 
		{
			cout<<"match black"<<endl;
			return 2;
		}
		else if(nn.end() == it_b) // not in black list
		{
			cout << "not in black yet" << endl;
			cout<<">>>   IP CHECK END   <<<"<<endl;
			return -1;
		}
	}
}

int check_url(string url) 
{
	cout<<">>>   URL CHECK   <<<"<<endl;
	string strin = url;

	it_w_url = mm_url.find(strin);
	if(mm_url.end() != it_w_url)  // in white list
	{
		cout<<"match white"<<endl;
		return 1;
	}
	else if(mm_url.end() == it_w_url)  // not in white list
	{
		cout << "not in white"<<endl;
		
		it_b_url = nn_url.find(strin);
		if(nn_url.end() != it_b_url) // in black list 
		{
			cout<<"match black"<<endl;
			return 2;
		}
		else if(nn_url.end() == it_b_url) // not in black list
		{
			cout << "not in black yet" << endl;
			cout<<">>>  URL CHECK END   <<<"<<endl;
			return -1;
		}
	}
}




int check_dns(string dns) 
{
	cout<<">>>   DNS CHECK   <<<"<<endl;
	string strin = dns;

	it_w_dns = mm_dns.find(strin);
	if(mm_dns.end() != it_w_dns)  // in white list
	{
		cout<<"match white"<<endl;
		return 1;
	}
	else if(mm_dns.end() == it_w_dns)  // not in white list
	{
		cout << "not in white"<<endl;
		
		it_b_dns = nn_dns.find(strin);
		if(nn_dns.end() != it_b_dns) // in black list 
		{
			cout<<"match black"<<endl;
			return 2;
		}
		else if(nn_dns.end() == it_b_dns) // not in black list
		{
			cout << "not in black yet" << endl;
			cout<<">>>  DNS CHECK END   <<<"<<endl;
			return -1;
		}
	}
}

int check_av(const char *file, string &v)		// v - name of virus if have
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
		v=q;
		cout<<">>>   AV CHECK END   <<<"<<endl;
		return 2;
	}else{
    	pclose(fstream);   
		v=q;
		cout<<">>>   AV CHECK END   <<<"<<endl;
		return 1;
	}
}

int check(vector<string> t, vector<string> & r)
{

	cout<<"---------------------"<<endl;
	cout<<"-   DO CHECK HERE   -"<<endl;
	cout<<"---------------------"<<endl;

	string check_dir="/home/SD/Data/DataDIR/"; //the path for clamAV check
	string virus;
	int i=0;	
	for(i=0; i<16; i++)		
	{
		r.push_back(t[i]);
	}
	r.push_back("0");
	r.push_back("0");

	int ret;
	ret=check_md5(t[14]);	
	if(ret == 1){
		r[17] = "md5";
		return 1;
	}
	else if(ret == 2){
		r[17] = "md5";
		return 2;
	}

	ret=check_ip(t[13]);
	if(ret == 1){
		r[17] = "ip";
		return 1;
	}
	else if(ret == 2){
		r[17] = "ip";
		return 2;
	}

	ret=check_url(t[11]);
	if(ret == 1){
		r[17] = "url";
		return 1;
	}
	else if(ret == 2){
		r[17] = "url";
		return 2;
	}

	ret=check_dns(t[12]);
	if(ret == 1){
		r[17] = "dns";
		return 1;
	}
	else if(ret == 2){
		r[17] = "dns";
		return 2;
	}

	string check_file = t[6];
	string check_path = check_dir + check_file;
	ret=check_av(check_path.c_str(), virus);
	if(ret == 1){
		printf("the file is infected!\n");
		r[16] = virus;
		r[17] = "av";
		return 3;
	}
	else if(ret == 2){
		printf("the file is not sure !\n");
		r[16] = virus;
		r[17] = "av";
		return 4;
	}

}

void writejsonfile(int tag, const char * file, vector<string>  p)
{
	char write_path[1024]={0};
	if(tag==1)
	{
		if(p[7] == "M")
		strcpy(write_path, "/home/SD/Data/ResDIR/DIR-1/");
		if(p[7] == "F")
		strcpy(write_path, "/home/SD/Data/ResDIR/DIR-2/");
		if(p[7] == "N")
		strcpy(write_path, "/home/SD/Data/ResDIR/DIR-3/");
	}
	if(tag == 2)
		strcpy(write_path, "/home/SD/Data/DetectDIR/");
	
	strcat(write_path, file);
	//根节点
    Json::Value root; 
    //根节点属性

	root["sip"]			=	Json::Value(p[0]);
	root["sport"]		=	Json::Value(p[1]);
	root["dip"]			=	Json::Value(p[2]);
	root["dport"]		=	Json::Value(p[3]);
	root["protocol"]	=	Json::Value(p[4]);
	root["app_type"]	=	Json::Value(p[5]);
	root["name"]		=	Json::Value(p[6]);
	root["from"]		=	Json::Value(p[7]);
	root["session_id"]	=	Json::Value(p[8]);
	root["sender"]		=	Json::Value(p[9]);
 	root["receiver"]	=	Json::Value(p[10]);
 	root["url"]			=	Json::Value(p[11]);
 	root["dns"]			=	Json::Value(p[12]);
 	root["ip"]			=	Json::Value(p[13]);
 	root["md5"]			=	Json::Value(p[14]);
 	root["c_time"]		=	Json::Value(p[15]);
 	root["virus_name"]	=	Json::Value(p[16]);		//[ ok, virname] 
 	root["detect_type"]	=	Json::Value(p[17]);		//[ md5, ip, url, dns , av ]

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

int readjsonfile(const char *dir, const char *file, vector <string> & p)
{	

	printf("---------------------------\n");
	printf("-     READ JSON FILE      -\n");
	printf("---------------------------\n");

	string member[16];
	Json::Reader reader;
	Json::Value root;
	char tmp_path[1024]={0};
	char cmd[1024]={0};

	strcpy(tmp_path, dir);
	printf("---------------------------\n");
	printf("- json file dir is [%s]\n", tmp_path);
	printf("- json file name is [%s]\n", file);
	strcat(tmp_path,file);
	printf("- absolute path is [%s]\n", tmp_path);
	printf("---------------------------\n\n");
	 
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
    }
 
    is.close();
	
		
	int i=0;

	for(i=0; i<16; i++)		
	{
		p.push_back(member[i]);
	}

	printf("---------------------------\n");
	printf("-     DEL JSON FILE       -\n");
	printf("---------------------------\n");

	strcpy(cmd, "rm -rf ");
	strcat(cmd, tmp_path);
	printf("- absolute del cmd is [%s]\n", cmd);
	system(cmd);

	printf("---------------------------\n");
	printf("-     READ JSON END       -\n");
	printf("---------------------------\n");
	

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

	printf("\n");
	printf("---------------------------\n");
	printf("-          BEGIN          -\n");
	printf("---------------------------\n");
	printf("- DIR %s\n", dir);
	printf("- FIL %s\n", file);

	suffix = ch+1;
	printf("- SUF %s\n", suffix);
	
	if (!strcmp(suffix, "json")) {
		printf("- suffix is json !\n");
	}
	else{
		printf("- suffix not json !\n");
		return 0;
	}
	
	printf("---------------------------\n");
	return 1;
}

void monitor()
{
	string path="/home/SD/Data/InfoDIR/";		//path store incoming file information
	vector<string> p; 
	vector<string> result; //save json data;

    int monitor = inotify_init();
    if ( -1 == monitor ) {
        perror("monitor: ");
    }

    int watcher = inotify_add_watch(monitor, path.c_str(), IN_CLOSE_WRITE);
    if ( -1 == watcher  ) {
        perror("inotify_add_watch: ");
    }

    FILE *monitor_file = fdopen(monitor, "r");
    char name[1024];

    while (1) {

		p.clear();
		result.clear();

        struct inotify_event event;
        if ( -1 == freadsome(&event, sizeof(event), monitor_file) )
		{
            perror("fread monitor");
        }

        if (event.len)
		{
            freadsome(name, event.len, monitor_file);
        }
		else{
            sprintf(name, "FD: %d\n", event.wd);
        }

        if (!callback(path.c_str(), name)) {
			printf("callback func false!\n");
        }

		readjsonfile(path.c_str(), name, p);

		int ret=check(p, result);
		if(ret==1)
			writejsonfile(1, name, result);
		if(ret==2)
			writejsonfile(1, name, result);
		if(ret==3)
			writejsonfile(1, name, result);
		if(ret==4)
			writejsonfile(2, name, result);
    }
    return ;
}


void * func1(void* args)  
{  

	struct msgstru  
	{  
	   int  categary; 
	   char version[2048];  
	  
	};  
	
	int imsgID;
	struct msgstru slQMsg,slRcvMsg;
	int ilrc;
	
	while(1)
	{	
		//pthread_mutex_lock(&mutex);  

		imsgID=msgget(MSGKEY, IPC_EXCL);//检查消息队列是否存在  

		if(imsgID < 0)
		{
		      printf("消息队列不存在! errno=%d [%s]\n",errno,strerror(errno));  
		      exit(-1);  
		}

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

		printf("TYPE	=	[%d]\n", slRcvMsg.categary);  
		printf("VERSION	=	[%s]\n", slRcvMsg.version);  
		
		//	 msgctl(imsgID,IPC_RMID,0); //删除消息队列  
		
		printf("---------------------------\n");
		printf("-          UPDATE          \n");
		printf("---------------------------\n");
		
		switch(slRcvMsg.categary)
		{
			case 1:
				load_msg_ip();
				break;
			case 2:
				load_msg_url();
				break;
			case 3:
				load_msg_dns();
				break;
			case 4:
				load_msg_md5();
				break;
			default:
				printf("Enter the right categary: 1 2 3 4\n");
		}
		
		
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

int main(void)
{

    pthread_t pid1, pid2;  
    pthread_mutex_init(&mutex, NULL);  


	printf("---------------------------\n");
	printf("-          START          -\n");
	printf("---------------------------\n");

	load_msg_md5();
	load_msg_ip();
	load_msg_url();
	load_msg_dns();


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
