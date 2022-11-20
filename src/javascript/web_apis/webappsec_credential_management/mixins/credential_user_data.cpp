#include "credential_user_data.hpp"
#include "credential_user_data_private.hpp"

#include "url/detail/url_internals.hpp"
#include "webappsec_mixed_content/detail/algorithm_internals.hpp"


auto webappsec::credential_management::mixins::credential_user_data::get_name() const -> ext::string_view
{
    ACCESS_PIMPL(const credential_user_data);
    return d->name;
}


auto webappsec::credential_management::mixins::credential_user_data::get_icon_url() const -> ext::string
{
    ACCESS_PIMPL(const credential_user_data);
    return detail::is_priori_authenticated_url(*d->icon_url) ? url::detail::url_serializer(*d->icon_url) : u"";
}
