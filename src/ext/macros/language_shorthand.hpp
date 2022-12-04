#ifndef SBROWSER2_SRC_EXT_MACROS_LANGUAGE_SHORTHAND
#define SBROWSER2_SRC_EXT_MACROS_LANGUAGE_SHORTHAND


#define return_if(condition) if (condition) return
#define break_if(condition) if (condition) break
#define continue_if(condition) if (condition) continue
#define for_if(if_statement, for_statement) if (if_statement) for (for_statement)

#define constexpr_return_if(condition) if constexpr (condition) return


#endif //SBROWSER2_SRC_EXT_MACROS_LANGUAGE_SHORTHAND
