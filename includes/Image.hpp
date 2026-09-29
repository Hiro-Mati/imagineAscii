#pragma once

#include <cstdint>
#include <filesystem>
#include <vector>

namespace image {

    struct Size {
        int width{0};
        int height{0};
        int channels{0};

        [[nodiscard]] int getPixelsCount() const {
            return width * height;
        }
    };

    struct Pixel {
        std::uint8_t r{0};
        std::uint8_t g{0};
        std::uint8_t b{0};
    };

    class Image final {
    public:
        Image () = default;
        explicit Image(std::filesystem::path  path);

        void printImage(int targetWidth) const;

        [[nodiscard]] const std::vector<Pixel> &getPixels() const {
            return m_pixels;
        };

        [[nodiscard]] int getWidth() const {
            return m_size.width;
        }

        [[nodiscard]] int getHeight() const {
            return m_size.height;
        }

    private:
        Size m_size;
        std::vector<Pixel> m_pixels;
        std::filesystem::path m_path;
    };
}

