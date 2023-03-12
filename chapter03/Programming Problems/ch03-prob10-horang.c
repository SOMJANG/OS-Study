#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 512
#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[])
{
    int fd[2];
    char writetext[BUFFER_SIZE];
    char readtext[BUFFER_SIZE];
    char source_filename[BUFFER_SIZE];
    char destination_filename[BUFFER_SIZE];
    strcpy(source_filename,argv[1]);
    strcpy(destination_filename,argv[2]);
    pid_t pid;
    if (pipe(fd) == -1){
        fprintf(stderr,"Pipe failed");
        return 1;
    }
    pid = fork();
    if (pid > 0) { // parent
        /* file read from source_filename*/
        FILE *sfd = fopen(source_filename,"r");
        // fread(&writetext,BUFFER_SIZE,1,sfd);
        fscanf(sfd,"%s",writetext);
        printf("%s",writetext);
        fclose(sfd);
        /* file read from source_filename*/
        close(fd[READ_END]);
        write(fd[WRITE_END],writetext,strlen(writetext)+1);
        close(fd[WRITE_END]);
        wait();
        printf("END\n");
        return 0;
    }else {
        close(fd[WRITE_END]);
        read(fd[READ_END],readtext,BUFFER_SIZE);
        close(fd[READ_END]);
        /* file write to destination_filename*/
        FILE *dfd = fopen(destination_filename,"w");
        // fwrite(&readtext,BUFFER_SIZE,1,dfd);
        fprintf(dfd,"%s\n",readtext);
        fclose(dfd);
        return 0;
    }
}