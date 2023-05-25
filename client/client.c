#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
int main() {
	
	struct sockaddr_in server_addr; 
	struct hostent* server; 
	int server_sock; 

	char msg[500] = "[+] CONNECTED \n"; 
	char buf[500]; 
	
	
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	
	server_addr.sin_family = AF_INET; 
	server_addr.sin_port = htons(8080); 
	server_addr.sin_addr.s_addr = inet_addr("192.168.178.20"); 
	int err; 
	
	while(err != 0) {
		sleep(2);
		err = connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)); 
	}
	printf("%d \n", err); 
	printf("connected \n"); 	
	send(sock, msg, sizeof(msg), 0);

	while (1) {
		memset(buf, 0, sizeof(buf));
		recv(sock, buf, sizeof(buf), 0);
		printf("got  >>>    %s  \n", buf);
		

		if(strcmp(buf, "quit") == 10) {
			printf("quiting \n");
			break;
		}
	}

	close(sock);

	
}
