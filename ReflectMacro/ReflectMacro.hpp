#pragma once

#include "../InfoCollection/InfoCollection.hpp"
#include "../TypeExtraction/TypeExtration.hpp"

#ifndef REFLECT_BEGIN
#define REFLECT_BEGIN(Type) \
    template <>             \
    struct TypeInfo<Type>   \
    {                       \
        static constexpr const char *Name = #Type;
#endif

#ifndef REFLECT_FUNCTIONS
#define REFLECT_FUNCTIONS(...) \
    static constexpr auto Functions = std::make_tuple(__VA_ARGS__);
#endif

#ifndef REGISTER_FUNCTION
#define REGISTER_FUNCTION(FuncPtr, FuncName) \
    field_traits { FuncPtr, #FuncName }
#endif

#ifndef REFLECT_VARIABLES
#define REFLECT_VARIABLES(...) \
    static constexpr auto Variables = std::make_tuple(__VA_ARGS__);
#endif

#ifndef REGISTER_VARIABLE
#define REGISTER_VARIABLE(VarPtr, VarName) \
    field_traits { VarPtr, #VarName }
#endif

#ifndef REFLECT_END
#define REFLECT_END() \
    }                 \
    ;
#endif
