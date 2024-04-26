#include "Attach_coder.h"
#include <RRCConnectionSetup.h>
#include <arpa/inet.h>
#include <conversions.h>
#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PAYLOAD_MAX 100

#define asn1cSeqAdd(VaR, PtR) \
    if (asn_sequence_add(VaR, PtR) != 0) assert(0)

void RRCMessage_decoder(char *buffer, size_t *len) {
    asn_dec_rval_t rval;        /* Decoder return value */
    RRCConnectionSetup_t *rrc_set = 0; /* Type to decode. Note this 01! */
    asn_TYPE_member_t ec;

    printf("Before FAULT\n");
    asn_decode(&asn_DEF_RRCConnectionSetup, 1024, &ec, &rrc_set, buffer, 1024);
    printf("After FAULT\n");

    // Print the decoded Rectangle type as XML //
    printf("Before xer\n");
    xer_fprint(stdout, &asn_DEF_RRCConnectionSetup, rrc_set);
    printf("after xer\n");
}

void tx_recv(char *buffer, size_t* len) {

   int listenfd, connfd;
    struct sockaddr_in servaddr;
    int n;
 
    // Create a TCP Socket
    if ((listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP)) == -1) {
        printf("create socket error: %s (errno :%d)\n");
        return 0;
    }
	
         // Clear the address and detect any IP
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(6666);
	
         // Address Bind to Listenfd
    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
        printf("bind socket error: %s (errno :%d)\n");
        return 0;
    }
 
         // Monitor Listenfd
    if (listen(listenfd, 10) == -1) {
        printf("listen socket error: %s (errno :%d)\n");
        return 0;
    }
 
    printf("====waiting for client's request=======\n");
         // Accept and RECV, pay attention to the receiving string add end character '\ 0'
    while(1) {
        if ((connfd = accept(listenfd, (struct sockaddr *)NULL, NULL))  == -1) {
            printf("accpt socket error: %s (errno :%d)\n");
            return 0;
        }

        n = sctp_recvmsg(connfd, *buffer, len, NULL, 0, 0, 0);
        if(n <= 0) {
            printf("recv msg ERROR\n");
            return;    
        }
        buffer[n] = '\0';
        printf("recv msg from client:%s\n", buffer);
        close(connfd);
    }
    close(listenfd);

}