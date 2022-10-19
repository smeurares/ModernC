#include "ProductType.h"

ProductType ParseProductType(const std::string& str)
{
    if (str == "Clothing")
    {
        return ProductType::Clothing;
    }
    else if (str == "PersonalHygiene")
    {
        return ProductType::PersonalHygiene;
    }
    else if (str == "SmallAppliences")
    {
        return ProductType::SmallAppliences;
    }
    else
    {
        throw std::exception();
    }
}

std::string ProductTypeToString(ProductType type)
{
    switch (type)
    {
        case ProductType::Clothing:
            return "Clothing"s;
        case ProductType::PersonalHygiene:
            return "PersonalHygiene"s;
        case ProductType::SmallAppliences:
            return "SmallAppliences"s;
    }
}