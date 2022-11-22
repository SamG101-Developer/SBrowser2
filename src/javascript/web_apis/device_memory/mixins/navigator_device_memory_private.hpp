#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_MEMORY_MIXINS_NAVIGATOR_DEVICE_MEMORY_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_MEMORY_MIXINS_NAVIGATOR_DEVICE_MEMORY_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#ifdef _WIN32
    #include <windows.h>
#elifdef __linux__
    #include <sys/types.h>
    #include <sys/sysinfo.h>
#endif


DEFINE_PRIVATE_CLASS(device_memory::mixins, navigator_device_memory)
        : virtual dom_object_private
{
    MAKE_QIMPL(navigator_device_memory);

    _EXT_NODISCARD auto device_memory() const -> ext::number<double>;
};


auto device_memory::mixins::navigator_device_memory_private::device_memory() const -> ext::number<double> // TODO : other platforms
{
#ifdef _WIN32
    using windows_memory_t = MEMORYSTATUSEX;
    auto memory = windows_memory_t{};
    memory.dwLength = sizeof(windows_memory_t);
    GlobalMemoryStatusEx(&memory);
    auto available_memory = memory.ullTotalPhys - memory.ullAvailPhys;
    return static_cast<double>(available_memory);
#elif __linux__
    using linux_memory_t = sysinfo;
    struct linux_memory_t memory;
    linux_memory_t (&memory);
    auto available_memory = (memory.total_ram - memory.freeram) * memory.mem_unit;
    return static_cast<double>(available_memory);
#endif
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_MEMORY_MIXINS_NAVIGATOR_DEVICE_MEMORY_PRIVATE_HPP
