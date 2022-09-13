#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL__TYPEDEFS_HPP

#include "ext/set.hpp"
#include "ext/string.hpp"


namespace webappsec::detail
{
    using principal_t = ext::string;
    using disjunction_set_t = ext::set<principal_t>;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL__TYPEDEFS_HPP
