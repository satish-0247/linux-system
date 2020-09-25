/*4. write a program to show zombie removal.
Method1: using wait in ISR. Use signal() and wait()
Method2: using periodic-zombie-check(polling).. use waitpid(..,..,WNOHANG) and sigaction().
Method3: using waitpid(), flags as SA_NOCLDWAIT*/

#include<stdio.h>
#include<signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
// method 1

/*
void isr(int n)
{
printf("in isr because child got terminated\n");
wait(NULL);
}


int main()
{
signal(SIGCHLD,isr);
if(fork()==0)
{
sleep(1);
printf("in child\n");
sleep(5);	
exit(0);
}
else
{
printf("parent in 20 sec delay\n");
sleep(20);	
printf("i am in parent\n");
}
}
*/

//method2
/*
int main()
{
if(fork()==0)
{
printf("in child\n");
sleep(5);       
exit(0);
}
else
{
	int status;
while(waitpid(-1,&status,WNOHANG)!=-1);     
printf("parent collected child exit value\n");
}
}
*/

//method3

int main()
{
struct sigaction act={
        .sa_flags=SA_NOCLDWAIT,
};

sigemptyset(&act.sa_mask);
sigaction(SIGCHLD,&act,NULL);

if(fork()==0)
{
printf("in child\n");
sleep(5);
exit(0);
}
else
{
        int status;
waitpid(-1,&status,WNOHANG);
printf("parent collected child exit value\n");
}
}

