#ifndef BIN_H
#define BIN_H

#include <string>

class Bin {
public:
    Bin();
    Bin(const Bin& orig);
    virtual ~Bin();
    std::string GetBin() const;
    void SetBin(std::string bin);
    std::string GetBrand() const;
    void SetBrand(std::string brand);
    bool IsCredit() const;
    void SetCredit(bool credit);
    long GetId() const;
    void SetId(long id);
    std::string GetIssuer() const;
    void SetIssuer(std::string issuer);

private:
    long id;
    std::string bin;
    std::string brand;
    std::string issuer;
    bool credit;
};



#endif /* BIN_H */

