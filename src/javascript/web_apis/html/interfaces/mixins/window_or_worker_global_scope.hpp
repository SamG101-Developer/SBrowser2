#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_WINDOW_OR_WORKER_GLOBAL_SCOPE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_WINDOW_OR_WORKER_GLOBAL_SCOPE_HPP


namespace html::mixins {class window_or_worker_global_scope;}
namespace html::mixins {class window_or_worker_global_scope_private;}


#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(html)
namespace fetch {class response;}
namespace indexed_db {class idb_factory;}
namespace service_workers::caches {class cache_storage;}
namespace web_crypto {class crypto;}


class html::mixins::window_or_worker_global_scope
        : public virtual dom_object
{
public constructors:
    MAKE_PIMPL(window_or_worker_global_scope);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto report_error(ext::any&& e) -> void;

    // Base64 Utility Methods
    auto btoa(ext::string_view data) -> ext::string;
    auto atob(ext::string_view data) -> ext::byte_string;

    // Timers
    template <typename ...Args> auto set_timeout(detail::timer_handler_t&& handler, ext::number<long> timeout = 0, Args&&... arguments) -> ext::number<long>;
    template <typename ...Args> auto set_interval(detail::timer_handler_t&& handler, ext::number<long> timeout = 0, Args&&... arguments) -> ext::number<long>;
    auto clear_timeout(ext::number<long> id = 0) -> void;
    auto clear_interval(ext::number<long> id = 0) -> void;

    // Microtask Queueing
    auto queue_microtask(ext::function<void()>&& callback) -> void;

    // Image Bitmap
    auto create_image_bitmap(detail::image_bitmap_source_t image, detail::image_bitmap_options_t&& options = {}) -> ext::promise<canvasing::image_bitmap*>;
    auto create_image_bitmap(detail::image_bitmap_source_t image, ext::number<long> sx, ext::number<long> sy, ext::number<long> sw, ext::number<long> sh, detail::image_bitmap_options_t&& options = {}) -> ext::promise<canvasing::image_bitmap*>;

    // Structured Cloning
    auto structured_clone(ext::any&& value, detail::structured_serialize_options_t&& options = {}) -> ext::any&;

    /* [FETCH] */
    auto fetch(fetch::detail::request_info_t&& input, fetch::detail::request_init_t&& init = {}) -> ext::promise<std::unique_ptr<fetch::response>>;

private js_properties:
    DEFINE_GETTER(origin, ext::string);
    DEFINE_GETTER(is_secure_context, ext::boolean);
    DEFINE_GETTER(cross_origin_isolated, ext::boolean);

    /* [INDEX-DB] */
    DEFINE_GETTER(indexed_db, indexed_db::idb_factory*);

    /* [SERVICE-WORKERS] */
    DEFINE_GETTER(cache, service_workers::caches::cache_storage);

    /* [WEB-CRYPTO] */
    DEFINE_GETTER(crypto, web_crypto::crypto*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_WINDOW_OR_WORKER_GLOBAL_SCOPE_HPP
