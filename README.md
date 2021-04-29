# Command Shell Project

CSc 332 - Operating Systems  
Professor Zaid Al-Mashhadani  
The City College of New York  
Spring '21  

### Task:
The object of this assignment is to gain experience with some advanced programming techniques like process creation and control, file descriptors, signals and possibly pipes. To do this, a team of 5 students will be working together to write their own command shell - much like csh, bsh or the DOS command shell.

Each member the team will write the code for one of the following customized commands:

1. shell*: The environment that will execute the rest of the commands. The shell won’t terminate unless the exit command gets executed. The shell displays a different command prompt (i.e. something other than $ and >).
3. tree*: This new command will create a directory and call it Dir0. Then it will change the working directory to Dir0 and create three empty text files namely, t1.txt, t2.txt, t3.txt, and one empty directory, called Dir1, inside it.
4. list*: This new command will clear the terminal screen and print a detailed list of all content of the current directory (like ls -l) to the terminal and t1.txt. Finally, it will change the name of t1.txt to tree.txt.
5. path*: This new command will print the path of the current directory to the terminal and t2.txt, and change the name of t2.txt to path.txt. It will then concatenate the content of tree.txt and path.txt into t3.txt and rename it to log.txt. Finally, it will delete tree.txt and path.txt.
6. exit*: This new command will print a list of the last 4 commands to the terminal andit a detailed list of all content of the current directory (like ls -l). Finally, it will wait for the user to hit the “return” key to terminate the shell and return the control to the original shell program on your machine.

### Implementation notes:
Aside from being able to call the above, user-defined commands, our terminal passes all other commands into an execvp to execute them as normal. Thus, any regular linux command works as expected when called in shell.
