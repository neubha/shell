#include<stdio.h>
#include<stdbool.h>  //used for boolean true
#include<string.h>
#include<unistd.h>
#include<stdlib.h> //for exit()
#include <sys/wait.h> //for waitpid

#define MAX_SIZE 512
#define MAX_ARGS 64

int main(){

    char input[MAX_SIZE];
    char* args[MAX_ARGS];

    //an infinite loop to take user input
    while (true){

        //prompt with a $
        printf("$ ");

        //flush the output buffer
        fflush(stdout);

        //gets the input in input and have an Max Size of max size
        //if gets null, show error and then prints an errorthen move to next step, i.e. $
        if(fgets(input, MAX_SIZE, stdin) == NULL){
            perror("fgets failed");
            continue;
        }

        //replace the new line from the input from the user with a string literal
        input[strcspn(input, "\n")] = '\0';
        if(strcmp(input, "exit" ) == 0){
            break;
        }

        //splits the input using " ", a single space, return pointer to the first token
        char* token = strtok(input," ");
        int i=0;

        //keep looping as long as token exist and array limit hasnt been reached
        //store the token in the args array and gets next token
        while(token!=NULL && i < MAX_ARGS){
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }

        //execvp() expects argument array ending with NULL.
        args[i] = NULL;

        //create a child process "pid", so the parent process remains working
        pid_t pid = fork();

        if(strcmp(args[0], "cd") == 0){
            if (args[1] == NULL){
                perror("cd: Missing Arguments");
            }

            //print error if chdir fails
            else if(chdir(args[1])!= 0){
                perror("cd Failed");
            }
        }

        //check if its a child process, and then execute if the process exist
        if(pid == 0){
            execvp(args[0], args); //if anything below execvp executeres, its an error
            perror("execvp failed"); 
            exit(EXIT_FAILURE); // we can "continue" if we want to omit the exist status
        }

        //check if its the parent process and display 
        else if (pid > 0){
            int status;
            waitpid(pid, &status, 0); //wait for the child process, store child exit information, and no special optins.
            printf("Exist status: %d\n", status);
        }

        //well if pid is -1, just means the fork process failed.
        else{
            printf("Fork failed");
        }

        printf("%s\n", input);
    }
    return 0;
}
