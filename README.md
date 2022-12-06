# SBrowser

SBrowser is a brand-new browser engine built from the ground up, containing no code from the Chromium or Firefox
project. It contains its own DOM/CSS/HTML implementations, and every web spec is implemented in raw C++. The web api
implementations, network stack, render stack, storage access and GUI are all newly designed. The only major 3rd party
components used are the Qt6 GUI Framework, and Google's V8 JavaScript engine. Other 3rd party components used are
smaller projects individually developed and available on GitHub, of which are mostly drop-in STL component replacements,
offering better performance. A list of these can be identified in the CMakeLists.txt file.

The SBrowser engine aims to be very memory-efficient, whilst still offering ultra-high speeds for webpage access and
rendering.


## Note
Currently undergoing Major Refactor 4.0

- Public .hpp/.cpp
    - Remove intermediate namespaces (dom::nodes::node -> dom::node)
    - Use MAKE_PUBLIC_CLASS macro for .ixx public class
    - Any special types used in classes and only in that class - move definition into that class (map types etc)
        - Detail files working on maps will become PIMPL private class methods
    - Split variant parameters into separate method overloads
        - Define the variant type in the class ie to mark its existenace and usage in the class
        - Define a potential non-exposed / private method to deduplicate code in overloads
    - ext::string_view's / ext::vector_span's that type-erase typedefs
        - Use new view_of_t<T> and span_of_t<T> to show their specific type

- Detail .hpp/.cpp
    - Convert all #include -> imports (remove transitives)
    - Move methods into PIMPL .cpp file of the class they mainly revolve around (ie trees -> dom::event_target_private)

- All
    - Convert all .hpp -> .ixx modules (c++ modernization)
    - Convert all #include -> imports (remove transitives)
    - Convert all inherited classes into FQN (consistent for other-spec inheritance)
    - Use "ext/pimpl2.hpp" new PIMPL/QIMPL macros
    - Format and grammar check in comments in .cpp file
    - Make all ext::any, ext::variant, ext::optional, ext::expected parameters to r-value-references&& and use std::move
    - Const correctness
    - Auto correctness

