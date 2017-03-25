#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <process.h>

typedef struct my_msg {
	int code;
	char txt[256];
}my_msg;

int main(int argc, char *argv[]) {
	my_msg msg;
	int chid, pid, rcvid;
	
	chid = ChannelCreate(0);
	if(chid < 0) { exit(EXIT_FAILURE); }

	pid = getpid();
	printf("Server's pid: %d, chid: %d\n", pid, chid);
	
	while(1) {
		rcvid = MsgReceive(chid, &msg, sizeof(msg), NULL);
		if(rcvid < 0) { perror("MsgReceive error"); }

		printf("MSGc from client: %d\n", msg.code);
		printf("MSGt from client: %s\n", msg.txt);	
			
	}
	
	return EXIT_SUCCESS;
}
