#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_DECODER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_DECODER_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"
#include "encoding/mixins/text_decoder_common_private.hpp"


DEFINE_PRIVATE_CLASS(encoding, text_decoder)
        : virtual dom_object_private
        , mixins::text_decoder_common_private
{
    MAKE_QIMPL(text_decoder);
    ext::boolean do_not_flush;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_TEXT_DECODER_PRIVATE_HPP
