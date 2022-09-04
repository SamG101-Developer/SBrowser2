#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD__TYPEDEFS_HPP

#include "ext/promise.hpp"
#include <QtGui/QClipboard>
#include "ext/any.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include "ext/variant.hpp"
#include USE_INNER_TYPES(mimesniff)
namespace file_api {class blob;}

namespace clipboard::detail
{
    struct representation_t;
    struct clipboard_item_t;

    enum class presentation_style_t {UNSPECIFIED, INLINE, ATTACHMENT};

    using clipboard_item_data_t = ext::variant<ext::promise<ext::string>, ext::promise<file_api::blob*>>;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD__TYPEDEFS_HPP
