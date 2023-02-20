#include<map>
#include<iostream>
#include<string>
#include<set>
#include<fstream>
#include<sstream>
#include<utility>
#include<vector>


int main(){
    std::string filename ="";
    std::cout << "Input file: ";
    getline(std::cin, filename);
    std::ifstream file_object(filename);
    if(not file_object){
        std::cout << "Error! The file "<<filename<<" cannot be opened.";
        return EXIT_FAILURE;
    }else{
        std::string line= "";
        std::string delimeter = " ";
        std::map<std::string, std::pair<int, std::vector<int>>> wordInLine;
        int numberLine = 1;
        while(getline(std::cin, line)){
           ++ numberLine;
           std::stringstream sentance(line);
           std::string word;
           std::set<std::string> isWordInLine;
           while(sentance >> word){

               if (wordInLine.find(word) == wordInLine.end()){
                   wordInLine[word] = std::make_pair(1, std::vector<int>());
                   isWordInLine.insert(word);
               }
               if (isWordInLine.find(word) != isWordInLine.end()){
                   wordInLine[word].first ++;
                   wordInLine[word].second.push_back(numberLine);
               }

               }
           }
        for (auto& data_pair : wordInLine){
            std::cout << data_pair.first<< " "<<
                         data_pair.second.first<<": ";
            std::vector<int>::const_iterator begin = data_pair.second.second.begin();
            std::vector<int>::const_iterator end = data_pair.second.second.end();
            while(begin != end-1){
                std::cout << *begin << ", ";
            }
            std::cout << *end << std::endl;
        }
        }
    }

