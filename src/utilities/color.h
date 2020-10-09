#pragma once

#include <cstddef>
#include <cstdint>

class ColorU8;
class ColorF;

class ColorU8
{
public:
    ColorU8() = default;
    explicit ColorU8(const std::uint8_t val);
    explicit ColorU8(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue);
    ColorU8(const ColorF& color);
    
    ~ColorU8() = default;
    
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
private:
};

class ColorF
{
public:
    ColorF() = default;
    explicit ColorF(const float val);
    explicit ColorF(const float red, const float green, const float blue);
    ColorF(const ColorU8& color);
    
    ~ColorF() = default;
    
    float r;
    float g;
    float b;
private:
    bool is_valid(const float val);
};


