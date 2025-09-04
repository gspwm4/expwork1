#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include "cr_dir.h"
void create_directories(){
    if(mkdir("Assets", 0755) == 0){
        puts("Directory Assets create DONE...");
    }
    else{
        puts("WARNING You have directory Assets");
        return;
    }
    if(mkdir("Assets/Scripts", 0755) == 0){
        puts("Directory Assets/Scripts create DONE...");
    }
    else if(mkdir("Assets/Scripts", 0755) == -1){
        puts("WARNING You have directory Assets/Scripts");
        return;
    }
    if(mkdir("Assets/Textures", 0755) == 0){
        puts("Directory Assets/Textures create DONE...");
    }
    else{
        puts("WARNING You have directory Assets/Textures");
        return;
    }
}

int check_directories(const char *path){
    DIR *op_path = opendir(path);
    if(op_path == NULL){
        fprintf(stderr, "Open %s directory ERROR\n", path);
        return EXIT_FAILURE;
    }
    struct dirent *en_path;
    int read_count;
    while((en_path = readdir(op_path)) != NULL){
        fprintf(stdout, "In directory %s have %s\n", path, en_path->d_name);
        read_count++;
    }
    closedir(op_path);
    return read_count++;
}
