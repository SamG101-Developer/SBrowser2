#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_MIXINS_TEXT_DECODER_COMMON_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_MIXINS_TEXT_DECODER_COMMON_HPP

#include "dom_object.hpp"
namespace encoding::mixins {class text_decoder_common;}

#include "ext/variant.hpp"
#include INCLUDE_INNER_TYPES(encoding)
namespace encoding {class encoding;}


class encoding::mixins::text_decoder_common
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(text_decoder_common);
    text_decoder_common() = default;

public js_properties:
    ext::property<ext::string> encoding_object;
    ext::property<ext::boolean> fatal;
    ext::property<ext::boolean> ignore_bom;

private cpp_properties:
    const encoding& m_encoding;
    const detail::decoder_t& m_decoder;
    const detail::encoder_t& m_encoder;
    detail::io_queue_t& m_io_queue;
    ext::boolean m_ignore_bom;
    ext::boolean m_bom_seen;
    ext::variant<detail::decoder_error_mode_t, detail::encoder_error_mode_t> m_error_mode;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_MIXINS_TEXT_DECODER_COMMON_HPP
