#include "html_canvas_element.hpp"
#include "html_canvas_element_private.hpp"

#include "javascript/environment/feature_support.hpp"






#include "file_api/file.hpp"
#include "file_api/file_private.hpp"

#include "html/_typedefs.hpp"
#include "html/canvasing/canvas_rendering_context_2d.hpp"
#include "html/canvasing/image_bitmap.hpp"
#include "html/canvasing/image_bitmap_rendering_context.hpp"
#include "html/canvasing/offscreen_canvas.hpp"
#include "html/detail/canvas_internals.hpp"
#include "html/detail/task_internals.hpp"

#include "webgl2/contexts/webgl_rendering_context.hpp"
#include "webgl2/contexts/webgl2_rendering_context.hpp"


auto html::elements::html_canvas_element::get_context(
        detail::canvas_context_mode_t context_id,
        ext::map<ext::string, ext::any>&& options)
        -> detail::rendering_context_t
{
    ACCESS_PIMPL(html_canvas_element);
    using enum dom::detail::dom_exception_error_t;

    // If this HTMLCanvasElement is currently acting as a placeholder canvas, then throw an INVALID_STATE_ERR, as no
    // actual canvas object can be ontained from the HTMLCanvasElement.
    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [d] {return d->canvas_context_mode == detail::canvas_context_mode_t::PLACEHOLDER;},
            u8"Cannot get the context of a HTMLCanvasElement that has a placeholder context");

    // If the current context mode is NONE (no context but isn't placeholding a context either), then create the correct
    // type of context and return it. WebGL contexts are only creatable if OpenGL is supported on this device
    // (determined by a macro). Set the created context into the 'm_context' attribute too.
    if (d->canvas_context_mode == detail::canvas_context_mode_t::NONE)
    {
        if (context_id == detail::canvas_context_mode_t::_2D)
            return d->context = detail::context_creation_algorithm<canvasing::canvas_rendering_context_2d>(std::move(options));

        if (context_id == detail::canvas_context_mode_t::BITMAP_RENDERER)
            return d->context = detail::context_creation_algorithm<canvasing::image_bitmap_rendering_context>(std::move(options));

        #ifdef __open_gl_supported
        if (context_id == detail::canvas_context_mode_t::WEBGL)
            return d->context = detail::context_creation_algorithm<webgl2::contexts::webgl_rendering_context>(std::move(options));

        if (context_id == detail::canvas_context_mode_t::WEBGL2)
            return d->context = detail::context_creation_algorithm<webgl2::contexts::webgl2_rendering_context>(std::move(options));
        #endif

        if (context_id == detail::canvas_context_mode_t::WEBGPU)
            return d->context = detail::context_creation_algorithm<webgpu::gpu_canvas_context>(std::move(options));

        return static_cast<canvasing::canvas_rendering_context_2d*>(nullptr);
    }

    // If the desired context type (enum-determined) matches the curently stored context type, then return the context
    // type from the internally stored variant (JavaScript interop handles variants).
    else if (d->canvas_context_mode == context_id)
        return d->context;

    // Otherwise, there is a context type mismatch, so return nullptr (cast for the variant)
    return static_cast<canvasing::canvas_rendering_context_2d*>(nullptr);
}


auto html::elements::html_canvas_element::to_data_url(
        ext::string_view type,
        ext::any&& quality)
        -> ext::string
{
    ACCESS_PIMPL(html_canvas_element);
    using enum dom::detail::dom_exception_error_t;
    using namespace ext::literals;

    dom::detail::throw_v8_exception<SECURITY_ERR>(
            [d] {return !d->bitmap->d_func()->origin_clean_flag;},
            u8"Canvas bitmap must be origin-clean");

    return_if (d->bitmap->d_func()->width == 0 || d->bitmap->d_func()->height == 0) u"data:,";
    auto file = detail::serialization_of_bitmap_as_file(type, std::move(quality));

    return !file.has_value()
            ? "data:,"_es16
            : "data:,["_es16 + file->d_func()->type + u"];base64[" + file->d_func()->byte_sequence + u"]";
}


auto html::elements::html_canvas_element::to_blob(
        detail::blob_callback_t&& callback,
        ext::string_view type,
        ext::any&& quality)
        -> file_api::blob
{
    ACCESS_PIMPL(html_canvas_element);
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<SECURITY_ERR>(
            [d] {return !d->bitmap->d_func()->origin_clean_flag;},
            "Canvas bitmap must be origin-clean");

    auto result = (d->bitmap->d_func()->width > 0 || d->bitmap->d_func()->height > 0)
            ? detail::blob_callback_param_t{auto{*d->bitmap}}
            : detail::blob_callback_param_t{ext::variant_monostate_t{}};

    GO [type, &result, quality = std::move(quality), callback = std::move(callback)] mutable
    {
        result = ext::holds_alternative<ext::nullopt_t>(result)
                ? detail::serialization_of_bitmap_as_file(type, std::move(quality))
                : result;

        dom::detail::queue_element_task(html::detail::canvas_blob_serialization_task_source,
                [&result, callback = std::move(callback)]
                {callback(result ?: file_api::blob{{result}});});
    };
}


auto html::elements::html_canvas_element::transfer_control_to_offscreen()
        -> canvasing::offscreen_canvas
{
    ACCESS_PIMPL(html_canvas_element);
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [d] {return d->canvas_context_mode != detail::canvas_context_mode_t::NONE;},
            u8"HTMLCanvasElement's context mode must be NONE");

    auto offscreen_canvas = canvasing::offscreen_canvas{};
    offscreen_canvas.d_func()->placeholder_canvas_element = std::shared_ptr<html_canvas_element>{this};
    d->canvas_context_mode = detail::canvas_context_mode_t::PLACEHOLDER;
    return offscreen_canvas;
}
