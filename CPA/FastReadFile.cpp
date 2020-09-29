#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include"functionsbody.h"

typedef unsigned long long uint64;
using namespace std;

#define MAX_Size 60000



//uint64 buffSize = (1 << 29);
//char * bufTemp = (char*)malloc(sizeof(char)*buffSize);

void readFile(const char* file_name,char *&bufTemp,unsigned long long buffSize){

	const char  *rot_filename ;
	long long rot_fd = -1;
	off_t rot_total;
	void  *rot_base;
	uint64 tb;
	struct stat file_status;
	long long page_size = sysconf(_SC_PAGE_SIZE); /* needed for mmap */
	int ii = 0;
	char * buffer = (char*)malloc(sizeof(char)*buffSize*12); 
	void *rot;  
	rot_filename = file_name;

	if ((rot_fd = open(rot_filename, O_RDONLY)) < 0) {
		fprintf(stderr, "Error opening file \"%s\": ",
				rot_filename);
		perror((const char *) 0); 
		return;
	}

	if (fstat(rot_fd, &file_status)) {
		fprintf(stderr, "Error checking file \"%s\": ",
				rot_filename);
		perror((const char *) 0);
	}

	rot_total = file_status.st_size;

	rot_base = mmap( (void *) 0, rot_total, PROT_READ, MAP_SHARED,
			rot_fd, 0);
	//	cerr<<"Reading File Finish"<<endl;
	ii = 0;
	int n = 0;

	int sc=0,dc=0,spc=0,dpc=0,pc=0,ac=0;

	tb = read(rot_fd, bufTemp, buffSize);
//	if ((rot_fd = close(rot_filename, O_RDONLY)) < 0) {
//		fprintf(stderr, "Error opening file \"%s\": ",
//				rot_filename);
//		perror((const char *) 0); 
//		return;
//	}

/*	if( (munmap( rot_base, rot_total))<0){
		cout<<"err"<<endl;
		exit(0);
	}
*/
	close(rot_fd);
	//cout<<tb<<endl;
	int i=0;
	while(i < tb){
		//	cout<<bufTemp[i];
		i++;
	}

	return;
}

