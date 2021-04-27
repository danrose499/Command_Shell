//Viviana Perls
//CSC 332
//Group A: list
//28 April 2021
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

// I'm using a struct here instead of a 2-element array because it is stored in memory
// in the same way, and it makes my code more readable.
struct Pipe{
    int read;
    int write;
};

void List(){
    int clearpid;
    int clearstatus = 1;
    struct Pipe pipeline;

    clearpid = fork();

    if(clearpid == 0){
        //inside child process
        execlp("clear", "clear", NULL);

    }  

    while(!WIFEXITED(clearstatus)){
        waitpid(clearpid, &clearstatus, 0);
    }

    
    pipe(&pipeline.read);
    int lspid = fork();
    int lsstatus = 1;

    if(lspid == 0){
        //inside the child process
        close(pipeline.read);
        dup2(pipeline.write,1); //passing stdout to the pipe
        execlp("ls", "ls", "-l", NULL);

    }

    while(!WIFEXITED(lsstatus)){
        waitpid(lspid, &lsstatus, 0);
    }

    // tee is a command which, according to the BSD General Commands Manual:
    // "copies standard input to standard output, making a copy in zero or more files.  The output is unbuffered."
    // Therefore, we can use tee here to write to t1.txt
    
    int teepid = fork();
    int teestatus = 1;
    if(teepid == 0){
        close(pipeline.write);
        dup2(pipeline.read,0);
        execlp("tee", "tee", "t1.txt", NULL);
        perror("tee");

    }

    close(pipeline.read);
    close(pipeline.write);

    while(!WIFEXITED(teestatus)){
        waitpid(teepid, &teestatus, 0);
    }

    rename("t1.txt", "tree.txt");

}
