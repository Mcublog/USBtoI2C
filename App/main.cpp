#include <stdio.h>

#include "application.h"

int main(int argc, char* argv[]) {
    char* tty;
    // TODO: need more checks
    if (argc == 2) {
        tty = argv[1];
        printf("Usage: %s", tty);
        if (!freopen(tty, "r", stdin) || !freopen(tty, "w", stdout)) {
            perror("freopen");
            return -1;
        }
    }
    application();
}