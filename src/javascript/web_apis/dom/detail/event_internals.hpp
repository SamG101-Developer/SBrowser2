namespace dom::events {class event;}
namespace dom::nodes {class event_target;}


namespace dom::detail
{
    auto flatten_more(
            ext::variant<ext::map<ext::string, ext::any>, ext::boolean>&& options)
            -> ext::map<ext::string, ext::any>;

    auto flatten(
            event_listener_options_t&& options)
            -> ext::boolean;

    auto remove_all_event_listeners(
            nodes::event_target* event_target)
            -> void;

    template <ext::inherit<events::event> T=events::event>
    auto fire_event(
            ext::string&& e,
            nodes::event_target* target,
            ext::map<ext::string, ext::any>&& init = {})
            -> ext::boolean;
}



