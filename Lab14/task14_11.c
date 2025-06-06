#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <stdint.h>
#include <errno.h>

#define MAX_EVENTS 64

typedef struct {
    int fd;
    char name[64];
} Event;

void add_event(int epoll_fd, int seconds, const char *event_name, Event *event) {
    int tfd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (tfd == -1) {
        perror("timerfd_create");
        exit(1);
    }

    struct itimerspec ts = {
        .it_value = { .tv_sec = seconds, .tv_nsec = 0 },
        .it_interval = { 0, 0 } // одноразовий
    };

    if (timerfd_settime(tfd, 0, &ts, NULL) == -1) {
        perror("timerfd_settime");
        close(tfd);
        exit(1);
    }

    struct epoll_event ev = { .events = EPOLLIN, .data.fd = tfd };
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, tfd, &ev) == -1) {
        perror("epoll_ctl ADD");
        close(tfd);
        exit(1);
    }

    event->fd = tfd;
    strncpy(event->name, event_name, sizeof(event->name));
}

void remove_event(int epoll_fd, Event *event) {
    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, event->fd, NULL);
    close(event->fd);
    printf("Event '%s' removed.\n", event->name);
}
  
int main() {
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        exit(1);
    }

    Event events[10];
    int event_count = 0;

    // Додаю кілька подій з таймерами
    add_event(epoll_fd, 5, "Backup Event", &events[event_count++]);
    add_event(epoll_fd, 10, "Reminder", &events[event_count++]);
    add_event(epoll_fd, 15, "Session Timeout", &events[event_count++]);

    struct epoll_event triggered[MAX_EVENTS];

    while (event_count > 0) {
        int n = epoll_wait(epoll_fd, triggered, MAX_EVENTS, -1);
        if (n == -1) {
            perror("epoll_wait");
            break;
        }

        for (int i = 0; i < n; ++i) {
            uint64_t expirations;
            read(triggered[i].data.fd, &expirations, sizeof(expirations)); // очищення

            // Знаходжу і обробляю подію
            for (int j = 0; j < event_count; ++j) {
                if (events[j].fd == triggered[i].data.fd) {
                    printf(">>> Event '%s' triggered!\n", events[j].name);
                    remove_event(epoll_fd, &events[j]);

                    // Зміщую решту
                    for (int k = j; k < event_count - 1; ++k)
                        events[k] = events[k + 1];
                    --event_count;

                    break;
                }
            }
        }
    }

    close(epoll_fd);
    return 0;
}
