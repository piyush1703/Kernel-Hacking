#include "types.h"
#include "fcntl.h"
#include "user.h"  // Include the header file containing getreadcount() declaration

#define BUF_SIZE 1024  // Define buffer size for reading

int main(int argc, char *argv[]) {
    char *path="testfile.txt";
    int read_count;

    // Get the read count
    read_count = getreadcount();

    // Print the read count and the content read from the file
    printf(1, "Number of read() calls: %d\n", read_count);
     
  

    // Open a file
    int fd = open(path,O_CREATE| O_RDWR);
    if (fd < 0) {
        printf(1, "Error: Failed to open file\n");
        exit();
    }

    // Read from the file
    char buf[BUF_SIZE];
    int bytes_read = read(fd, buf, BUF_SIZE);
    if (bytes_read < 0) {
        printf(1, "Error: Failed to read from file\n");
        close(fd);
        exit();
    }

    // Get the read count
    read_count = getreadcount();

    // Print the read count and the content read from the file
    printf(1, "Number of read() calls: %d\n", read_count);

    // Close the file
    close(fd);

    exit();
}


