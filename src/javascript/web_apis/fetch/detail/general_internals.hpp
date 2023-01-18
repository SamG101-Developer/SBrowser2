#pragma once
#include "ext/memory.ixx"
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_DETAIL_GENERAL_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_DETAIL_GENERAL_INTERNALS_HPP


#include "ext/optional.ixx"
#include "ext/vector.hpp"
#include <v8-forward.h>
#include <range/v3/to_container.hpp>
#include <range/v3/view/iota.hpp>
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(hr_time)
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(url)

namespace dom::other {class dom_exception;}


namespace fetch::detail
{
    using algorithm_t = ext::function<void(v8::Local<v8::Object>)>;

    const ext::vector<ext::number<ushort>> null_body_status {101, 103, 204, 205, 304};
    const ext::vector<ext::number<ushort>> ok_status = ranges::views::closed_iota(200, 299) | ranges::to<ext::vector<ext::number<ushort>>>;
    const ext::vector<ext::number<ushort>> redirect_status {101, 103, 204, 205, 304};


    auto translate_potential_destination(
            ext::string_view potential_destination)
            -> ext::string;

    auto terminate_fetch_group(
            fetch_group_t& fetch_group_object)
            -> void;
}


struct fetch::detail::fetch_record_t
{
    // Don't retain any ownership over these pointers TODO ???
    std::observer_ptr<request_t> request;
    std::observer_ptr<fetch_controller_t> controller;
};


struct fetch::detail::fetch_group_t
{
    ext::vector<std::unique_ptr<fetch_record_t>> fetch_records;
    std::observer_ptr<request_t> request;
    std::observer_ptr<fetch_controller_t> fetch_controller;

    ~fetch_group_t();
};





#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_DETAIL_GENERAL_INTERNALS_HPP
