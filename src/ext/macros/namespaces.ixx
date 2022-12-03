module;

#define _EXT ::ext::
#define _EXT_BEGIN namespace ext {
#define _EXT_END } // namespace ext

#define _EXT_DETAIL_BEGIN namespace ext::detail {
#define _EXT_DETAIL_END } // namespace ext::detail

#define _EXT_SHORTHAND_BEGIN namespace ext::shorthand {
#define _EXT_SHORTHAND_END } // namespace ext::shorthand

#define _EXT_LITERALS_BEGIN namespace ext::literals {
#define _EXT_LITERALS_END } // namespace ext::literals

#define _EXT_SECURE_BEGIN namespace ext::secure {
#define _EXT_SECURE_END } // namespace ext::secure

#define RFC_DEFINITION_BEGIN namespace rfc {
#define RFC_DEFINITION_END }

export module ext.macros.namespaces;
