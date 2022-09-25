#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API_FILE_READER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API_FILE_READER_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/nodes/event_target_private.hpp"

#include INCLUDE_INNER_TYPES(file_api)
namespace dom::other {class dom_exception;}


DEFINE_PRIVATE_CLASS(file_api, file_reader) : dom::nodes::event_target_private
{
    detail::state_t state;
    detail::result_t result;
    std::unique_ptr<dom::other::dom_exception> error;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API_FILE_READER_PRIVATE_HPP
