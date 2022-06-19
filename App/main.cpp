#include <stdio.h>

#include "application.h"
#include "cobsr.h"

void cobs_test(void)
{
    uint8_t dst_buf[64];
    uint8_t src_buf[64];

    for (int i = 0; i < 32; i++) {
        src_buf[i] = i;
    }

    cobsr_encode_result result = cobsr_encode(dst_buf, 64, src_buf, 32);
    printf("%d\r\n", result.status);
}

int main(int argc, char* argv[]) {
    char* tty;
    cobs_test();
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