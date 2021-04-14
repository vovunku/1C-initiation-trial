#ifndef MY_DIFF_FINDER_H
#define MY_DIFF_FINDER_H

#include <iostream>

class Finder {
public:
    Finder(size_t block_size, size_t file_size);

    void generate_difference(std::istream &previous, std::istream& updated, std::ostream& result);

    void restore_file(std::istream &file, std::istream& difference, std::ostream& result);

private:
    void fflush_diff_buffer(std::ostream& result, size_t offset, char type, std::string& buffer);

    size_t block_size_;
    size_t file_size_;
};

#endif //MY_DIFF_FINDER_H
