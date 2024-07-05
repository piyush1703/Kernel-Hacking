#include "types.h"
#include "user.h"
#include "fcntl.h"

#define MAX_PATH_LEN 256

int main() {

    char* pathname = "testfile.txt";

    // Trace the specified pathname
    if (trace(pathname) < 0) {
        printf(1, "Failed to trace pathname\n");
        exit();
    }
    
    int fd=open(pathname,O_CREATE| O_RDWR);
    if(fd<0) {
      printf(1,"Error fail to open file: %d\n",fd);
      exit();
    }
    // Get the trace count
    int count = getcount();
    close(fd);
    printf(1, "Trace count: %d\n", count);

    fd=open(pathname,O_CREATE| O_RDWR);
    if(fd<0) {
      printf(1,"Error fail to open file: %d\n",fd);
      exit();
    }
    // Get the trace count
    count = getcount();
    close(fd);
    printf(1, "Trace count: %d\n", count);
    

    exit();
}

