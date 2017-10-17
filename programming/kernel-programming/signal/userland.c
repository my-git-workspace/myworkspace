#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "common.h"
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(#x)
#define SIG_ACTION
#ifdef SIG_ACTION
void sig_handler(int signo, siginfo_t *siginfo, void *context) {
  if (signo == MODULE_SIGNAL){
    	printf(STR(MODULE_SIGNAL)" received\n");
	printf ("Sending PID: %ld, UID: %ld\n", (long)siginfo->si_pid, (long)siginfo->si_uid);
	printf("value from kernel: %d\n", siginfo->si_int);
	//printf("value from kernel: %s\n", (char *)siginfo->si_ptr);
   }	
}
#else
void sig_handler(int signo) {
  if (signo == MODULE_SIGNAL)
    	printf(STR(MODULE_SIGNAL)" received\n");
}
#endif
int main(int argc, char *argv){
	
	int devfd=open("mydev", O_RDONLY);
	if(devfd==-1){
		printf("invalid mydev\n");
		close(devfd);
		return (0);
	}
#ifdef SIG_ACTION
	struct sigaction act;
	memset (&act, '\0', sizeof(act));
	/* Use the sa_sigaction field because the handles has two additional parameters */
	act.sa_sigaction = &sig_handler;
	/* The SA_SIGINFO flag tells sigaction() to use the sa_sigaction field, not sa_handler. */
	act.sa_flags = SA_SIGINFO;
	if (sigaction(MODULE_SIGNAL, &act, NULL) < 0) {
		perror ("sigaction");
		return 1;
	}
#else
	if (signal(MODULE_SIGNAL, sig_handler) == SIG_ERR)
 		 printf("\ncan't catch SIGINT\n");
#endif
	printf("mydev: %d opened successfully\n", devfd);
	sleep(1);
	close(devfd);
	//return from main
	return 0;
}
