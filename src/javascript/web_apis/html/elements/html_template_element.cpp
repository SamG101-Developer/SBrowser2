#include "html_template_element.hpp"

#include "ext/casting.hpp"

#include "dom/detail/node_internals.hpp"
#include "dom/nodes/document_fragment.hpp"

#include "html/detail/document_internals.hpp"

#include <range/v3/view/transform.hpp>


html::elements::html_template_element::html_template_element()
{
    m_dom_behaviour.adopting_steps =
            [this]
            {
                decltype(auto) document = detail::appropriate_template_contents_owner_document(owner_document());
                dom::detail::adopt(content(), document);
            };

    m_dom_behaviour.cloning_steps =
            [this](dom::nodes::node* clone, dom::nodes::document* document, ext::boolean&& deep)
            {
                return_if (!deep);
                auto copied_contents = content()->child_nodes() | ranges::views::transform(ext::bind_back{dom::detail::clone<dom::nodes::document_fragment>, content()->owner_document(), true});

                ext::apply(
                        ext::make_tuple(copied_contents),
                        &dom_cast<html_template_element*>(clone)->content()->append);
            };

    HTML_CONSTRUCTOR
}
