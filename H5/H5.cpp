#include <filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <map>
#include <regex>

namespace fs = std::filesystem;
//-----------------------------------------------------------------------------------
void print_word_quantity(auto iter) {
   for (const auto& entry : iter) {

      if (entry.is_regular_file())
      { 
         std::cout << "[file] " << entry.path() << std::endl;

         std::ifstream in(entry.path());         
         std::map<std::string, unsigned short int> words;
         int number = 0;

         if (in.is_open())
         {
            std::cout << "true" << std::endl;
            for (std::string line; std::getline(in, line, ' ');)
            {
               std::regex re("\\w+");
               auto line_begin = std::sregex_iterator(line.begin(), line.end(), re);
               auto line_end = std::sregex_iterator();
               for (std::sregex_iterator i = line_begin; i != line_end; ++i) {
                  std::smatch match = *i;
                  auto word = match.str();
                  if (words.find(word) != words.cend())
                     words[word]++;
                  else
                     words[word] = 1;

                  number++;
               }              
            }
            std::cout << number << std::endl;
            for (const auto& el : words)
               std::cout << el.first << ' ' << el.second << std::endl;
         }
         in.close();
      }

   }
}
//-----------------------------------------------------------------------------------
int main()
{
   fs::path directoryPath = "C:\\C++\\STL\\H5\\H5\\text\\";
   auto dirIter = fs::directory_iterator(directoryPath);
    
   print_word_quantity(dirIter);
}
