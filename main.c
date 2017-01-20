#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	pid_t f_pid;
	f_pid = getpid();
	printf("parent pid -- %d\n", f_pid);
	if (fork() == 0) {
		pid_t pid1;
		pid1 = getpid();
		printf("parent %d <- child №1 %d\n", f_pid, pid1);
		if (fork() == 0) {
			pid_t new_child;
			new_child = getpid();
			printf("parent %d <- child №1 %d\n", pid1, new_child);
			return 2;
		}
		wait(0);
		return 1;
	}
	if (fork() == 0) {
		pid_t new_pid;
		new_pid = getpid();
		printf("parent %d <- child №2 %d\n", f_pid, new_pid);
		if (fork() == 0) {
			pid_t new_child1;
			new_child1 = getpid();
			printf("parent %d <- child №1 %d\n", new_pid, new_child1);
			return 2;
		}
		if (fork() == 0) {
			pid_t new_child2;
			new_child2 = getpid();
			printf("parent %d <- child №2 %d\n", new_pid, new_child2);
			return 2;
		}
		wait(0);
		return 1;
	}
	wait(0);
	return 0;
}
