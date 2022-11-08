#include <iostream>
#include <cctype>
#include <limits>
#include <string>

// Ciphertext A-Z alphabet implementation
class Ciphertext {
    public:
        void cipher();
        void decipher();
        int getkey();
        std::string text;
};

void Ciphertext::decipher() {
    int key = getkey();

    for (auto& letter : text) {
        // Guard clause to ignore spaces
        if (letter == ' ') { continue; }
        // Subtracts the value of the key from each character in the string, wrapping around if necessary
        if (letter - key < 'A') {
            letter -= (key - 26);
        } else {
            letter -= key;
        }
    }

    std::cout << "\n===============\nDeciphered text:\n" << text << "\n===============\n";
}

void Ciphertext::cipher() {
    int key = getkey();

    for (auto& letter : text) {
        // Guard clause to ignore spaces
        if (letter == ' ') { continue; }
        // Adds the value of the key from each character in the string, wrapping around if necessary
        if (letter + key > 'Z') {
            letter += (key - 26);
        } else {
            letter += key;
        }
    }

    std::cout << "\n===============\nCiphered text:\n" << text << "\n===============\n";
}

// Helper functions/methods for getting user input
int Ciphertext::getkey() {
    int key;
    std::cout << "Enter an ASCII increment/decrement key: ";

    while (!(std::cin >> key)) {
        // Clear the cin buffer if std::cin reports an error
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a valid key.\nEnter key: ";
    }

    // Cap key at 26 increment/decrements as things go strange beyond this territory
    if (abs(key) > 26) {
        std::cout << "Request denied. Your input was capped at 26 iterations.\n";
        return 26;
    }

    return abs(key);
}

std::string getstring() {
    std::string str = "";

    std::cout << "Enter a string to cipher: ";
    std::cin.clear();
    getline(std::cin, str);

    // Capitalise the entire string
    for (unsigned int i = 0; i < str.length(); i++) {
        str[i] = toupper(str[i]);
    }

    // Check if the string contains letters that are not in the 26 letter alphabet (or spaces)
    for (unsigned int i = 0; i < str.size(); i++) {
        if (str[i] == ' ') { continue; }
        if (str[i] < 'A' || str[i] > 'Z') {
            throw std::invalid_argument("There are invalid characters in the phrase you entered. Alphabet A-Z only.");
        }
    }

    return str;
}

int main() {
    int option;
    Ciphertext cipher;

    std::cout << "Alphabet Caesar Cipher Algorithm in C++\n";
    
    while (true) {
        try {
            cipher.text = getstring();
            break;
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }

    while (true) {
        std::cout << "\n1 - Cipher\n";
        std::cout << "2 - Decipher\n";
        std::cout << "3 - Change string (currently: '" << cipher.text << "')\n";
        std::cout << "4 - Exit\n";
        std::cout << "Enter an option: ";
        std::cin >> option;
        
        switch (option) {
            case 1:
                cipher.cipher();
                break;
            case 2:
                cipher.decipher();
                break;
            case 3:
                // Clear the std::cin buffer before making any changes
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                try {
                    cipher.text = getstring();
                } catch (const std::invalid_argument& e) {
                    std::cout << "\nChange request denied." << std::endl;
                    std::cout << e.what() << std::endl;
                    break;
                }
                std::cout << "\nChanged string to '" << cipher.text << "'\n";
                break;
            case 4:
                std::exit(0);
            default:
                std::cout << "\nNot an option.";
        }
    }
    return 0;
}