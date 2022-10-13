#ifndef SBROWSER2_SRC_EXT_JSON_HPP
#define SBROWSER2_SRC_EXT_JSON_HPP

#include "ext/keywords.hpp"
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


#endif //SBROWSER2_SRC_EXT_JSON_HPP
