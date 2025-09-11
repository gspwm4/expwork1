#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include "main1.h"
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

void check_directories(const char *path){
    DIR *op_path = opendir(path);
    if(op_path == NULL){
        fprintf(stderr, "Open %s directory ERROR\n", path);
        return;
    }
    struct dirent *en_path;
    while((en_path = readdir(op_path)) != NULL){
        fprintf(stdout, "In directory %s have %s\n", path, en_path->d_name);
    }
    closedir(op_path);
}
