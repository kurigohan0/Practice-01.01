#include <iostream>                                   // для оператора cout
#include <cstdio>                                     // для функции rename
 
int main ()
{
    char oldfilename[] = "Document.docx";                   // старое имя файла
    char newfilename[] = "NewDocument.docx";                   // новое имя файла
 
    if ( rename( oldfilename, newfilename ) == 0 )            // переименование файла
        std::cout << "Файл успешно переименованn";
    else
        std::cout << "Ошибка переименования файлаn";
    return 0;
}


// #include <string>
// #include <iostream>
// #include <experimental/filesystem>
// namespace fs = std::filesystem;

// int main()
// {
//     std::string path = "/path/to/directory";
//     for (const auto & entry : fs::directory_iterator(path))
//         std::cout << entry.path() << std::endl;
// }

// #include <string>
// #include <iostream>
// #include <boost/filesystem.hpp>
// using namespace std;
// using namespace boost::filesystem;

// int main()
// {
//     path p("D:/AnyFolder");
//     for (auto i = directory_iterator(p); i != directory_iterator(); i++)
//     {
//         if (!is_directory(i->path())) //we eliminate directories
//         {
//             cout << i->path().filename().string() << endl;
//         }
//         else
//             continue;
//     }
// }