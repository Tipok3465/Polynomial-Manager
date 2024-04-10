#include "Node.h"

Node::Node() {
    coef = 0;
    powers.resize(26, 0);
    next = nullptr;
}

bool Node::is_free() {
    for (int i = 0; i < 26; ++i) {
        if (powers[i])
            return false;
    }
    return true;
}

Node::Node(std::string s) {
    coef = 0;
    powers.resize(26, 0);
    next = nullptr;
    int sign = 1;
    int cur_state = 0;
    int cur_power = -1;
    std::string str_coef = "";
    std::string str_power = "";
    try {
        if (s.size() == 1 && (s.back() == '-' || s.back() == '+')) {
            throw Error::SignInWrongPlace;
        }
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '-') {
                if (cur_state != 0) {
                    throw Error::DoubleSign;
                }
                cur_state = 1;
                sign = -1;
            } else if (s[i] == '+') {
                if (cur_state != 0) {
                    throw Error::DoubleSign;
                }
                cur_state = 1;
                sign = 1;
            } else if ('0' <= s[i] && s[i] <= '9') {
                if (cur_state == 3) {
                    str_power += s[i];
                }
                else if (cur_state == 0) {
                    str_coef += s[i];
                    cur_state = 1;
                }
                else if (cur_state == 2) {
                    throw Error::DoubleCoeff;
                } else {
                    str_coef += s[i];
                }
            } else if ('a' <= s[i] && s[i] <= 'z') {
                if (!str_coef.empty() && (cur_state == 1 || cur_state == 0)) {
                    if (str_coef.size() > 9) {
                        throw Error::BigInt;
                    }
                    coef =  sign * std::stoi(str_coef);
                } else if (cur_state == 1 || cur_state == 0) {
                    coef = sign;
                }
                else if (cur_state == 2) {
                    if (!str_power.empty()) {
                        if (str_power.size() > 9) {
                            throw Error::BigInt;
                        }
                        if (powers[cur_power] != 0) {
                            powers[cur_power] = powers[cur_power] + std::stoi(str_power);
                        }
                        else {
                            powers[cur_power] = std::stoi(str_power);
                        }
                    } else {
                        if (powers[cur_power] != 0) {
                            powers[cur_power] = powers[cur_power] + 1;
                        }
                        else {
                            powers[cur_power] = 1;
                        }
                        str_power = "";
                    }
                } else if (cur_state == 3) {
                    if (str_power.empty()) {
                        throw Error::PowerInStrangePlace;
                    } else {
                        if (str_power.size() > 9) {
                            throw Error::BigInt;
                        }
                        if (powers[cur_power] != 0) {
                            powers[cur_power] = powers[cur_power] + std::stoi(str_power);
                        }
                        else {
                            powers[cur_power] = std::stoi(str_power);
                        }
                    }
                    str_power = "";
                }
                cur_state = 2;
                cur_power = s[i] - 'a';
            } else if (s[i] == '^') {
                if (cur_state != 2) {
                    throw Error::PowerInStrangePlace;
                }
                cur_state = 3;
            } else if (s[i] == ' ') {
                continue;
            } else {
                throw Error::UnknownSymbol;
            }
        }
        if (!str_coef.empty() && cur_state == 1) {
            if (str_coef.size() > 9) {
                throw Error::BigInt;
            }
            coef =  sign * std::stoi(str_coef);
        } else if (cur_state == 1) {
            coef = sign;
        } else if (cur_state == 2 && !str_power.empty()) {
            if (str_power.size() > 9) {
                throw Error::BigInt;
            }
            if (powers[cur_power] != 0) {
                powers[cur_power] = powers[cur_power] + std::stoi(str_power);
            }
            else {
                powers[cur_power] = std::stoi(str_power);
            }
        } else if (cur_state == 2) {
            if (powers[cur_power] != 0) {
                powers[cur_power] = powers[cur_power] + 1;
            }
            else {
                powers[cur_power] = 1;
            }
        } if (cur_state == 3 && str_power.empty()) {
            throw Error::PowerInStrangePlace;
        } else if (cur_state == 3) {
            if (str_power.size() > 9) {
                throw Error::BigInt;
            }
            if (powers[cur_power] != 0) {
                powers[cur_power] = powers[cur_power] + std::stoi(str_power);
            }
            else {
                powers[cur_power] = std::stoi(str_power);
            }
        }
    } catch (Error error) {
        throw;
    }
}

bool Node::operator<(Node r) {
    for (int i = 0; i < 26; ++i) {
        if (powers[i] < r.powers[i]) {
            return true;
        } else if (powers[i] > r.powers[i]) {
            return false;
        }
    }
    if (coef < r.coef) {
        return true;
    } else {
        return false;
    }
}

bool Node::operator==(Node r) {
    for (int i = 0; i < 26; ++i) {
        if (powers[i] != r.powers[i])
            return false;
    }
    return true;
}

void Node::setNext(Node *q) {
    next = q;
}

Node* Node::getNext() {
    return next;
}

std::string Node::getString(bool is_first) {
    std::string res = "";
    if (is_first) {
        if (coef > 0) {
            if (coef != 1 || is_free()) {
                res = std::to_string(coef);
            }
        } else {
            if (coef == -1) {
                if (!is_free())
                    res = "-";
                else
                    res = "-1";
            } else {
                res = std::to_string(coef);
            }
        }
    } else {
        if (coef > 0) {
            if (coef == 1) {
                if (!is_free())
                    res = " + ";
                else
                    res = " + 1";
            } else {
                res = " + " + std::to_string(coef);
            }
        } else {
            if (coef == -1) {
                if (!is_free())
                    res = " - ";
                else
                    res = " - 1";
            } else {
                res = " - " + std::to_string(abs(coef));
            }
        }
    }
    for (int i = 0; i < 26; ++i) {
        if (powers[i]==1) {
            res += (char)('a'+i);
        }
        else if (powers[i] > 1) {
            res +=  (char)('a'+i);
            res += '^';
            res += std::to_string(powers[i]);
        }
    }
    return res;
}

int Node::getPower(int i) {
    return powers[i];
}

int Node::getCoef() {
    return coef;
}

void Node::setCoef(int n) {
    coef = n;
}

Node* Node::multiply(Node *node) {
    auto res = new Node();
    res->coef = coef * node->coef;
    for (int i = 0; i < 26; ++i) {
        res->powers[i] = powers[i] + node->powers[i];
    }
    return res;
}

Node* Node::derivative(int par_id, int der_order) {
    auto res = new Node();
    if (!powers[par_id]) {
        res->coef = 0;
        res->powers = std::vector<int>(26, 0);
    } else {
        res->coef = coef;
        res->powers = powers;
        while (res->powers[par_id] > 0 && der_order != 0) {
            res->coef *= res->powers[par_id];
            --res->powers[par_id];
            --der_order;
        }
        if (!res->powers[par_id] && der_order != 0) {
            res->coef = 0;
            res->powers = std::vector<int>(26, 0);
        }
    }
    return res;
}

Node* Node::division(Node *second, int par_id) {
    auto res = new Node();
    res->coef = coef / second->coef;
    res->powers[par_id] = powers[par_id] - second->powers[par_id];
    return res;
}
