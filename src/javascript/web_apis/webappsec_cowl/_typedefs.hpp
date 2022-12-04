#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL__TYPEDEFS_HPP


#include "ext/set.hpp"




namespace webappsec::detail
{
    struct cowl_state_t;

    using principal_t = ext::string;
    using disjunction_set_t = ext::set<principal_t>;
    using label_set_t = ext::set<disjunction_set_t>;
    using ci_label_t = ext::map<ext::string, ext::any>;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL__TYPEDEFS_HPP
