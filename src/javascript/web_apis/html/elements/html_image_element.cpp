#include "html_image_element.hpp"
#include "dom/_typedefs.hpp"
#include "html/_typedefs.hpp"
#include "html_image_element_private.hpp"

#include "ext/threading.hpp"

#include "javascript/environment/reflection.hpp"

#include "dom/detail/customization_internals.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/other/dom_exception.hpp"

#include "html/detail/image_internals.hpp"
#include "html/detail/miscellaneous_internals.hpp"


html::elements::html_image_element::html_image_element()
{
    INIT_PIMPL(html_image_element);
    ACCESS_PIMPL(html_image_element);

    d->insertion_steps = []
    {
        /* TODO */
    };

    d->remove_steps = [](dom::nodes::node* old_parent)
    {
        /* TODO */
    };

    d->dimension_attribute_source = std::unique_ptr<html_image_element>{this};
    d->current_request = std::make_unique<detail::image_request_t>();
    d->pending_request = nullptr;

    HTML_CONSTRUCTOR
}


auto html::elements::html_image_element::decode() -> ext::promise<void>
{
    ACCESS_PIMPL(html_image_element);
    auto promise = ext::promise<void>{};

    // queue a microtask for decoding the HTMLImageElement properly
    dom::detail::queue_microtask([this, d, &promise]
    {
        using detail::state_t;
        using enum dom::detail::dom_exception_error_t;

        // automatically reject the promise if the HTMLImageElement's 'owner_document' isn't fully active; only an image
        // belonging to a filly active document has be decoded
        if (dom::detail::is_document_fully_active(d->node_document) || d->current_request->state == state_t::BROKEN)
        {
            promise.reject(dom::other::dom_exception{u8"", ENCODING_ERR});
            return;
        }

        // otherwise, the document is fully active, so the process to try and decode the image can begin
        // run the loop (which can wait for a bit of time) in a separate thread - this is because the waiting
        // process would otherwise block the main thread
        GO [this, d, &promise]
        {
            // save the data of the image, so that the loop can check if the current requests image data has
            // mutated, as this is a reason to break from the loop
            decltype(auto) old_image_data = d->current_request->image_data;
            while (true)
            {
                // if the document becomes not fully active, the current request's image data mutates, or the state
                // of the current request becomes BROKEN, then reject the promise with an encoding error (and break
                // the while-loop)
                if (!dom::detail::is_document_fully_active(d->node_document)
                        || d->current_request->image_data != old_image_data
                        || d->current_request->state == state_t::BROKEN)
                {
                    promise.reject(dom::other::dom_exception{"", ENCODING_ERR});
                    break;
                }

                // if the current request's state becomes COMPLETELY_AVAILABLE, then run the internal detail method
                // to decode the image (and break from the loop)
                if(d->current_request->state == state_t::COMPLETELY_AVAILABLE)
                {
                    detail::decode(this);
                    break;
                }
            }
        };
    });
}


auto html::elements::html_image_element::get_alt() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_image_element);
        return d->alt;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_image_element::get_src() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_image_element);
        return d->src;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_image_element::get_srcset() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_image_element);
        return d->srcset;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_image_element::get_sizes() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_image_element);
        return d->sizes;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_image_element::get_cross_origin() const -> detail::cross_origin_settings_attribute_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_image_element);
        return d->cross_origin;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_image_element::get_use_map() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_image_element);
        return d->use_map;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_image_element::get_is_map() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_image_element);
        return d->is_map;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_image_element::get_referrer_policy() const -> referrer_policy::detail::referrer_policy_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_image_element);
        return d->referrer_policy;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_image_element::get_decoding() const -> detail::image_decoding_hint_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_image_element);
        return d->decoding;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_image_element::get_loading() const -> detail::lazy_loading_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_image_element);
        return d->loading;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_image_element::set_alt(ext::string new_alt) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_image_element);
        return d->alt = std::move(new_alt);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_image_element::set_src(ext::string new_src) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_image_element);
        return d->src = std::move(new_src);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_image_element::set_srcset(ext::string new_srcset) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_image_element);
        return d->srcset = std::move(new_srcset);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_image_element::set_sizes(ext::string new_sizes) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_image_element);
        return d->sizes = std::move(new_sizes);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_image_element::set_cross_origin(detail::cross_origin_settings_attribute_t new_cross_origin) -> detail::cross_origin_settings_attribute_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_image_element);
        return d->cross_origin = new_cross_origin;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_image_element::set_use_map(ext::string new_use_map) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_image_element);
        return d->use_map = std::move(new_use_map);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_image_element::set_is_map(ext::boolean new_is_map) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_image_element);
        return d->is_map = new_is_map;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_image_element::set_referrer_policy(referrer_policy::detail::referrer_policy_t new_referrer_policy) -> referrer_policy::detail::referrer_policy_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_image_element);
        return d->referrer_policy = new_referrer_policy;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_image_element::set_loading(detail::lazy_loading_t new_loading) -> detail::lazy_loading_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_image_element);
        d->loading = new_loading;

        if (new_loading == detail::lazy_loading_t::EAGER)
        {
            return_if(!d->lazy_load_resumption_steps.empty()) d->loading;
            d->lazy_load_resumption_steps();
            d->lazy_load_resumption_steps = [] {};
        }

        return d->loading;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_image_element::set_decoding(detail::image_decoding_hint_t new_decoding) -> detail::image_decoding_hint_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_image_element);
        return d->decoding = new_decoding;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_image_element::get_current_src() const -> ext::string_view
{
    ACCESS_PIMPL(const html_image_element);
    return detail::serialize_url(*d->current_request->url);
}


auto html::elements::html_image_element::get_complete() const -> ext::boolean
{
    ACCESS_PIMPL(const html_image_element);

    // if there is no 'src' or 'srcset', then the HTMLImageElement is automatically complete, as there is nothing to do;
    // this is teh same as when the 'src' exists but is an empty string. if the current request is COMPLETELY_AVAILABLE
    // or BROKEN, and there is no pending request, then the image is 'complete' too
    auto e = js::env::env::relevant(this);
    return !reflect_has_attribute_value(this, "src", this_relevant) && !reflect_has_attribute_value(this, "srcset", this_relevant)
           || !reflect_has_attribute_value(this, "srcset", this_relevant) && d->src.empty()
           || d->current_request->state == detail::state_t::COMPLETELY_AVAILABLE && !d->pending_request
           || d->current_request->state == detail::state_t::BROKEN && !d->pending_request;
}
