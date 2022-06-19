#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <map>

class Branch
{
private:
    int parent;
    int child;
    std::string** bigBranch = nullptr;
    std::map<int, std::vector<std::string>> nameBranches;
public: 
    int getChild() {
        child = std::rand() % 2 + 2;
        return child;
    }
    
    Branch() {
        parent = std::rand() % 3 + 3;
    }

    void inputName() {
        int countBigBranch = 0;
        for (int i = 0; i < 5; ++i) {//i - кол-во деревьев
            Branch* wood = new Branch();
            std::cout << "\nWood " << i + 1 << " - " << parent << " big branches:" << '\n';
            for (int j = 0; j < parent; ++j) {
                countBigBranch++;
                int woodGetChild = getChild();
                std::cout << " Big Branch " << j + 1 << " contains " << "medium branches = " << woodGetChild << ":" << '\n';
                woodGetChild++;
                    
                bigBranch = new std::string*[woodGetChild]; // динамическая инициализация массива
                for (int z = 0; z < woodGetChild; z++) {
                    if (z == 0) std::cout << "Enter Elf's name " << z + 1 << " for the house on the Big Branch: ";
                    else std::cout << "Enter Elf's name " << z + 1 << " for the house on the Middle Branch: ";
                    std::string name;
                    std::cin >> name;
                    bigBranch[z] = new std::string(name);
                    
                }
                    
                std::vector<std::string> temp;
                for (int s = 0; s < woodGetChild; s++) { 
                    if (*bigBranch[s] != "None")
                        temp.push_back(*bigBranch[s]);
                }
                        
                nameBranches.insert(std::pair<int, std::vector<std::string>>(countBigBranch, temp));
            }
            delete wood; wood = nullptr;
        }
    }

    void search(std::string Elfname) {
        for (std::map<int, std::vector<std::string>>::iterator it = nameBranches.begin(); it != nameBranches.end(); ++it) {
            for (int i = 0; i < nameBranches[it->first].size(); ++i) {
                if (it->second[i] == Elfname)
                std::cout << "Number of neighbors = " << nameBranches[it->first].size() - 1 << '\n';
            }
        }
    }
};

int main() {
    std::srand(std::time(nullptr));
    
    Branch* names = new Branch();
    names->inputName();

    std::cout << "\nEnter the Name of the Elf you are looking for: ";
    std::string Elfname;
    std::cin >> Elfname;
    names->search(Elfname);
    delete names; names = nullptr;
}