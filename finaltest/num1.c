 #include <sys/types.h>
 #include <stdio.h>
 #include <unistd.h>
 #include <signal.h>

 int main( )
 {
    int pid1, pid2, pid3, count1=0, count2=0, count3=0;

    pid1 = fork( );
    if (pid1 == 0) {
       while (1) {
          sleep(1);
          printf("[child 0] execute: %d\n", ++count1);
       }
    }

    pid2 = fork( );
    if (pid2 == 0) {
       while (1) {
          sleep(1);
          printf("[child 1] execute: %d\n", ++count2);
       }
    }

	pid3 = fork( );
	if (pid3 == 0) {
		while(1) {
		  sleep(1);
		  printf("[child 2] execute: %d\n", ++count3);
		}
	}
	printf("type num of childs : %d", count3);
    sleep(1);
    kill(pid1, SIGSTOP);
    sleep(1);
    kill(pid1, SIGCONT);
    sleep(2);
    kill(pid2, SIGSTOP);
    sleep(2);
    kill(pid2, SIGCONT);
    sleep(3);
	kill(pid3, SIGSTOP);
	sleep(3);
	kill(pid3, SIGCONT);
    kill(pid1, SIGKILL);
    kill(pid2, SIGKILL);
	kill(pid3, SIGKILL);
 }

