#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void listener(int sig) {
    switch (sig) {
        case SIGTERM:
            printf("Вызван SIGTERM\n");
            exit(0);
    }
}
 
int main() {
    struct sigaction sa;
    sigset_t newset;
    sigemptyset(&newset);
    sigaddset(&newset, SIGINT);
    sigprocmask(SIG_BLOCK, &newset, 0);
    sa.sa_handler = listener;
    sigaction(SIGTERM, &sa, 0);
    printf("My pid is %i\n", getpid());
    printf("Waiting...\n");
    while(1)
        pause();
    return 0;
}