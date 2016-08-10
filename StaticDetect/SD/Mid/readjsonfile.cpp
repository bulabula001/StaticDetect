#include <iostream>
#include <fstream>
#include <cstring>
#include "json/json.h"

using namespace std;

string * readjsonfile(const char *dir, const char *file)
{	
	string member[16];
	string *p;
	Json::Reader reader;
	Json::Value root;
	char tmp_path[1024]={0};

	strcpy(tmp_path, dir);
	printf("%s--\n", tmp_path);
	printf("%s--\n", file);
	strcat(tmp_path,file);
	printf("path is --[%s]--\n", tmp_path);
	 
	cout<<"1"<<endl;
    //从文件中读取
    ifstream is;
    //is.open("/home/SD/Data/InfoDIR/a.json", ios::binary);
    is.open(tmp_path, ios::binary);
	if(!is.is_open())
	{
		cout<<"open error!"<<endl;
		is.close();
		return NULL;
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

		cout<<"------------------------------------------"<<endl;	
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

		cout<<"----Reading Comlete!----------------------"<<endl;	
    }
 
    is.close();
	p=member;

	cout<<"return the value p : "<<p<<endl;

    return p;
}

int main(void){
	
	string *ret;
	string path="/home/SD/Data/InfoDIR/";
	string file="a.json";
	//ret=readjsonfile("/home/SD/Data/InfoDIR/", "a.json");	
	ret=readjsonfile(path.c_str(), file.c_str());	
	cout<<"return the value : "<<ret<<endl;
	
	int i;
	for(i=0;i<16;i++)
	{
		cout<<*ret<<endl; 
 	}

	return 0;
}
