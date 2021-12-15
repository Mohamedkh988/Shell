#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <libgen.h>
#define MAX_SIZE 512

int readCommand(char command[]) 
/* 
This function takes input from the user and saves it in command array
*/
{
int overSize=0;   //this flag is to indicate if command is over 512 byte
fgets(command,(MAX_SIZE+2),stdin);    //passing user's input to command array
if ((strlen(command) == (MAX_SIZE+1)) && command[MAX_SIZE]!='\n')     //to check that iser entered oversize
	overSize=1;
command[strlen(command)-1]='\0';    //removing the \n as it makes mistakes while excuting execvp 
return overSize;
}

int isEmpty(char str[])
/*
This function to indicate if the array is empty
*/
{
int i=0;
while (str[i])
{
    if (!isspace(str[i]))
     {
        return 0;
     }
       i++;
}
return 1;
}


int parse(char str[], char* tokens[])
{
  /*
This function is used to parse the input , it divides the array into many tokens splitted by spaces
  */
int backGround=0;     //a flag used to indicate if the command should run on background or foreground
int i=0;
tokens[0] = strtok(str," ");    //usig strtoken to split the array
while( tokens[i] != NULL ) 
   {
    i++;
    tokens[i] = strtok(NULL, " ");
   }

if (strcmp(tokens[i-1],"&") == 0)     //check if & is the last tokken (check if background)
	{
	tokens[i-1]=NULL;
	backGround=1;
	}
return backGround;
}



void excute(char* args[])
{
  /*
This function excutes what is supplied in the arrguments
  */

if(execvp(args[0],args)== -1)     //excute and check for errors
    if(strcmp(args[0],"exit")!=0)   //exit  is not a cmmand so it will return an error but we need to neglect that
       perror("Error");
}




int main()
{
 char* args[15];    //array of strings (or array of pointers to theses strings)
 int overSize;    //flag to check if command is more than 512 byte
 int empty;   //flag to check if the array is empty (no command were input)
 int backGround=0;    //a flag used to indicate if the command should run on background or foreground
 char command[MAX_SIZE+2];    //array to take the command as a string
 pid_t pid;   //process ID
 int status;  //to check id child has finished

 while(strcmp(args[0],"exit")!=0)     //the function excutes until it reads "exit"
 {
   printf("Shell> ");
   if (readCommand(command))    //if it returned error print error
       fprintf(stderr, "Error: command is over size \n");
   else if (isEmpty(command))    //if empy print warning
       printf("Warning: No command was entered \n");
   else
   {
     backGround=parse(command, args);   
     if (strcmp(args[0],"cd")==0)     //if the command is change directory it should be handled without forking
    	  chdir((args[1]));
     else	 //if there are no errors and commands is not cd fork
     {
       pid = fork();
     }       
     if (pid == 0)   /* child */
     {
        excute(args);
        return 0;
     }
     else    /* parent */
     { 
         if (!backGround)  //if command should run in forground parent should wait for child
             waitpid(pid, &status, 0);
     }
   } 

 }
 return 0;
}
