#include <iostream>
#include <string>
#include <cstring>
#include "header.h"

Product AllocationFor1()
{
    Product p;
    std::cout << "Enter the product name: ";
    if (std::cin.peek() == '\n')
    {
        std::cin.ignore();
    }
    inputString(p.name, 50);

    std::cout << "Enter the number of produced items: ";
    p.NumOfProducts = ifPositiveInt();

    std::cout << "Enter the price per unit: ";
    p.price = ifPositive();

    std::cout << "Do you want to enter the workshop number or its name? (1 - number, 2 - name): ";
    int choice = ifChoice1or2();

    if (choice == 1)
    {
        std::cout << "Enter the workshop number: ";
        p.workshopInfo.workshopNumber = ifPositiveInt();
        p.isWorkshopName = false;
    }
    else if (choice == 2)
    {
        std::cout << "Enter the workshop name: ";
        if (std::cin.peek() == '\n')
        {
            std::cin.ignore();
        }
        inputString(p.workshopInfo.workshopName, 50);
        p.isWorkshopName = true;
    }

    return p;
}

Product *AllocationWhile(int &count)
{
    int size = 1;
    Product *products = new Product[size];
    count = 0;

    while (true)
    {
        if (count >= size)
        {
            size *= 2;
            Product *new_products = new Product[size];
            for (int i = 0; i < count; i++)
            {
                new_products[i] = products[i];
            }
            delete[] products;
            products = new_products;
        }

        Product temp = AllocationFor1();
        if (strcmp(temp.name, "STOP") == 0)
        {
            break;
        }
        products[count] = temp;
        CalculateTotalPrice(products[count]);
        count++;
    }
    return products;
}

Product *AllocationByN(int N)
{
    Product *products = new Product[N];
    for (int i = 0; i < N; i++)
    {
        std::cout << "Enter data for product #" << i + 1 << ": " << std::endl;
        products[i] = AllocationFor1();
        CalculateTotalPrice(products[i]);
    }
    return products;
}

Product *DialogueInput(int &count)
{
    int size = 1;
    Product *p = new Product[size];
    count = 0;
    while (true)
    {
        if (count >= size)
        {
            size *= 2;
            Product *new_p = new Product[size];
            for (int i = 0; i < count; i++)
            {
                new_p[i] = p[i];
            }
            delete[] p;
            p = new_p;
        }
        std::string Z;
        std::cout << "Do you want to enter data for product " << count + 1 << "? (Yes if yes): ";
        std::cin >> Z;
        if (Z == "Yes")
        {
            p[count] = AllocationFor1();
            CalculateTotalPrice(p[count++]);
        }
        else
        {
            break;
        }
    }
    return p;
}
