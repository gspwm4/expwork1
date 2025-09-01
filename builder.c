#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "cr_dir.h"
int main(){
    char buff[1024];
    const char *dir_path = "dir";
    const char *dir_file = "dir/hello";
    const char *dir_assets = "Assets";

    struct stat dir_info;
    struct stat file_info;

    create_directories(dir_assets);

    int dir_stat = stat(dir_path, &dir_info);

    if(dir_stat == 0){
        if(S_ISDIR(dir_info.st_mode)){
         fprintf(stdout, "Check directory \033[32mfind directory %s\033[0m\n", dir_path);               
        }
    }
    else if(dir_stat == -1){
        fprintf(stderr, "Check directory \033[31mdidn't find a %s\033[0m\n", dir_path);
        return EXIT_FAILURE;
    }

    DIR *op_dir = opendir(dir_path);

    if(op_dir == NULL){
        fprintf(stderr, "Open directory \033[31mERROR\033[0m\n");
        return EXIT_FAILURE;
    }
    else{
        fprintf(stdout, "Open directory DONE...\n");
    }

    struct dirent *exam;

    while((exam = readdir(op_dir)) != NULL){
       fprintf(stdout, "In directory %s have %s\n",dir_path, exam->d_name);
        if(exam->d_type == DT_DIR){
            fprintf(stdout, "Find and read directory %s\n",dir_path);
            break;
        }
    }

    int file_stat = stat(dir_file, &file_info);

    if(file_stat == -1){
        fprintf(stderr, "Check file \033[31mdidn't find a path file %s\033[0m\n", dir_file);
        return EXIT_FAILURE;
    }
    else if(!S_ISREG(file_info.st_mode)){
        fprintf(stderr, "Check file \033[31mis not regular file %s\033[0m\n", dir_file);
        return EXIT_FAILURE;
    }
    else{
        fprintf(stdout, "Check file \033[32mfind a path file %s\033[0m\n", dir_file);
    }
    FILE *op_file = fopen(dir_file, "rb");

    if(op_file == NULL){
        perror("\033[31mOpen file ERROR\033[0m");
        return EXIT_FAILURE;
    }
    else{
        fprintf(stdout, "Open file path %s \033[32mDONE...\033[0m\n", dir_file);
    }
    size_t bin_read;

    bin_read = fread(buff, sizeof(*buff), sizeof(buff), op_file);

    if(bin_read == 0){
        fprintf(stderr, "\033[31mRead file ERROR\033[0m\n");
        fclose(op_file);
        return EXIT_FAILURE;
    }

    else if(ferror(op_file)){
        fprintf(stderr, "\033[31OStream file path ERROR\033[0m");
        fclose(op_file);
        return EXIT_FAILURE;
    }
    else{
        fprintf(stdout, "Read file path %s \033[32mDONE...\033[0m\n", dir_file);
    }
    int ch_per = chmod(dir_file, file_info.st_mode | S_IXUSR);
    if(ch_per == -1){
        fprintf(stdout, "Change %s execution permissions \033[31mERROR...\033[0m\n", dir_file);
        return EXIT_FAILURE;
    }
    else{
        fprintf(stdout, "Change %s execution permissions \033[32mDONE...\033[0m\n", dir_file);
    }
    fprintf(stdout, "File execution...\n");
    fflush(stdout);
    int ex_fl = execl(dir_file, "hello", NULL);
    fflush(stdout);
    if(ex_fl == -1){
        fprintf(stderr, "file %s execution \033[31mERROR\033[0m\n", dir_file);
        return EXIT_FAILURE;
    }
    closedir(op_dir);
    return 0;
}
