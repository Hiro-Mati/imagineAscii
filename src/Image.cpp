#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Image.hpp"

#include <iostream>

namespace image {
    constexpr int desiredChannels = 3;
    constexpr float terminalCorrection = 0.5f;

    const std::string chars{" .:-=+*#%@"};

    Image::Image(std::filesystem::path path) : m_path{std::move(path)} {
        if (!std::filesystem::exists(this->m_path)) {
            throw std::invalid_argument{"Path does not exist"};
        }

        unsigned char *data = stbi_load(
            this->m_path.string().c_str(),
            &this->m_size.width,
            &this->m_size.height,
            &this->m_size.channels,
            desiredChannels
        );
        this->m_pixels.reserve(this->m_size.getPixelsCount());

        const std::size_t pixelsCount = this->m_size.getPixelsCount();

        for (std::size_t i = 0; i < pixelsCount; i++) {
            this->m_pixels.push_back(Pixel{
                .r = data[i * desiredChannels],
                .g = data[i * desiredChannels + 1],
                .b = data[i * desiredChannels + 2]
            });
        }

        stbi_image_free(data);
    };

    void Image::printImage(const int targetWidth) const {
        const int x = this->m_size.width;
        const int y = this->m_size.height;

        const float ratio =
                static_cast<float>(y) / static_cast<float>(x);

        const int targetHeight =
                static_cast<int>(
                    static_cast<float>(targetWidth) * ratio * terminalCorrection
                );

        for (int newY = 0; newY < targetHeight; ++newY) {
            for (int newX = 0; newX < targetWidth; ++newX) {
                const int sourceX =
                        newX * x / targetWidth;

                const int sourceY =
                        newY * y / targetHeight;

                const std::size_t index =
                        static_cast<std::size_t>(sourceY) * x + sourceX;

                const Pixel &pixel = this->m_pixels[index];

                const int brightness =
                (static_cast<int>(pixel.r)
                 + static_cast<int>(pixel.g)
                 + static_cast<int>(pixel.b)) / 3;

                const std::size_t charIndex =
                        brightness * (chars.size() - 1) / 255;

                std::cout << chars[charIndex];
            }

            std::cout << '\n';
        }
    }
}
