#include "report_body.hpp"
#include "report_body_private.hpp"


reporting::report_body::report_body()
{
    INIT_PIMPL(report_body);
}


auto reporting::report_body::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<report_body>{isolate}
        .inherit<dom_object>()
        .function("toJSON", &report_body::operator ext::string)
        .auto_wrap_objects();

    return std::move(conversion);
}


reporting::report_body::operator ext::string() const
{
    return web_idl::detail::default_json_steps(this);
}
