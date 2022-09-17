#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_MIXINS_LINK_STYLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_MIXINS_LINK_STYLE_HPP

#include "dom_object.hpp"
namespace css::cssom::mixins {class link_style;}

namespace css::cssom::style_sheets {class css_style_sheet;}


class css::cssom::mixins::link_style
        : public virtual dom_object
{
public js_properties:
    ext::property<std::unique_ptr<style_sheets::css_style_sheet>> sheet;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_MIXINS_LINK_STYLE_HPP
