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
///*
void RRCSetup_coder(char *buffer, size_t *len) {
    asn_enc_rval_t res;
    RRCConnectionSetup_t* rrc_set = 0;
    asn_TYPE_member_t ec;

    rrc_set->_asn_ctx.context = 1;

    memset(&res, 0, sizeof(res));
    printf("BEFORE FAULT\n");
    res = asn_encode_to_buffer(&asn_DEF_RRCConnectionSetup, 2, &rrc_set, &ec, buffer, 1024);
    printf("AFTER FAULT\n");

    if (*buffer == NULL) {
        fprintf(stderr, "Error enconing s1ap pdu\n");
        exit(1);
    } else {
        fprintf(stderr, "Encoded pdu\n");
    }

    /* Print the decoded Rectangle type as XML */
    xer_fprint(stdout, &asn_DEF_RRCConnectionSetup, rrc_set);
}
//*/

void tx_send(char *buffer, size_t* len) {
    int sockfd, n;
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP)) == -1) {
        printf("create socket error: %s (errno :%d)\n");
        return 0;
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
 
 
         // connection
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) <0) {
        printf("connect socket error: %s(errno :%d)\n");
        return 0;
    }
 
    printf("send msg to server:\n");
    //fgets(sendline, 4096, stdin);
         // send send
    char* temp_char = "a word";
    if (sctp_sendmsg(sockfd, temp_char, strlen(temp_char), NULL, 0, 0, 0, 0, 0, 0) < 0) {
        printf("send msg error: %s(errno :%d)\n");
        return 0;
    }
 
    close(sockfd);
}