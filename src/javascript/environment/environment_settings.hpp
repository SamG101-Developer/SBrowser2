#ifndef SBROWSER2_SRC_JAVASCRIPT_ENVIRONMENT_ENVIRONMENT_SETTINGS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_ENVIRONMENT_ENVIRONMENT_SETTINGS_HPP

#include USE_INNER_TYPES(url)
#include <v8pp/class.hpp>
#include <v8pp/convert.hpp>


namespace javascript::environment {struct settings_t;}

struct javascript::environment::settings_t
{
    url::detail::url_t& api_base_url;

    auto to_v8_object(v8::Isolate* isolate)
    {return v8pp::class_<settings_t>{isolate};}
};


#endif //SBROWSER2_SRC_JAVASCRIPT_ENVIRONMENT_ENVIRONMENT_SETTINGS_HPP