#pragma once

#include <NekiraReflect/DynamicReflect/Accessor/ReflectAccessor.hpp>

// =========================== Generate Enum Reflection Code =========================== 
// Enum: SampleEnum
NEKIRA_REFLECT_ENUM_ACCESSOR_BEGIN(SampleEnum)
NEKIRA_REFLECT_ENUM_ACCESSOR_VALUE(Value1)
NEKIRA_REFLECT_ENUM_ACCESSOR_VALUE(Value2)
NEKIRA_REFLECT_ENUM_ACCESSOR_VALUE(Value3)
NEKIRA_REFLECT_ENUM_ACCESSOR_END()

NEKIRA_REFLECT_ENUM_REGISTER_AUTO(SampleEnum)
/////////////////////////////////////////////////////////////
// Enum: SampleZakoEnum
NEKIRA_REFLECT_ENUM_ACCESSOR_BEGIN(SampleZakoEnum)
NEKIRA_REFLECT_ENUM_ACCESSOR_VALUE(Value1)
NEKIRA_REFLECT_ENUM_ACCESSOR_VALUE(Value2)
NEKIRA_REFLECT_ENUM_ACCESSOR_VALUE(Value3)
NEKIRA_REFLECT_ENUM_ACCESSOR_END()

NEKIRA_REFLECT_ENUM_REGISTER_AUTO(SampleZakoEnum)
/////////////////////////////////////////////////////////////
// =========================== Generate Class Reflection Code =========================== 
// Class: SampleClass
NEKIRA_REFLECT_CLASS_ACCESSOR_BEGIN(SampleClass)
NEKIRA_REFLECT_CLASS_ACCESSOR_VAR(Value)
NEKIRA_REFLECT_CLASS_ACCESSOR_FUNC(Func)
NEKIRA_REFLECT_CLASS_ACCESSOR_END()

NEKIRA_REFLECT_CLASS_REGISTER_AUTO(SampleClass)
/////////////////////////////////////////////////////////////
