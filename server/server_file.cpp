#include "server_file.h"

//POTRZEBA JAKOŚ PRZEKAZAĆ DO NIEGO OBIEKT ACCESS MANAGERA UŻYWANY PRZEZ SERWER
ServerFileManager::ServerFileManager() {
    this->manager = AccessManager();
}
ServerFileManager::ServerFileManager(AccessManager new_manager) {
    this->manager = new_manager;
}

std::string  ServerFileManager::open_file(std::string message) {
    OpenRequest req = OpenRequest().deserialize(message);
    std::string path = req.get_path();
    int open_mode = req.get_open_mode();

    int file_exists = access(path, R_OK);

    if (file_exists == 0) {
        switch (open_mode) {
            case 3:
                return ErrorReply("ERROR IN: open_file for create - File already exists\n").serialize();
                break;
            case 1:
                if(manager.is_file_blocked(path))
                    return ErrorReply("ERROR IN: open_file for writer - file is blocked\n").serialize();
                else {
                    manager.block_file_for_writer(path);
                    return OpenReply().serialize();
                }
                break;
            case 2:
                if(manager.is_file_blocked(path))
                    return ErrorReply("ERROR IN: open_file for reader - file is blocked\n").serialize();
                else
                    return  OpenReply().serialize();
                break;
            default:
                return  ErrorReply("ERROR IN: open_file - unknown open mode\n").serialize();
        }
    }else if (file_exists > 0) {
        return ErrorReply("ERROR IN: open_file - Something went wrong when checking if file exists\n").serialize();
    } else if (file_exists != ENOENT) {
        return ErrorReply("ERROR IN: open_file - Path inaccessible\n").serialize();
    } else {
        if(open_mode == 3) {
            FILE *new_file;
            new_file = fopen(path, "w");
            fclose(new_file);
            manager.block_file_for_writer(path);
            return OpenReply().serialize();
        }else{
            return ErrorReply("ERROR IN: open_file - file does not exist\n").serialize();
        }
    }
    return ErrorReply("ERROR IN: Create Mssg - unknown error\n");
}



std::string ServerFileManager::write_file(std::string message) {
    //ASUMING THAT FILE EXISTANCE WAS CHECKED BY OPENFILE
    WriteRequest req = WriteRequest();
    req.deserialize(message);
    std::string path = req.get_path();

    while (manager.is_file_operated_on());

    manager.set_operated_on(true);
    FILE *file;
    file = fopen(path, "w");
    if(file != NULL){
        fputs(req.get_file_content(), file);
        fclose(file);
        manager.set_operated_on(false);
        return WriteReply().serialize();
    }else
        manager.set_operated_on(false);
        return ErrorReply("ERROR IN: write_file - file couldn't open\n");
}

std::string ServerFileManager::read_file(std::string message) {
    //ASUMING THAT FILE EXISTANCE WAS CHECKED BY OPENFILE
    ReadRequest req = WriteRequest();
    req.deserialize(message);
    std::string path = req.get_path();
    std::string read_content;

    while (manager.is_file_operated_on());

    manager.set_operated_on(true);

    FILE *file;
    file = fopen(path, "r");
    if(file != NULL){
        while(true){
            read_content += fgetc(file);
            if(feof(file)) {
                break;
            }
        }
        fclose(file);
        manager.set_operated_on(false);
        return ReadReply(read_content).serialize();
    }else
        manager.set_operated_on(false);
    return ErrorReply("ERROR IN: read_file - file couldn't open\n").serialize();
}