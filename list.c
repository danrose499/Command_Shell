//Viviana Perls
//CSC 332
//Group A: list
//28 April 2021
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int clearpid, lspid;
    int clearstatus = 0;
    int lsstatus = 0;

    clearpid = fork();

    if(clearpid == 0){
        //inside child process
        execlp("clear", "clear", NULL);
        return 0;
    }  

    while(!WEXITSTATUS(clearstatus)){
        waitpid(clearpid, &clearstatus, 0);
    }
    printf("exited clear process normally\n");

    
    lspid = fork();

    if(lspid == 0){
        //inside the child process
        execlp("ls", "ls", "-l", NULL);
        return 0;
    }

    while(!WEXITSTATUS(lsstatus)){
        waitpid(lspid, &lsstatus, 0);
    }

    return 0;
}