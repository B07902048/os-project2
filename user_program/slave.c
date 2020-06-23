#define _GNU_SOURCE
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
#define MAX_FILE_NUM 100
#define MAP_SIZE (PAGE_SIZE * 10)
int main (int argc, char* argv[]){
    char buf[BUF_SIZE];
    //char buf[BUF_SIZE];
    int N, dev_fd, file_fd, offset = 0;;// the fd for the device and the fd for the input file
    size_t ret, file_size = 0, data_size = -1;
    char file_name[MAX_FILE_NUM][50];
    char method[20];
    char ip[20];
    struct timeval start;
    struct timeval end;
    double trans_time; //calulate the time between the device is opened and it is closed
    char *kernel_address, *file_address;
    long mmap_size = sysconf(_SC_PAGE_SIZE);

    N = atoi(argv[1]);
    for(int i = 0; i < N; i++)
        strcpy(file_name[i], argv[i + 2]);
    strcpy(method, argv[N + 2]);
    strcpy(ip, argv[N + 3]);

    gettimeofday(&start ,NULL);
    for(int i = 0; i < N; i++){
        if((dev_fd = open("/dev/slave_device", O_RDWR)) < 0){//should be O_RDWR for PROT_WRITE when mmap()
        	perror("failed to open /dev/slave_device\n");
        	return 1;
        }
        
        if((file_fd = open(file_name[i], O_RDWR | O_CREAT | O_TRUNC)) < 0){
        	perror("failed to open input file\n");
        	return 1;
        }

        if(ioctl(dev_fd, 0x12345677, ip) == -1){//0x12345677 : connect to master in the device
        	perror("ioclt create slave socket error\n");
        	return 1;
        }

        write(1, "ioctl success\n", 14);

        char *src, *dst;
        size_t length;

        switch(method[0]){
            case 'f': //fcntl : read()/write()
            	do{
            	    ret = read(dev_fd, buf, sizeof(buf)); // read from the the device
            	    write(file_fd, buf, ret); //write to the input file
            	    file_size += ret;
            	} while(ret > 0);
            	break;
            case 'm': //mmap
                offset = 0;
                while(1){
                    length = ioctl(dev_fd, 0x12345678, 0);
                    if(length == 0){
                        file_size += offset;
                        break;
                    }
                    printf("slave length: %lu\n", length);
                    if((src = mmap(NULL, length, PROT_READ, MAP_SHARED, dev_fd, offset)) == (void *) -1) {
                        perror("slave mapping input device");
                        return 1;
                    }
                    
                    posix_fallocate(file_fd, offset, length);
                    if((dst = mmap(NULL, length, PROT_WRITE, MAP_SHARED, file_fd, offset)) == (void *) -1) {
                        perror("slave mapping output file");
                        return 1;
                    }
                    memcpy(dst, src, length);
                    ioctl(dev_fd, 0x12345676, (unsigned long)dst);
                    munmap(src, length);
                    munmap(dst, length);
                    offset += length;
                }
                break;
        }

        if(ioctl(dev_fd, 0x12345679) == -1){// end receiving data, close the connection
        	perror("ioclt client exits error\n");
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


