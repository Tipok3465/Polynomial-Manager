#include "Polynomial.h"

Polynomial::Polynomial() {
    L = nullptr;
}

Polynomial::~Polynomial(){
    while (L != nullptr) {
        Node* q = L;
        L = L->getNext();
        delete q;
    }
}

void Polynomial::normalizePol() {
    Node* R = L;
    while (R != nullptr && R->getNext() != nullptr) {
        R = R->getNext();
    }
    SortPol(L, R);
    Node* cur = L;
    Node* pref = nullptr;
    while (cur != nullptr && cur->getNext() != nullptr) {
       if (*cur == *cur->getNext()) {
           if (cur->getCoef() + cur->getNext()->getCoef() != 0) {
               Node* q = cur->getNext();
               cur->setCoef(cur->getCoef() + cur->getNext()->getCoef());
               cur->setNext(cur->getNext()->getNext());
               if (pref == nullptr) {
                   L = cur;
               } else {
                   pref->setNext(cur);
               }
               delete q;
           } else {
               Node *q, *p;
               q = cur;
               p = cur->getNext();
               cur = cur->getNext()->getNext();
               delete q;
               delete p;
               if (pref == nullptr) {
                   L = cur;
               } else {
                   pref->setNext(cur);
               }
           }
       } else if (cur->getCoef() == 0) {
           Node* q = cur;
           if (pref == nullptr) {
               L = cur->getNext();
               cur = cur->getNext();
           } else {
               pref->setNext(cur->getNext());
               cur = cur->getNext();
           }
           delete q;
       } else {
           pref = cur;
           cur = cur->getNext();
       }
    }
    if (cur != nullptr) {
        if (cur->getCoef() == 0) {
            Node *q = cur;
            if (pref == nullptr) {
                L = cur->getNext();
            } else {
                pref->setNext(cur->getNext());
            }
            delete q;
        }
    }
    if (L == nullptr) {
        L = new Node("0");
    }
}

void Polynomial::addNode(Node *&l, Node *&r, Node *&p) {
    if (l == nullptr) {
        l = p;
        r = p;
    } else {
        r->setNext(p);
        r = r->getNext();
    }
    p = p->getNext();
    r->setNext(nullptr);
}

int Polynomial::power(int n, int q) {
    if (q == 0) return 1;
    if (q % 2 == 0) return power(n * n, q/2);
    else return n * power(n, q - 1);
}

void Polynomial::SortPol(Node*& l, Node*& r) {
    if (l == nullptr || l->getNext() == nullptr)
        return;
    Node* pivot = l;
    Node *lowl, *lowr, *equall, *equalr, *highl, *highr;
    lowl = nullptr;
    lowr = nullptr;
    equall = nullptr;
    equalr = nullptr;
    highl = nullptr;
    highr = nullptr;
    Node* cur = l;
    while (cur != nullptr) {
        if (*cur < *pivot) {
            addNode(highl, highr, cur);
        } else if (*pivot < *cur) {
            addNode(lowl, lowr, cur);
        } else {
            addNode(equall, equalr, cur);
        }
    }
    SortPol(lowl, lowr);
    SortPol(highl, highr);
    if (lowl == nullptr) {
        lowl = equall;
    } else {
        lowr->setNext(equall);
    }
    lowr = equalr;
    if (lowl == nullptr) {
        lowl = highl;
    } else {
        lowr->setNext(highl);
    }
    if (highr != nullptr)
        lowr = highr;
    l = lowl;
    r = lowr;
}

Polynomial::Polynomial(std::string s) {
    std::string buffer;
    std::set<char> params;
    int cur_state = 0;
    Node* it = nullptr;
    try {
        bool pref_sign = false;
        for (auto e : s) {
            if (pref_sign) {
                if (e == '+' || e == '-') {
                    throw Error::DoubleSign;
                }
            }
            pref_sign = (e == '+' || e == '-');
        }
        for (auto e : s) {
            if ('a' <= e && e <= 'z') {
                params.insert(e);
            }
            if (e == '-' || e == '+') {
                if (cur_state == 1) {
                    if (it == nullptr) {
                        L = new Node(buffer);
                        it = L;
                    } else {
                        it->setNext(new Node(buffer));
                        it = it->getNext();
                    }
                }
                if (cur_state == 1) buffer.clear();
                cur_state = 1;
            } else if (e == '^') {
                cur_state = 2;
            }
            if (cur_state == 2 && e != '^') cur_state = 1;
            if (!cur_state && e != ' ') cur_state = 1;
            buffer.push_back(e);
        }
        if (it == nullptr) {
            L = new Node(buffer);
        } else {
            it->setNext(new Node(buffer));
        }
    } catch (Error error) {
        it = L;
        while (L != nullptr) {
            it = L;
            L = L->getNext();
            delete it;
        }
        throw;
    }
    Node* R = L;
    while (R != nullptr && R->getNext() != nullptr) {
        R = R->getNext();
    }
    SortPol(L, R);
    normalizePol();
    if (L == nullptr)
        L = new Node("0");
}

std::string Polynomial::getString() {
    Node* cur = L;
    std::string res = "";
    bool is_first = true;
    while (cur != nullptr) {
        res += cur->getString(is_first);
        cur = cur->getNext();
        is_first = false;
    }
    return res;
}

std::vector<int> Polynomial::paramCount() {
    Node* cur = L;
    std::vector<int> res(26, 0);
    while (cur != nullptr) {
        for (int i = 0; i < 26; ++i) {
            if (cur->getPower(i) != 0) {
                res[i] = 1;
            }
        }
        cur = cur->getNext();
    }
    return res;
}

int Polynomial::getValue(std::vector<int> params) {
    Node* cur = L;
    int value = 0;
    while (cur != nullptr) {
        int res = cur->getCoef();
        for (int i = 0; i < 26; ++i) {
            if (cur->getPower(i) != 0) {
                res *= power(params[i], cur->getPower(i));
            }
        }
        value += res;
        cur = cur->getNext();
    }
    return value;
}

std::string Polynomial::addition(Polynomial *pol) {
    Node* f = L;
    Node* s = pol->L;
    while (f->getNext() != nullptr) {
        f = f->getNext();
    }
    f->setNext(s);
    Node* q = L;
    std::string res_pol = "";
    bool is_first = true;
    while (q != nullptr) {
        res_pol += q->getString(is_first);
        is_first = false;
        q = q->getNext();
    }
    f->setNext(nullptr);
    return res_pol;
}

Polynomial* Polynomial::multiplication(Polynomial *pol) {
    Node* f = L;
    auto res = new Polynomial();
    Node* cur = res->L;
    while (f != nullptr) {
        Node* s = pol->L;
        while (s != nullptr) {
            if (res->L == nullptr) {
                res->L = f->multiply(s);
                cur = res->L;
            } else {
                cur->setNext(f->multiply(s));
                cur = cur->getNext();
            }
            s = s->getNext();
        }
        f = f->getNext();
    }
    res->normalizePol();
    return res;
}

bool Polynomial::empty() {
    return (L == nullptr);
}

bool Polynomial::equal(Polynomial *pol) {
    Node* f = L;
    Node* s = pol->L;
    while (f != nullptr && s != nullptr) {
        if (*f == *s && f->getCoef() == s->getCoef()) {
            f = f->getNext();
            s = s->getNext();
            continue;
        }
        return false;
    }
    if (f == nullptr && s == nullptr)
        return true;
    return false;
}

bool Polynomial::oneVariable() {
    Node* cur = L;
    int cur_var = -1;
    while (cur != nullptr) {
        for (int i = 0; i < 26; ++i) {
            if(cur->getPower(i)) {
                if (cur_var == -1 || cur_var == i) {
                    cur_var = i;
                    continue;
                }
                return false;
            }
        }
        cur = cur->getNext();
    }
    return true;
}

std::vector<int> getDivs(int n) {
    std::vector <int> res;
    for (int i = sqrt(n) + 1; i >= 1; --i) {
        if (n % i == 0) {
            res.push_back(i);
            if (i != sqrt(n)) {
                res.push_back(n / i);
            }
        }
    }
    return res;
}

std::vector <int> Polynomial::solves() {
    Node* cur = L;
    int cur_id = -1;
    for (int i = 0; i < 26; ++i) {
        if (cur->getPower(i) != 0) {
            cur_id = i;
            break;
        }
    }
    std::vector<int> res;
    while (cur->getNext() != nullptr) {
        cur = cur->getNext();
    }
    if (cur->is_free()) {
        int coef = cur->getCoef();
        std::vector <int> values(26, 0);
        std::vector <int> divs = getDivs(abs(coef));
        for (auto e : divs) {
            values[cur_id] = e;
            if (getValue(values) == 0) {
                res.push_back(e);
            }
            values[cur_id] = -e;
            if (getValue(values) == 0) {
                res.push_back(-e);
            }
        }
    } else {
        int coef = cur->getCoef();
        res.push_back(0);
        std::vector <int> values(26, 0);
        std::vector <int> divs = getDivs(abs(coef));
        for (auto e : divs) {
            values[cur_id] = e;
            if (getValue(values) == 0) {
                res.push_back(e);
            }
            values[cur_id] = -e;
            if (getValue(values) == 0) {
                res.push_back(-e);
            }
        }
    }
    return res;
}

bool Polynomial::inPolynomial(int par) {
    Node* cur = L;
    while (cur != nullptr) {
        if (cur->getPower(par) != 0) {
            return true;
        }
        cur = cur->getNext();
    }
    return false;
}

Polynomial* Polynomial::derivative(int par_id, int der_order) {
    Node* f = L;
    auto res = new Polynomial();
    Node* cur = res->L;
    while (f != nullptr) {
        if (res->L == nullptr) {
            res->L = f->derivative(par_id, der_order);
            cur = res->L;
        } else {
            cur->setNext(f->derivative(par_id, der_order));
            cur = cur->getNext();
        }
        f = f->getNext();
    }
    res->normalizePol();
    return res;
}

Polynomial* Polynomial::maxPolynomial(Polynomial *second) {
    Node* f = L;
    Node* s = second->L;
    if (*s < *f) {
        return second;
    } else {
        return this;
    }
}

bool Polynomial::canDivPolynomials(Polynomial *second) {
    if (!oneVariable() || !second->oneVariable()) {
        return false;
    }
    Node* f = L;
    Node* s = second->L;
    int f_id = -1;
    int s_id = -1;
    while (f_id == -1 && f != nullptr) {
        for (int i = 0; i < 26; ++i) {
            if (f->getPower(i) != 0) {
                f_id = i;
            }
        }
        f = f->getNext();
    }
    while (s_id == -1 && s != nullptr) {
        for (int i = 0; i < 26; ++i) {
            if (s->getPower(i) != 0) {
                s_id = i;
            }
        }
        s = s->getNext();
    }
    if (f_id != -1 && s_id != -1) {
        if (this->L->getPower(f_id) < second->L->getPower(s_id))
            return false;
    }
    return (f_id == s_id || f_id == -1 && s_id == -1 || s_id == -1);
}

int Polynomial::getParId() {
    int id = 0;
    Node* cur = L;
    while (cur != nullptr) {
        for (int i = 0; i < 26; ++i) {
            if (cur->getPower(i) != 0) {
                return i;
            }
        }
        cur = cur->getNext();
    }
    return 0;
}

std::pair<Polynomial*, Polynomial*> Polynomial::divisionPolynomials(Polynomial *second) {
    auto div_res = new Polynomial();
    div_res->L = nullptr;
    auto cur_res = div_res->L;
    int fid = getParId(), sid = second->getParId();
    int id = std::max(fid, sid);
    auto first_copy = new Polynomial(this->getString());
    Node* fir = first_copy->L;
    Node* sec = second->L;
    while (fir != nullptr && sec != nullptr && fir->getPower(id) >= sec->getPower(id) && fir->getCoef() != 0 && sec->getCoef() != 0) {
        Polynomial term = Polynomial("-1");
        term = *term.multiplication(second);
        auto cur = fir->division(sec, id);
        term = *term.multiplication(new Polynomial(cur->getString(true)));
        auto q = new Polynomial(first_copy->addition(&term));
        delete first_copy;
        first_copy = q;
        fir = first_copy->L;
        if (cur->getCoef() == 0) {
            break;
        }
        if (cur_res == nullptr) {
            div_res->L = cur;
            cur_res = div_res->L;
        } else {
            cur_res->setNext(cur);
            cur_res = cur_res->getNext();
        }
    }
    div_res->normalizePol();
    first_copy->normalizePol();
    return {div_res, first_copy};
}