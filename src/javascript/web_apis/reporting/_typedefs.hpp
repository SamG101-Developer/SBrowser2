#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REPORTING__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REPORTING__TYPEDEFS_HPP



#include "ext/map.ixx"
#include "ext/span.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
namespace reporting {class reporting_observer;}


namespace reporting::detail
{
    struct endpoint_t;
    struct report_t;

    enum class delivery_response_t {SUCCESS, REMOVE_ENDPOINT, FAILURE};

    using report_type_t = ext::string;
    using reporting_observer_options_t = ext::map<ext::string, ext::any>;
    using reporting_observer_callback_t = ext::function<void(ext::vector_span<ext::string>, reporting_observer*)>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_REPORTING__TYPEDEFS_HPP
