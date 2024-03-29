#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS__NAMESPACE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS__NAMESPACE_HPP


namespace css {class css;}

namespace html::workers {class worklet;}


class css::css
        : public virtual dom_object
{
    /* CSS_ANIMATION_WORKLET */
    static ext::property<std::unique_ptr<html::workers::worklet>> animation_worklet;

    /* CSS_LAYOUT */
    static ext::property<std::unique_ptr<html::workers::worklet>> layout_worklet;

    /* CSSOM */
    auto escape(ext::string_view identifier) -> ext::string;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS__NAMESPACE_HPP
