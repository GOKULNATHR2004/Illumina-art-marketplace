
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Art class representing an art piece
class Art {
public:
    int id;
    std::string title;
    std::string artist;
    double price;
    bool sold;

    Art(int id, const std::string& title, const std::string& artist, double price)
        : id(id), title(title), artist(artist), price(price), sold(false) {}
};

// User class representing a user in the system
class User {
public:
    std::string name;
    double balance;

    User(const std::string& name, double balance) : name(name), balance(balance) {}

    bool purchaseArt(Art& art) {
        if (art.sold) {
            std::cout << "Art piece \"" << art.title << "\" is already sold.\n";
            return false;
        }
        if (balance >= art.price) {
            balance -= art.price;
            art.sold = true;
            std::cout << "Purchase successful! You bought \"" << art.title << "\" by " << art.artist << ".\n";
            return true;
        }
        else {
            std::cout << "Insufficient balance to purchase \"" << art.title << "\".\n";
            return false;
        }
    }
};

// IlluminaApp class to manage the art marketplace
class IlluminaApp {
private:
    std::vector<Art> artGallery;
    std::vector<User> users;
    int nextArtId = 1;

public:
    void addArt(const std::string& title, const std::string& artist, double price) {
        artGallery.emplace_back(nextArtId++, title, artist, price);
        std::cout << "Art piece \"" << title << "\" by " << artist << " added to the gallery.\n";
    }

    void displayArt() const {
        std::cout << "Art Gallery:\n";
        for (const auto& art : artGallery) {
            std::cout << "ID: " << art.id << ", Title: " << art.title << ", Artist: " << art.artist
                << ", Price: $" << art.price << ", Sold: " << (art.sold ? "Yes" : "No") << "\n";
        }
    }

    void exploreArt() const {
        std::cout << "Exploring Art:\n";
        for (const auto& art : artGallery) {
            if (!art.sold) {
                std::cout << "ID: " << art.id << ", Title: " << art.title << ", Artist: " << art.artist
                    << ", Price: $" << art.price << "\n";
            }
        }
    }

    void addUser(const std::string& name, double balance) {
        users.emplace_back(name, balance);
        std::cout << "User \"" << name << "\" added with a balance of $" << balance << ".\n";
    }

    User* getUser(const std::string& name) {
        for (auto& user : users) {
            if (user.name == name) {
                return &user;
            }
        }
        std::cout << "User \"" << name << "\" not found.\n";
        return nullptr;
    }

    Art* getArtById(int id) {
        for (auto& art : artGallery) {
            if (art.id == id) {
                return &art;
            }
        }
        std::cout << "Art with ID " << id << " not found.\n";
        return nullptr;
    }
};

// Main function
int main() {
    IlluminaApp app;
    app.addUser("Hannah", 1000.0);
    app.addUser("James", 500.0);
    app.addUser("Vin Diesel", 2000.0);

    app.addArt("Starry Night", "Vincent van Gogh", 300.0);
    app.addArt("Mona Lisa", "Leonardo da Vinci", 500.0);
    app.addArt("The Persistence of Memory", "Salvador Dali", 400.0);

    int choice;
    std::string name;
    int artId;

    do {
        std::cout << "\nIllumina Art Marketplace\n";
        std::cout << "1. Display Art Gallery\n";
        std::cout << "2. Explore Art\n";
        std::cout << "3. Purchase Art\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            app.displayArt();
            break;
        case 2:
            app.exploreArt();
            break;
        case 3:
            std::cout << "Enter your name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            {
                User* user = app.getUser(name);
                if (user) {
                    std::cout << "Enter the ID of the art you wish to purchase: ";
                    std::cin >> artId;
                    Art* art = app.getArtById(artId);
                    if (art) {
                        user->purchaseArt(*art);
                    }
                }
            }
            break;
        case 4:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 4);

    return 0;
}
