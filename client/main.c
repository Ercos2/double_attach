#include <stdio.h>
#include <sys/types.h>

#include <Attach_coder.h>
#include <unistd.h>

int main() {
    char buffer[1024];
    size_t len = 1024;
    RRCSetup_coder(buffer, &len);
    tx_send(buffer, &len);
    
    return 0;
}
