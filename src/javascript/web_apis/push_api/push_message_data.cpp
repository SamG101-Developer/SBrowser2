#include "push_message_data.hpp"
#include "push_message_data_private.hpp"

#include "file_api/blob.hpp"

#include <v8-array-buffer.h>


auto push_api::push_message_data::array_buffer() const -> v8::Local<v8::ArrayBuffer>
{
    ACCESS_PIMPL(const push_message_data);
    return v8::ArrayBuffer::New(v8::ArrayBuffer::NewBackingStore(d->bytes.data(), d->bytes.size(), [] {}, nullptr));
}


auto push_api::push_message_data::blob() const -> file_api::blob
{
    ACCESS_PIMPL(const push_message_data);
    return file_api::blob{{d->bytes}};
}


auto push_api::push_message_data::json() const -> ext::any
{
    ACCESS_PIMPL(const push_message_data);
    JS_REALM_GET_RELEVANT(this);

    auto v8_string = v8pp::to_v8(this_relevant_agent, d->bytes);
    auto v8_json = v8::JSON::Parse(this_relevant_realm, v8_string).ToLocalChecked();
    return v8pp::from_v8<ext::string>(this_relevant_agent, v8_json);
}


auto push_api::push_message_data::text() const -> ext::string_view
{
    ACCESS_PIMPL(const push_message_data);
    return d->bytes;
}
