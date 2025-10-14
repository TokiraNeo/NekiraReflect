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

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <cstring>

using Json = nlohmann::json;

static void PrintHelp()
{
    std::cout << "\033[32mUsage: " << "NekiraSerializeTool " << "<mode> <input_file> <output_dir> [options]" << "\033[0m\n";

    std::cout << "Detail:\n"
              << "  \033[35mmode\033[0m         Serialize mode (e.g., \033[35m-mSerialize\033[0m, \033[35m-mDeSerialize\033[0m)\n"
              << "  \033[35minput_file\033[0m   Path to the input JSON file(.json, .JSON)\n"
              << "  \033[35moutput_dir\033[0m   Directory to save output JSON files\n";

    std::cout << "Single Arg:\n";
    std::cout << "  \033[36m-help\033[0m Usage information." << "\n";
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Print \"NekiraSerializeTool -help\" usage information.\n";
        return 0;
    }

    // 检查是否需要打印帮助信息
    if (std::strcmp(argv[1], "-help") == 0)
    {
        PrintHelp();
        return 0;
    }

    // 获取输入文件路径
    std::filesystem::path InputJson(argv[1]);
    // 检查文件是否存在
    if( !std::filesystem::exists(InputJson) )
    {
        std::cerr << "Error: Input Json file does not exist: " << InputJson << "\n";
        return 1;
    }
    // 检查文件是否是JSON文件
    if( InputJson.extension() != ".json" || InputJson.extension() != ".JSON" )
    {
        std::cerr << "Error: Input file is not a JSON file: " << InputJson << "\n";
        return 1;
    }

    // 默认输出目录
    std::filesystem::path OutputDir = "Serialization";

    // 检查输出目录是否存在，如果不存在则创建
    if (!std::filesystem::exists(OutputDir))
    {
        std::filesystem::create_directories(OutputDir);
    }

    // 读取 JSON 文件
    std::ifstream inputFile(InputJson);
    Json data = Json::parse(inputFile);

    // 输出 JSON 内容到控制台 @TODO: remove this line
    std::cout << "Read JSON data:\n" << data.dump() << '\n';

    // @TODO: 进行序列化或反序列化操作

    return 0;
}