/*
 
Rafael-David Sanchez
CSc 332
Group A - Path
28 April 2021
*/

#include <stdio.h>
#include <unistd.h>
#include <limits.h> // Where we get PATH_MAX from
#include <fcntl.h>

int Path(){

    char cwd[PATH_MAX]; // Current Working Directory
    getcwd(cwd,sizeof(cwd)); // Returns Null-Terminated String Containing an Absolute Path Name that is the Current Working Directory, places pathname in cwd
    printf("%s\n", cwd); // Prints Current Working Directory to Terminal
    
    int fdT2 = open("t2.txt", O_WRONLY); // Opens t2.txt in Write-Only Mode
    if(fdT2 < 0){ // Checks for Open Error
        printf("Error occured when opening file t2.txt\n");
        perror("open");
    }   

    else{ // If no Error, print path into t2.txt
        int i = 0;
        while(cwd[i] !='\0') { // While loop that goes until it reaches the null termination character 
            write(fdT2, cwd + i, 1); // Writes into t2.txt   
            i++;
        }
    close(fdT2); // Closes fdT2
    }

    int name = rename("t2.txt", "path.txt"); // Renames t2.txt to path.txt
    if(name < 0){ // Checks for Renaming Error
        printf("Error renaming t2.txt\n");
        perror("rename");   
    }    
    
    int fdTree = open("tree.txt", O_RDONLY); // Opens tree.txt in Read-Only Mode
    if(fdTree < 0){ // Checks for Open Error
        printf("Error occured when opening tree.txt\n");
        perror("open");
        return 1;
    }
    
    int fdPath = open("path.txt", O_RDONLY); // Opens path.txt in Read-Only Mode
    if(fdPath < 0){ // Checks for Open Error
        printf("Error occured when opening path.txt\n");
        perror("open");
        return 1;    
    }
    
    int fdT3 = open("t3.txt", O_WRONLY);
    if(fdT3 < 0){ // Checks for Open Error
        printf("Error occured when opening t3.txt\n");
        perror("open");
        return 1;    
    }
    
    char buf[1];

    while(read(fdTree, buf,1) != 0){ // While Loop that Reads from tree.txt and Writes into t3.txt 
        write(fdT3, buf, 1);    
    }

    while(read(fdPath, buf,1) != 0){ // While Loop that Reads from path.txt and Writes into t3.txt
        write(fdT3, buf, 1);    
    }

    close(fdTree); // Closes tree.txt
    close(fdPath); // Closes path.txt
    close(fdT3); // Closes t3.txt

    name = rename("t3.txt", "log.txt"); // Changes name of t3.txt to log.txt
    if(name < 0){ // Checks for Renaming Error
        printf("Error renaming t3.txt\n");
        perror("rename");   
    }    
    
    int delete = remove("tree.txt"); // Deletes tree.txt
    if(delete != 0){ // Checks for Deletion Error
        printf("Error deleting tree.txt\n");
        perror("remove");   
    }    
    
    delete = remove("path.txt"); // Deletes path.txt
    if(delete != 0){ // Checks for Deletion Error
        printf("Error deleting path.txt\n");
        perror("remove");    
    }

    return 0;
}
