#include <iostream>   
#include <fstream>   
#include <vector>   
#include <string>   
#include <queue>   
#include <algorithm>   

bool isOneLetterDifferent(const std::string& word1, const std::string& word2) {
    int count = 0;
    for (size_t i = 0; i < word1.length(); i++) {
        if (word1[i] != word2[i]) {
            count++;
        }
    }
    return count == 1;
}

std::vector<std::string> findWordChain(const std::string& start, const std::string& end, const std::vector<std::string>& words) {
    std::queue<std::vector<std::string>> queue;
    queue.push({ start });

    std::vector<bool> visited(words.size(), false);

    while (!queue.empty()) {
        std::vector<std::string> currentPath = queue.front();
        queue.pop();
        std::string lastWord = currentPath.back();

        if (lastWord == end) {
            return currentPath;
        }

        for (size_t i = 0; i < words.size(); i++) {
            if (!visited[i] && isOneLetterDifferent(lastWord, words[i])) {
                visited[i] = true;
                std::vector<std::string> newPath = currentPath;
                newPath.push_back(words[i]);
                queue.push(newPath);
                if (words[i] == end) {
                    return newPath;
                }
            }
        }
    }

    return std::vector<std::string>();
}

bool containsOnlyDigits(const std::string& str) {
    return str.find_first_not_of("0123456789") == std::string::npos;
}

int main() {
    std::string dictionaryFilename, sourceWord, destinationWord;
    std::cout << "Word Morph" << std::endl;

    std::vector<std::pair<std::string, std::string>> inputs;  // Вектор для пар данных чтобы хранить

    while (true) {
        std::cout << "Input a dictionary filename: ";
        std::cin >> dictionaryFilename;

        std::ifstream file(dictionaryFilename);
        if (!file.is_open()) {
            std::cout << "Error: Unable to open file" << std::endl;
            continue;
        }

        std::vector<std::string> dictionary;
        std::string word;
        while (file >> word) {
            dictionary.push_back(word);
        }
        file.close();

        std::cout << "Input a source word: ";
        std::cin >> sourceWord;
        if (std::find(dictionary.begin(), dictionary.end(), sourceWord) == dictionary.end()) {
            std::cout << "Error: Source word not found in dictionary" << std::endl;
            continue;
        }

        std::cout << "Input a destination word: ";
        std::cin >> destinationWord;
        if (std::find(dictionary.begin(), dictionary.end(), destinationWord) == dictionary.end()) {
            std::cout << "Error: Destination word not found in dictionary" << std::endl;
            continue;
        }

        inputs.push_back(std::make_pair(sourceWord, destinationWord));  // тут сохраняем данные значит

        std::vector<std::string> wordChain = findWordChain(sourceWord, destinationWord, dictionary);
        if (wordChain.empty()) {
            std::cout << "No solution" << std::endl;
        }
        else {
            for (size_t i = 0; i < wordChain.size() - 1; i++) {
                std::cout << wordChain[i] << " -> ";
            }
            std::cout << wordChain.back() << std::endl;
        }

        std::cout << "Continue? (Y/N): ";
        std::string choice;
        std::cin >> choice;
        if (choice != "Y" && choice != "y") {
            break;
        }
    }

    return 0;
}
