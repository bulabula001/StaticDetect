#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include <mysql/mysql.h>

#include "logdb.h"
#include <iostream>

using namespace std;

int logdb(const char *opt_content, const int engine, const int level, const int module)
{

	static MYSQL 	  *db_conn     = NULL;
	static const char *db_username = "radius"; 
	static const char *db_password = "Ztb1234567";
	static const char *db_database = "DMDB";
	static const char *db_hostname = "192.168.10.183";
	static const int   db_port	   = 3306;

    char sql[1024];
	time_t now=0;
	char datetime[100];

    // init the database connection
    db_conn = mysql_init(NULL);

    // connect the database
    if(!mysql_real_connect(db_conn, db_hostname, db_username, db_password, db_database, db_port, NULL, 0))
    {
		perror("mysql connect");
		return -1;
	}

    //test first 
    sprintf(sql, "set names utf8");
    if (mysql_real_query(db_conn, sql, strlen(sql)))
    {
		perror("test error: ");
		return -1;
	}

	now=time(0);
	strftime(datetime, 100, "%Y-%m-%d %H:%M:%S", localtime(&now));	

    sprintf(sql, "INSERT INTO `syslog` (`opt_content`, `level`, `engine`, `module`, `create_time`) VALUES ('[StaticDetect]: %s', '%d', '%d', '%d', '%s')", opt_content, level, engine, module, datetime);
	printf("%s\n",sql);

    if (mysql_real_query(db_conn, sql, strlen(sql)))
    {
		perror("execute error");
		return -1;
	}

    mysql_close(db_conn);
	return 0;
}
