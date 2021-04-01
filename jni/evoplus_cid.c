#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "mmc.h"

#define CID_SIZE 16
@@ -114,7 +117,7 @@ int parse_serial(const char *str) {
	return (int)val;
}

void main(int argc, const char **argv) {
int main(int argc, const char **argv) {
	int fd, ret, i, len;
	unsigned char cid[CID_SIZE] = {0};

@@ -129,21 +132,21 @@ void main(int argc, const char **argv) {
		printf("  and will be applied to the supplied cid before writing\n");
		printf("\n");
		printf("Warning: use at own risk!\n");
		return;
		return -1;
	}

	len = strlen(argv[2]);
	if (len != 30 && len != 32) {
		printf("CID should be 30 or 32 chars long!\n");
		return;
		return -1;
	}

	// parse cid
	for (i = 0; i < (len/2); i++){
		ret = sscanf(&argv[2][i*2], "%2hhx", &cid[i]);
		if (!ret){
			printf("CID should be hex (without 0x prefix)!\n");
			return;
			return -1;
		}
	}

@@ -161,7 +164,7 @@ void main(int argc, const char **argv) {
	fd = open(argv[1], O_RDWR);
	if (fd < 0){
		printf("Unable to open device %s\n", argv[1]);
		return;
		return -1;
	}

	// unlock card
@@ -177,6 +180,5 @@ void main(int argc, const char **argv) {
		}
	}
	close(fd);

	return 0;
}
