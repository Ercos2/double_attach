
#ifndef _S1SETUPREQUESTCODER_H
#define _S1SETUPREQUESTCODER_H

#include <stdio.h>
#include <sys/types.h>
#include <RRCConnectionSetup.h>

void RRCMessage_decoder(char *buffer, size_t *len);
void tx_recv(char *buffer, size_t *len);

#endif