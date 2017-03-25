#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <process.h>

typedef struct my_msg {
	int code;
	char txt[256];
}my_msg;

int main(int argc, char *argv[]) {
	int coid, status, server_pid, server_chid;
	my_msg msg;
	
	if(argc < 4) { perror("Podaj pid, chid, msg"); exit(EXIT_FAILURE); }		
	
	server_pid = atoi(argv[1]);
	server_chid = atoi(argv[2]);
	strcpy(msg.txt, argv[3]);
	msg.code = 0;
	
	printf("Lacze sie z pid: %d, chid %d\n", server_pid, server_chid);
	
	coid = ConnectAttach(ND_LOCAL_NODE, server_pid, server_chid, _NTO_SIDE_CHANNEL, 0);	
	if(coid < 0) { exit(EXIT_FAILURE); }
	
	printf("\nWysylam: %s\n", msg.txt);
	
	status = MsgSend(coid, &msg, sizeof(msg), NULL, NULL);
	if(status < 0) { exit(EXIT_FAILURE); }
	
	
	
	return EXIT_SUCCESS;
}
