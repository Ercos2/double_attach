#include <stdio.h>
#include <sys/types.h>

#include <Attach_coder.h>
#include <unistd.h>

int main() {
    char buffer[1024];
    size_t len = 1024;

    tx_recv(buffer, &len);
    RRCMessage_decoder(&buffer, &len);
    free(buffer);
    
    return 0;
}
