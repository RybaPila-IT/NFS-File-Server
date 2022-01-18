#include "NFS_client.h"

#define LOOP_BACK    "127.0.0.1"
#define DEFAULT_PORT 6941

int main() {
    NFS_client client(LOOP_BACK, DEFAULT_PORT);
    client.tmp_func_handle_session_interactive();
    //std::string path = "/tmp/file";
    //client.open_file(1, path);
    return 0;
}