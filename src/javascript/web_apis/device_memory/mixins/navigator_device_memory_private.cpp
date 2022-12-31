module;
#include <hwinfo/ram.h>

//#ifdef OS_WINDOWS
//    #include <sysinfoapi.h>
//#elifdef OS_LINUX
//    #include <sys/sysinfo.h>
//#elifdef OS_UNIX
//    #include <unistd.h>
//#endif



module apis.device_memory.mixins.navigator_device_memory:p;
import ext.core;


auto device_memory::mixins::navigator_device_memory_private::device_memory() const -> ext::number<double>
{
    return hwinfo::RAM::getTotalSize_Bytes();
//#ifdef OS_WINDOWS
//    using windows_memory_t = PULONGLONG;
//    auto windows_memory = windows_memory_t{};
//    return GetPhysicallyInstalledSystemMemory(windows_memory) / 1048576;
//#elifdef OS_UNIX
//    auto pages = sysconf(_SC_PHYS_PAGES);
//    auto page_size = sysconf(_SC_PAGE_SIZE);
//    return pages * page_size;
//#endif
}
