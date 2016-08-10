#include<stdio.h>   
#include<string.h>   
#include <string.h>

int check_av(){
    FILE *fstream=NULL;     
    char buff[1024];   
	char *p;
	char *q;
	char *t;
    memset(buff,0,sizeof(buff));   
    if(NULL==(fstream=popen("/usr/bin/clamscan /tmp/a.out","r")))     
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
		return 2;
	}else{
    	pclose(fstream);   
		return 1;
	}
}


int main(void){   
	int ret=check_av();
	printf("%d\n", ret);
    return 0;    
}  
