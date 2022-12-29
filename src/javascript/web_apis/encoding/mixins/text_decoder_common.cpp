module;
#include "ext/macros/pimpl.hpp"


module apis.encoding.mixins.text_decoder_common;
import apis.encoding.mixins.text_decoder_common_private;
import ext.core;


auto encoding::mixins::text_decoder_common::get_encoding() const -> ext::string
{
    ACCESS_PIMPL;
    return d->encoding->name | ranges::views::lowercase | ranges::to_string();
}


auto encoding::mixins::text_decoder_common::get_fatal() const -> ext::boolean
{
    ACCESS_PIMPL;
    return ext::visit([]<ext::type_is_enum T>(T error_type) {return error_type == T::REPLACEMENT;}, d->error_mode);
}


auto encoding::mixins::text_decoder_common::get_ignore_bom() const -> ext::boolean
{
    ACCESS_PIMPL;
    return d->ignore_bom;
}
