#include "NFS_client.h"

#define LOOP_BACK    "127.0.0.1"
#define DEFAULT_PORT 6941

int main() {
    NFS_client client(LOOP_BACK, DEFAULT_PORT);
    return 0;
}