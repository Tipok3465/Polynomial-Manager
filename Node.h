#include "header.h"

enum class Error {
    UnknownSymbol, DoubleParam, PowerInStrangePlace, DoubleCoeff, DoubleSign, ZeroPolynomial, BigInt, SignInWrongPlace
};

class Node {
public:
    Node();
    Node(std::string s);
    bool operator<(Node r);
    bool operator==(Node r);
    void setNext(Node* q);
    Node* getNext();
    std::string getString(bool is_first);
    int getPower(int i);
    int getCoef();
    void setCoef(int n);
    Node* multiply(Node* node);
    bool is_free();
    Node* derivative(int par_id, int der_order);
    Node* division(Node* second, int par_id);
private:
    std::vector <int> powers;
    int coef;
    Node* next;
};
