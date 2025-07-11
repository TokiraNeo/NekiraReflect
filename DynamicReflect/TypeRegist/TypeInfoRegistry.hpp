#pragma once

#include "../TypeCollection/DynamicTypeInfo.hpp"
#include <unordered_map>

namespace NekiraReflect
{

    // 用于管理运行时类型信息的全局注册表
    class TypeInfoRegistry final
    {
    public:
        // 获取注册表的单例实例
        static TypeInfoRegistry &Get()
        {
            static TypeInfoRegistry instance;
            return instance;
        }

        // 获取指定名称的类型信息
        std::shared_ptr<DynamicTypeInfo> GetTypeInfo(const std::string &TypeName) const
        {
            std::shared_ptr<DynamicTypeInfo> Result = nullptr;

            auto it = TypeInfoMap.find(TypeName);
            if (it != TypeInfoMap.end())
            {
                Result = it->second;
            }

            return Result;
        }

        // 注册类型信息
        void RegistTypeInfo(const std::string &TypeName, std::shared_ptr<DynamicTypeInfo> TypeInfo)
        {
            TypeInfoMap[TypeName] = std::move(TypeInfo);
        }

    private:
        TypeInfoRegistry() = default;

        TypeInfoRegistry(const TypeInfoRegistry &) = delete;
        TypeInfoRegistry &operator=(const TypeInfoRegistry &) = delete;

        TypeInfoRegistry(TypeInfoRegistry &&) = delete;
        TypeInfoRegistry &operator=(TypeInfoRegistry &&) = delete;

    private:
        // 存储类型信息的映射
        std::unordered_map<std::string, std::shared_ptr<DynamicTypeInfo>> TypeInfoMap;
    };

} // namespace NekiraReflect

namespace NekiraReflect
{

    // 注册枚举类型的信息
    using EnumVector = std::vector<std::pair<std::string, size_t>>;
    static std::shared_ptr<EnumTypeInfo> RegistEnumTypeInfo(const std::string &EnumName, const EnumVector &EnumPairs)
    {
        auto &Registry = TypeInfoRegistry::Get();

        // 检查是否已经注册了该枚举类型
        if (auto Info = Registry.GetTypeInfo(EnumName); Info != nullptr)
        {
            return CastDynamicTypeInfo<EnumTypeInfo>(Info);
        }

        // 若未注册，则创建新的 EnumTypeInfo 实例
        auto NewEnumTypeInfo = EnumTypeInfo::Create(EnumName);
        if (NewEnumTypeInfo)
        {
            for (auto &Pair : EnumPairs)
            {
                NewEnumTypeInfo->AddEnumPair(std::move(Pair.first), Pair.second);
            }

            // 注册新的枚举类型信息
            Registry.RegistTypeInfo(EnumName, std::static_pointer_cast<DynamicTypeInfo>(NewEnumTypeInfo));
        }

        return NewEnumTypeInfo;
    }

}