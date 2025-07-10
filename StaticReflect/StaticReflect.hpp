
#pragma once

#include "StaticTypeInfo.hpp"
#include "../TypeExtraction/TypeExtration.hpp"

// [INFO] NekiraReflect::TypeInfo定义在StaticTypeInfo.hpp中
// [INFO] NekiraReflect::field_traits定义在TypeExtraction/TypeExtration.hpp中

#ifndef STATIC_REFLECT_BEGIN
#define STATIC_REFLECT_BEGIN(Type)             \
    template <>                                \
    struct NekiraReflect::StaticTypeInfo<Type> \
    {                                          \
        static constexpr const char *Name = #Type;
#endif

#ifndef STATIC_REFLECT_FUNCTIONS
#define STATIC_REFLECT_FUNCTIONS(...) \
    static constexpr auto Functions = std::make_tuple(__VA_ARGS__);
#endif

#ifndef STATIC_REGISTER_FUNCTION
#define STATIC_REGISTER_FUNCTION(FuncPtr, FuncName) \
    NekiraReflect::field_traits { FuncPtr, #FuncName }
#endif

#ifndef STATIC_REFLECT_VARIABLES
#define STATIC_REFLECT_VARIABLES(...) \
    static constexpr auto Variables = std::make_tuple(__VA_ARGS__);
#endif

#ifndef STATIC_REGISTER_VARIABLE
#define STATIC_REGISTER_VARIABLE(VarPtr, VarName) \
    NekiraReflect::field_traits { VarPtr, #VarName }
#endif

#ifndef STATIC_REFLECT_END
#define STATIC_REFLECT_END() \
    }                        \
    ;
#endif
