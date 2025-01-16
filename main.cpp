#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using std::cout;
std::ifstream infile("memo.sb"); // 采用标准输入流方式打开“memo.sb”文件
std::ofstream outfile("memo.sb", std::ios::app); // 创建一个输出流对象outfile
std::string line;

std::string vectorToString(const std::vector<std::string>& vec) {
    std::string result;
    for (const auto& str : vec) {
        result += str + " "; // 你可以根据需要调整分隔符
    }
    return result;
}

void writeAmemo() {
    std::string title = "TITLE";
    std::string messages = "MESSAGES";
    cout << "TITLE:\n";
    std::getline(std::cin, title); // 使用 getline 读取整行标题

    cout << "MESSAGES:\n";
    std::getline(std::cin, messages); // 使用 getline 读取整行消息

    // 写入分隔符
    outfile << "\n---\n";

    outfile << "TITLE: " << title << "\nMESSAGES: " << messages << "\n";
}

void findmemo(std::string memoTitle) {
    infile.seekg(0); // 确保文件指针在文件开头
    bool found = false; // 标记是否找到目标标题

    while (std::getline(infile, line)) {
        //cout << "Reading line: " << line << "\n"; // 调试输出

        if (line == "---") {
            //cout << "Skipping separator\n"; // 调试输出
            continue; // 跳过分隔符
        }
        if (line.find("TITLE: ") == 0) {// 检查是否是标题行
            std::string title = line.substr(7); // 提取标题部分
            //cout << "Found title: " << title << "\n"; // 调试输出
            if (title == memoTitle) {
                found = true;
                //cout << "Title matched\n"; // 调试输出
            }
        }
        if (found) {
            if (line.find("MESSAGES: ") == 0) {
                std::string messages = line.substr(10); // 提取消息部分
                cout << "THE MEMO:" << "\n";
                cout << messages << "\n";
                break; // 找到消息后跳出循环
            }
        }
    }

    if (!found) {
        cout << "Memo with title '" << memoTitle << "' not found." << "\n";
    }
}

int main() {
    writeAmemo();
    findmemo("test");

    outfile.close();
    infile.close();
    return 0;
}