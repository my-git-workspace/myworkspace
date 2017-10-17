#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef QNAP_ZFS_LINUX

/*
	Executes shell command and retuns stdout.
*/
char *execute_command(char *cmd){  //Execute shell command and return stdout;

	FILE *fp = popen(cmd, "r");
        if( !fp ){	//check popen returned valid ptr or not?
                printf("Execution error %s\n", cmd);
		pclose(fp);
		return NULL;
        }
	char *output=(char *)malloc(256);
	output[0]='\0';
	fscanf(fp, "%s", output);
	if(!strlen(output)){ //if output len==0 return NULL
		free(output);
		output=NULL;
		pclose(fp);
		return NULL;
	}
	pclose(fp);
	return output;
}


int compare_string(char *cmdoutput, const char *cmdinput){ //compares two strings and returns 0 if equal otherwise returns -1
	if(!cmdoutput){
		return -1;
	}
	
	if(!strcmp(cmdoutput,cmdinput)){ //verify module loaded or not
		free(cmdoutput);
		cmdoutput=NULL;	
		return 0;
	}else{
		free(cmdoutput);
		cmdoutput=NULL;	
		return -1;
	}
}

/*
	kldload() implementation for linux platform
	loads kernel module.
*/
int kldload(char *module){ //if module loaded successfully returns 0 otherwise returns -1.
        if(!module){
                return -1;
        }
        char cmd[256];
        sprintf(cmd, "/sbin/modprobe %s;echo $?\n", module);
	char *ptr=execute_command(cmd);	
	return compare_string(ptr,"0"); //compare and result of comparison
}

/*
	modfind implementaion for linux platform	
	finds kernel module loaded or not.
*/
int modfind(const char *module){ //if module found loaded returns 0 otherwise it will return -1.
        if(!module){
                return -1;
        }
        char cmd[256];
        sprintf(cmd, "lsmod | grep -o %s\n", module);
	
	char *ptr=execute_command(cmd);	
	return compare_string(ptr, module); //compare and result of comparision
}

#endif //QNAP_ZFS_LINUX

int main(int argc, char **argv){
	int status=0;
	if(argc==2){
		while (1){
		printf("modfind: %d\n",modfind(argv[1]));
		printf("kldload: %d\n",kldload(argv[1]));
		}
	
	}
	//load a kernel module	

	//return from main
	return (0);
}
