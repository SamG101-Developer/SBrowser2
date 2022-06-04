#include <iostream>
#include <javascript/environment/environment_initialization.hpp>

//#include <cppfs/FileHandle.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>


int main(int argc, char** argv)
{
    /*
    javascript::environment::initialize_v8_engine(argv);
    auto* isolate = javascript::environment::create_new_isolate();
    auto& context = javascript::environment::create_new_context(isolate, javascript::environment::module_t::WINDOW);

    // auto init_script = cppfs::FileHandle{}.open("src/javascript/initialization_scripts/module_to_global.js").readFile();

    javascript::environment::execute(isolate, context, "let a = new Window.A(5);"
                                                       "let b = new Window.A(1);");

    javascript::environment::execute(isolate, context, "a.a_ptr = b;"
                                                       "b.a_int = 100;"
                                                       "a.a_ptr.doubleA();");
    javascript::environment::dispose_isolate(isolate);
    javascript::environment::dispose_v8_engine();
     */

    QApplication app {argc, argv};
    QPushButton button {"hello world!"};
    button.show();

    return QApplication::exec();
}
