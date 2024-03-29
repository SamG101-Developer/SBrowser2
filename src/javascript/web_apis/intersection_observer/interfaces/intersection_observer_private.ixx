module;
#include "ext/macros.hpp"


export module apis.intersection_observer.intersection_observer:p;
import apis.dom_object;

IMPORT_ALL_TYPES(intersection_observer);


DEFINE_PRIVATE_CLASS(intersection_observer, intersection_observer)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(intersection_observer);

public:
    auto parse_root_margin(ext::string_view margin_string) -> ext::expected<ext::array<ext::number<int>, 4>>;
    auto intersection_root() -> dom::node*;
    auto implicit_root() -> dom::node*;
    auto is_explicit_root_observer() -> ext::boolean;
    auto is_implicit_root_observer() -> ext::boolean;

public:
    intersection_observer_callback_t callback;
    ext::array<int, 4> root_margin;
    ext::vector<dom::element*> observation_targets;
    ext::vector<intersection_observer_entry*> queued_entries;
    ext::vector<ext::number<double>> thresholds;
    std::observer_ptr<dom::node> root;
};
