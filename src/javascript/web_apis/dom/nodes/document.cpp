#include "document.hpp"

#include <url/url.hpp>


dom::nodes::document::document()
        : url{std::make_unique<url::url>("about:blank")}
        , implementation{std::make_smart<other::dom_implementation>()}
        , content_type{"application/xml"}
        , ready_state{"complete"}
{

}
