#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_DOCUMENT_TIMELINE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_DOCUMENT_TIMELINE_HPP

#include "css/css_web_animations/animation_timeline.hpp"
namespace css::css_web_animations {class document_timeline;}

#include INCLUDE_INNER_TYPES(css/css_web_animations)


class css::css_web_animations::document_timeline
        : public animation_timeline
{
public constructors:
    document_timeline() = default;
    document_timeline(detail::document_timeline_options_t&& options = {});

private cpp_members:
    MAKE_PIMPL(document_timeline);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_DOCUMENT_TIMELINE_HPP
