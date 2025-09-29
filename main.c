#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main1.h"
int main(){
    const char *dir_assets = "Assets";
    const char *dir_textures = "Assets/Textures";
    const char *dir_scripts = "Assets/Scripts";

    struct stat dir_info;

    create_directories();
    check_directories(dir_assets);
    check_directories(dir_textures);
    check_directories(dir_scripts);

    if(mkdir("dir", 0755) == 0){
        fprintf(stdout, "Create directory dir DONE...\n");
    }
    else{
        printf("Directory has already been created\n");
    }

    if(stat("dir", &dir_info) == 0){
        fprintf(stdout, "find \033[32mdirectory dir\033[0m\n");        
    }
    else if(stat("dir", &dir_info) == -1){
        perror("stat failed");
    }
    DIR *op_dir = opendir("dir");

    if(op_dir == NULL){
        perror("Open directory failed");
        return EXIT_FAILURE;
    }
    else{
        fprintf(stdout, "Open directory DONE...\n");
    }

    struct dirent *en_dir;

    while((en_dir = readdir(op_dir)) != NULL){
       if(strcmp(en_dir->d_name, ".") == 0 || strcmp(en_dir->d_name, "..") == 0){
           continue;
       }
       fprintf(stdout, "In directory dir have %s\n", en_dir->d_name);
        if(en_dir->d_type == DT_DIR){
            fprintf(stdout, "Find and read directory dir\n");
            break;
        }
    }

    FILE *op_file = fopen("dir/hello", "w");

    if(op_file == NULL){
        perror("fopen file failed");
        return EXIT_FAILURE;
    }
    else{
        fprintf(stdout, "Open file path dir/hello \033[32mDONE...\033[0m\n");
    }

    char *text = "#!/bin/bash\necho \"Hello, World!\"\n";
    int write_text = fprintf(op_file, "%s", text);
    if(write_text < 0){
        perror("Write text failed");
    }
    fclose(op_file);

    FILE *r_file = fopen("dir/hello", "rb");

    if(r_file == NULL){
        perror("fopen file failed");
        return EXIT_FAILURE;
    }
    int ch_per = chmod("dir/hello", 0755);
    if(ch_per == -1){
        perror("chmod failed");
        return EXIT_FAILURE;
    }
    else{
        fprintf(stdout, "Change file hello execution permissions \033[32mDONE...\033[0m\n");
    }
    fprintf(stdout, "File execution...\n");
    fflush(stdout);
    fclose(r_file);
    closedir(op_dir);
    pid_t pid = fork();
    if(pid == 0){
        execl("dir/hello", "dir/hello", NULL);
        exit(EXIT_FAILURE);
    }
    if(pid > 0){
        wait(NULL);

    }
    if(pid < 0){
        exit(1);
    }
    return 0;
}
