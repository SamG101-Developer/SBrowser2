#ifndef SBROWSER2_CONTEXT_INTERNALS_HPP
#define SBROWSER2_CONTEXT_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/vector.hpp"
#include "url/url.hpp"
#include <memory>
namespace dom::nodes {class document;}
namespace dom::nodes {class window_proxy;}

namespace html::detail::context_internals
{
    struct browsing_context;

    auto is_still_on_initial(
            browsing_context* context)
            -> ext::boolean;
}


struct html::detail::context_internals::browsing_context
{
    std::unique_ptr<dom::nodes::window_proxy> window_proxy;
    std::unique_ptr<browsing_context> opener_browsing_context;
    ext::boolean disowned;
    ext::boolean is_closing;

    std::unique_ptr<dom::nodes::document> container_document;

    ext::string creator_origin;
    url::url_object creator_url;
    url::url_object creator_base_url;

    ext::vector<dom::nodes::document*> session_history {};
};

#endif //SBROWSER2_CONTEXT_INTERNALS_HPP
