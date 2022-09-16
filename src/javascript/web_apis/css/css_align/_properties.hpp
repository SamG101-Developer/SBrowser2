#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ALIGN__PROPERTIES_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ALIGN__PROPERTIES_HPP

#include "css/property.hpp"

namespace css::properties
{
    enum class align_values_t {NORMAL = 0x01, BASELINE = 0x02, FIRST_BASELINE = 0x02, LAST_BASELINE = 0x04,
            SPACE_BETWEEN = 0x08, SPACE_AROUND = 0x10, SPACE_EVENLY = 0x20, STRETCH = 0x40, UNSAFE = 0x80, SAFE = 0x100,
            CENTER = 0x200, START = 0x400, END = 0x800, FLEX_START = 0x1000, FLEX_END = 0x2000, SELF_START = 0x4000,
            SELF_END = 0x8000, LEFT = 0x10000, RIGHT = 0x20000};


    struct align_content
            : public abstract_property<align_values_t>
    {
        auto name() -> ext::string override {return "align-content";}
        auto initial() -> ext::string override {return "normal";}

        auto paint(QPainter* painter, QWidget* widget, values_t value) -> void override
        {
            ASSERT()
        }
    };


    struct justify_content
            : public abstract_property<align_values_t>
    {
        auto name() -> ext::string override {return "justify-content";}
        auto initial() -> ext::string override {return "normal";}
    };
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ALIGN__PROPERTIES_HPP
