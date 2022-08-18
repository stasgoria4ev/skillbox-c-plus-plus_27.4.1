#include <iostream>
#include <vector>
#include <ctime>
#include <string>

class Branch {
    Branch* parent; 
    std::vector <Branch*> children;
    std::string nameElf = "unknown";
public:
    void addChild(Branch* parent)
    {
        Branch* child = new Branch(this);
        children.push_back(child);
    }

    void creatTree() {
        for (int i = 0; i < std::rand() % 3 + 3; ++i) {
            this->addChild(this);
            
            std::cout << "Enter the name of the elf from the house on the Big Branch: ";
            std::cin >> children[i]->nameElf;
        }
        for (int j = 0; j < this->children.size(); j++) {
            for (int z = 0; z < std::rand() % 2 + 2; ++z) {
                this->children[j]->addChild(this);
                
                std::cout << "Enter the name of the elf from the house on the Middle Branch: ";
                std::cin >> children[j]->children[z]->nameElf;
            }
        }
    }

    bool good = true;
    void search(std::string& Elfname) { 
        for (int i = 0; i < children.size(); ++i) {
            if (parent == nullptr && i > 0 && children[i - 1]->children.empty())
                return;
            if (parent == nullptr && children[i]->nameElf == Elfname) {
                this->good = true;
                int count = 0;
                for (int j = 0; j < children[i]->children.size(); j++) { 
                    if (children[i]->children[j]->nameElf != "None")
                        count++;
                }
                std::cout << "The desired number of neighbors of the large branch = " << count << '\n';
                return;
            } else if (children[i]->nameElf == Elfname ) {
                this->good = true;
                int count = 0;
                for (int j = 0; j < this->children.size(); j++) { 
                    if (this->children[j]->nameElf != "None" && this->children[j] != children[i])
                        count++;
                }
                if (this->nameElf != "None")
                    count++;
                std::cout << "The desired number of neighbors of the middle branch = " << count << '\n';
                this->children.clear();
            } else if (parent != nullptr && children[i]->nameElf != Elfname ) {
                this->good = false;
            } else 
                children[i]->search(Elfname);

            if (parent == nullptr && children[i]->good == false) 
                good = false;
            else if (parent == nullptr)
                good = true;
        }
    }

    Branch(Branch* inParent) {
        parent = inParent;
    }
};

int main() {
    std::srand(std::time(nullptr));
    Branch* branch = new Branch(nullptr);
    branch->creatTree();   

    std::string* Elfname = new std::string;
    do {
        branch->good = true;
        std::string* Elfname = new std::string;
        do {
            std::cout << "\nEnter the Name of the Elf you are looking for: ";
            std::cin >> *Elfname;
            if (*Elfname == "None")
                std::cout << "Invalid search name, please try again...\n";
        } while (*Elfname == "None");
        branch->search(*Elfname);
        if (!branch->good) {
            std::cout << "There is no such Elf on this tree, please try again...\n";
        }
    } while (!branch->good);
    delete Elfname; Elfname = nullptr;
    delete branch; branch = nullptr;
}