#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    // 检查是否提供了文件名作为命令行参数
    if (argc != 4) {
        std::cerr << "format: " << argv[0] << " <filename.cpp>" << std::endl;
        return 1;
    }

    std::string file1 = argv[1]; // 获取文件名1
    std::string file2 = argv[2]; // 获取文件名2
    std::string suc = argv[3]; // 获取文件名2
    
    for(int i=1;i<=50;i++){
        std::string num="";
        if(i>=10) num+=char(i/10+'0');
        if(i>=1) num+=char(i%10+'0');
        std::string command = "rename " + file1 + num + suc + " " + file2 + num + suc + " > ./mod_temp"; // 构建编译命令
        int result = system(command.c_str());
    }

    system("rm ./mod_temp");
}