#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include "main1.h"
void create_directories(){
    if(mkdir("Assets", 0755) == 0){
        puts("Directory Assets create DONE...");
    }
    else if (errno == EEXIST){
        puts("WARNING You have directory Assets");
    }
    if(mkdir("Assets/Scripts", 0755) == 0){
        puts("Directory Assets/Scripts create DONE...");
    }
    else if(errno == EEXIST){
        puts("WARNING You have directory Assets/Scripts");
    }
    if(mkdir("Assets/Textures", 0755) == 0){
        puts("Directory Assets/Textures create DONE...");
    }
    else if(errno == EEXIST){
        puts("WARNING You have directory Assets/Textures");
    }
}

void check_directories(const char *path){
    DIR *op_path = opendir(path);
    if(op_path == NULL){
        fprintf(stderr, "Open %s directory ERROR\n", path);
        return;
    }
    closedir(op_path);
} 
