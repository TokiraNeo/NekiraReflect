/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../TypeExtraction/TypeExtraction.hpp"


 // ================================================== 动态类型信息存储 ================================================== //

namespace NekiraReflect
{

    // DynamicTypeInfo 类用于表示动态类型信息的基类
    class DynamicTypeInfo
    {
    public:
        virtual ~DynamicTypeInfo() = default;

        DynamicTypeInfo( const std::string& name )
            : Name( name )
        {
        }

        const std::string GetName() const
        {
            return Name;
        }

    private:
        std::string Name;
    };

} // namespace NekiraReflect

namespace NekiraReflect
{

    // NumericTypeInfo 类用于表示数值类型信息
    class NumericTypeInfo : public DynamicTypeInfo
    {
    public:
        // 数值类别枚举
        enum class NumericCategory
        {
            Unknown,
            Int8,
            Int16,
            Int32,
            Int64,
            Float,
            Double
        };

        // 拷贝构造函数
        NumericTypeInfo( const NumericTypeInfo& other )
            : DynamicTypeInfo( GetCategoryName( other.Category ) ), Category( other.Category ), IsSigned( other.IsSigned )
        {
        }

        // 构造函数，接受数值类别和是否有符号的标志
        NumericTypeInfo( NumericCategory category, bool isSigned )
            : DynamicTypeInfo( GetCategoryName( category ) ), Category( category ), IsSigned( isSigned )
        {
        }

        // 创建 NumericTypeInfo 实例的静态方法

        // 获取类型类别
        const NumericCategory GetTypeCategory() const
        {
            return Category;
        }

        // 类型是否有符号
        const bool IsSignedType() const
        {
            return IsSigned;
        }

    private:
        NumericCategory Category;
        bool IsSigned;

        // 根据数值类别返回对应的名称
        static std::string GetCategoryName( NumericCategory category )
        {
            switch ( category )
            {
            case NumericCategory::Int8:
                return "int8";
            case NumericCategory::Int16:
                return "int16";
            case NumericCategory::Int32:
                return "int32";
            case NumericCategory::Int64:
                return "int64";
            case NumericCategory::Float:
                return "float";
            case NumericCategory::Double:
                return "double";
            default:
                return "Unknown";
            }
        }

        // 根据类型 T 返回对应的数值类别
        template <typename T>
        static NumericCategory type_category_v()
        {
            if constexpr ( std::is_same_v<T, char> )
            {
                return NumericCategory::Int8;
            }
            else if constexpr ( std::is_same_v<T, short> )
            {
                return NumericCategory::Int16;
            }
            else if constexpr ( std::is_same_v<T, int> )
            {
                return NumericCategory::Int32;
            }
            else if constexpr ( std::is_same_v<T, long long> )
            {
                return NumericCategory::Int64;
            }
            else if constexpr ( std::is_same_v<T, float> )
            {
                return NumericCategory::Float;
            }
            else if constexpr ( std::is_same_v<T, double> )
            {
                return NumericCategory::Double;
            }
            else
            {
                return NumericCategory::Unknown;
            }
        }
    };

} // namespace NekiraReflect

namespace NekiraReflect
{

    // EnumTypeInfo 类用于表示枚举类型信息
    class EnumTypeInfo : public DynamicTypeInfo
    {
    public:
        // 枚举对结构体，用于存储枚举成员名称和值
        struct EnumPair
        {
            std::string Name;
            size_t Value;
        };

        // 构造函数，接受枚举类型的名称
        EnumTypeInfo( const std::string& EnumTypeName )
            : DynamicTypeInfo( EnumTypeName )
        {
        }

        // 静态方法创建 EnumTypeInfo 实例
        static std::shared_ptr<EnumTypeInfo> Create( const std::string& EnumTypeName )
        {
            return std::make_shared<EnumTypeInfo>( EnumTypeName );
        }

        // 添加枚举对
        void AddEnumPair( const std::string& name, size_t value )
        {
            Enums.push_back( std::move( EnumPair{ name, value } ) );
        }

        // 获取枚举对的数量
        const size_t GetEnumCount() const
        {
            return Enums.size();
        }

        // 通过枚举成员名称获取枚举值
        const size_t GetEnumValueByName( const std::string& name ) const
        {
            size_t Result = -1;

            for ( const auto& pair : Enums )
            {
                if ( pair.Name == name )
                {
                    Result = pair.Value;
                    break;
                }
            }

            return Result;
        }

        // 通过值获取枚举成员名称
        const std::string GetEnumNameByValue( size_t value ) const
        {
            std::string Result = "Unknown";

            for ( const auto& pair : Enums )
            {
                if ( pair.Value == value )
                {
                    Result = pair.Name;
                    break;
                }
            }

            return Result;
        }

        // 获取所有枚举对
        const std::vector<EnumPair>& GetEnums() const
        {
            return Enums;
        }

    private:
        // 存储枚举对的向量
        std::vector<EnumPair> Enums;
    };

} // namespace NekiraReflect

namespace NekiraReflect
{
    // ClassTypeInfo 类用于表示类的类型信息

    // ================================================== 成员信息 ================================================== //
    // 成员信息接口
    struct IMemberInfo
    {
        virtual ~IMemberInfo() = default;
        // 获取成员名称
        virtual const char* GetName() const = 0;
    };

    // 成员变量信息
    template <typename T>
    struct MemberVarialbleInfo : IMemberInfo, field_traits<T>
    {
        constexpr MemberVarialbleInfo( T pointer, const char* name )
            : field_traits<T>( pointer, name )
        {
        }

        const char* GetName() const override
        {
            return field_traits<T>::FieldName;
        }
    };

    // 成员函数信息
    template <typename T>
    struct MemberFunctionInfo : IMemberInfo, field_traits<T>
    {
        constexpr MemberFunctionInfo( T pointer, const char* name )
            : field_traits<T>( pointer, name )
        {
        }

        const char* GetName() const override
        {
            return field_traits<T>::FieldName;
        }
    };

    // 判断成员变量指针
    template <typename T>
    using IsMemberVariablePtr = std::enable_if_t< std::is_member_pointer_v<T> && !std::is_member_function_pointer_v<T> >;

    // 判断成员函数指针
    template <typename T>
    using IsMemberFunctionPtr = std::enable_if_t< std::is_member_function_pointer_v<T> >;

    // 创建成员变量信息的辅助函数
    template < typename T, typename = IsMemberVariablePtr<T> >
    static std::shared_ptr<IMemberInfo> MakeMemberVariableInfo( T MemberVarPtr, const char* Name )
    {
        auto MemberVarInfo = std::make_shared< MemberVarialbleInfo<T> >( MemberVarPtr, Name );

        return std::static_pointer_cast< IMemberInfo >( MemberVarInfo );
    }

    // 创建成员函数信息的辅助函数
    template < typename T, typename = IsMemberFunctionPtr<T> >
    static std::shared_ptr<IMemberInfo> MakeMemberFunctionInfo( T MemberFuncPtr, const char* Name )
    {
        auto MemberFuncInfo = std::make_shared< MemberFunctionInfo<T> >( MemberFuncPtr, Name );

        return std::static_pointer_cast< IMemberInfo >( MemberFuncInfo );
    }

    // ================================================== 类类型信息 ================================================== //
    class ClassTypeInfo : public DynamicTypeInfo
    {
    public:
        // 构造函数，接受类的名称
        ClassTypeInfo( const std::string& ClassName )
            : DynamicTypeInfo( ClassName )
        {
        }

        // 创建 ClassTypeInfo 实例的静态方法
        static std::shared_ptr<ClassTypeInfo> Create( const std::string& ClassName )
        {
            return std::make_shared<ClassTypeInfo>( ClassName );
        }

        // 添加成员变量(通过IMemberInfo接口)
        void AddMemberVariable( std::shared_ptr<IMemberInfo> MemberVarInfo )
        {
            if ( MemberVarInfo )
            {
                Variables.push_back( std::move( MemberVarInfo ) );
            }
        }

        // 添加成员变量(通过成员变量指针和名称)
        template < typename T, typename = IsMemberVariablePtr<T> >
        void AddMemberVariable( T MemberVarPtr, const char* Name )
        {
            auto MemberVarInfo = MakeMemberVariableInfo( MemberVarPtr, Name );

            Variables.push_back( std::move( MemberVarInfo ) );
        }

        // 添加成员函数(通过IMemberInfo接口)
        void AddMemberFunction( std::shared_ptr<IMemberInfo> MemberFuncInfo )
        {
            if ( MemberFuncInfo )
            {
                Functions.push_back( std::move( MemberFuncInfo ) );
            }
        }

        // 添加成员函数(通过成员函数指针和名称)
        template < typename T, typename = IsMemberFunctionPtr<T> >
        void AddMemberFunction( T MemberFuncPtr, const char* Name )
        {
            auto MemberFuncInfo = MakeMemberFunctionInfo( MemberFuncPtr, Name );

            Functions.push_back( std::move( MemberFuncInfo ) );
        }

        // 获取成员变量指针
        template < typename T, typename = IsMemberVariablePtr<T> >
        T GetMemberVariable( const std::string& Name ) const
        {
            if ( Name.empty() )
            {
                return nullptr;
            }

            for ( const auto& VarInfo : Variables )
            {
                if ( VarInfo->GetName() != Name ) { continue; }

                // 尝试转换为特定的MemberVarialbleInfo类型
                auto MemberVarInfo = std::dynamic_pointer_cast< MemberVarialbleInfo<T> >( VarInfo );

                return MemberVarInfo ? MemberVarInfo->FieldPointer : nullptr;
            }

            return nullptr;
        }

        // 获取成员函数指针
        template < typename T, typename = IsMemberFunctionPtr<T> >
        T GetMemberFunction( const std::string& Name ) const
        {
            if ( Name.empty() )
            {
                return nullptr;
            }

            for ( const auto& FuncInfo : Functions )
            {
                if ( FuncInfo->GetName() != Name ) { continue; }

                // 尝试转换为特定的MemberFunctionInfo类型
                auto MemberFuncInfo = std::dynamic_pointer_cast< MemberFunctionInfo<T> >( FuncInfo );

                return MemberFuncInfo ? MemberFuncInfo->FieldPointer : nullptr;
            }

            return nullptr;
        }

    private:
        // 存储类的成员变量
        std::vector< std::shared_ptr<IMemberInfo> > Variables;
        // 存储类的成员函数
        std::vector< std::shared_ptr<IMemberInfo> > Functions;
    };

} // namespace NekiraReflect

// ====================================================== 辅助方法 ====================================================== //
namespace NekiraReflect
{
    // 辅助函数：用于转换DynamicTypeInfo为具体的子类
    // Helper function to cast DynamicTypeInfo to specific derived type.

    template <typename T>
    T* CastDynamicTypeInfo( DynamicTypeInfo* TypeInfo )
    {
        return dynamic_cast< T* >( TypeInfo );
    }

    template <typename T>
    std::shared_ptr<T> CastDynamicTypeInfo( const std::shared_ptr<DynamicTypeInfo>& TypeInfo )
    {
        return std::dynamic_pointer_cast< T >( TypeInfo );
    }

} // namespace NekiraReflect