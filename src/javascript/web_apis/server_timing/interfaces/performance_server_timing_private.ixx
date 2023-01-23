module;
#include "ext/macros.hpp"


export module apis.server_timing.performance_server_timing:p;
import apis.dom_object;


DEFINE_PRIVATE_CLASS(server_timing, performance_server_timing)
        : dom_object_private
{
public:
    MAKE_QIMPL(performance_server_timing);

public:
    ext::string metric_name;
    ext::map<ext::string, ext::any> params;
};
