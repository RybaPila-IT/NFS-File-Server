#include "NFS_Client.h"

int main() {
    NFS_Client client;
    std::string path = "/tmp/file";
    client.open_file(0, path);
    //client.tmp_func_handle_session_interactive();
    return 0;
}

