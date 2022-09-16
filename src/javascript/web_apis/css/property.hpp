#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_PROPERTY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_PROPERTY_HPP

#include "ext/assertion.hpp"
#include "ext/boolean.hpp"
#include "ext/concepts.hpp"
#include "ext/functional.hpp"
#include "ext/property.hpp"
#include "ext/detail/meta_property.hpp"

#include <qpainter.h>
#include <qwidget.h>


namespace css::detail
{
    enum class percent_t {NA};
    enum class computed_value_t {SPECIFIED_KEYWORDS};
    enum class canonical_order_t {PER_GRAMMAR};
    enum class animation_type_t {DISCRETE};
}


namespace css
{

template <
        type_is_enum allowed_values_t,
        bool inherited = false,
        css::detail::percent_t percent = detail::percent_t::NA,
        css::detail::computed_value_t computed_value = detail::computed_value_t::SPECIFIED_KEYWORDS,
        css::detail::canonical_order_t canonical_order = detail::canonical_order_t::PER_GRAMMAR,
        css::detail::animation_type_t animation_type = detail::animation_type_t::DISCRETE>
struct abstract_property
{
    using values_t = allowed_values_t;

    virtual auto name() -> ext::string = 0;
    virtual auto initial() -> ext::string = 0;
    virtual auto paint(QPainter* painter, QWidget* widget, values_t value) -> void = 0;
};

}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_PROPERTY_HPP
