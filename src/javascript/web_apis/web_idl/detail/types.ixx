module;
#include "ext/macros/macros.hpp"
#include <v8-forward.h>


export module apis.web_idl.types;


DEFINE_FWD_DECL_NAMESPACE(v8)
{
    using BufferSource = v8::ArrayBufferView;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(web_idl)
{}
