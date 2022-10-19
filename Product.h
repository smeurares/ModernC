#ifndef PRODUCT_H
#define PRODUCT_H

#include <cstdint>
#include <iostream>
#include <string>
#include <variant>
#include "ProductType.h"

class Product
{
public:
    Product(uint16_t id, const std::string& name, float price, uint16_t tva, std::string expirationDate);
    Product(uint16_t id, const std::string& name, float price, uint16_t tva, ProductType type);

    //Product(const Product& other) = default;
    //Product& operator= (const Product& other) = default;
    //~Product() = default;

    uint16_t GetId() const;
    std::string GetName() const;
    float GetPrice() const;
    uint16_t GetTVA() const;
    std::string GetExpirationDate() const;
    ProductType GetType() const;

    // optional a
    friend std::istream& operator>> (std::istream& in, Product& product);

    // obligatoriu
    friend std::ostream& operator<< (std::ostream& out, const Product& product);

    friend bool operator< (const Product& p1, const Product& p2);
    friend bool ProductNameComparator2(const Product& p1, const Product& p2);

private:
    uint16_t m_id;
    std::string m_name;
    float m_price;

    uint16_t m_tva;
    std::string m_expirationDate;
    ProductType m_type;

    // posibila idee de tema optionala pt cei interesati - provocare - discutie lab 2
    std::variant<std::string, ProductType> m_expirationDateOrType;

};

bool ProductNameComparator2(const Product& p1, const Product& p2);
#endif