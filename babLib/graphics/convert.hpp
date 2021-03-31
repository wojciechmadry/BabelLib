#ifndef BABEL_GRAPHICS_CONVERT
#define BABEL_GRAPHICS_CONVERT

#include "rgb.hpp"
#include "cmyk.hpp"

namespace babel::GRAPHICS{
    using byte = uint8_t;

    constexpr cmyk RGB_TO_CMYK(const rgb &_rgb) noexcept
    {
        auto rp = static_cast<double>(_rgb.R()) / 255.0;
        auto gp = static_cast<double>(_rgb.G()) / 255.0;
        auto bp = static_cast<double>(_rgb.B()) / 255.0;
        double k = 1.0 - babel::MATH::max(babel::MATH::max(rp, gp), bp);
        double o_m_k = 1.0 - k;
        double c = ( ( 1.0 - rp - k ) / o_m_k ) * 100.0;
        double m = ( ( 1.0 - gp - k ) / o_m_k ) * 100.0;
        double y = ( ( 1.0 - bp - k ) / o_m_k ) * 100.0;
        k *= 100.0;
        return cmyk(static_cast<byte>(c), static_cast<byte>(m), static_cast<byte>(y), static_cast<byte>(k));
    }


}
#endif