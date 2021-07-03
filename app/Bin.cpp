#include "Bin.h"

Bin::Bin() {
    this->id = 0;
    this->bin = "";
    this->brand = "";
    this->issuer = "";
    this->credit = true;
}

Bin::Bin(const Bin& orig) {
    this->id = orig.GetId();
    this->bin = orig.GetBin();
    this->brand = orig.GetBrand();
    this->issuer = orig.GetIssuer();
    this->credit = orig.IsCredit();
}

Bin::~Bin() {
}

std::string Bin::GetBin() const {
    return bin;
}

void Bin::SetBin(std::string bin) {
    this->bin = bin;
}

std::string Bin::GetBrand() const {
    return brand;
}

void Bin::SetBrand(std::string brand) {
    this->brand = brand;
}

bool Bin::IsCredit() const {
    return credit;
}

void Bin::SetCredit(bool credit) {
    this->credit = credit;
}

long Bin::GetId() const {
    return id;
}

void Bin::SetId(long id) {
    this->id = id;
}

std::string Bin::GetIssuer() const {
    return issuer;
}

void Bin::SetIssuer(std::string issuer) {
    this->issuer = issuer;
}

std::string Bin::to_string() {
    return "Bin[id=" + std::to_string(this->id) + "' | Bin='" + this->bin + "' | Brand='" + this->brand + "' | Issuer='" + this->issuer + "' | Credit='" + std::to_string(this->credit) + "']";
}