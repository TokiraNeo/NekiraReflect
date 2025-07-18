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
#include <typeindex>
#include <unordered_map>
#include <any>
#include <vector>
#include "MemberFuncWrapper.hpp"

 // ======================================= 动态反射核心类型 ======================================= //




 // ======================================= 类型定义 ======================================= //
namespace NekiraReflect
{

    enum class TypeCategory
    {
        Unknown,
        Fundamental,   // int, float, char, bool, etc.
        Enum,
        Class,
        Pointer,
        Array
    };

} // namespace NekiraReflect




// ======================================= 统一的类型信息 ======================================= //
namespace NekiraReflect
{

    class TypeInfo
    {
    public:
        TypeInfo( const std::string& name, std::type_index typeIndex, size_t size )
            : Name( name ), TypeIndex( typeIndex ), Size( size )
        {
        }

        const std::string GetName() const { return Name; }

        const std::type_index GetTypeIndex() const { return TypeIndex; }

        const size_t GetSize() const { return Size; }

        void SetSize( size_t size ) { Size = size; }

    private:
        std::string Name;
        std::type_index TypeIndex;
        size_t Size;
    };

} // namespace NekiraReflect



// ======================================= 枚举类型信息 ======================================= //
namespace NekiraReflect
{

    class EnumTypeInfo : public TypeInfo
    {
    public:
        EnumTypeInfo( const std::string& name, std::type_index typeIndex )
            : TypeInfo( name, typeIndex, 0 )
        {
        }

        // Add an enum value with its name
        // 通过枚举名称和对于的值添加枚举对
        void AddEnumValue( const std::string& name, __int64 value )
        {
            EnumValues[ name ] = value;
            EnumNames[ value ] = name;
        }

        // Add Enum Values
        // 添加多个枚举值
        void AddEnumValues( const std::unordered_map<std::string, __int64>& values )
        {
            for ( const auto& Pair : values )
            {
                AddEnumValue( Pair.first, Pair.second );
            }
        }

        // Get Value by Name, true if found
        // 通过名称获取枚举值, 返回true表示找到
        bool GetEnumValueByName( const std::string& name, __int64& outValue ) const
        {
            bool bFound = false;
            auto it = EnumValues.find( name );

            if ( it != EnumValues.end() )
            {
                outValue = it->second;
                bFound = true;
            }

            return bFound;
        }

        // Get Name by Value, true if found
        // 通过值获取枚举名称, 返回true表示找到
        bool GetEnumNameByValue( const __int64 value, std::string& outName ) const
        {
            bool bFound = false;
            auto it = EnumNames.find( value );

            if ( it != EnumNames.end() )
            {
                outName = it->second;
                bFound = true;
            }

            return bFound;
        }

        // Get all enum values
        // 获取所有枚举值
        const std::unordered_map<std::string, __int64>& GetAllEnumValues() const
        {
            return EnumValues;
        }

        // Get all enum names
        // 获取所有枚举名称
        const std::unordered_map<__int64, std::string>& GetAllEnumNames() const
        {
            return EnumNames;
        }

    private:
        // Enum Values Map
        std::unordered_map<std::string, __int64> EnumValues;

        // Enum Names Map
        std::unordered_map<__int64, std::string> EnumNames;
    };

} // namespace NekiraReflect



// ========================================== 成员变量信息 ========================================== //
namespace NekiraReflect
{

    class MemberVarInfo : public TypeInfo
    {
    public:
        template <typename ClassType, typename VarType>
        MemberVarInfo( const std::string& name, VarType ClassType::* memberPtr )
            : TypeInfo( name, typeid( VarType ), sizeof( VarType ) )
        {
            Offset = ( size_t ) & ( ( ( ClassType* )0 )->memberPtr );
        }

        // Get Member Variable Value.
        // 获取成员变量的值
        template <typename VarType>
        VarType& GetValue( void* Object ) const
        {
            VarType* MemberPtr = ( VarType* )( ( ( char* )Object ) + Offset );

            return *MemberPtr;
        }

        // Set Member Variable Value.
        // 设置成员变量的值
        template <typename VarType>
        void SetValue( void* Object, const VarType& Value ) const
        {
            VarType* MemberPtr = ( VarType* )( ( ( char* )Object ) + Offset );

            *MemberPtr = Value;
        }

    private:
        // Member Variable Offset
        // 成员变量的偏移量
        size_t Offset;
    };

}// namespace NekiraReflect



// ========================================== 成员函数信息 ========================================== //
namespace NekiraReflect
{
    class MemberFuncInfo : public TypeInfo
    {
    public:
        template <typename ClassType, typename RT, typename... Args>
        MemberFuncInfo( const std::string& name, RT( ClassType::* funcPtr )( Args... ) )
            : TypeInfo( name, typeid( funcPtr ), sizeof( funcPtr ) )
        {
            auto WrapperLambda = [ funcPtr ]( void* Object, const std::vector< std::any >& Params ) -> std::any
                {
                    ClassType* ObjectPtr = static_cast< ClassType* >( Object );
                    if constexpr ( std::is_void_v<RT> )
                    {
                        auto VoidLambda = [ funcPtr, ObjectPtr ]( auto&&... args ) -> void
                            {
                                ( ObjectPtr->*funcPtr )( std::forward<Args>( args )... );
                            };

                        std::apply( VoidLambda, std::any_cast< Args >( Params )... );

                        return std::any();
                    }
                    else
                    {
                        auto AnyLambda = [ funcPtr, ObjectPtr ]( auto&&... args ) -> std::any
                            {
                                return ( ObjectPtr->*funcPtr )( std::forward<Args>( args )... );
                            };

                        return std::apply( AnyLambda, std::any_cast< Args >( Params )... );
                    }
                };

            FuncWrapper = WrapperLambda;
        }

        // 调用函数
        template <typename... Args>
        std::any Invoke( void* Object, Args&&... args )
        {
            std::vector<std::any> Params{ std::any( std::forward<Args>( args ) ) ... };
            return FuncWrapper.Invoke( Object, Params );
        }

    private:
        MemberFuncWrapper < std::any( void*, const std::vector< std::any >& ) > FuncWrapper;
    };

} // namespace NekiraReflect




// ========================================== 类、结构体的信息 ========================================== //
namespace NekiraReflect
{

    class ClassTypeInfo : public TypeInfo
    {
        using VariableMap = std::unordered_map< std::string, std::unique_ptr<MemberVarInfo> >;
        using FunctionMap = std::unordered_map< std::string, std::unique_ptr<MemberFuncInfo> >;

    public:
        ClassTypeInfo( const std::string& name, std::type_index typeIndex )
            : TypeInfo( name, typeIndex, 0 )
        {
        }

        // Add a member variable
        void AddVariable( const std::string& name, std::unique_ptr<MemberVarInfo> varInfo )
        {
            Variables[ name ] = std::move( varInfo );
        }

        // Add a member function
        void AddFunction( const std::string& name, std::unique_ptr<MemberFuncInfo> funcInfo )
        {
            Functions[ name ] = std::move( funcInfo );
        }

        // Remove a member variable by name
        void RemoveVariable( const std::string& name )
        {
            Variables.erase( name );
        }

        // Remove a member function by name
        void RemoveFunction( const std::string& name )
        {
            Functions.erase( name );
        }

        // Get a member variable by name
        const MemberVarInfo* GetVariable( const std::string& name ) const
        {
            const MemberVarInfo* Result = nullptr;

            auto it = Variables.find( name );

            if ( it != Variables.end() )
            {
                Result = it->second.get();
            }

            return Result;
        }

        // Get a member function by name
        const MemberFuncInfo* GetFunction( const std::string& name ) const
        {
            const MemberFuncInfo* Result = nullptr;

            auto it = Functions.find( name );

            if ( it != Functions.end() )
            {
                Result = it->second.get();
            }

            return Result;
        }

        // Get all member variables
        const VariableMap& GetAllVariables() const
        {
            return Variables;
        }

        // Get all member functions
        const FunctionMap& GetAllFunctions() const
        {
            return Functions;
        }

    private:
        // Member Variables
        VariableMap Variables;

        // Member Functions
        FunctionMap Functions;
    };

} // namespace NekiraReflect