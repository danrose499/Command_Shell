//Viviana Perls
//CSC 332
//Group A: list
//28 April 2021
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

struct Pipe{
    int read;
    int write;
};

int main(int argc, char *argv[]){
    int clearpid;
    int clearstatus = 1;
    struct Pipe pipeline;

    clearpid = fork();

    if(clearpid == 0){
        //inside child process
        execlp("clear", "clear", NULL);
        return 1;
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
        dup2(pipeline.write,1);
        execlp("ls", "ls", "-l", NULL);
        return 1;
    }

    while(!WIFEXITED(lsstatus)){
        waitpid(lspid, &lsstatus, 0);
    }

    int teepid = fork();
    int teestatus = 1;
    if(teepid == 0){
        close(pipeline.write);
        dup2(pipeline.read,0);
        execlp("tee", "tee", "t1.txt", NULL);
        perror("tee");
        return 1;
    }

    close(pipeline.read);
    close(pipeline.write);

    while(!WIFEXITED(teestatus)){
        waitpid(teepid, &teestatus, 0);
    }

    rename("t1.txt", "tree.txt");

    return 0;
}