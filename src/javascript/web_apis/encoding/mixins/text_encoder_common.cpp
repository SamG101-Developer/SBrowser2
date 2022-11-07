#include "text_encoder_common.hpp"
#include "text_encoder_common_private.hpp"


auto encoding::mixins::text_encoder_common::get_encoding() const -> ext::string_view
{
    ACCESS_PIMPL(const text_encoder_common);
    return d->encoding;
}
