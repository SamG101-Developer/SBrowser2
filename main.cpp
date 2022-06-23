#include <iostream>
#include <javascript/environment/environment_initialization.hpp>


int main(int argc, char** argv)
{
    javascript::environment::initialize_v8_engine(argv);
    auto* isolate = javascript::environment::create_new_isolate();
    auto& context = javascript::environment::create_new_context(isolate, javascript::environment::module_t::WINDOW);

    javascript::environment::execute(isolate, context, "let e = new Window.Event({bubbles: true});"
                                                       "e.bubbles");

    javascript::environment::dispose_isolate(isolate);
    javascript::environment::dispose_v8_engine();

    return 0;
}
