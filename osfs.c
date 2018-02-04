/*
* File system implementation in Userspace using FUSE.
* 
* PES University UE15CS352
* This program is written as a part of academic course.
*/

#define FUSE_USE_VERSION 31
#ifdef HAVE_CONFIG_H
#include <config.h>
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
#include <sys/stat.h>
#include <string.h>
#ifdef HAVE_SETXATTR
#include <sys/xattr.h>
#endif

static int osfs_getattribute(const char *path, struct stat  *buf, struct fuse_file_info file){
	fprintf(stderr,"\nIn init");
	(void) file;
	int res;
	buf->st_uid = getuid();
	buf->st_gid = getgid();
	buf->st_atime = time(NULL);
	buf->st_mtime = time(NULL);
	res = lstat(path, buf);
	if(strcmp(path,"/") == 0){
		buf->st_mode = S_IFREG | 0644;
		buf->st_nlink = 2;
	}
	else{
		buf->st_mode =S_IFREG | 0644;
		buf->st_nlink = 1;
		buf->st_size = 1024;
	}
	if(res == -1){
		return -errno;
	}
	
	return 0;
}

static int osfs_access(const char *path, int mask){
	fprintf(stderr,"\nIn permission");
	int res;
	res = access(path,6);
	fprintf(stderr,"\nPermission mode : %d",mask);
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
	fprintf(stderr,"\n 1 Directory successfully made.");
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
	printf("\n");
}
