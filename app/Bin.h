#ifndef BIN_H
#define BIN_H

#include <string>

/**
 * El bin corresponde a los primeros 6 dígitos de una tarjeta y permite 
 * identificar información relativa a la misma.
 */
class Bin {
public:
    /**
     * Constructor Vacío. Inicializa las variables.
     */
    Bin();
    /**
     * Copia los valores en la inicialización
     * @param orig Objeto a copiar
     */
    Bin(const Bin& orig);
    /**
     * Destructor. 
     */
    virtual ~Bin();
    /**
     * 
     * @return El bin (Ej: 520000)
     */
    std::string GetBin() const;
    /**
     * 
     * @param bin (Ej: 520000)
     */
    void SetBin(std::string bin);
    /**
     * 
     * @return La marca del emisor del plástico (Ej: Mastercard)
     */
    std::string GetBrand() const;
    /**
     * 
     * @param brand Marca del emisor del plástico (Ej: Visa)
     */
    void SetBrand(std::string brand);
    /**
     * 
     * @return Si el bin es de crédito o no
     */
    bool IsCredit() const;
    /**
     * 
     * @param credit true si el Bin de la tarjeta es de crédito
     */
    void SetCredit(bool credit);
    /**
     * 
     * @return El identificador único del objeto
     */
    long GetId() const;
    /**
     * 
     * @param id El identificador único del objeto
     */
    void SetId(long id);
    /**
     * 
     * @return El banco que emite la tarjeta
     */
    std::string GetIssuer() const;
    /**
     * 
     * @param issuer El banco que emite la tarjeta
     */
    void SetIssuer(std::string issuer);

private:
    long id;
    std::string bin;
    std::string brand;
    std::string issuer;
    bool credit;
};



#endif /* BIN_H */

