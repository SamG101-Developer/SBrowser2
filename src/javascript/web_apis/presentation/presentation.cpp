#include "presentation.hpp"
#include "presentation_private.hpp"


presentation::presentation::presentation()
{
    INIT_PIMPL(presentation);
}


auto presentation::presentation::get_presentation_request() const -> presentation_request*
{
    ACCESS_PIMPL(const presentation);
    return d->presentation_request.get();
}


auto presentation::presentation::get_presentation_receiver() const -> presentation_receiver*
{
    ACCESS_PIMPL(const presentation);
    return d->presentation_receiver.get();
}


auto presentation::presentation::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<presentation>{isolate}
        .inherit<dom_object>()
        .property("presentationRequest", &presentation::get_presentation_request)
        .property("presentationReceiver", &presentation::get_presentation_receiver)
        .auto_wrap_objects();
}
