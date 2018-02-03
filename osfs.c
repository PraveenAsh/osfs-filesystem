/*
* File system implementation in Userspace using FUSE.
* 
* PES University UE15CS352
* This program is written as a part of academic course.
*/

#define FUSE_USE_VERSION 31
#ifdef CONFIG_H
#include<config.h>
#endif
#ifdef linux
#define SOURCE_DEF 700
#endif
#include <fuse.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/stat>
#include <string.h>

static void *osfs_init(struct fuse_conn_info *connect, struct fuse_config *config){
	(void) connect;
	config->use_ino = 1;
	config->
	config->attr_timeout = 0;
	config->negative_timeout = 0;
	return NULL;
}

static int osfs_getattribute(const char *path, struct stat *stringbuf, struct fuse_file_info file){
	(void) file;
	int res;
	res = lstat(path, stbuf);
	if(res == -1){
		return -errno;
	}
	return 0;
}

static int osfs_access(const char *path, char *buf, size_t size){
	int res;
	res = readlink(path, buf, size-1);
	if(res == -1){
		return -errno;
	}
	return 0;
}

static int osfs_readlink(const char *path, char *buf, size_t size){
	int res;
	res = readlink(path, buf, size - 1);
	if(res == -1){
		return -errno;
	}
	buf[res] = '\0';
	return 0;
}


// TODO : complete these stub functions
// TODO : Please add approp print statements to viwe in debug mode.
// EX : fprintf(strr,"print something");
//parameter needed is path of the directory and file mode ie READ and WRITE
static int osfs_mkdir(const char *path, mode_t mode){
	//TODO : Function implementation here
	int res;
	res = mkdir(path, mode);
	if(res == -1)	return -errno;
	return 0;
}
static int osfs_open(){
	//TODO : Function implementation here
	return 0;
}
static int osfs_read(){
	//TODO : Function implementation here
	return 0;
}
static int osfs_write(){
	//TODO : Function implementation here
	return 0;
}
static int osfs_rmdir(){
	//TODO : Function implementation here
	return 0;
}
static int osfs_readdir(){
	//TODO : Function implementation here
	return 0;
}
static int osfs_rename(){
	//TODO : Function implementation here
	return 0;
}
static int osfs_link(){
	//TODO : Function implementation here
	return 0;
}
static int osfs_unlink(){
	//TODO : Function implementation here
	return 0;
}

static struct fuse_operations osfs = {
	.init 			=	osfs_init,
	.getattr 		=	osfs_getattribute,
	.access 		=	osfs_access,
	.readlink 		=	osfs_readlink,
	.mkdir 			=	osfs_mkdir,
	.open 			=	osfs_open,
	.read 			=	osfs_read,
	.write 			=	osfs_write,
	.rmdir 			=	osfs_rmdir,
	.readdir 		=	osfs_readdir,
	.rename 		=	osfs_rename,
	.link 			=	osfs_link,
	.unlink 		=	osfs_unlink,
};

int main(int argc, char *argv[]){
	return fuse_main(argc, argv, &osfs, NULL);
}
