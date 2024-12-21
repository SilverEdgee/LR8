#include <iostream>
#include <cstring>
#include <vector>
#include "header.h"

Product *AddToExistingArray(Product *existingProducts, int& currentCount, int newCount) {
    std::cout << "Enter the new number of products (not less than the current " << currentCount << "): ";
    newCount = ifValidNewCount(currentCount);

    Product *newProducts = new Product[currentCount + newCount];
    for (int i = 0; i < currentCount; i++) {
        newProducts[i] = existingProducts[i];
    }

    delete[] existingProducts;
    existingProducts = nullptr;

    for (int i = 0; i < newCount; i++) {
        std::cout << "Enter data for new product #" << (currentCount + i + 1) << ":\n";
        newProducts[currentCount + i] = AllocationFor1();
        CalculateTotalPrice(newProducts[currentCount + i]);
    }

    currentCount += newCount;
    return newProducts;
}

void DeleteProducts(Product *&p, int &ProductCount)
{
    if (p == nullptr || ProductCount == 0)
    {
        std::cout << "No data to delete.\n";
        return;
    }
    std::vector<int> foundIndices;
    bool found = true;
    FindSmth(p, ProductCount, found, foundIndices);
    if (!found)
    {
        std::cout << "No data found for deletion." << std::endl;
    }
    int last = foundIndices.size();
    std::cout << "Enter the product number to delete (" << foundIndices[0] + 1 << "-" << last << "): ";
    int index = ifPositiveInt();

    while (index > last)
    {
        std::cout << "Invalid number. Enter a number between " << foundIndices[0] + 1 << " and " << last << ": ";
        index = ifPositiveInt();
    }

    index--;
    for (int i = index; i < ProductCount - 1; i++)
    {
        p[i] = p[i + 1];
    }

    ProductCount--;
    if (ProductCount > 0)
    {
        Product *newProducts = new Product[ProductCount];
        for (int i = 0; i < ProductCount; i++)
        {
            newProducts[i] = p[i];
        }
        delete[] p;
        p = newProducts;
    }
    else
    {
        delete[] p;
        p = nullptr;
    }

    std::cout << "Product successfully deleted.\n";
    return;
}

void ModifyProduct(Product *p, int ProductCount)
{
    if (p == nullptr || ProductCount == 0)
    {
        std::cout << "No data to modify.\n";
        return;
    }
    bool found = true;
    std::vector<int> foundIndeces = {0};
    FindSmth(p, ProductCount, found, foundIndeces);
    int last = foundIndeces.size();
    std::cout << "Enter the product number to modify (" << foundIndeces[0] + 1 << "-" << last << "): ";
    int index = ifPositiveInt();

    while (index > last)
    {
        std::cout << "Invalid number. Enter a number between " << foundIndeces[0] + 1 << " and " << last << ": ";
        index = ifPositiveInt();
    }

    index--;

    std::cout << "\nSelect the field to modify:\n"
              << "1. Product name\n"
              << "2. Product quantity\n"
              << "3. Price per unit\n"
              << "4. Workshop information\n"
              << "Your choice: ";

    int choice = ifInt();
    while (choice < 1 || choice > 4)
    {
        std::cout << "Enter a number between 1 and 4: ";
        choice = ifInt();
    }

    switch (choice)
    {
    case 1:
    {
        std::cout << "Enter a new product name: ";
        if (std::cin.peek() == '\n')
            std::cin.ignore();
        std::cin >> p[index].name;
        break;
    }
    case 2:
    {
        std::cout << "Enter a new product quantity: ";
        p[index].NumOfProducts = ifPositiveInt();
        CalculateTotalPrice(p[index]);
        break;
    }
    case 3:
    {
        std::cout << "Enter a new price per unit: ";
        p[index].price = ifPositive();
        CalculateTotalPrice(p[index]);
        break;
    }
    case 4:
    {
        std::cout << "Do you want to enter a workshop number or name? (1 - number, 2 - name): ";
        int workshopChoice = ifChoice1or2();

        if (workshopChoice == 1)
        {
            std::cout << "Enter the workshop number: ";
            p[index].workshopInfo.workshopNumber = ifPositiveInt();
            p[index].isWorkshopName = false;
        }
        else
        {
            std::cout << "Enter the workshop name: ";
            if (std::cin.peek() == '\n')
                std::cin.ignore();
            std::cin >> p[index].workshopInfo.workshopName;
            p[index].isWorkshopName = true;
        }
        break;
    }
    }
    std::cout << "Product successfully modified.\n";
}

void shekerSort(int *NumofProducts, int count)
{
    int left = 0, right = count - 1;
    int flag = 1;                    
    while ((left < right) && flag > 0)
    {
        flag = 0;
        for (int i = left; i < right; i++)
        {
            if (NumofProducts[i] > NumofProducts[i + 1])
            {
                double t = NumofProducts[i];
                NumofProducts[i] = NumofProducts[i + 1];
                NumofProducts[i + 1] = t;
                flag = 1; 
            }
        }
        right--;                       
        for (int i = right; i > left; i--) 
        {
            if (NumofProducts[i - 1] > NumofProducts[i])
            {
                int t = NumofProducts[i];
                NumofProducts[i] = NumofProducts[i - 1];
                NumofProducts[i - 1] = t;
                flag = 1; 
            }
        }
        left++;
        if (flag == 0)
            break;
    }
}


void PrintStruct(Product *p, int count) {
    if (p == nullptr || count == 0) {
        std::cout << "No products entered.\n";
    } else {
        for (int i = 0; i < count; i++) {
            std::cout << "Product #" << (i + 1) << ":\n"
                      << "Name: " << p[i].name << "\n"
                      << "Number of products: " << p[i].NumOfProducts << "\n"
                      << "Price per unit: " << p[i].price << "\n"
                      << "Total price: " << p[i].totalPrice << "\n";

            if (p[i].isWorkshopName) {
                std::cout << "Workshop name: " << p[i].workshopInfo.workshopName << "\n";
            } else {
                std::cout << "Workshop number: " << p[i].workshopInfo.workshopNumber << "\n";
            }
        }
    }
}

void FindSmth(Product *p, int ProductCount, bool found, std::vector<int> &foundIndices) {
    if (p == nullptr || ProductCount == 0) {
        std::cout << "No data to search.\n";
        return;
    }
    std::cout << "Choose a field to search:\n"
              << "1. Product name\n"
              << "2. Number of products\n"
              << "3. Price per unit\n"
              << "4. Workshop name or number\n"
              << "5. Total price\n"
              << "Your choice: ";
    int choice = ifInt();
    while (choice < 1 || choice > 5) {
        std::cout << "Enter a number between 1 and 5: ";
        choice = ifInt();
    }

    char SearchString[100];
    int searchInt;
    double searchDouble;

    
    foundIndices.clear();

    switch (choice) {
    case 1:
        std::cout << "Enter product name: ";
        std::cin.ignore();
        std::cin.getline(SearchString, 100);
        break;
    case 2:
        std::cout << "Enter number of products: ";
        searchInt = ifPositiveInt();
        break;
    case 3:
        std::cout << "Enter price per unit: ";
        searchDouble = ifPositive();
        break;
    case 4:
        std::cout << "Enter workshop name or number: ";
        std::cin.ignore();
        std::cin.getline(SearchString, 100);
        break;
    case 5:
        std::cout << "Enter total price: ";
        searchDouble = ifPositive();
        break;
    default:
        std::cout << "Invalid choice.\n";
        return;
    }

    for (int i = 0; i < ProductCount; i++) {
        bool match = false;
        switch (choice) {
        case 1:
            if (std::strcmp(p[i].name, SearchString) == 0) {
                match = true;
            }
            break;
        case 2:
            if (p[i].NumOfProducts == searchInt) {
                match = true;
            }
            break;
        case 3:
            if (p[i].price == searchDouble) {
                match = true;
            }
            break;
        case 4:
            if (p[i].isWorkshopName) {
                if (std::strcmp(p[i].workshopInfo.workshopName, SearchString) == 0) {
                    match = true;
                }
            } else {
                if (std::to_string(p[i].workshopInfo.workshopNumber) == SearchString) {
                    match = true;
                }
            }
            break;
        case 5:
            if (p[i].totalPrice == searchDouble) {
                match = true;
            }
            break;
        }
        if (match) {
            foundIndices.push_back(i);
        }
    }

    if (!foundIndices.empty()) {
        std::cout << "\nFound products:\n";
        for (int index : foundIndices) {
            std::cout << "Product #" << index + 1 << ":\n"
                      << "Name: " << p[index].name << "\n"
                      << "Number of products: " << p[index].NumOfProducts << "\n"
                      << "Price per unit: " << p[index].price << "\n"
                      << "Total price: " << p[index].totalPrice << "\n";

            if (p[index].isWorkshopName) {
                std::cout << "Workshop name: " << p[index].workshopInfo.workshopName << "\n";
            } else {
                std::cout << "Workshop number: " << p[index].workshopInfo.workshopNumber << "\n";
            }
            std::cout << "\n";
        }
    } else {
        std::cout << "No matches found.\n";
    }
}

void PrintProductsByWorkshop(Product *p, int ProductCount) {
    if (p == nullptr || ProductCount == 0) {
        std::cout << "No data to analyze.\n";
        return;
    }

    std::cout << "Enter workshop name or number: ";
    char workshopInput[100];
    std::cin >> workshopInput;

    int totalProducts = 0; 
    bool found = false; 

    for (int i = 0; i < ProductCount; i++) {
        if (p[i].isWorkshopName) {
            if (std::strcmp(p[i].workshopInfo.workshopName, workshopInput) == 0) {
                totalProducts += p[i].NumOfProducts;
                found = true;
            }
        } else {
            if (std::to_string(p[i].workshopInfo.workshopNumber) == workshopInput) {
                totalProducts += p[i].NumOfProducts;
                found = true;
            }
        }
    }

    if (found) {
        std::cout << "Total number of products released for workshop \"" 
                  << workshopInput << "\": " << totalProducts << "\n";
    } else {
        std::cout << "No data found for workshop \"" << workshopInput << "\".\n";
    }
}

void CalculateTotalPrice(Product &p)
{
    if (p.NumOfProducts > 0)
    {
        p.totalPrice = p.price * p.NumOfProducts;
    }
}


void SortStruct(Product *p, int ProductCount)
{
    if (p == nullptr || ProductCount == 0)
    {
        std::cout << "No data for sort.\n";
        return;
    }
    int new_array[ProductCount];
    for (int i = 0; i < ProductCount; i++)
    {
        new_array[i] = p[i].NumOfProducts;
    }

    shekerSort(new_array, ProductCount);

    Product sortedProducts[ProductCount];

    for (int i = 0; i < ProductCount; i++)
    {
        for (int j = 0; j < ProductCount; j++)
        {
            if (new_array[i] == p[j].NumOfProducts)
            {
                sortedProducts[i] = p[j];
                p[j].NumOfProducts = -1;
                break;
            }
        }
    }

    for (int i = 0; i < ProductCount; i++)
    {
        p[i] = sortedProducts[i];
    }

    PrintStruct(p, ProductCount);
}
