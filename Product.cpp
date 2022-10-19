#include "Product.h"
#include <regex>


Product::Product(uint16_t id, const std::string& name, float price, uint16_t tva, std::string expirationDate)
        : m_id{ id }, m_name{ name }, m_price{ price }, m_tva{ tva }, m_expirationDate{ expirationDate }
{
    //m_expirationDateOrType = expirationDate;
}

Product::Product(uint16_t id, const std::string& name, float price, uint16_t tva, ProductType type)
        : m_id{ id }, m_name{ name }, m_price{ price }, m_tva{ tva }, m_type{type}
{
    //m_expirationDateOrType = type;
}

uint16_t Product::GetId() const { return m_id; }

std::string Product::GetName() const { return m_name; }

float Product::GetPrice() const
{
    return m_price + m_price * GetTVA() / 100.0f;
}

uint16_t Product::GetTVA() const
{
    return m_tva; // to refactor later
}

std::string Product::GetExpirationDate() const
{
    //return m_expirationDate;

    // cu std::variant
   // return std::get<std::string>(m_expirationDateOrType);  // can throw
  //  return std::get<0>(m_expirationDateOrType);  // can throw

    //cu verificare
    if (std::holds_alternative<std::string>(m_expirationDateOrType))
    {
        return std::get<std::string>(m_expirationDateOrType);  // guaranteed no exception
    }
    else
    {
        return "";
    }
}

ProductType Product::GetType() const
{
    return m_type;

    // for variant see above
}


std::istream& operator >> (std::istream& in, Product& product)
{
    in >> product.m_id >> product.m_name >> product.m_price >> product.m_tva;
    std::string aux;
    in >> aux;

    std::regex dateRegexFormat{ "\\d\\d\\d\\d-\\d\\d-\\d\\d" };
    if (std::regex_match(aux, dateRegexFormat))
    {
        product.m_expirationDate = aux;

        // cu std::variant
        product.m_expirationDateOrType = aux;
    }
    else if (aux == "Clothing")
    {
        product.m_type = ProductType::Clothing;

        // cu std::variant
        product.m_expirationDateOrType = ProductType::Clothing;
    }
    else if (aux == "PersonalHygiene")
    {
        product.m_type = ProductType::PersonalHygiene;

        // cu std::variant
        product.m_expirationDateOrType = ProductType::PersonalHygiene;
    }
    else if (aux == "SmallAppliences")
    {
        product.m_type = ProductType::SmallAppliences;

        // cu std::variant
        product.m_expirationDateOrType = ProductType::SmallAppliences;
    }
    else
    {
        throw  std::exception() ;
    }
}

std::ostream& operator<< (std::ostream& out, const Product& product)
{
    out << product.m_id << " "
        << product.m_name << " "
        << product.GetPrice() << " "
        << product.m_tva << " ";

    if (product.m_tva == 9)
    {
        out << product.m_expirationDate;
        // out << std::get<0>(product.m_expirationDateOrType);
    }
    else
    {
        switch (product.m_type)
        {
            case ProductType::Clothing:
                out << "Clothing";
                break;
            case ProductType::PersonalHygiene:
                out << "PersonalHygiene";
                break;
            case ProductType::SmallAppliences:
                out << "SmallAppliences";
                break;
            default:
                break;
        }
    }

    return out << '\n';
}

bool operator<(const Product& p1, const Product& p2)
{
    return p1.GetPrice() < p2.GetPrice();
}

bool ProductNameComparator2(const Product& p1, const Product& p2)
{
    return p1.m_name < p2.m_name;
}