#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include "cr_dir.h"
int create_directories(const char *path){
    if(mkdir("Assets", 0755) == 0){
        puts("Directory Assets create DONE...");
    }
    else{
        puts("Directory Assets create ERROR... You have directory Assets");
        return EXIT_FAILURE;
    }
    if(mkdir("Assets/Scripts", 0755) == 0){
        puts("Directory Assets/Scripts create DONE...");
    }
    else if(mkdir("Assets/Scripts", 0755) == -1){
        puts("Directory Assets/Scripts create ERROR. You have directory Assets/Scripts");
        return EXIT_FAILURE;
    }
    if(mkdir("Assets/Textures", 0755) == 0){
        puts("Directory Assets/Textures create DONE...");
    }
    else{
        puts("Directory Assets/Textures create ERROR. You have directory Assets/Textures");
        return EXIT_FAILURE;
    }
    DIR *op_assets = opendir(path);
    if(op_assets == NULL){
        fprintf(stderr, "Open %s directory ERROR\n", path);
        return EXIT_FAILURE;
    }
    struct dirent *en_assets;
    int read_count;
    while((en_assets = readdir(op_assets)) != NULL){
        fprintf(stdout, "In directory %s have %s\n", path, en_assets->d_name);
        read_count++;
    }
    closedir(op_assets);
    return read_count;
}
