#include "credentials_container.hpp"

#include "javascript/environment/environment_settings.hpp"

#include "dom/abort/abort_signal.hpp"
#include "webappsec_credential_management/detail/algorithm_internals.hpp"


auto webappsec::credential_management::credentials_container::get(
        detail::credential_request_options_t&& options)
        -> ext::promise<credential*>
{

}
