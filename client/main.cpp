#include <iostream>
#include "file_system_manager.h"
#include "NFS_client.h"
#define LOOP_BACK    "127.0.0.1"
#define DEFAULT_PORT 6941

#define CREATE 1
#define READ   2
#define WRITE  3


int main() {
  NFS_client client(LOOP_BACK, DEFAULT_PORT);
  std::string path = "test.txt";
  std::string content = "ALA MA KOTA\n KOT NIE ŻYJE";

  client.write_to_file(path, content);
  std::cout << client.read_from_file(path) <<std::endl;
  std::cout << "END\n";
}