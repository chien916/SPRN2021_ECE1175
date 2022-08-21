#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

void timer_handler(int signum)
{
	puts("time_handler called\n");
}

int main()
{
	struct sigaction sa;
	struct itimerval timer;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &timer_handler;
	sigaction(SIGVTALRM, &sa, NULL);

	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = 500000;

	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 500000;

	setitimer(ITIMER_VIRTUAL, &timer, NULL);
	while(1);

}