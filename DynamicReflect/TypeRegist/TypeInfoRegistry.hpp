#pragma once

#include "../TypeCollection/DynamicTypeInfo.hpp"
#include <unordered_map>

namespace NekiraReflect
{
    // 用于管理运行时类型信息的全局注册表.
    // Global Singleton Registry for Runtime Type Information Management.

    class TypeInfoRegistry final
    {
    public:
        // 获取注册表的单例实例
        // Get the singleton instance of the registry.
        static TypeInfoRegistry& Get()
        {
            static TypeInfoRegistry instance;
            return instance;
        }

        // 获取指定名称的类型信息
        // Get type information by type name.
        std::shared_ptr<DynamicTypeInfo> GetTypeInfo( const std::string& TypeName ) const
        {
            std::shared_ptr<DynamicTypeInfo> Result = nullptr;

            auto it = TypeInfoMap.find( TypeName );
            if ( it != TypeInfoMap.end() )
            {
                Result = it->second;
            }

            return Result;
        }

        // 注册类型信息
        // Register type information with a given type name.
        void RegistTypeInfo( const std::string& TypeName, std::shared_ptr<DynamicTypeInfo> TypeInfo )
        {
            TypeInfoMap[ TypeName ] = std::move( TypeInfo );
        }

        // 删除指定名称的类型信息
        // Remove type information by type name.
        void RemoveTypeInfo( const std::string& TypeName )
        {
            TypeInfoMap.erase( TypeName );
        }

    private:
        TypeInfoRegistry() = default;

        TypeInfoRegistry( const TypeInfoRegistry& ) = delete;
        TypeInfoRegistry& operator=( const TypeInfoRegistry& ) = delete;

        TypeInfoRegistry( TypeInfoRegistry&& ) = delete;
        TypeInfoRegistry& operator=( TypeInfoRegistry&& ) = delete;

    private:
        // 存储类型信息的映射
        // Map to store type information.
        std::unordered_map<std::string, std::shared_ptr<DynamicTypeInfo>> TypeInfoMap;
    };

} // namespace NekiraReflect

namespace NekiraReflect
{
    // 注册枚举类型信息的辅助函数.
    // Helper function to register Dynamic Enum Type Info.

    using EnumVector = std::vector<std::pair<std::string, size_t>>;

    static std::shared_ptr<EnumTypeInfo> RegistEnumTypeInfo( const std::string& EnumName, const EnumVector& EnumPairs )
    {
        auto& Registry = TypeInfoRegistry::Get();

        // 检查是否已经注册了该枚举类型
        // Check if the enum type is already registered.
        if ( auto Info = Registry.GetTypeInfo( EnumName ); Info != nullptr )
        {
            return CastDynamicTypeInfo<EnumTypeInfo>( Info );
        }

        // 若未注册，则创建新的 EnumTypeInfo 实例
        // If not registered, create a new EnumTypeInfo instance.
        auto NewEnumTypeInfo = EnumTypeInfo::Create( EnumName );

        if ( NewEnumTypeInfo )
        {
            for ( auto& Pair : EnumPairs )
            {
                NewEnumTypeInfo->AddEnumPair( std::move( Pair.first ), Pair.second );
            }

            // 注册新的枚举类型信息
            // Register the new enum type information.
            Registry.RegistTypeInfo( EnumName, std::static_pointer_cast< DynamicTypeInfo >( NewEnumTypeInfo ) );
        }

        return NewEnumTypeInfo;
    }

} // namespace NekiraReflect

namespace NekiraReflect
{
    // 注册类类型信息的辅助函数.
    // Helper function to register Dynamic Class Type Info.

    // [INFO] 使用NekiraReflect::MakeMemberVariableInfo()来创建IMemberInfo实例
    // [INFO] Use NekiraReflect::MakeMemberVariableInfo() to create IMemberInfo instances.
    using MemberVarInfoVector = std::vector< std::shared_ptr<IMemberInfo> >;

    // [INFO] 使用NekiraReflect::MakeMemberFunctionInfo()来创建IMemberInfo实例
    // [INFO] Use NekiraReflect::MakeMemberFunctionInfo() to create IMemberInfo instances.
    using MemberFuncInfoVector = std::vector< std::shared_ptr<IMemberInfo> >;

    static std::shared_ptr<ClassTypeInfo> RegistClassTypeInfo( const std::string& ClassName, const MemberVarInfoVector& MemberVars,
        const MemberFuncInfoVector& MemberFuncs )
    {
        auto& Registry = TypeInfoRegistry::Get();

        // 检查是否已经注册了该类类型
        // Check if the class type is already registered.
        if ( auto Info = Registry.GetTypeInfo( ClassName ); Info != nullptr )
        {
            return CastDynamicTypeInfo<ClassTypeInfo>( Info );
        }

        // 若未注册，则创建新的 ClassTypeInfo 实例
        // If not registered, create a new ClassTypeInfo instance.
        auto NewClassTypeInfo = ClassTypeInfo::Create( ClassName );

        if ( NewClassTypeInfo )
        {
            for ( const auto& Var : MemberVars )
            {
                NewClassTypeInfo->AddMemberVariable( std::move( Var ) );
            }
            for ( const auto& Func : MemberFuncs )
            {
                NewClassTypeInfo->AddMemberFunction( std::move( Func ) );
            }

            // 注册新的类类型信息
            // Register the new class type information.
            Registry.RegistTypeInfo( ClassName, std::static_pointer_cast< DynamicTypeInfo >( NewClassTypeInfo ) );
        }

        return NewClassTypeInfo;
    }
}