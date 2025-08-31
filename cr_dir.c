#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "cr_dir.h"
int create_directories(void){
    if (mkdir("Assets", 0755) == 0){
        puts("Directory Assets create DONE...");
        return EXIT_SUCCESS;
    }
    else{
        puts("Directory Assets create ERROR. You have directory Assets");
        return EXIT_FAILURE;
    }
}
