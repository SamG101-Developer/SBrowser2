#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD__TYPEDEFS_HPP

#include <future>
#include "mimesniff/_typedefs.hpp"
#include "ext/any.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include "ext/variant.hpp"
namespace file_api {class blob;}

namespace clipboard::detail
{
    enum class presentation_style_t {UNSPECIFIED, INLINE, ATTACHMENT};
    using clipboard_item_data_t = ext::variant<std::promise<ext::string>, std::promise<file_api::blob>>;

    struct representation_t;
    struct clipboard_item_t;
}


struct clipboard::detail::representation_t
{
    mimesniff::detail::mime_type_t mime_type;
    clipboard_item_data_t data;
};

struct clipboard::detail::clipboard_item_t
{
    ext::vector<representation_t> list_of_representations;
    presentation_style_t presentation_style;
};

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD__TYPEDEFS_HPP
