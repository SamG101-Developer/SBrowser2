module;
#include "ext/macros/macros.hpp"


export module apis._3ds.types;

import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(three_ds)
{
    enum class three_ds_challenge_ind {REQUESTED, MANDATED, NONE};

    using three_ds_request = ext::map<ext::string, ext::any>;
    using three_ds_response = ext::map<ext::string, ext::any>;
}
