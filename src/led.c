#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/led.h"

int32_t open_cpld() {
    int32_t fd;
    if (access("/dev/cpld_periph", F_OK) == 0) {
        fd = open("/dev/cpld_periph", O_RDWR);
    } else {
        fd = -1;
    }
    return fd;
}

void usage() {
    puts("Led Control v0.1\n\nUsage: led <options>\n\nOptions: \n\t-b[fast|slow|pulse|on|off]  Blue led mode\n\t-y[fast|slow|on|off]        Yellow led mode\n\t-l[on|off]                  Light on/off   \n\nExample: led -bon -lon\n");
}

void run2(int32_t fd, int offset) {
    ioctl(fd, (DEVICE_NUM << 8) + offset );
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        usage();
        return 1;
    }

    int32_t fd = open_cpld();
	if (fd < 0) {
        puts("Error: cannot open /dev/cpld_periph");
        return 1;
    }

    int opt;
    while((opt = getopt(argc, argv, ":b:y:l:")) != -1)
    {
        switch (opt) {
            case 'b':
                if (strcmp(optarg, "on") == 0) {
                    run2(fd, 0x0a);
                    run2(fd, 0x01);
                }

                if (strcmp(optarg, "off") == 0) {
                    run2(fd, 0x02);
                }

                if (strcmp(optarg, "fast") == 0) {
                    run2(fd, 0x03);
                }

                if (strcmp(optarg, "slow") == 0) {
                    run2(fd, 0x04);
                }

                if (strcmp(optarg, "pulse") == 0) {
                    run2(fd, 0x05);
                }
                break;
            case 'y':
                if (strcmp(optarg, "on") == 0) {
                    run2(fd, 0x09);
                    run2(fd, 0x02);
                }
                if (strcmp(optarg, "fast") == 0) {
                    run2(fd, 0x0b);
                }

                if (strcmp(optarg, "slow") == 0) {
                    run2(fd, 0x0c);
                }

                if (strcmp(optarg, "off") == 0) {
                    run2(fd, 0x0a);
                }
                break;
            case 'l':
                if (strcmp(optarg, "on") == 0) {
                    run2(fd, 0x1c);
                }
                if (strcmp(optarg, "off") == 0) {
                    run2(fd, 0x1b);
                }
                break;
            case '?':
                usage();
                break;
        }
    }

    return 0;
}