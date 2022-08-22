#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FULLSCREEN_DETAIL_FULLSCREEN_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FULLSCREEN_DETAIL_FULLSCREEN_INTERNALS_HPP

namespace dom::nodes {class document;}
namespace dom::nodes {class element;}


namespace fullscreen::detail
{
    auto fullscreen_element(
            dom::nodes::element* element)
            -> void;

    auto unfullscreen_element(
            dom::nodes::element* element)
            -> void;

    auto unfullscreen_document(
            dom::nodes::document* document)
            -> void;

    auto fully_exit_fullscreen(
            dom::nodes::document* document)
            -> void;

    auto fullscreen_steps(
            dom::nodes::document* document)
            -> void;

    auto fullscreen_element_ready_check(
            dom::nodes::element* element)
            -> ext::boolean;

    auto collect_documents_to_unfullscreen(
            dom::nodes::document* document)
            -> ext::vector<dom::nodes::document*>;

    auto exit_fullscreen(
            dom::nodes::document* document)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FULLSCREEN_DETAIL_FULLSCREEN_INTERNALS_HPP
