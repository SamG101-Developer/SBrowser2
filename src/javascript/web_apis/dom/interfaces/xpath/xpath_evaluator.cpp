


auto dom::xpath::xpath_evaluator::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<xpath_evaluator>{isolate}
            .ctor<>()
            .inherit<dom_object>()
            .auto_wrap_objects();
}
