#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_DETAIL_PROPERTY_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_DETAIL_PROPERTY_INTERNALS_HPP

#include "ext/keywords.hpp"
#include INCLUDE_INNER_TYPES(css)

class QPainter;
class QWidget;


struct css::detail::abstract_property_t
{
    ext::number<ulonglong> allowed_values_t;
    bool inherited = false;
    percent_t percent = percent_t::NA;
    computed_value_t computed_value = computed_value_t::SPECIFIED_KEYWORDS;
    canonical_order_t canonical_order = canonical_order_t::PER_GRAMMAR;
    property_animation_type_t animation_type = property_animation_type_t::DISCRETE;

    virtual auto name() -> ext::string = 0;
    virtual auto initial() -> ext::string = 0;
    virtual auto paint(QPainter* painter, QWidget* widget, ext::number<ulonglong> value) -> void = 0;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_DETAIL_PROPERTY_INTERNALS_HPP
