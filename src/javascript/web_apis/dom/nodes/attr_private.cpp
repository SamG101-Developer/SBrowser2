module apis.dom.attr_private;

import ext.string;


auto dom::attr_private::qualified_name() const -> ext::string
{
    // The qualified name of an attribute is the 'attribute's prefix followed by a ":", followed by the 'attribute's
    // local name.
    return namespace_prefix + u":" + local_name;
}
