#include <iostream>
#include <cstring>
#include <limits>
#include <vector>
#include <fstream>
#include "header.h"


int main()
{
    const char *filename = "products.bin";
    Product *products = nullptr;
    int productCount = 0;
    int newCount = 0;
    bool found = false;
    std::vector<int> foundIndices = {0};

    while (true)
    {
        std::cout << "\nMenu:\n"
                  << "1. Input data into the structure\n"
                  << "2. Show entered data\n"
                  << "3. Add new structures to the existing array\n"
                  << "4. Search and display products with specific characteristics\n"
                  << "5. Delete products\n"
                  << "6. Modify product characteristics\n"
                  << "7. Sort array by product quantity\n"
                  << "8. Display total product count for a specific workshop\n"
                  << "9. Write to file\n"
                  << "10. Read from file\n"
                  << "11. Edit file\n"
                  << "12. Exit\n"
                  << "Your choice: ";
        int choice = ifPositiveInt();

        switch (choice)
        {
        case 1:
        {
            std::cout << "\nChoose a method to input data:\n"
                      << "1. Enter a predefined number of products\n"
                      << "2. Input products until the \"STOP\" command\n"
                      << "3. Dialog input for products\n"
                      << "4. Cancel\n"
                      << "Your choice: ";
            int inputMethod = ifInt();

            if (products != nullptr)
            {
                delete[] products;
            }

            if (inputMethod == 1)
            {
                std::cout << "Enter the number of products: ";
                int N = ifPositiveInt();
                products = AllocationByN(N);
                productCount = N;
            }
            else if (inputMethod == 2)
            {
                products = AllocationWhile(productCount);
            }
            else if (inputMethod == 3)
            {
                products = DialogueInput(productCount);
            }
            else if (inputMethod == 4)
            {
                break;
            }
            break;
        }
        case 2:
            PrintStruct(products, productCount);
            break;
        case 3:
            products = AddToExistingArray(products, productCount, newCount);
            break;
        case 4:
            FindSmth(products, productCount, found, foundIndices);
            break;
        case 5:
            DeleteProducts(products, productCount);
            break;
        case 6:
            ModifyProduct(products, productCount);
            break;
        case 7:
            SortStruct(products, productCount);
            break;
        case 8:
            PrintProductsByWorkshop(products, productCount);
            break;
        case 9:
        {
            bool write = writeToFile(filename, products, productCount);
            if (write)
                std::cout << "Успешный ввод";
            else
                std::cout << "Неуспешный ввод";
            break;
        }
        case 10:
            readFromFile(filename);
            break;
        case 11:
            editRecord(filename);
            break;
        case 12:
            if (products != nullptr)
            {
                delete[] products;
            }
            return 0;
        }
    }
}

bool writeToFile(const std::string filename, Product *products, int productCount)
{
    std::ofstream file(filename, std::ios::binary);
    if (!file)
    {
        return false;
    }

    for (int i = 0; i < productCount; i++)
    {
        file.write((char *)&products[i], sizeof(Product));
    }

    file.close();
    return true;
}

void readFromFile(const std::string filename)
{
    std::fstream file(filename, std::ios::in | std::ios::binary);
    Product product;
    int i = 0;

    while (file.read((char *)&product, sizeof(Product)))
    {
        std::cout << "\nЗапись #" << i++ << std::endl;
        std::cout << "Название: " << product.name << std::endl;
        std::cout << "Количество: " << product.NumOfProducts << std::endl;
        if (product.isWorkshopName)
        {
            std::cout << "Цех: " << product.workshopInfo.workshopName << std::endl;
        }
        else
        {
            std::cout << "Номер цеха: " << product.workshopInfo.workshopNumber << std::endl;
        }
        std::cout << "Цена: " << product.price << std::endl;
        std::cout << "Общая стоимость: " << product.totalPrice << std::endl;
    }
    file.close();
}

void editRecord(const std::string filename)
{
    std::fstream file(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!file) {
        std::cout << "Ошибка открытия файла\n";
        return;
    }

    int record_number;
    std::cout << "Введите номер записи для редактирования: ";
    std::cin >> record_number;

    long record_offset = record_number * sizeof(Product);

    Product product;
    file.seekg(record_offset, std::ios::beg);
    file.read(reinterpret_cast<char*>(&product), sizeof(Product));
    if (file.fail()) {
        std::cout << "Ошибка чтения записи\n";
        file.close();
        return;
    }

    std::cout << "\nВыберите поле для редактирования:\n"
              << "1. Название продукта\n"
              << "2. Количество\n"
              << "3. Информация о цехе\n"
              << "4. Цена\n"
              << "5. Общая стоимость\n"
              << "Ваш выбор: ";
    
    int choice;
    std::cin >> choice;

    long field_offset = record_offset;

    switch (choice) {
        case 1: { 
            std::cout << "Новое название продукта: ";
            std::cin.ignore(); 
            inputString(product.name, 50);

            
            field_offset += offsetof(Product, name);
            file.seekp(field_offset, std::ios::beg);
            file.write(product.name, sizeof(product.name));
            break;
        }
        case 2: { 
            std::cout << "Новое количество: ";
            std::cin >> product.NumOfProducts;

            
            field_offset += offsetof(Product, NumOfProducts);
            file.seekp(field_offset, std::ios::beg);
            file.write(reinterpret_cast<char*>(&product.NumOfProducts), sizeof(product.NumOfProducts));
            break;
        }
        case 3: { 
            std::cout << "Использовать название цеха? (1/0): ";
            std::cin >> product.isWorkshopName;

            
            field_offset += offsetof(Product, isWorkshopName);
            file.seekp(field_offset, std::ios::beg);
            file.write(reinterpret_cast<char*>(&product.isWorkshopName), sizeof(product.isWorkshopName));

            if (product.isWorkshopName) {
                std::cout << "Название цеха: ";
                std::cin.ignore();
            inputString(product.workshopInfo.workshopName, 50);

                
                field_offset = record_offset + offsetof(Product, workshopInfo.workshopName);
                file.seekp(field_offset, std::ios::beg);
                file.write(product.workshopInfo.workshopName, sizeof(product.workshopInfo.workshopName));
            } else {
                std::cout << "Номер цеха: ";
                std::cin >> product.workshopInfo.workshopNumber;
                

                
                field_offset = record_offset + offsetof(Product, workshopInfo.workshopNumber);
                file.seekp(field_offset, std::ios::beg);
                file.write(reinterpret_cast<char*>(&product.workshopInfo.workshopNumber), sizeof(product.workshopInfo.workshopNumber));
            }
            break;
        }
        case 4: { 
            std::cout << "Новая цена: ";
            std::cin >> product.price;

            
            field_offset += offsetof(Product, price);
            file.seekp(field_offset, std::ios::beg);
            file.write(reinterpret_cast<char*>(&product.price), sizeof(product.price));
            break;
        }
        case 5: { 
            std::cout << "Новая общая стоимость: ";
            std::cin >> product.totalPrice;

            
            field_offset += offsetof(Product, totalPrice);
            file.seekp(field_offset, std::ios::beg);
            file.write(reinterpret_cast<char*>(&product.totalPrice), sizeof(product.totalPrice));
            break;
        }
        default: {
            std::cout << "Неверный выбор\n";
            file.close();
            return;
        }
    }

    if (file.fail()) {
        std::cout << "Ошибка записи в файл\n";
    } else {
        std::cout << "Поле успешно обновлено\n";
    }

    file.close();
}
