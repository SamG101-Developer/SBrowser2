#include <iostream>
#include <javascript/environment/environment_initialization.hpp>


int main(int argc, char** argv)
{
    js::env::initialize_v8_engine(argv);
    auto* isolate = js::env::create_new_isolate();
    auto& context = js::env::create_new_context(isolate, js::env::module_t::WINDOW);

    js::env::execute(isolate, context, "let e = new Window.Event({bubbles: true});"
                                                       "e.bubbles");

    js::env::dispose_isolate(isolate);
    js::env::dispose_v8_engine();

    return 0;
}
