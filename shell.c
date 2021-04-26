#include "tree.c"
#include "list.c"
#include "path.c"
#include "exit.c"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifndef SHELL_H
#define SHELL_H

void print_prompt1(void);
// void print_prompt2(void);

char *read_cmd(void);

#endif

void print_prompt1(void)
{
    fprintf(stderr, "# ");
}

int main(int argc, char **argv)
{
    char *command;

    do
    {
        command = read_cmd();
        print_prompt1();

        if (!command)
        {
            exit(EXIT_SUCCESS);
        }

        else if (command[0] == '\0' || strcmp(command, "\n") == 0)
        {
            free(command);
            continue;
        }

        else if (strcmp(command, "exit\n") == 0)
        {
            free(command);
            break;
        }
        
        else if(strcmp(command, "list") == 0)
        {
			List();
            continue;
		}

        printf("%s\n", command);

        free(command);

    } while (1);

    exit(EXIT_SUCCESS);
}

char *read_cmd(void)
{
    char buf[1024];
    char *ptr = NULL;
    char ptrlen = 0;

    while (fgets(buf, 1024, stdin))
    {
        int bufferlen = strlen(buf);

        if (!ptr)
        {
            ptr = malloc(bufferlen + 1);
        }
        else
        {
            char *ptr2 = realloc(ptr, ptrlen + bufferlen + 1);

            if (ptr2)
            {
                ptr = ptr2;
            }
            else
            {
                free(ptr);
                ptr = NULL;
            }
        }

        if (!ptr)
        {
            fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
            return NULL;
        }

        strcpy(ptr + ptrlen, buf);

        if (buf[bufferlen - 1] == '\n')
        {
            if (bufferlen == 1 || buf[bufferlen - 2] != '\\')
            {
                return ptr;
            }

            ptr[ptrlen + bufferlen - 2] = '\0';
            bufferlen -= 2;
            // print_prompt2();
        }

        ptrlen += bufferlen;
    }

    return ptr;
}
