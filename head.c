#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h> 
#include<sys/stat.h>
#include<fcntl.h>
#include<err.h>
#include<string.h>

void n_comand(int file, int n){
    int lines = 0;
    char symbol;
    int read_status = read(file, &symbol, 1);
    while(read_status == 1){
        if(symbol == '\n'){
            lines++;
        }
        if(lines == n){
            return;
        }
        printf("%c", symbol);
        read_status = read(file, &symbol, 1);
    }
    return;
}

int main(int argc, char* argv[]){
    if(argc == 1){
        errx(1, "Error. You have to give a file");
    }
    
    int file = open(argv[1], O_RDONLY);
    if(file == -1){
        errx(1, "Error. Can't open file");
    }
    
    if(argc == 2){
        n_comand(file, 10);
    }    
    
    if(argc > 2){
        if(strcmp(argv[2], "-n") == 0){
            int n = atoi(argv[3]);
            if(n <= 0){
                errx(1, "Error. You have to give a positive number argument");
            }
            n_comand(file, n);
        }
    }
    
    printf("\n");
    close(file);
    exit(0);
}