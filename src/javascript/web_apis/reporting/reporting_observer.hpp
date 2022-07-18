#pragma once
#ifndef SBROWSER2_REPORTING_OBSERVER_HPP
#define SBROWSER2_REPORTING_OBSERVER_HPP

#include "dom_object.hpp"
namespace reporting {class reporting_observer;}

#include "ext/functional.hpp"
#include "ext/map.hpp"
#include "ext/vector.hpp"
namespace reporting {class report;}


class reporting::reporting_observer
        : public dom_object
{
public aliases:
    using reporting_observer_callback = ext::function<void(const ext::vector<ext::string>&, reporting_observer*)>;

public constructors:
    reporting_observer(reporting_observer_callback&& callback, ext::map<ext::string, ext::any> options = {});

public js_methods:
    auto observe() -> void;
    auto disconnect() -> void;
    auto take_record() -> ext::vector<report*>;
};


#endif //SBROWSER2_REPORTING_OBSERVER_HPP
