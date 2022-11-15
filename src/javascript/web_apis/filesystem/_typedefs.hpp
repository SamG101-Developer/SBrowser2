#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM__TYPEDEFS_HPP


#include "ext/any.hpp"
#include "ext/array_buffer.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/variant.hpp"

namespace file_api {class blob;}


namespace filesystem::detail
{
    struct entry_t;
    struct file_entry_t;
    struct directory_entry_t;

    enum class mode_t {READ, READWRITE};
    enum class lock_t {OPEN, TAKEN_EXCLUSIVE, TAKEN_SHARED};
    enum class take_lock_t {EXCLUSIVE, SHARED};
    enum class file_system_handle_kind_t {FILE, DIRECTORY};
    enum class write_command_type_t {WRITE, SEEK, TRUNCATE};
    enum class file_state_t {OPEN, CLOSED};

    using file_system_create_writable_options_t = ext::map<ext::string, ext::boolean>;
    using file_system_get_file_options_t = ext::map<ext::string, ext::boolean>;
    using file_system_get_directory_options_t = ext::map<ext::string, ext::boolean>;
    using file_system_remove_options_t = ext::map<ext::string, ext::boolean>;
    using file_system_read_write_options_t = ext::map<ext::string, ext::any>;
    using write_params_t = ext::map<ext::string, ext::any>;
    using file_system_write_chunk_type_t = ext::variant<ext::buffer_source*, file_api::blob*, ext::string, write_params_t>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM__TYPEDEFS_HPP
