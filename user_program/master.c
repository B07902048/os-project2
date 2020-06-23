#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>


#define PAGE_SIZE 4096
#define BUF_SIZE 512
#define MAP_SIZE (10 * PAGE_SIZE)
#define MAX_FILE_NUM 100

size_t get_filesize(const char* filename);//get the size of the input file


int main (int argc, char* argv[]){
    char buf[BUF_SIZE];
    int N, dev_fd, file_fd;// the fd for the device and the fd for the input file
    size_t ret, file_size = 0, offset = 0;
    char file_name[MAX_FILE_NUM][50], method[20];
    char *kernel_address = NULL, *file_address = NULL;
    struct timeval start;
    struct timeval end;
    double trans_time; //calulate the time between the device is opened and it is closed


    N = atoi(argv[1]);
    for(int i = 0; i < N; i++)
        strcpy(file_name[i], argv[i + 2]);
    strcpy(method, argv[N + 2]);

    for(int i = 0; i < N; i++){
        if((dev_fd = open("/dev/master_device", O_RDWR)) < 0){
        	perror("failed to open /dev/master_device\n");
        	return 1;
        }
        gettimeofday(&start ,NULL);
        if((file_fd = open(file_name[i], O_RDWR)) < 0){
        	perror("failed to open input file\n");
        	return 1;
        }

        if((file_size = get_filesize(file_name[i])) < 0){
        	perror("failed to get filesize\n");
        	return 1;
        }

        if(ioctl(dev_fd, 0x12345677) == -1){ //0x12345677 : create socket and accept the connection from the slave
        	perror("ioclt server create socket error\n");
        	return 1;
        }

        char *src, *dst;
        size_t length;
        char fs_buf[BUF_SIZE];
        switch(method[0]){
            case 'f': //fcntl : read()/write()
                do{
                    ret = read(file_fd, buf, sizeof(buf)); // read from the input file
                    write(dev_fd, buf, ret);//write to the the device
                }while(ret > 0);
                break;
            case 'm': //mmap
                offset = 0;
                while (offset < file_size){
                    length = MAP_SIZE;
                    if(file_size - offset < length) length = file_size - offset;
                    if((src = mmap(NULL, length, PROT_READ, MAP_SHARED, file_fd, offset)) == (void *) -1) {
                        perror("master mapping input file");
                        return 1;
                    }
                    if((dst = mmap(NULL, length, PROT_WRITE, MAP_SHARED, dev_fd, offset)) == (void *) -1) {
                        perror("master mapping output device");
                        return 1;
                    }
                    memcpy(dst, src, length);
                    offset += length;
                    ioctl(dev_fd, 0x12345678, length);
                    munmap(src, length);
                    munmap(dst, length);
                }
                break;
        }

        if(ioctl(dev_fd, 0x12345679) == -1){ // end sending data, close the connection
        	perror("ioclt server exits error\n");
        	return 1;
        }
        close(file_fd);
        close(dev_fd);
    }
    gettimeofday(&end, NULL);
    trans_time = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)*0.0001;
    printf("Transmission time: %lf ms, File size: %ld bytes\n", trans_time, file_size / 8);

    return 0;
}

size_t get_filesize(const char* filename)
{
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}
