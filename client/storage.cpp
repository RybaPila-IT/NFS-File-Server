#include "storage.h"

int Storage::new_file_descriptor = 0;

int Storage::get_file_descriptor(std::string& file_path) {
    auto result = files_meta.find(file_path);
    return result == files_meta.end() ? -1 : result->second.desc;
}

int Storage::add_file(std::string &file_path, File &file) {
    int file_descriptor = new_file_descriptor++;
    files_meta.insert(
            std::make_pair(
                    file_path,
                    file_meta({file_descriptor, false})
            )
    );
    opened_files.insert(std::make_pair(file_descriptor, file));
    return file_descriptor;
}

void Storage::erase_file(int desc) {
    auto file_iter = opened_files.find(desc);
    files_meta.erase(file_iter->second.get_path());
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

