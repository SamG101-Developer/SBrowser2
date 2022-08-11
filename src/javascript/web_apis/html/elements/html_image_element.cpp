#include "html_image_element.hpp"

#include "ext/threading.hpp"

#include "javascript/environment/reflection.hpp"

#include "dom/detail/exception_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/other/dom_exception.hpp"

#include "html/detail/image_internals.hpp"
#include "html/detail/miscellaneous_internals.hpp"


html::elements::html_image_element::html_image_element()
{
    bind_set(loading);

    loading._Meta._AttachConstraint("eager", "lazy");

    m_dom_behaviour.insertion_steps = []
    {
        /* TODO */
    };

    m_dom_behaviour.remove_steps = [](dom::nodes::node* old_parent)
    {
        /* TODO */
    };

    m_dimension_attribute_source = std::unique_ptr<html_image_element>{this};
    m_current_request = std::unique_ptr<detail::image_internals::image_request>();
    m_pending_request = nullptr;

    HTML_CONSTRUCTOR
}


auto html::elements::html_image_element::decode()
        -> std::promise<void>
{
    std::promise<void> promise;

    // queue a microtask for decoding the HTMLImageElement properly
    dom::detail::observer_internals::queue_microtask([this, &promise]
    {
        using enum detail::image_internals::state_t;

        // automatically reject the promise if the HTMLImageElement's 'owner_document' isn't fully active; only an image
        // belonging to a filly active document has be decoded
        if (dom::detail::node_internals::is_document_fully_active(owner_document())
                || m_current_request->state == BROKEN)
            promise.set_exception(dom::other::dom_exception{"", ENCODING_ERR});

        // otherwise, the document is fully active, so the process to try and decode the image can begin
        else
        {
            // run the loop (which can wait for a bit of time) in a separate thread - this is because the waiting
            // process would otherwise block the main thread
            ext::thread_pool pool {10};
            pool.push_task([this, &promise]
            {
                // save the data of the image, so that the loop can check if the current requests image data has
                // mutated, as this is a reason to break from the loop
                auto old_image_data = m_current_request->image_data;
                while (true)
                {
                    // if the document becomes not fully active, the current request's image data mutates, or the state
                    // of the current request becomes BROKEN, then reject the promise with an encoding error (and break
                    // the while-loop)
                    if (!dom::detail::node_internals::is_document_fully_active(owner_document())
                            || m_current_request->image_data != old_image_data
                            || m_current_request->state == BROKEN)
                    {
                        promise.set_exception(dom::other::dom_exception{"", ENCODING_ERR});
                        break;
                    }

                    // if the current request's state becomes COMPLETELY_AVAILABLE, then run the internal detail method
                    // to decode the image (and break from the loop)
                    if(m_current_request->state == COMPLETELY_AVAILABLE)
                    {
                        detail::image_internals::decode(this);
                        break;
                    }
                }
            }); // pool.push_task(...)
        }
    }); // queue_microtask(...)
}


auto html::elements::html_image_element::get_current_src()
        const -> ext::string
{
    return detail::miscellaneous_internals::serialize_url(m_current_request->url);
}


auto html::elements::html_image_element::get_complete()
        const -> ext::boolean
{
    using enum detail::image_internals::state_t;

    // if there is no 'src' or 'srcset', then the HTMLImageElement is automatically complete, as there is nothing to do;
    // this is teh same as when the 'src' exists but is an empty string. if the current request is COMPLETELY_AVAILABLE
    // or BROKEN, and there is no pending request, then the image is 'complete' too
    JS_REALM_GET_RELEVANT(this)
    return !reflect_has_attribute_value(this, "src", this_relevant) && !reflect_has_attribute_value(this, "srcset", this_relevant)
           || !reflect_has_attribute_value(this, "srcset", this_relevant) && src().empty()
           || m_current_request->state == COMPLETELY_AVAILABLE && !m_pending_request
           || m_current_request->state == BROKEN && !m_pending_request;
}


auto html::elements::html_image_element::set_loading(
        ext::string_view val)
        -> void
{
    if (val == "eager")
    {
        return_if(!m_lazy_load_resumption_steps);
        m_lazy_load_resumption_steps();
        m_lazy_load_resumption_steps = [] {};
    }
}
