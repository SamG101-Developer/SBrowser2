#include "navigator_concurrent_hardware.hpp"
#include "navigator_concurrent_hardware_private.hpp"

#include <hwinfo/cpu.h>


auto html::navigators::mixins::navigator_concurrent_hardware::get_navigator_concurrent_hardware() const -> ext::number<ulonglong>
{
    return hwinfo::CPU::getNumLogicalCores();
}
