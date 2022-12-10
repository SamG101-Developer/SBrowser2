module;
#include "ext/macros/language_shorthand.hpp"
#include "javascript/macros/errors.hpp"

module apis.dom.abstract_iterator_private;

import apis.dom.node;
import apis.dom.node_private;
import apis.dom.node_filter;
import apis.dom.node_filter_private;

import apis.dom.detail;
import apis.dom.types;
import ext.number;


auto dom::abstract_iterator_private::filter(const node* node) -> ext::number<ushort>
{
    using enum detail::dom_exception_error_t;

    throw_v8_exception<INVALID_STATE_ERR>(
            [this] {return active_flag;},
            u8"NodeIterator/TreeWalker must be inactive to start filtering");

    // get the 'node_type' of the 'node', and if the 'what_to_shot' doesn't have this bit set, then return FILTER_SKIP;
    // if there is no filter, then return FILTER_ACCEPT as everything is automatically accepted. for example, if the
    // 'what_to_show' is '000000000010', only Element nodes ('node_type' == 1) would be accepted
    const auto n = node->d_func()->node_type - 1;
    return_if(~(what_to_show & (2 << n))) node_filter::FILTER_SKIP;
    return_if(!node_filter) node_filter::FILTER_ACCEPT;

    // begin the filtering with the use function set in the NodeIterator/TreeWalker's filter's 'accept_node' attribute,
    // so set the active flag to true, so that multiple filtering calls don't happen (exception guard at top of method
    // checks this)
    active_flag = true;

    // begin JavaScript error handling in-case the 'accept_node' method throws an error; call the 'accept_node' method
    // with the 'node' as the parameter, and save the result; the result is whether to FILTER_SKIP / FILTER_REJECT /
    // FILTER_ACCEPT the node
    JS_EXCEPTION_HANDLER;
    auto result = node_filter->d_func()->accept_node_callback(node);

    // if the method threw an exception, then set the active flag to false (processing has finished), and then rethrow
    // the error; this means that the state of the NodeIterator/TreeWalker has been adjusted for post-filtering, and the
    // error can be managed correctly
    active_flag = false;
    JS_EXCEPTION_RETHROW_IF_HAS_THROWN;

    // otherwise, return the result of the filtering process (FILTER_SKIP / FILTER_REJECT / FILTER_ACCEPT
    return result;
}