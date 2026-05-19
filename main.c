#include<stdio.h>
#include<stdbool.h>  //used for boolean true
#include<string.h>

#define MAX_SIZE 512

int main(){

    char input[MAX_SIZE];
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
        printf("%s\n", input);
    }
    return 0;
}
