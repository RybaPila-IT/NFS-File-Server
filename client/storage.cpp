#include "storage.h"

int Storage::new_file_descriptor = 0;

int Storage::get_file_descriptor(std::string &file_path) {
    auto result = files_to_desc.find(file_path);
    return result == files_to_desc.end() ? -1 : result->second;
}

int Storage::add_file(std::string &file_path, File &file) {
    int file_descriptor = new_file_descriptor++;
    files_to_desc.insert(
            std::make_pair(
                    file_path,
                    file_descriptor
            )
    );
    opened_files.insert(std::make_pair(file_descriptor, file));
    return file_descriptor;
}

void Storage::erase_file(int desc) {
    auto file_iter = opened_files.find(desc);
    files_to_desc.erase(file_iter->second.get_path());
    opened_files.erase(desc);
}

std::string Storage::desc_to_file_path(int desc) {
    auto file_iter = opened_files.find(desc);
    return file_iter == opened_files.end() ? "" : file_iter->second.get_path();
}

void Storage::set_file_content(int desc, std::string &content) {
    auto file_iter = opened_files.find(desc);
    if (file_iter == opened_files.end())
        throw std::runtime_error("obtain_file: file with descriptor " + std::to_string(desc) + " does not exist!");
    file_iter->second.set_content(content);
}

File Storage::obtain_file(int desc) {
    auto file_iter = opened_files.find(desc);
    if (file_iter == opened_files.end())
        throw std::runtime_error("obtain_file: file with descriptor " + std::to_string(desc) + " does not exist!");
    return file_iter->second;
}

