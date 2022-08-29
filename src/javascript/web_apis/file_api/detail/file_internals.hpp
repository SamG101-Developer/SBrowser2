#ifndef SBROWSER2_FILE_INTERNALS_HPP
#define SBROWSER2_FILE_INTERNALS_HPP


#include <future>

#include "ext/boolean.hpp"
#include "ext/string.hpp"
namespace file_api {class blob;}
namespace file_api {class file;}
namespace file_api {class file_reader;}

namespace file_api::detail
{
    auto read_operation(
            file_reader* file_reader,
            blob* blob,
            ext::string_view optional_encoding_name = "")
            -> std::promise<ext::string>;

    auto fire_progress_event(
            ext::string_view e,
            file_reader* file_reader)
            -> ext::boolean;
}


#endif //SBROWSER2_FILE_INTERNALS_HPP
