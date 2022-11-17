#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h> 
#include<sys/stat.h>
#include<fcntl.h>
#include<err.h>
#include<string.h>


int count_lines(int file){
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
void print_all(int file){
    lseek(file, 0, SEEK_SET);
    char symbol;
    int read_status = read(file, &symbol, 1);
    while(read_status == 1){
        printf("%c", symbol);
        read_status = read(file, &symbol, 1);
    }
}
int bytes_to_n_line(int file, int n){
    lseek(file, 1, SEEK_SET);
    int lines = 0, bytes = 0;
    char symbol;
    int read_status = read(file, &symbol, 1);
    while(read_status == 1){
        bytes++;
        if(symbol == '\n'){
            lines++;
        }
        if(lines == n){
            return bytes + 1;
        }
        read_status = read(file, &symbol, 1);
    }
}
void last_n_lines(int file, int bytes){
    lseek(file, bytes, SEEK_SET);
    char symbol;
    int read_status = read(file, &symbol, 1);
    while(read_status == 1){
        printf("%c", symbol);
        read_status = read(file, &symbol, 1);
    }
}

int main(int argc, char* argv[]){
    if(argc == 1){
        errx(1, "Error. You have to give a file");
    }
            
    int file = open(argv[1], O_RDONLY);

    if(argc == 2){
        if(file == -1){
            errx(1, "Error. Can't open file");
        }
        int lines = count_lines(file);

        if(lines < 10){
            print_all(file);
        }else{
            int bytes = bytes_to_n_line(file, lines - 10);
            last_n_lines(file, bytes);
        }
    }    
    else if(argc > 2){
        if(strcmp(argv[2], "-n") == 0){
            int wanted_lines = atoi(argv[3]);
            if(wanted_lines <= 0){
                errx(1, "Error. You have to give a positive number argument");
            }
            int lines = count_lines(file);
            
            if(lines <= wanted_lines){
                print_all(file);
            }else{
                int bytes = bytes_to_n_line(file, lines - wanted_lines);
                last_n_lines(file, bytes);
            }
        }
    }  
    printf("\n");
    close(file);
    exit(0);
}