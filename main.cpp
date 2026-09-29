#include "Image.hpp"

#include <iostream>
#include <ostream>
#include <cassert>
#include <filesystem>

int main(const int argc, char** argv) {

    if (argc != 3) {
        std::cout
            << "Usage: " << argv[0]
            << " <image> <width>\n";

        return 1;
    }

    const std::filesystem::path fileName{argv[1]};

    int targetWidth;
    try {
        std::size_t parsed = 0;
        targetWidth = std::stoi(argv[2], &parsed);

        if (parsed != std::string{argv[2]}.size() || targetWidth <= 0) {
            throw std::invalid_argument{"not a positive integer"};
        }
    } catch (const std::exception &) {
        std::cerr << "Error: <width> must be a positive integer\n";

        return 1;
    }

    try {
        const image::Image image{fileName};

        image.printImage(targetWidth);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';

        return 1;
    }

    return EXIT_SUCCESS;
}
