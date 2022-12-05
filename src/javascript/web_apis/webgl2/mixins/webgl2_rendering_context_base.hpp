#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBdetail::gl2_MIXINS_WEBdetail::gl2_RENDERING_CONTEXT_BASE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBdetail::gl2_MIXINS_WEBdetail::gl2_RENDERING_CONTEXT_BASE_HPP


namespace webgl2::mixins {class webgl2_rendering_context_base;}
namespace webgl2::mixins {class webgl2_rendering_context_base_private;}

#include INCLUDE_INNER_TYPES(webgl2)
#include "ext/span.hpp"
#include <v8-forward.h>
namespace webgl2::objects {class webgl_program;}
namespace webgl2::objects {class webgl_texture;}
namespace webgl2::other {class webgl_uniform_location;}


class webgl2::mixins::webgl2_rendering_context_base
        : public virtual dom_object
{
public constructors:
    webgl2_rendering_context_base();
    MAKE_PIMPL(webgl2_rendering_context_base);
    MAKE_V8_AVAILABLE;

public js_methods:
    // Buffer Objects
    auto copy_buffer_sub_data(
            detail::glenum_t read_target, detail::glenum_t write_target, detail::glintptr_t read_offset,
            detail::glintptr_t write_offset, detail::glsizeiptr_t size) -> void;

    auto get_buffer_sub_data(
            detail::glenum_t target, detail::glintptr_t src_byte_offset,v8::ArrayBufferView dst_buffer,
            detail::gluint_t dst_offset = 0, detail::gluint_t length = 0) -> void;

    // Frame Buffer Objects
    auto blit_frame_buffer(
            detail::glint_t src_x0, detail::glint_t src_y0, detail::glint_t src_x1, detail::glint_t src_y1,
            detail::glint_t dst_x0, detail::glint_t dst_y0, detail::glint_t dst_x1, detail::glint_t dst_y1,
            detail::glbitfield_t mask, detail::glenum_t filter) -> void;

    auto framebuffer_texture_layer(
            detail::glenum_t target, detail::glenum_t attachment, objects::webgl_texture* texture, detail::glint_t level,
            detail::glint_t layer) -> void;

    auto invalidate_framebuffer(
            detail::glenum_t target, ext::vector_span<detail::glenum_t> attachments) -> void;

    auto invalidate_sub_framebuffer(
            detail::glenum_t target, ext::vector_span<detail::glenum_t> attachments, detail::glint_t x,
            detail::glint_t y, detail::glsizei_t width, detail::glsizei_t height) -> void;

    auto read_buffer(
            detail::glenum_t src) -> void;

    // Renderbuffer Objects
    auto get_internalformat_parameter(
            detail::glenum_t target, detail::glenum_t internalformat, detail::glenum_t pname) -> ext::any;

    auto renderbuffer_storage_multisample(
            detail::glenum_t target, detail::glsizei_t samples, detail::glenum_t internalformat,
            detail::glsizei_t width, detail::glsizei_t height) -> void;

    // Texture Objects
    auto tex_storage_2d(
            detail::glenum_t target, detail::glsizei_t levels, detail::glenum_t internalformat, detail::glsizei_t width,
            detail::glsizei_t height) -> void;

    auto tex_storage_3d(
            detail::glenum_t target, detail::glsizei_t levels, detail::glenum_t internalformat, detail::glsizei_t width,
            detail::glsizei_t height, detail::glsizei_t depth) -> void;

    auto tex_image_3d(
            detail::glenum_t target, detail::glint_t level, detail::glint_t internalformat, detail::glsizei_t width,
            detail::glsizei_t height, detail::glsizei_t depth, detail::glint_t border, detail::glenum_t format,
            detail::glenum_t type, detail::glintptr_t pbo_offset) -> void;

    auto tex_image_3d(
            detail::glenum_t target, detail::glint_t level, detail::glint_t internalformat, detail::glsizei_t width,
            detail::glsizei_t height, detail::glsizei_t depth, detail::glint_t border, detail::glenum_t format,
            detail::glenum_t type, detail::tex_image_source&& source) -> void;

    auto tex_image_3d(
            detail::glenum_t target, detail::glint_t level, detail::glint_t internalformat, detail::glsizei_t width,
            detail::glsizei_t height, detail::glsizei_t depth, detail::glint_t border, detail::glenum_t format,
            detail::glenum_t type, v8::ArrayBufferView src_data, detail::gluint_t src_offset = 0) -> void;

    auto tex_sub_image_3d(
            detail::glenum_t target, detail::glint_t level, detail::glint_t xoffset, detail::glint_t yoffset,
            detail::glint_t zoffset, detail::glsizei_t width, detail::glsizei_t height, detail::glsizei_t depth,
            detail::glenum_t format, detail::glenum_t type, detail::glintptr_t pbo_offset) -> void;

    auto tex_sub_image_3d(
            detail::glenum_t target, detail::glint_t level, detail::glint_t xoffset, detail::glint_t yoffset,
            detail::glint_t zoffset, detail::glsizei_t width, detail::glsizei_t height, detail::glsizei_t depth,
            detail::glenum_t format, detail::glenum_t type, detail::tex_image_source&& source) -> void;

    auto tex_sub_image_3d(
            detail::glenum_t target, detail::glint_t level, detail::glint_t xoffset, detail::glint_t yoffset,
            detail::glint_t zoffset, detail::glsizei_t width, detail::glsizei_t height, detail::glsizei_t depth,
            detail::glenum_t format, detail::glenum_t type, v8::ArrayBufferView src_data,
            detail::gluint_t src_offset = 0) -> void;

    auto copy_tex_sub_image_3d(
            detail::glenum_t target, detail::glint_t level, detail::glint_t xoffset, detail::glint_t yoffset,
            detail::glint_t zoffset, detail::glint_t x, detail::glint_t y, detail::glsizei_t width,
            detail::glsizei_t height) -> void;

    auto compressed_tex_image_3d(
            detail::glenum_t target, detail::glint_t level, detail::glenum_t internalformat, detail::glsizei_t width,
            detail::glsizei_t height, detail::glsizei_t depth, detail::glint_t border, detail::glsizei_t image_size,
            detail::glintptr_t offset) -> void;

    auto compressed_tex_image_3d(
            detail::glenum_t target, detail::glint_t level, detail::glenum_t internalformat, detail::glsizei_t width,
            detail::glsizei_t height, detail::glsizei_t depth, detail::glint_t border, v8::ArrayBufferView src_data,
            detail::gluint_t src_offset = 0, detail::gluint_t src_length_override = 0) -> void;

    auto compressed_tex_sub_image_3d(
            detail::glenum_t target, detail::glint_t level, detail::glint_t xoffset, detail::glint_t yoffset,
            detail::glint_t zoffset, detail::glsizei_t width, detail::glsizei_t height, detail::glsizei_t depth,
            detail::glenum_t format, detail::glsizei_t image_size, detail::glintptr_t offset) -> void;

    auto compressed_tex_sub_image_3d(
            detail::glenum_t target, detail::glint_t level, detail::glint_t xoffset, detail::glint_t yoffset,
            detail::glint_t zoffset, detail::glsizei_t width, detail::glsizei_t height, detail::glsizei_t depth,
            detail::glenum_t format, v8::ArrayBufferView src_data, detail::gluint_t src_offset = 0,
            detail::gluint_t src_length_override = 0) -> void;

    // Programs & Shaders
    auto get_frag_data_location(
            objects::webgl_program* program, ext::string&& name) -> detail::glint_t;

    // Uniforms
    auto uniform1ui(
            other::webgl_uniform_location* location, detail::gluint_t v0) -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBdetail::gl2_MIXINS_WEBdetail::gl2_RENDERING_CONTEXT_BASE_HPP
