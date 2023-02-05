

auto dom::xpath::xpath_result::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<xpath_result>{isolate}
            .inherit<dom_object>()
            .static_("ANY_TYPE", xpath_result::ANY_TYPE)
            .static_("NUMBER_TYPE", xpath_result::NUMBER_TYPE)
            .static_("STRING_TYPE", xpath_result::STRING_TYPE)
            .static_("BOOLEAN_TYPE", xpath_result::BOOLEAN_TYPE)
            .static_("UNORDERED_NODE_ITERATOR_TYPE", xpath_result::UNORDERED_NODE_ITERATOR_TYPE)
            .static_("ORDERED_NODE_ITERATOR_TYPE", xpath_result::ORDERED_NODE_ITERATOR_TYPE)
            .static_("UNORDERED_NODE_SNAPSHOT_TYPE", xpath_result::UNORDERED_NODE_SNAPSHOT_TYPE)
            .static_("ORDERED_NODE_SNAPSHOT_TYPE", xpath_result::ORDERED_NODE_SNAPSHOT_TYPE)
            .static_("ANY_UNORDERED_NODE_TYPE", xpath_result::ANY_UNORDERED_NODE_TYPE)
            .static_("FIRST_ORDERED_NODE_TYPE", xpath_result::FIRST_ORDERED_NODE_TYPE)
            .function("iteratorNext", &xpath_result::iterate_next)
            .function("snapshotITem", &xpath_result::snapshot_item)
            .var("numberValue", &xpath_result::number_value, true)
            .var("stringValue", &xpath_result::string_value, true)
            .var("booleanValue", &xpath_result::boolean_value, true)
            .var("singleNodeValue", &xpath_result::single_node_value, true)
            .var("invalidIteratorState", &xpath_result::invalid_iterator_state, true)
            .var("snapshotLength", &xpath_result::snapshot_length, true)
            .var("resultType", &xpath_result::result_type, true)
            .auto_wrap_objects();
}
