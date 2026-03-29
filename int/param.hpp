#include <stdio.h>




#define PARAM_DEF_ARG(type, name) type name(#name);
#define PARAM_DEF_STR(type, ...) APPLY_MACRO(PARAM_DEF_ARG, type, __VA_ARGS__)

#define APPLY_MACRO(macro, type, ...) EXPAND(APPLY_MACRO_HELPER(macro, type, __VA_ARGS__))
#define APPLY_MACRO_HELPER(macro, type, arg1, ...) macro(type, arg1) IF_MORE_ARGS(__VA_ARGS__)(APPLY_MACRO_HELPER(macro, type, __VA_ARGS__))

#define IF_MORE_ARGS(...) IF_MORE_ARGS_HELPER(__VA_ARGS__, 1, 0)
#define IF_MORE_ARGS_HELPER(x, y, ...) y
#define EXPAND(x) x

PARAM_DEF_STR(str,nam,moc,lic)

#define _CLASS_ARG(namesp ,name) \
class name{ \
    using ns=namesp ; \
  static const c = "class##name"; \
  };

#define PARAM_CLASS_ARG(namesp , ) APPLY_MACRO(_CLASS_ARG , namesp, __VA_ARGS__)
