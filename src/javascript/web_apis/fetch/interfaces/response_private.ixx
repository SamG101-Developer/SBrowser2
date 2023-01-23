module;
#include "ext/macros.hpp"


export module apis.fetch.response:p;
import apis.dom_object;
import ext.mixins;


DEFINE_PRIVATE_CLASS(fetch, response)
        : virtual dom_object_private
        , mixins::body_private
{
public:
    MAKE_QIMPL(response);

public:
    std::unique_ptr<detail::response_t> response;

    auto mime_type() const -> ext::string override;
    auto body() const -> detail::body_t& override;
};
