#pragma once
#ifndef SBROWSER2_POINTER_INTERNALS_HPP
#define SBROWSER2_POINTER_INTERNALS_HPP





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
