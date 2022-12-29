#include "navigator_id.hpp"
#include "navigator_id_private.hpp"

#include <hwinfo/os.h>


auto html::navigators::mixins::navigator_id::get_platform() const -> ext::string
{
    auto os_name = hwinfo::OS::getName();
    return {std::make_move_iterator(os_name.begin()), std::make_move_iterator(os_name.end())};
}


auto html::navigators::mixins::navigator_id::get_oscpu() const -> ext::string
{
    auto os_full_name = hwinfo::OS::getFullName();
    return {std::make_move_iterator(os_full_name.begin()), std::make_move_iterator(os_full_name.end())};
}
