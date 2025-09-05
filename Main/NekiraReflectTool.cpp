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

#include <NekiraReflect/Generation/Generator/ReflectGenerator.hpp>
#include <NekiraReflect/Generation/Tools/ReflectGenSettings.hpp>
#include <cstring>
#include <filesystem>
#include <iostream>


static void PrintHelp()
{
    std::cout << "\033[32mUsage: " << "NekiraReflectTool " << "<input_header> <output_dir> [options]" << "\033[0m\n";
    std::cout << "Options:\n"
              << "  \033[35m-I<path>\033[0m       Add include path (e.g., -I/usr/include)\n"
              << "  \033[35m-D<macro>\033[0m      Define a preprocessor macro (e.g., -DDEBUG)\n"
              << "  \033[35m-std=<version>\033[0m Specify the C++ standard version (e.g., -std=c++20)\n";

    std::cout << "Single Arg:\n";
    std::cout << "  \033[36m-help\033[0m Usage information." << "\n";
    // std::cout << "  \033[36m-zako\033[0m Secret♥ " << "\n";
}

static void PrintSecretInfo()
{
    std::cout << "\033[31mZako♥ Zako~Zako♥ Zako~\033[0m\n";
    std::cout << "\033[35m杂鱼♥ 杂鱼~杂鱼♥ 杂鱼~\033[0m\n";

    std::cout << "\033[36m杂鱼大哥哥不知道怎么用吧(ᗒᗣᗕ)՞~~♥ ♥ \033[0m\n";

    std::cout << "\033[32m(✧≖‿ゝ≖)\033[0m\n";
    std::cout << "\033[32m(✧≖‿ゝ≖)\033[0m\n";
    std::cout << "\033[32m(✧≖‿ゝ≖)\033[0m\n";

    std::cout << "\033[34m如果实在想用的话, 试试\"NekiraReflectTool -help\"吧♥ ~\033[0m\n";
    std::cout << "\033[35m如果还是不会用的话, 去看一下TokiraNeo的GitHub仓库吧♥ ~\033[0m\n";
    std::cout << "\033[33mhttps://github.com/TokiraNeo/NekiraReflect\033[0m\n";
    std::cout << "\033[31m_(:△」∠)_\033[0m\n";
}

int main(int argc, char* argv[])
{

    if (argc < 2)
    {
        std::cout << "Print \"NekiraReflectTool -help\" usage information.\n";
        return 0;
    }

    if (std::strcmp(argv[1], "-zako") == 0)
    {
        PrintSecretInfo();
        return 0;
    }

    // 检查是否需要打印帮助信息
    if (std::strcmp(argv[1], "-help") == 0)
    {
        PrintHelp();
        return 0;
    }

    NekiraReflect::ReflectGenSettings Settings;

    // 获取输入文件路径
    std::filesystem::path InputHeader(argv[1]);
    // 检查输入文件是否存在
    if (!std::filesystem::exists(InputHeader))
    {
        std::cerr << "Error: Input header file does not exist: " << InputHeader << '\n';
        return 1;
    }

    // 默认输出目录
    std::filesystem::path OutputDir = "Generated";
    // 检查是否提供了输出目录
    if (argc > 2 && argv[2][0] != '-')
    {
        OutputDir = argv[2];
    }


    // 检查输出目录是否存在，如果不存在则创建
    if (!std::filesystem::exists(OutputDir))
    {
        std::filesystem::create_directories(OutputDir);
    }

    // 确保添加__NEKIRA_REFLECT_TOOL__预定义宏
    Settings.CommandLineArgs.push_back("-D__NEKIRA_REFLECT_TOOL__");

    // 解析其他参数
    if (argc > 3)
    {
        for (int i = 3; i < argc; ++i)
        {
            Settings.CommandLineArgs.push_back(argv[i]);
        }
    }


    // 生成反射代码
    NekiraReflect::ReflectGenerator::GenerateReflectCode(InputHeader, OutputDir, Settings);

    return 0;
}
