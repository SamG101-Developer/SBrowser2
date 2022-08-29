#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_WEB_DETAIL_STREAMING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_WEB_DETAIL_STREAMING_INTERNALS_HPP

#include "ext/promise.hpp"
namespace fetch {class response;}
namespace web_assembly::js {class module;}

namespace web_assembly::detail
{
    auto compile_potential_web_assembly_response(
            ext::promise<fetch::response*> source)
            -> ext::promise<js::module>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_WEB_DETAIL_STREAMING_INTERNALS_HPP
