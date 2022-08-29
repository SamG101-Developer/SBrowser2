#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS__NAMESPACE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS__NAMESPACE_HPP

#include "dom_object.hpp"
namespace css {class css;}

namespace html::workers {class worklet;}


class css::css
        : public virtual dom_object
{
    static ext::property<std::unique_ptr<html::workers::worklet>> animation_worklet;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS__NAMESPACE_HPP