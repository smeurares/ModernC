#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <algorithm>
#include "Product.h"
#include "ProductType.h"

bool productNameComparator(const Product& p1, const Product& p2)
{
    return p1.GetName() < p2.GetName();
}

bool productPriceComparator(const Product& p1, const Product& p2)
{
    return p1.GetPrice() < p2.GetPrice();
}


int main()
{
    std::vector<Product> products;

    uint16_t id;
    std::string name;
    float price;
    uint16_t tva;
    std::string expDateOrType;

    for (std::ifstream in{ "/home/DATA/QT/Test/product.txt" }; !in.eof(); /*EMPTY*/)
    {
        in >> id >> name >> price >> tva >> expDateOrType;

        std::regex dateRegexFormat{ R"(\d\d\d\d-\d\d-\d\d)" };
        if (std::regex_match(expDateOrType, dateRegexFormat))
        {
            products.emplace_back(id, name, price, tva, expDateOrType);

            //Product p{ id, name, price, tva, expDateOrType };
            //products.push_back(p);
        }
        else
        {
            products.emplace_back(id, name, price, tva, ParseProductType(expDateOrType));

            //Product p{ id, name, price, tva, ParseProductType(expDateOrType) };
            //products.push_back(p);
        }

        //Product p;
        //in >> p;
        //products.push_back(p);
    }

    for (Product product : products)
    {
        if (product.GetTVA() == 19)
        {
            std::cout << product;
        }
    }
    std::cout << std::endl;

    // normal func
    //std::sort(products.begin(), products.end(), productNameComparator);
    // friend func
    std::sort(products.begin(), products.end(), ProductNameComparator2);
    // lambda
    //std::sort(products.begin(), products.end(), [](const Product& p1, const Product& p2) { return p1.GetName() < p2.GetName(); });

    for (Product product : products)
    {
        std::cout << product;
    }
    std::cout << std::endl;

    // normal func
    //std::sort(products.begin(), products.end(), productPriceComparator);
    // operator<
    std::sort(products.begin(), products.end());

    for (Product product : products)
    {
        std::cout << product;
    }
    std::cout << std::endl;

    return 0;
}