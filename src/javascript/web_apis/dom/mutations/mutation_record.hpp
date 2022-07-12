#ifndef SBROWSER2_MUTATION_RECORD_HPP
#define SBROWSER2_MUTATION_RECORD_HPP

#include "dom_object.hpp"
namespace dom::mutations {class mutation_record;}

#include "ext/vector.hpp"


class dom::mutations::mutation_record
        : public virtual web_apis::dom_object
{
public constructors:
    mutation_record() = default;

public js_properties:
    ext::property<ext::string> type;
    ext::property<ext::string> attribute_name;
    ext::property<ext::string> attribute_namespace;
    ext::property<ext::string> old_value;

    ext::property<std::unique_ptr<nodes::node>> target;
    ext::property<std::unique_ptr<nodes::node>> previous_sibling;
    ext::property<std::unique_ptr<nodes::node>> next_sibling;

    ext::property<std::unique_ptr<ext::vector<nodes::node*>>> added_nodes;
    ext::property<std::unique_ptr<ext::vector<nodes::node*>>> removed_nodes;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_MUTATION_RECORD_HPP
