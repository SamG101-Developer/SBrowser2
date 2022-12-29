#include "form_data_event.hpp"
#include "form_data_event_private.hpp"

#include "xhr/form_data.hpp"


html::events::form_data_event::form_data_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event{std::move(event_type), std::move(event_init)}
{
    INIT_PIMPL(form_data_event);

    ACCESS_PIMPL(form_data_event);
    d->form_data = std::unique_ptr<xhr::form_data>{event_init[u"formData"].to<xhr::form_data*>()};
}


auto html::events::form_data_event::get_form_data() const -> xhr::form_data*
{
    ACCESS_PIMPL(const form_data_event);
    return d->form_data.get();
}
