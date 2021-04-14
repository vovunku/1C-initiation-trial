#include "finder.h"

#include <string>
#include <algorithm>

Finder::Finder(size_t block_size, size_t file_size) : block_size_(block_size), file_size_(file_size) {
}

void Finder::generate_difference(std::istream &previous, std::istream &updated, std::ostream &result) {
    std::string buffer;
    size_t offset = 0;
    bool are_matching = true;

    char prev_c, upd_c;
    while (previous.good() && updated.good()) {
        previous.get(prev_c);
        updated.get(upd_c);

        if (!are_matching && prev_c != upd_c) {
            buffer.push_back(upd_c);
        } else {
            are_matching = prev_c == upd_c;
            fflush_diff_buffer(result, offset, 'c', buffer);
        }
        ++offset;
    }

    while (previous.good()) {
        previous.get(prev_c);
        buffer.push_back(prev_c);
        ++offset;
    }
    fflush_diff_buffer(result, offset, 'r', buffer);

    while (updated.good()) {
        updated.get(upd_c);
        buffer.push_back(upd_c);
        ++offset;
    }
    fflush_diff_buffer(result, offset, 'i', buffer);
}

void Finder::restore_file(std::istream &file, std::istream &difference, std::ostream &result) {
    // Doesn't work

    while (difference.good()) {
        size_t offset;
        size_t size;
        char type;
        char tmp;
        difference.read(reinterpret_cast<char *>(&offset), sizeof(offset));
        difference.read(reinterpret_cast<char *>(&size), sizeof(size));
        difference.get(type);
        for(int i = 0; i < size && difference.good(); ++i) {
            difference.get(tmp);
        }
    }
}

void Finder::fflush_diff_buffer(std::ostream &result, size_t offset, char type, std::string &buffer) {
    if (buffer.empty()) {
        return;
    }
    result.write(reinterpret_cast<char *>(&offset), sizeof(offset));
    size_t size = buffer.size();
    result.write(reinterpret_cast<char *>(&size), sizeof(size));
    result.put(type);
    for(int i = 0; i < size; ++i) {
        result.put(buffer[i]);
    }
    buffer.clear();
}
