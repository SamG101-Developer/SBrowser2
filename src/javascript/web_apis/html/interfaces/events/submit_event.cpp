#include "submit_event.hpp"
#include "submit_event_private.hpp"

#include "html/elements/html_form_element.hpp"


html::events::submit_event::submit_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event(std::move(event_type), std::move(event_init))
{
    INIT_PIMPL(submit_event);

    ACCESS_PIMPL(submit_event);
    d->submitter = std::unique_ptr<elements::html_form_element>(event_init[u"submitter"].to<elements::html_form_element*>());
}


auto html::events::submit_event::get_submitter() const -> html::elements::html_form_element*
{
    ACCESS_PIMPL(const submit_event);
    return d->submitter.get();
}
