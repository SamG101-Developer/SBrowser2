#ifndef SBROWSER2_MUTATION_INTERNALS_HPP
#define SBROWSER2_MUTATION_INTERNALS_HPP

#include <memory>





#include INCLUDE_INNER_TYPES(dom)
namespace dom::nodes {class node;}
namespace dom::mutations {class mutation_observer;}


namespace dom::detail
{

}


struct dom::detail::registered_observer_t
{
    mutations::mutation_observer* observer = nullptr;
    ext::map<ext::string, ext::any> options;

    virtual ~registered_observer_t() = default;
};


struct dom::detail::transient_registered_observer_t : public registered_observer_t
{
    registered_observer_t* source = nullptr;
};


#endif //SBROWSER2_MUTATION_INTERNALS_HPP
