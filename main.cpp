#include <iostream>
#include <fstream>
#include <string>

#include "lib/finder.h"

const std::string HELP_MSG = "Usage: my_diff [OPTION] file file\n\n"
                             "-d, --difference        create file describing differences assuming second file is newer\n"
                             "-r, --restore           restore previous version using second file as difference\n";

void display_help() {
    std::cout << HELP_MSG;
}

size_t get_filesize(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    return file.tellg();
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        display_help();
        return 1;
    }

    std::string option(argv[1]);
    std::string first_file(argv[2]);
    std::string second_file(argv[3]);

    size_t approx_size = (get_filesize(first_file) + get_filesize(second_file)) / 2;

    std::ifstream first_in(first_file, std::ios::binary);
    std::ifstream second_in(second_file, std::ios::binary);

    std::ofstream result("result.diff", std::ios::binary);

    Finder finder(0, approx_size);
    if (option == "-d" || option == "--difference") {
        finder.generate_difference(first_in, second_in, result);
    } else if (option == "-r" || option == "--restore") {
        std::cout << "Sorry, not implemented yet";
    } else {
        display_help();
    }

    first_in.close();
    second_in.close();

    return 0;
}
