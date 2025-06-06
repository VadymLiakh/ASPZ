#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>

void *signal_handler_thread(void *arg) {
    int *signals = (int *)arg;
    sigset_t set;
    siginfo_t info;

    sigemptyset(&set);
    sigaddset(&set, signals[0]);
    sigaddset(&set, signals[1]);

    char thread_name[16];
    pthread_getname_np(pthread_self(), thread_name, sizeof(thread_name));
    printf("%s is waiting for signals...\n", thread_name);

    while (1) {
        if (sigwaitinfo(&set, &info) > 0) {
            printf("%s received signal: %d from PID %d\n",
                   thread_name, info.si_signo, info.si_pid);
        }
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int sigs1[] = {SIGUSR1, SIGUSR2};
    int sigs2[] = {SIGTERM, SIGINT};

    // Маскую сигнали для всіх потоків
    sigset_t full_set;
    sigemptyset(&full_set);
    sigaddset(&full_set, SIGUSR1);
    sigaddset(&full_set, SIGUSR2);
    sigaddset(&full_set, SIGTERM);
    sigaddset(&full_set, SIGINT);
    pthread_sigmask(SIG_BLOCK, &full_set, NULL);

    pthread_create(&t1, NULL, signal_handler_thread, sigs1);
    pthread_setname_np(t1, "Handler-USR");

    pthread_create(&t2, NULL, signal_handler_thread, sigs2);
    pthread_setname_np(t2, "Handler-TERM");

    printf("Main thread PID: %d\n", getpid());

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
