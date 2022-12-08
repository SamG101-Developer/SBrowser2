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

}



