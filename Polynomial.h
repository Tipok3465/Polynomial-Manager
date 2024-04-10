#pragma once
#include "header.h"
#include "Node.h"

class Polynomial {
public:
    Polynomial();
    ~Polynomial();
    Polynomial(std::string s);
    void SortPol(Node*& L, Node*& R);
    void addNode(Node*& l, Node*& r, Node*& p);
    std::string getString();
    std::vector<int> paramCount();
    int getValue(std::vector<int> params);
    int power(int n, int q);
    void normalizePol();
    std::string addition(Polynomial* pol);
    Polynomial* multiplication(Polynomial* pol);
    bool empty();
    bool equal(Polynomial* pol);
    bool oneVariable();
    std::vector<int> solves();
    bool inPolynomial(int par);
    bool canDivPolynomials(Polynomial* second);
    Polynomial* maxPolynomial(Polynomial* second);
    std::pair<Polynomial*, Polynomial*> divisionPolynomials(Polynomial* second);
    Polynomial* derivative(int par_id, int der_order);
    int getParId();
private:
    Node* L;
};
