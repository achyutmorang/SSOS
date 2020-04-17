#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main(void)
{
    int pfds[2];
    char buf[30];
    char msg[] = "test";

    if (pipe(pfds) == -1) {
	perror("pipe"); /* <stdio.h> */
	exit(1);  /* <stdlib.h> */
    }

    printf("writing \"%s\" to file descriptor #%d\n", msg, pfds[1]);
    write(pfds[1], msg, 5);

    printf("reading from file descriptor #%d\n", pfds[0]);
    read(pfds[0], buf, 5);
    printf("read \"%s\"\n", buf);

    return 0;
}
