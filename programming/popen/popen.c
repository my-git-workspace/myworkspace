#include <stdio.h>
#include <stdlib.h>
void get_devices(){
    FILE *fp = popen("lsblk -nr | awk '{print $1}'", "r");
    char buffer[100];
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%s", line);
    }
    pclose(fp);
}
int main(int argc, char *argv[]){
	get_devices();
	//return from main
	return (0);
}
