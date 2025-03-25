#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello (pid:%d) \n", (int) getpid());
    int rc = fork();

    if (rc < 0) {  // fork failed 
        fprintf(stderr, "fork failed\n");
        exit(1);    // exit
    }
    else if (rc == 0) {     // child (new process)  
        printf("child (pid:%d) \n", (int) getpid());
        char *myarg[3];
        myarg[0] = strdup("wc");    // program: "wc"
        myarg[1] = strdup("p3.c");  // arg: input file
        myarg[2] = NULL;        // arg: input file
        execvp(myarg[0], myarg);    // runs word count
        printf("this shouldn't print out"); 
    }
    else {          // parent goes down this path
        int rc_wait = wait(NULL);
        printf("parent of %d (rc_wait:%d) (pid:%d) \n",
        rc, rc_wait, (int) getpid());
    }
}

// Calling fork(), wait(), And exec()