module;
#include "ext/macros/namespaces.hpp"
#include <jsonpp/dumper.h>
#include <jsonpp/parser.h>


_EXT_BEGIN
    namespace json
    {
        using dumper = jsonpp::Dumper;
        using parser = jsonpp::Parser;
        using json_map_t = metapp::Variant;
    }
_EXT_END


export module ext.json;
