#include "media_source_handle.hpp"
#include "media_source_handle_private.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"


media::source::media_source_handle::media_source_handle()
{
    INIT_PIMPL(media_source_handle);
}


media::source::media_source_handle::media_source_handle(const media::source::media_source_handle& other)
{
    ACCESS_PIMPL(media_source_handle);
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<DATA_CLONE_ERR>(
            [d] {return d->has_ever_been_assigned_as_srcobject;},
            u8"MediaSourceHandle cannot have ever been assigned as a srcobject");
}
