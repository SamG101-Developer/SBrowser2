#pragma once
#ifndef SBROWSER2_POINTER_INTERNALS_HPP
#define SBROWSER2_POINTER_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
namespace dom::nodes {class event_target;}


namespace pointer_events::pointer_internals
{
    auto fire_pointer_event(
            ext::string&& e,
            dom::nodes::event_target* target,
            ext::map<ext::string, ext::any>&& init = {})
            -> ext::boolean;
};


#endif //SBROWSER2_POINTER_INTERNALS_HPP
