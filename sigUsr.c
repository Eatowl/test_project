#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
 
void listener(int sig) {
    switch (sig) {
        case SIGUSR1:
            printf("Вызван SIGUSR1\n");
    }
}
 
int main() {
    if (signal(SIGUSR1, listener) == SIG_ERR) {
        perror("error signal");
        return 1;
    }
    printf("Посылаем сигнал\n");
    if (raise(SIGUSR1) != 0) {
        perror("error raise");
        return 1;
    }
    return 0;
}