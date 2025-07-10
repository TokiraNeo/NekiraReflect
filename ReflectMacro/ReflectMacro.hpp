#pragma once

#include "../InfoCollection/InfoCollection.hpp"
#include "../TypeExtraction/TypeExtration.hpp"

// [INFO] NekiraReflect::TypeInfo定义在InfoCollection/InfoCollection.hpp中
// [INFO] NekiraReflect::field_traits定义在TypeExtraction/TypeExtration.hpp中

#ifndef REFLECT_BEGIN
#define REFLECT_BEGIN(Type)              \
    template <>                          \
    struct NekiraReflect::TypeInfo<Type> \
    {                                    \
        static constexpr const char *Name = #Type;
#endif

#ifndef REFLECT_FUNCTIONS
#define REFLECT_FUNCTIONS(...) \
    static constexpr auto Functions = std::make_tuple(__VA_ARGS__);
#endif

#ifndef REGISTER_FUNCTION
#define REGISTER_FUNCTION(FuncPtr, FuncName) \
    NekiraReflect::field_traits { FuncPtr, #FuncName }
#endif

#ifndef REFLECT_VARIABLES
#define REFLECT_VARIABLES(...) \
    static constexpr auto Variables = std::make_tuple(__VA_ARGS__);
#endif

#ifndef REGISTER_VARIABLE
#define REGISTER_VARIABLE(VarPtr, VarName) \
    NekiraReflect::field_traits { VarPtr, #VarName }
#endif

#ifndef REFLECT_END
#define REFLECT_END() \
    }                 \
    ;
#endif
