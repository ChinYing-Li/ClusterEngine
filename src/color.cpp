#include <cassert>
#include "src/color.h"

#define INV_256 1.0f/255.0f
ColorU8::ColorU8(const std::uint8_t val):
r(val), g(val), b(val)
{}

ColorU8::ColorU8(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue):
r(red), g(green), b(blue)
{}

ColorU8::ColorU8(const ColorF& color)
{
    r = float(color.r * 256.0f);
    g = float(color.g * 256.0f);
    b = float(color.b * 256.0f);
}

ColorF::ColorF(const float val)
{
    assert(is_valid(val));
    r = val;
    g = val;
    b = val;
}

ColorF::ColorF(const float red, const float green, const float blue)
{
    assert(is_valid(red));
    assert(is_valid(green));
    assert(is_valid(blue));
    r = red;
    g = green;
    b = blue;
}

ColorF::ColorF(const ColorU8& color)
{
    r = float(color.r) * INV_256;
    g = float(color.g) * INV_256;
    b = float(color.b) * INV_256;
}
bool ColorF::is_valid(const float val)
{
    return (val >= float(0) && val <= 1.0f);
}
