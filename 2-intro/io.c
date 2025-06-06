// A Program That Does I/O

#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    int fd = open("/tmp/file",
                    O_WRONLY | O_CREAT | O_TRUNC,
                    S_IRWXU);
    assert(fd > -1);
    int rc = write(fd, "Bikund Kumar\n", 14);
    assert(rc == 14);
    close(fd);

    return 0;
}