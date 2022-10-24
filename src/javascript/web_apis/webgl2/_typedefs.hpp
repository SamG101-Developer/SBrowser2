#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2__TYPEDEFS_HPP

#include "ext/type_traits.hpp"
#include "ext/number.hpp"
#include "ext/variant.hpp"

#include <QtOpenGL/QOpenGLFunctions_4_5_Core>

namespace webgl2::detail
{
    enum class web_gl_power_preference_t {DEFAULT, LOW_POWER, HIGH_PERFORMANCE};

    using glenum_t = ext::number<ulong>;
    using glboolean_t = ext::boolean;

    using glbyte_t = char;
    using octet_t = uchar;
    using glshort_t = ext::number<short>;
    using glushort_t = ext::number<ushort>;
    using glint_t = ext::number<int>;
    using gluint_t = ext::number<uint>;

    using glbitfield_t = ext::number<ulong>;
    using glsizei_t = ext::number<long>;
    using glintptr_t = ext::number<longlong>*;
    using glsizeiptr_t = ext::number<longlong>*;

    using glfloat_t = ext::number<float>;
    using glclampf_t = ext::number<float>;

    using glint64_t = ext::number<longlong>;
    using gluint64_t = ext::number<ulonglong>;

    using web_gl_context_attributes_t = ext::map<ext::string, ext::boolean>;

    using gl_base = QOpenGLFunctions_4_5_Core;
    using tex_image_source = ext::variant<>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBGL2__TYPEDEFS_HPP
