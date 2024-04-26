
#ifndef _S1SETUPREQUESTCODER_H
#define _S1SETUPREQUESTCODER_H

#include <stdio.h>
#include <sys/types.h>
#include <RRCConnectionSetup.h>

void RRCSetup_coder(uint8_t **buffer, ssize_t *len);
void tx_send(char *buffer, size_t *len);

#endif