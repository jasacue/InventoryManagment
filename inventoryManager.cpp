#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <sstream>
#include <limits>
//Things to remember about c++, you have to compile the thing into an exectuable. From there you can easily run it from the command line.
//Design a program to manage a simple inventory system with items, quantities, and prices.



//You need to declare the function before you can use it in main
//Function Declarations
void display_text(std::string display_text);
void clear_newline();
void add_item(std::string item_name, int quantity, double price);
void remove_item(std::string item_name); 
void view_inventory(); 
void load_inventory(std::string filename);
void save_inventory(std::string filename);
int menu();

//global variables
int running = 1;
std::unordered_map<std::string, std::pair<int, double>> inventory; //Global inventory variable to hold the stuff.

int main() {
    while (running == 1){
        menu();
    }
    return 0;

}

int menu(){
    std::string menu_message = "Welcome to your inventory. Please select an option: \n 1. View Inventory \n 2. Add Item \n 3. Remove Item";
    std::string second_message = "\n 4. Load Inventory \n 5. Save Inventory \n 6. Quit";
    display_text(menu_message + second_message);   
    int choice;
    std::cin >> choice;
    // Variables for case 2 // (They can't be instantiated inside the case statment)
    std::string itemName;
    int itemQuantity;
    double itemValue;
    ///////////////////////// 

    //case 4 & 5 variables//
    std::string loadName;
    std::string saveName;
    ////////////////////////

    switch (choice){
        case 1: //View Inventory
            view_inventory();
            break;
        case 2: //Add Item
        //get name of item
            clear_newline();
            display_text("What is the name of the item?");
            std::getline(std::cin, itemName); //I put get line here because if whitespace is added it freaks out like crazy
            display_text("How many of this item would you like to add");
            std::cin >> itemQuantity;
            display_text("What is the dollar amount of each of these items?");
            std::cin >> itemValue;
            add_item(itemName, itemQuantity, itemValue);
            break;
        case 3://Remove Item
            clear_newline();
            display_text("What is the name of the item that you would like to remove?");
            std::getline(std::cin, itemName);
            remove_item(itemName);
            break;
        case 4: //Load Inventory file
            display_text("Enter the file name you want to load from:");
            std::cin >> loadName;
            load_inventory(loadName);
            break;
        case 5: //Save Inventory file
            display_text("Enter the filename you want to save too:");
            std::cin >> saveName;
            save_inventory(saveName);
            break;
        case 6: //
            running = 0;
            break;
    }
}

//Simple text display function to display text to the console
void display_text(std::string display_text){
    std::cout << display_text << std::endl;
}
//Makes it so that when the user inputs it, it doesn't explode
void clear_newline()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
///EDIT FUNCTIONS///

    //This will add an item, to the global inventory.
void add_item(std::string item_name, int quantity, double price){
    auto findit = inventory.find(item_name);

    if (findit != inventory.end()) { //This will update the quantity and price of an existing item in the inventory.
        inventory[item_name].first += quantity; // Update quantity
        inventory[item_name].second = price; // Update price.
        //If i dont do it in stages like this the compiler throughs a clot and explodes.
        display_text(item_name + " already exists, the price has been updated to your recent entry.");
        }
    else{
        inventory[item_name] = std::make_pair(quantity, price); //This will add a new item to the inventory.
    }
}

void remove_item(std::string item_name){
    auto findit = inventory.find(item_name);
    if (findit != inventory.end()) {
        inventory.erase(findit); 
        display_text("Item succesfully removed");
    }
    else{
        display_text("Item not found in inventory.");
    }
}

void view_inventory(){
    if (inventory.empty()) {
        display_text("Inventory is empty.");
        return;
    }
    display_text("=====================================");
    for (const auto& item : inventory) {
        display_text("Item: " + item.first);
        display_text("Quantity: " + std::to_string(item.second.first));
        display_text("Price: $" + std::to_string(item.second.second));
        display_text("=====================================");
        
    }
    display_text(("Press Enter To Continue"));
    clear_newline();
    std::cin.get();
}

///EXTERML FILE FUNCTIONS///

void save_inventory(std::string filename){
    //This function will save the inventory to a file.
    std::ofstream outfile(filename); //this creates a new file
    if (!outfile.is_open())
    {
        display_text("Couldn't find that file");
    }
    else
    {
        for (const auto& item : inventory)
        {
            outfile << item.first +","+ std::to_string(item.second.first)+ "," + std::to_string(item.second.second) + "\n";
        }
    
    }
    outfile.close();
    display_text("Save was successful");
}

void load_inventory(std::string filename)
{
    std::ifstream infile(filename);
    if (!infile.is_open()){
        display_text("Coulnd't find that file");
    }
    else{
        std::string line;
        while (std::getline(infile, line)){
            std::stringstream ss(line);
            std::string token;
            std::vector<std::string> tokens;

            while (std::getline(ss, token, ',')) //Rips apart the string from the inventory file
            {
                tokens.push_back(token);
            }       
            if (tokens.size() >= 3) {
                add_item(tokens[0], std::stoi(tokens[1]), std::stod(tokens[2]));
            }
        }
    }
}


//this language is difficult