#include "webgl2_rendering_context_base.hpp"
#include "webgl2_rendering_context_base_private.hpp"

#include "webgl2/objects/webgl_texture.hpp"
#include "webgl2/objects/webgl_texture_private.hpp"


auto webgl2::mixins::webgl2_rendering_context_base::copy_buffer_sub_data(
        detail::glenum_t read_target, detail::glenum_t write_target,
        detail::glintptr_t read_offset, detail::glintptr_t write_offset,
        detail::glsizeiptr_t size)
        -> void
{
    ACCESS_PIMPL(webgl2_rendering_context_base);
    d->gl->glCopyBufferSubData(read_target, write_target, read_offset, write_offset, size);
}


auto webgl2::mixins::webgl2_rendering_context_base::get_buffer_sub_data(
        detail::glenum_t target, detail::glintptr_t src_byte_offset,
        v8::ArrayBufferView dst_buffer, detail::gluint_t dst_offset,
        detail::gluint_t length)
        -> void
{
    ACCESS_PIMPL(webgl2_rendering_context_base);
    d->gl->glGetBufferSubData(target, src_byte_offset, length, dst_buffer.Buffer()->GetBackingStore()->Data() + dst_offset);
}


auto webgl2::mixins::webgl2_rendering_context_base::blit_frame_buffer(
        detail::glint_t src_x0, detail::glint_t src_y0, detail::glint_t src_x1, detail::glint_t src_y1,
        detail::glint_t dst_x0, detail::glint_t dst_y0, detail::glint_t dst_x1, detail::glint_t dst_y1,
        detail::glbitfield_t mask, detail::glenum_t filter)
        -> void
{
    ACCESS_PIMPL(webgl2_rendering_context_base);
    d->gl->glBlitFramebuffer(src_x0, src_y0, src_x1, src_y1, dst_x0, dst_y0, dst_x1, dst_y1, mask, filter);
}


auto webgl2::mixins::webgl2_rendering_context_base::framebuffer_texture_layer(
        detail::glenum_t target, detail::glenum_t attachment,
        objects::webgl_texture* texture, detail::glint_t level, detail::glint_t layer)
        -> void
{
    ACCESS_PIMPL(webgl2_rendering_context_base);
    d->gl->glFramebufferTextureLayer(target, attachment, texture->d_func()->gl->textureId(), level, layer);
}


auto webgl2::mixins::webgl2_rendering_context_base::invalidate_framebuffer(
        detail::glenum_t target, ext::vector_span<detail::glenum_t> attachments)
        -> void
{
    ACCESS_PIMPL(webgl2_rendering_context_base);
    d->gl->glInvalidateFramebuffer(target, attachments.size(), attachments.data());
}


auto webgl2::mixins::webgl2_rendering_context_base::invalidate_sub_framebuffer(
        detail::glenum_t target, ext::vector_span<detail::glenum_t> attachments,
        detail::glint_t x, detail::glint_t y,
        detail::glsizei_t width, detail::glsizei_t height)
        -> void
{
    ACCESS_PIMPL(webgl2_rendering_context_base);
    d->gl->glInvalidateSubFramebuffer(target, attachments.size(), attachments.data(), x, y, width, height);
}


auto webgl2::mixins::webgl2_rendering_context_base::read_buffer(
        detail::glenum_t src)
        -> void
{
    ACCESS_PIMPL(webgl2_rendering_context_base);
    d->gl->glReadBuffer(src);
}


auto webgl2::mixins::webgl2_rendering_context_base::get_internalformat_parameter(
        detail::glenum_t target, detail::glenum_t internalformat, detail::glenum_t pname)
        -> ext::any
{
    ACCESS_PIMPL(webgl2_rendering_context_base);
    // TODO
}


auto webgl2::mixins::webgl2_rendering_context_base::tex_storage_2d(
        detail::glenum_t target, detail::glsizei_t levels, detail::glenum_t internalformat,
        detail::glsizei_t width, detail::glsizei_t height)
        -> void
{
    ACCESS_PIMPL(webgl2_rendering_context_base);
    d->gl->glTexStorage2D(target, levels, internalformat, width, height);
}


auto webgl2::mixins::webgl2_rendering_context_base::tex_storage_3d(
        detail::glenum_t target, detail::glsizei_t levels, detail::glenum_t internalformat,
        detail::glsizei_t width, detail::glsizei_t height, detail::glsizei_t depth)
        -> void
{
    ACCESS_PIMPL(webgl2_rendering_context_base);
    d->gl->glTexStorage3D(target, levels, internalformat, width, height, depth);
}


auto webgl2::mixins::webgl2_rendering_context_base::tex_image_3d(
        detail::glenum_t target, detail::glint_t level, detail::glint_t internalformat,
        detail::glsizei_t width, detail::glsizei_t height, detail::glsizei_t depth,
        detail::glint_t border, detail::glenum_t format, detail::glenum_t type, v8::ArrayBufferView src_data)
        -> void
{
    ACCESS_PIMPL(webgl2_rendering_context_base);
    d->gl->glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, src_data.Buffer()->GetBackingStore()->Data());
}