#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "cr_dir.h"
int main(){
    char buff[1024];
    const char *dir_assets = "Assets";
    const char *dir_textures = "Assets/Textures";
    const char *dir_scripts = "Assets/Scripts";

    struct stat dir_info;
    struct stat file_info;

    create_directories();
    check_directories(dir_assets);
    check_directories(dir_textures);
    check_directories(dir_scripts);

    if(mkdir("dir", 0755) == 0){
        fprintf(stdout, "Create directory dir DONE...\n");
    }
    else if(mkdir("dir", 0755) == -1){
        fprintf(stderr, "Create directory dir WARNING. You have directory dir\n");
    }

    if(stat("dir", &dir_info) == 0){
        if(S_ISDIR(dir_info.st_mode)){
         fprintf(stdout, "Check directory \033[32mfind directory dir\033[0m\n");               
        }
    }
    else if(stat("dir", &dir_info) == -1){
        fprintf(stderr, "Check directory \033[31mdidn't find a dir\033[0m\n");
        return EXIT_FAILURE;
    }

    DIR *op_dir = opendir("dir");

    if(op_dir == NULL){
        fprintf(stderr, "Open directory \033[31mERROR\033[0m\n");
        return EXIT_FAILURE;
    }
    else{
        fprintf(stdout, "Open directory DONE...\n");
    }

    struct dirent *exam;

    while((exam = readdir(op_dir)) != NULL){
       fprintf(stdout, "In directory dir have %s\n", exam->d_name);
        if(exam->d_type == DT_DIR){
            fprintf(stdout, "Find and read directory dir\n");
            break;
        }
    }

    FILE *op_file = fopen("dir/hello", "w");

    if(op_file == NULL){
        perror("\033[31mOpen file ERROR\033[0m");
        return EXIT_FAILURE;
    }
    else{
        fprintf(stdout, "Open file path dir/hello \033[32mDONE...\033[0m\n");
    }

    int file_stat = stat("dir/hello", &file_info);

    if(file_stat == -1){
        fprintf(stderr, "Check file \033[31mdidn't find a path file dir/hello\033[0m\n");
        return EXIT_FAILURE;
    }
    else if(!S_ISREG(file_info.st_mode)){
        fprintf(stderr, "Check file \033[31mis not regular file hello\033[0m\n");
        return EXIT_FAILURE;
    }
    else{
        fprintf(stdout, "Check file \033[32mfind a path file dir/hello\033[0m\n");
    }
    char *text = "#!/bin/bash\necho \"Hell, World!\"\n");
    fprintf(op_file, "%s", text);
    fclose(op_file);

    size_t bin_read;

    FILE *r_file = fopen("dir/hello", "rb");

    if(r_file == NULL){
        fprintf(stderr, "Read file \033[31ERROR\033[0m\n");
        return EXIT_FAILURE;
    }

    bin_read = fread(buff, sizeof(*buff), sizeof(buff), r_file);

    if(bin_read == 0){
        fprintf(stderr, "\033[31mRead file ERROR\033[0m\n");
        fclose(r_file);
        return EXIT_FAILURE;
    }

    else if(ferror(r_file)){
        fprintf(stderr, "\033[31OStream file path ERROR\033[0m");
        fclose(r_file);
        return EXIT_FAILURE;
    }
    else{
        fprintf(stdout, "Read file path dir/hello \033[32mDONE...\033[0m\n");
    }
    fclose(r_file);
    int ch_per = chmod("dir/hello", file_info.st_mode | S_IXUSR);
    if(ch_per == -1){
        fprintf(stdout, "Change file hello  execution permissions \033[31mERROR...\033[0m\n");
        return EXIT_FAILURE;
    }
    else{
        fprintf(stdout, "Change file hello execution permissions \033[32mDONE...\033[0m\n");
    }
    fprintf(stdout, "File execution...\n");
    fflush(stdout);
    int ex_fl = execl("dir/hello", "dir/hello", NULL);
    fflush(stdout);
    if(ex_fl == -1){
        fprintf(stderr, "file hello execution \033[31mERROR\033[0m\n");
        return EXIT_FAILURE;
    }
    closedir(op_dir);
    return 0;
}
