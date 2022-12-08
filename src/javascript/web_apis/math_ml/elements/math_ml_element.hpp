#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MATH_ML_ELEMENTS_MATH_ML_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MATH_ML_ELEMENTS_MATH_ML_ELEMENT_HPP


#include "css/cssom/mixins/element_css_inline_style.hpp"
namespace math_ml::elements {class math_ml_element;}


class math_ml::elements::math_ml_element
    : public dom::nodes::element
    , public css::cssom::mixins::element_css_inline_style
{
public constructors:
    math_ml_element() = default;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MATH_ML_ELEMENTS_MATH_ML_ELEMENT_HPP
