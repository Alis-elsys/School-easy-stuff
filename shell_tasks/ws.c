#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h> 
#include<sys/stat.h>
#include<fcntl.h>
#include<err.h>
#include<string.h>

int l_comand(int file){
    lseek(file, 0, SEEK_SET);
    int lines = 0, bytes = 0;
    char symbol;
    int read_status = read(file, &symbol, 1);
    while(read_status == 1){
        bytes++;
        if(symbol == '\n'){
            lines++;
            bytes++;
        }
        read_status = read(file, &symbol, 1);
    }
    return lines + 1;
}

int c_comand(int file){
    lseek(file, 0, SEEK_SET);
    int bytes = 0;
    char symbol;
    int read_status = read(file, &symbol, 1);
    while(read_status == 1){
        bytes++;
        read_status = read(file, &symbol, 1);
    }
    return bytes;
}

void compair(int file, char** argv, int index){
    if(strcmp(argv[index], "-l") == 0){
        int lines = l_comand(file);
        printf("%d \n", lines);
    }
    if(strcmp(argv[index], "-c") == 0){
        int bytes = c_comand(file);
        printf("%d \n", bytes);
    }
}

int main(int argc, char* argv[]){
    if(argc == 1){
        errx(1, "Not enough arguments");
    }
    int file = open(argv[1], O_RDONLY);
        
    if(argc == 2){
        if(file == -1){
            errx(2, "Error opening file");
        }
        int lines = l_comand(file);
        int bytes = c_comand(file);
        printf("%d %d \n", lines, bytes);
    }
        
    if(argc == 3){
        compair(file, argv, 2);
    }

    if(argc == 4){
        compair(file, argv, 2);
        compair(file, argv, 3);
    }

    close(file);
	exit(0);
}