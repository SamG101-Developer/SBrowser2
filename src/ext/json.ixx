export module ext.json;

#include "ext/keywords.ixx"
#include <jsonpp/dumper.h>
#include <jsonpp/parser.h>


_EXT_BEGIN
    namespace json
    {
        export using dumper = jsonpp::Dumper;
        export using parser = jsonpp::Parser;
        export using json_map_t = metapp::Variant;
    }
_EXT_END
