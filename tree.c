//Chelsea Lantigua
//CSc 332 - Group Project
//Group A - Tree
//28 April 2021

//  the tree command will create a directory called Dir0. Then it will change the working directory to Dir0, and create empty text files t1.txt, t2.txt, t3.txt, and one empty directory, called Dir1, inside of it.

#include <stdio.h> //refers to perror and fopen command
//both libraries below are used to create a directory
#include <sys/stat.h>
#include <sys/types.h>
//this library is used for chdir - to change the directory
#include <unistd.h>
//this library will check the errno value for the fopen command
#include <errno.h>

void Tree(){
    //there is an error when trying to create a directory called Dir0
    if(mkdir("Dir0", 0777) == -1){
        perror("mkdir");
    }
    //directory Dir0 is successfully made
    else{
        printf("directory successfully created \n");
        // change directory to Dir0
        int change = chdir("Dir0");
        //error in changing directory
        if(change < 0){
            printf("Change of directory is not successful\n");
        }
        //we are now in dir0
        else{
            printf("Dir0 created \n");
            FILE *file1, *file2, *file3;
            errno = 0;
            //create t1.txt
            file1 = fopen("t1.txt", "w");
            //check if there was an error in creating the file
            if(errno != 0){
                perror("error when creating the file \n");
            }
            //if there is no error then print following message
            else{ 
                printf("t1.txt created \n");
                
            }
            
            //resets the value of errno
            errno = 0;
            //create t2.txt
            file2 = fopen("t2.txt", "w");
            //check if there was an error in creating the file
            if(errno != 0){
                perror("error when creating the file \n");
            }
            //if there is no error then print following message
            else{
                printf("t2.txt created \n");
            }
            
            //resets the value of errno
            errno = 0;
            //create t3.txt
            file3 = fopen("t3.txt", "w");
            //check if there was an error in creating the file
            if(errno != 0){
                perror("error when creating the file \n");
            }
            //if there is no error then print following message
            else{
                printf("t3.txt created \n");
            }
            
            fclose(file1); //will close t1.txt
            fclose(file2); //will close t2.txt
            fclose(file3); //will close t3.txt
            
            //error in creating an empty directory, called Dir1, within Dir0
            if(mkdir("Dir1", 0777) == -1){
                perror("mkdir");
            }
            //sucessfully created an empty directory, called Dir1, within Dir0
            else{
                printf("Dir1 created \n");
            }
        }
    }
}

