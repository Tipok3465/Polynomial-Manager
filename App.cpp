#include "App.h"
#include "Polynomial.h"

App::App(int width, int height) {
    int id = QFontDatabase::addApplicationFont("/Users/noname/Documents/Programming/Applied/PolManager/resources/Quicksand-VariableFont_wght.ttf");
    family = QFontDatabase::applicationFontFamilies(id).at(0);

    window_ = new QMainWindow();
    window_->setFixedSize(width, height);
    window_->setStyleSheet("QMainWindow {"
                           "background: #686461;"
                           " }");
    background_ = new QLabel(window_);
    background_->resize(1000, 700);
    background_->setPixmap(QPixmap("../resources/bg.png"));

    warning_ = new QMainWindow();
    warning_->setFixedSize(400, 100);
    warning_->setStyleSheet("QMainWindow {"
                           "background: #686461;"
                           " }");
    warning_->setFont(QFont(family, 20));

    warning_label_ = new QLabel(warning_);
    warning_label_->resize(400, 100);
    warning_label_->setStyleSheet("QLabel {"
                                  "background: #686461;"
                                  " }");
    warning_label_->setAlignment(Qt::AlignCenter);
    warning_label_->setFont(QFont(family, 18));
    warning_->hide();

    base_table_header_ = new QLabel(window_);
    base_table_header_->resize(300, 50);
    base_table_header_->move(150, 0);
    base_table_header_->setStyleSheet("QLabel {"
                                      "text-align: center;"
                                      "}");
    base_table_header_->setFont(QFont(family, 40));
    base_table_header_->setText("BASE TABLE");


    base_table_ = new QLabel(window_);
    base_table_->resize(500, 630);
    base_table_->move(20, 50);
    base_table_->setStyleSheet("QLabel {"
                               "background-color: rgba(245, 244, 245, 90);"
                               "}");

    dialog_window_ = new QLabel(base_table_);
    dialog_window_->resize(400, 200);
    dialog_window_->move(50, 300);
    dialog_window_->setStyleSheet("QLabel {"
                               "background: #686461;"
                               "border-radius: 5px;"
                               "}");
    dialog_window_->setFont(QFont(family, 20));
    dialog_window_->setAlignment(Qt::AlignCenter);
    dialog_window_->hide();

    dialog_text_ = new QLabel(dialog_window_);
    dialog_text_->resize(400, 120);
    dialog_text_->move(0, 10);
    dialog_text_->setStyleSheet("QLabel {"
                                  "background: #686461;"
                                  "border-radius: 5px;"
                                  "}");
    dialog_text_->setFont(QFont(family, 20));
    dialog_text_->setAlignment(Qt::AlignCenter);

    accept_ = new QPushButton(dialog_window_);
    accept_->resize(100, 50);
    accept_->move(20, 130);
    accept_->setStyleSheet("QPushButton {"
                           "border-radius: 5px;"
                           "background: #CEAD6D;"
                           "color: #eee;"
                           "text-align: center;"
                           "}");
    accept_->setFont(QFont(family, 20));
    accept_->setText("Accept");
    connect(accept_, SIGNAL(released()), this, SLOT(accept()));

    reject_ = new QPushButton(dialog_window_);
    reject_->resize(100, 50);
    reject_->move(280, 130);
    reject_->setStyleSheet("QPushButton {"
                           "border-radius: 5px;"
                           "background: #CEAD6D;"
                           "color: #eee;"
                           "text-align: center;"
                           "}");
    reject_->setFont(QFont(family, 20));
    reject_->setText("Reject");
    connect(reject_, SIGNAL(released()), this, SLOT(reject()));

    dialog_window_scroll_ = new QScrollArea(dialog_window_);
    dialog_window_scroll_->setWidget(dialog_text_);
    dialog_window_scroll_->resize(400, 120);
    dialog_window_scroll_->move(0, 10);
    dialog_window_scroll_->setStyleSheet("QScrollArea {"
                                      "border-radius: 5px;"
                                      "background: #686461;"
                                      "}");



    base_table_scroll_ = new QScrollArea(window_);
    base_table_scroll_->setWidget(base_table_);
    base_table_scroll_->resize(500, 630);
    base_table_scroll_->move(20, 50);
    base_table_scroll_->setStyleSheet("QScrollArea {"
                                      "border-radius: 5px;"
                                      "background-color: rgba(245, 244, 245, 90);"
                                      "}");

    header_pol_adding_ = new QLabel(window_);
    header_pol_adding_->resize(400, 50);
    header_pol_adding_->move(570, 50);
    header_pol_adding_->setText("Operations with base");
    header_pol_adding_->setFont(QFont(family, 25));

    pol_data_ = new QLineEdit(window_);
    pol_data_->resize(300, 30);
    pol_data_->move(590, 100);
    pol_data_->setStyleSheet("QLineEdit {"
                             "border-radius: 5px;"
                             "background: #9E9B98;"
                             "color: #fff;"
                             "}");
    pol_data_->setFont(QFont(family, 15));
    pol_data_->setPlaceholderText("Input polynomial");

    set_pol_ = new QPushButton(window_);
    set_pol_->resize(70, 30);
    set_pol_->move(900, 100);
    set_pol_->setStyleSheet("QPushButton {"
                            "border-radius: 5px;"
                            "background: #CEAD6D;"
                            "color: #eee;"
                           
                            "}");
    set_pol_->setFont(QFont(family, 22));
    set_pol_->setText("ADD");
    connect(set_pol_, SIGNAL(released()), this, SLOT(addPolynom()));

    delete_polynomial_ = new QPushButton(window_);
    delete_polynomial_->resize(190, 40);
    delete_polynomial_->move(590, 140);
    delete_polynomial_->setText("DELETE");
    delete_polynomial_->setFont(QFont(family, 22));
    delete_polynomial_->setStyleSheet("QPushButton {"
                                      "color: #fff;"
                                      "background: #CEAD6D;"
                                      "border-radius: 5px;"
                                      "}");
    connect(delete_polynomial_, SIGNAL(released()), this, SLOT(deleteSelectedPol()));

    save_polynomial_ = new QPushButton(window_);
    save_polynomial_->resize(120, 40);
    save_polynomial_->move(590, 190);
    save_polynomial_->setFont(QFont(family, 22));
    save_polynomial_->setText("SAVE");
    save_polynomial_->setStyleSheet("QPushButton {"
                                    "color: #fff;"
                                    "background: #9E9B98;"
                                    "border-radius: 5px;"
                                    "}");
    connect(save_polynomial_, SIGNAL(released()), this, SLOT(saveToFile()));

    download_polynomial_ = new QPushButton(window_);
    download_polynomial_->resize(120, 40);
    download_polynomial_->move(720, 190);
    download_polynomial_->setFont(QFont(family, 20));
    download_polynomial_->setText("LOAD");
    download_polynomial_->setStyleSheet("QPushButton {"
                                        "color: #fff;"
                                        "background: #9E9B98;"
                                        "border-radius: 5px;"
                                        "}");
    connect(download_polynomial_, SIGNAL(released()), this, SLOT(loadFromFile()));

    value_data_ = new QLabel(base_table_);
    value_data_->resize(430, 450);
    value_data_->setStyleSheet("QLabel {"
                               "background: #686461;"
                               "border-radius: 3px;"
                               "border: 3px solid #CEAD6D;"
                               " }");
    value_data_->hide();

    set_param_values_ = new QPushButton(value_data_);
    set_param_values_->resize(280, 40);
    set_param_values_->move(10, 400);
    set_param_values_->setFont(QFont(family, 20));
    set_param_values_->setText("Set parameters");
    set_param_values_->setStyleSheet("QPushButton {"
                                     "border-radius: 5px;"
                                     "background: #CEAD6D;"
                                     "color: #eee;"
                                     "text-align: center;"
                                     "}");
    connect(set_param_values_, SIGNAL(released()), this, SLOT(setParamValues()));

    header_operations_ = new QLabel(window_);
    header_operations_->resize(400, 50);
    header_operations_->move(570, 270);
    header_operations_->setText("Operations for polynomials");
    header_operations_->setFont(QFont(family, 25));

    point_value_ = new QPushButton(window_);
    point_value_->resize(260, 40);
    point_value_->move(590, 330);
    point_value_->setStyleSheet("QPushButton {"
                                "border-radius: 5px;"
                                "background: #CEAD6D;"
                                "color: #eee;"
                               
                                "}");
    point_value_->setFont(QFont(family, 25));
    point_value_->setText("VALUE AT POINT");
    connect(point_value_, SIGNAL(released()), this, SLOT(getValueatPoint()));

    addition_ = new  QPushButton(window_);
    addition_->resize(260, 40);
    addition_->move(590, 380);
    addition_->setStyleSheet("QPushButton {"
                             "border-radius: 5px;"
                             "background: #CEAD6D;"
                             "color: #eee;"
                            
                             "}");
    addition_->setFont(QFont(family, 25));
    addition_->setText("ADDITION");
    connect(addition_, SIGNAL(released()), this, SLOT(additionPolynomials()));

    multiplication_ = new  QPushButton(window_);
    multiplication_->resize(260, 40);
    multiplication_->move(590, 430);
    multiplication_->setStyleSheet("QPushButton {"
                                   "border-radius: 5px;"
                                   "background: #CEAD6D;"
                                   "color: #eee;"
                                  
                                   "}");
    multiplication_->setFont(QFont(family, 25));
    multiplication_->setText("MULTIPLICATION");
    connect(multiplication_, SIGNAL(released()), this, SLOT(multiplyPolynomials()));

    comparison_ = new  QPushButton(window_);
    comparison_->resize(260, 40);
    comparison_->move(590, 480);
    comparison_->setStyleSheet("QPushButton {"
                               "border-radius: 5px;"
                               "background: #CEAD6D;"
                               "color: #eee;"
                              
                               "}");
    comparison_->setFont(QFont(family, 25));
    comparison_->setText("COMPARISON");
    connect(comparison_, SIGNAL(released()), this, SLOT(comparisonPolynomials()));

    derivative_ = new  QPushButton(window_);
    derivative_->resize(260, 40);
    derivative_->move(590, 530);
    derivative_->setStyleSheet("QPushButton {"
                               "border-radius: 5px;"
                               "background: #CEAD6D;"
                               "color: #eee;"
                              
                               "}");
    derivative_->setFont(QFont(family, 25));
    derivative_->setText("DERIVATIVE");
    connect(derivative_, SIGNAL(released()), this, SLOT(derivativePolynomial()));

    der_data_tablet_ = new QMainWindow();
    der_data_tablet_->setFixedSize(200, 80);
    der_data_tablet_->setStyleSheet("QMainWindow {"
                            "background: #686461;"
                            " }");
    der_data_tablet_->setFont(QFont(family, 20));
    der_data_tablet_->hide();

    der_parameter_ = new QLineEdit(der_data_tablet_);
    der_parameter_->resize(70, 25);
    der_parameter_->move(10, 10);
    der_parameter_->setStyleSheet("QLineEdit {"
                             "border-radius: 3px;"
                             "background: #9E9B98;"
                             "color: #fff;"
                             "}");
    der_parameter_->setPlaceholderText("Parameter");

    der_order_ = new QLineEdit(der_data_tablet_);
    der_order_->resize(100, 25);
    der_order_->move(90, 10);
    der_order_->setStyleSheet("QLineEdit {"
                                  "border-radius: 3px;"
                                  "background: #9E9B98;"
                                  "color: #fff;"
                                  "}");
    der_order_->setPlaceholderText("Derivative order");

    der_data_setter_ = new QPushButton(der_data_tablet_);
    der_data_setter_->resize(120, 30);
    der_data_setter_->move(40, 40);
    der_data_setter_->setStyleSheet("QPushButton {"
                             "border-radius: 3px;"
                             "background: #CEAD6D;"
                             "color: #eee;"
                            
                             "}");
    der_data_setter_->setFont(QFont(family, 20));
    der_data_setter_->setText("SET");
    connect(der_data_setter_, SIGNAL(released()), this, SLOT(setDerSettings()));

    division_ = new  QPushButton(window_);
    division_->resize(260, 40);
    division_->move(590, 580);
    division_->setStyleSheet("QPushButton {"
                             "border-radius: 5px;"
                             "background: #CEAD6D;"
                             "color: #eee;"
                            
                             "}");
    division_->setFont(QFont(family, 25));
    division_->setText("DIVISION");
    connect(division_, SIGNAL(released()), this, SLOT(divisionPolynomials()));

    equation_solves_ = new  QPushButton(window_);
    equation_solves_->resize(260, 40);
    equation_solves_->move(590, 630);
    equation_solves_->setStyleSheet("QPushButton {"
                                    "border-radius: 5px;"
                                    "background: #CEAD6D;"
                                    "color: #eee;"
                                    "}");
    equation_solves_->setFont(QFont(family, 25));
    equation_solves_->setText("EQUATION ROOTS");
    connect(equation_solves_, SIGNAL(released()), this, SLOT(solvePolynomial()));
}

App::~App() {
    delete window_;
}

void App::showWarning() {
    warning_label_->setText(QString::fromStdString(warning_text_));
    warning_->show();
}

void App::updBaseTable() {
    int i = 0;
    for (auto it = base_.begin(); it != base_.end(); ++it) {
        if (!i) {
            (*it)->move(10, 10);
        } else {
            (*it)->move(10, base_[i-1]->y() + 40);
        }
        (*it)->setProperty("id", i);
        (*it)->show();
        ++i;
    }
    base_table_->update();
}

void App::addPolynom() {
    QString pol = pol_data_->text();
    Polynomial* cur_polynomial = nullptr;
    try {
        cur_polynomial = new Polynomial(pol.toStdString());
    } catch (Error error) {
        if (error == Error::DoubleCoeff) {
            warning_text_ = "Double coefficient in polynomial";
            showWarning();
            return;
        }
        if (error == Error::DoubleSign) {
            warning_text_ = "Double sign in polynomial";
            showWarning();
            return;
        }
        if (error == Error::UnknownSymbol) {
            warning_text_ = "Unknown symbol in polynomial";
            showWarning();
            return;
        }
        if (error == Error::DoubleParam) {
            warning_text_ = "Double parameter in polynomial";
            showWarning();
            return;
        }
        if (error == Error::PowerInStrangePlace) {
            warning_text_ = "Power in wrong place";
            showWarning();
            return;
        }
        if (error == Error::ZeroPolynomial) {
            warning_text_ = "You set zero polynomial";
            showWarning();
            return;
        }
        if (error == Error::BigInt) {
            warning_text_ = "You set too big number";
            showWarning();
            return;
        }
        if (error == Error::SignInWrongPlace) {
            warning_text_ = "Sign in wrong place";
            showWarning();
            return;
        }
        //а даня самый лучший мальчик на планете а я такая дура собираюсь 40 минут его доставать посмотрим как он справится оставайтесь на связи дорогие подписчеки до урока осталось 2 минуты
        //но это не отменяет того что я его очень люблю!!!!!!!!!!!!!!!!!!!!!!!!! <3
    }
    pol = QString::fromStdString(cur_polynomial->getString());
    auto cur_pol = new QPushButton(base_table_);
    back_base_[cur_pol] = cur_polynomial;
    base_.push_back(cur_pol);
    base_.back()->setText(pol);
    base_.back()->setFont(QFont(family, 20));
    base_.back()->resize(480, 30);
    base_.back()->setStyleSheet("QPushButton {"
                                         "color: #fff;"
                                         "background: #9E9B98;"
                                         "border-radius: 5px;"
                                         "}");
    base_.back()->setProperty("id", (int)base_.size()-1);
    is_selected_[base_.back()] = 0;
    if (base_.size() == 1)
        base_.back()->move(10, 10);
    else {
        base_.back()->move(10, base_[base_.size()-2]->y() + 40);
        if (base_.back()->y() + 80 >= base_table_->height()) {
            base_table_->resize(500, base_table_->height() + 50);
        }
    }
    connect(base_.back(), SIGNAL(clicked(bool)), this, SLOT(clickedOnPolynom()));
    pol_data_->clear();
    updBaseTable();
}

void App::clickedOnPolynom() {
    QPushButton* cur_pol = base_[sender()->property("id").toInt()];
    std::string pol = base_[sender()->property("id").toInt()]->text().toStdString();
    if (is_selected_[cur_pol] == 0) {
        cur_pol->setStyleSheet("QPushButton {"
                               "color: #fff;"
                               "background: #686461;"
                               "border-radius: 5px;"
                               "}");
        is_selected_[cur_pol] = 1;
    } else if (is_selected_[cur_pol] == 1){
        cur_pol->setStyleSheet("QPushButton {"
                               "color: #fff;"
                               "background: #686461;"
                               "border-radius: 5px;"
                               "border: 3px solid #CEAD6D;"
                               "}");
        is_selected_[cur_pol] = 2;
    } else {
        cur_pol->setStyleSheet("QPushButton {"
                               "color: #fff;"
                               "background: #9E9B98;"
                               "border-radius: 5px;"
                               "}");
        is_selected_[cur_pol] = 0;
    }
    updBaseTable();
}

void App::deleteSelectedPol() {
    for (auto it = base_.begin(); it != base_.end(); ++it) {
        std::string s = (*it)->text().toStdString();
        if (is_selected_[(*it)]) {
            auto buf_pol = (*it);
            base_.erase(it);
            --it;
            delete back_base_[buf_pol];
            delete buf_pol;
        }
    }
    updBaseTable();
}

void App::getValueatPoint() {
    int selected_cnt = 0;
    QPushButton* cur;
    for (auto it = base_.begin(); it != base_.end(); ++it) {
        std::string s = (*it)->text().toStdString();
        if (is_selected_[(*it)]) {
            ++selected_cnt;
            cur = *it;
        }
    }
    if (selected_cnt != 1) {
        warning_text_ = "You must select one polynomial";
        showWarning();
        return;
    }
    Polynomial* cur_pol = back_base_[cur];
    std::vector <int> needed = cur_pol->paramCount();
    int cnt = 0;
    for (int i = 0; i < 26; ++i) {
        if (needed[i]) {
            ++cnt;
        }
    }
    if (cnt <= 13) {
        value_data_->resize(300, 40*cnt + 60);
        value_data_->move(100, 30);
    } else {
        value_data_->resize(430, 580);
        value_data_->move(35, 30);
    }
    int cur_dif = 10, cur_w = 10;
    for (int i = 0; i < 26; ++i) {
        if (needed[i] && cur_dif + 50 < value_data_->height()) {
            auto cur = new QLineEdit(value_data_);
            std::string s = "Set ";
            s += (char)('a' + i);
            s += " value";
            cur->resize(200, 30);
            cur->move(cur_w, cur_dif);
            cur->setPlaceholderText(QString::fromStdString(s));
            cur->setStyleSheet("QLineEdit {"
                               "border-radius: 3px;"
                               "background: #9E9B98;"
                               "color: #fff;"
                               "}");
            param_values_tablet_.push_back(cur);
            cur_dif += 40;
        } else if (needed[i]) {
            cur_dif = 10;
            cur_w = 220;
            auto cur = new QLineEdit(value_data_);
            std::string s = "Set ";
            s += (char)('a' + i);
            s += " value";
            cur->resize(200, 30);
            cur->move(cur_w, cur_dif);
            cur->setPlaceholderText(QString::fromStdString(s));
            cur->setStyleSheet("QLineEdit {"
                               "border-radius: 3px;"
                               "background: #9E9B98;"
                               "color: #fff;"
                               "}");
            param_values_tablet_.push_back(cur);
            cur_dif += 40;
        }
    }
    if (param_values_tablet_.size() > 13)
        set_param_values_->move(10, 530);
    else
        set_param_values_->move(10, cur_dif);
    value_data_->raise();
    value_data_->show();
}

void App::clearValueData() {
    for (int i = 0; i < param_values_tablet_.size(); ++i) {
        delete param_values_tablet_[i];
    }
    param_values_tablet_.resize(0);
}


void App::setParamValues() {
    std::vector <int> values(26, 0);
    for (int i = 0; i < param_values_tablet_.size(); ++i) {
        if (param_values_tablet_[i]) {
            std::string s = param_values_tablet_[i]->placeholderText().toStdString();
            int id = s[4] - 'a';
            values[id] = param_values_tablet_[i]->text().toInt();
        }
    }
    Polynomial* cur;
    for (auto it = base_.begin(); it != base_.end(); ++it) {
        std::string s = (*it)->text().toStdString();
        if (is_selected_[(*it)]) {
            cur = back_base_[(*it)];
            break;
        }
    }
    int res = cur->getValue(values);
    auto cur_polynomial = new Polynomial(std::to_string(res));

    QString pol  = QString::fromStdString(cur_polynomial->getString());
    auto cur_pol = new QPushButton(base_table_);
    back_base_[cur_pol] = cur_polynomial;
    base_.push_back(cur_pol);
    base_.back()->setText(pol);
    base_.back()->setFont(QFont(family, 20));
    base_.back()->resize(480, 30);
    base_.back()->setStyleSheet("QPushButton {"
                                         "color: #fff;"
                                         "background: #9E9B98;"
                                         "border-radius: 5px;"
                                         "}");
    base_.back()->setProperty("id", (int)base_.size()-1);
    is_selected_[base_.back()] = false;
    if (base_.size() == 1)
        base_.back()->move(10, 10);
    else {
        base_.back()->move(10, base_[base_.size()-2]->y() + 40);
        if (base_.back()->y() + 80 >= base_table_->height()) {
            base_table_->resize(500, base_table_->height() + 50);
        }
    }
    connect(base_.back(), SIGNAL(clicked(bool)), this, SLOT(clickedOnPolynom()));
    pol_data_->clear();
    updBaseTable();
    clearValueData();
    value_data_->hide();
}

void App::additionPolynomials() {
    int cnt = 0;
    for (auto it = base_.begin(); it != base_.end(); ++it) {
        std::string s = (*it)->text().toStdString();
        if (is_selected_[(*it)]) {
            ++cnt;
        }
    }
    if (cnt != 2 && cnt != 1) {
        warning_text_ = "You must select one or two polynomials";
        showWarning();
        return;
    }

    Polynomial* first, *second;
    if (cnt == 1) {
        for (auto it = base_.begin(); it != base_.end(); ++it) {
            std::string s = (*it)->text().toStdString();
            if (is_selected_[(*it)]) {
                first = back_base_[(*it)];
                second = back_base_[(*it)];
            }
        }
    } else {
        for (auto it = base_.begin(); it != base_.end(); ++it) {
            std::string s = (*it)->text().toStdString();
            if (is_selected_[(*it)]) {
                if (first == nullptr) {
                    first = back_base_[(*it)];
                } else {
                    second = back_base_[(*it)];
                }
            }
        }
    }
    if (cnt != 1) {
        std::string res = first->addition(second);
        sum_pol = new Polynomial(res);
    } else {
        Polynomial* cur = new Polynomial("2");
        sum_pol = first->multiplication(cur);
        delete cur;
    }
    dialog_text_->setText(QString::fromStdString("Add " + sum_pol->getString() + " to base?"));
    dialog_text_->resize(std::max((int)400, (int)dialog_text_->text().size() * 5), 120);
    dialog_window_->raise();
    dialog_window_->show();
}

void App::accept() {
    dialog_window_->hide();
    QString pol;
    auto cur_pol = new QPushButton(base_table_);
    if (sum_pol != nullptr) {
        pol  = QString::fromStdString(sum_pol->getString());
        back_base_[cur_pol] = sum_pol;
    }
    if (mul_pol != nullptr) {
        pol  = QString::fromStdString(mul_pol->getString());
        back_base_[cur_pol] = mul_pol;
    }
    if (der_pol != nullptr) {
        pol  = QString::fromStdString(der_pol->getString());
        back_base_[cur_pol] = der_pol;
    }
    base_.push_back(cur_pol);
    base_.back()->setText(pol);
    base_.back()->setFont(QFont(family, 20));
    base_.back()->resize(480, 30);
    base_.back()->setStyleSheet("QPushButton {"
                                "color: #fff;"
                                "background: #9E9B98;"
                                "border-radius: 5px;"
                                "}");
    base_.back()->setProperty("id", (int)base_.size()-1);
    is_selected_[base_.back()] = false;
    if (base_.size() == 1)
        base_.back()->move(10, 10);
    else {
        base_.back()->move(10, base_[base_.size()-2]->y() + 40);
        if (base_.back()->y() + 80 >= base_table_->height()) {
            base_table_->resize(500, base_table_->height() + 50);
        }
    }
    connect(base_.back(), SIGNAL(clicked(bool)), this, SLOT(clickedOnPolynom()));
    pol_data_->clear();
    updBaseTable();
    if (sum_pol != nullptr) {
        sum_pol = nullptr;
    }
    if (mul_pol != nullptr) {
        mul_pol = nullptr;
    }
    if (der_pol != nullptr) {
        der_pol = nullptr;
    }
}

void App::reject() {
    dialog_window_->hide();
    if (sum_pol != nullptr) {
        Polynomial* q = sum_pol;
        sum_pol = nullptr;
        delete q;
    }
    if (mul_pol != nullptr) {
        Polynomial* q = mul_pol;
        mul_pol = nullptr;
        delete q;
    }
    if (der_pol != nullptr) {
        Polynomial* q = der_pol;
        der_pol = nullptr;
        delete q;
    }
}

void App::multiplyPolynomials() {
    int cnt = 0;
    for (auto it = base_.begin(); it != base_.end(); ++it) {
        std::string s = (*it)->text().toStdString();
        if (is_selected_[(*it)]) {
            ++cnt;
        }
    }
    if (cnt == 0 || cnt > 2) {
        warning_text_ = "You must select one or two polynomials";
        showWarning();
        return;
    }
    Polynomial* first, *second;
    if (cnt == 1) {
        for (auto it = base_.begin(); it != base_.end(); ++it) {
            std::string s = (*it)->text().toStdString();
            if (is_selected_[(*it)]) {
                first = back_base_[(*it)];
                second = back_base_[(*it)];
            }
        }
    } else {
        for (auto it = base_.begin(); it != base_.end(); ++it) {
            std::string s = (*it)->text().toStdString();
            if (is_selected_[(*it)]) {
                if (first == nullptr) {
                    first = back_base_[(*it)];
                } else {
                    second = back_base_[(*it)];
                }
            }
        }
    }
    mul_pol = first->multiplication(second);
    mul_pol->normalizePol();
    dialog_text_->setText(QString::fromStdString("Add " + mul_pol->getString() + " to base?"));
    dialog_text_->resize(std::max((int)400, (int)dialog_text_->text().size() * 11), 120);
    dialog_window_->raise();
    dialog_window_->show();
}

void App::comparisonPolynomials() {
    int cnt = 0;
    for (auto it = base_.begin(); it != base_.end(); ++it) {
        std::string s = (*it)->text().toStdString();
        if (is_selected_[(*it)]) {
            ++cnt;
        }
    }
    if (cnt != 2) {
        warning_text_ = "You must select two polynomials";
        showWarning();
        return;
    }
    Polynomial* first, *second;
    for (auto it = base_.begin(); it != base_.end(); ++it) {
        std::string s = (*it)->text().toStdString();
        if (is_selected_[(*it)]) {
            if (first == nullptr) {
                first = back_base_[(*it)];
            } else {
                second = back_base_[(*it)];
            }
        }
    }
    bool is_equal = first->equal(second);
    if (is_equal) {
        warning_text_ = "Polynomials are equal!";
        showWarning();
        return;
    }
    warning_text_ = "Polynomials aren't equal!";
    showWarning();
}

void App::solvePolynomial() {
    int cnt = 0;
    for (auto it = base_.begin(); it != base_.end(); ++it) {
        std::string s = (*it)->text().toStdString();
        if (is_selected_[(*it)]) {
            ++cnt;
        }
    }
    if (cnt != 1) {
        warning_text_ = "You must select one polynomial";
        showWarning();
        return;
    }
    Polynomial* pol;
    for (auto it = base_.begin(); it != base_.end(); ++it) {
        std::string s = (*it)->text().toStdString();
        if (is_selected_[(*it)]) {
            pol = back_base_[(*it)];
        }
    }
    if (!pol->oneVariable()) {
        warning_text_ = "You must select one variable polynomial";
        showWarning();
        return;
    }
    std::vector <int> res = pol->solves();
    std::set<int> ans;
    for (auto e : res) {
        ans.insert(e);
    }
    std::string s;
    if (ans.empty()) {
        s = "This polynomial hasn't any solves";
    } else {
        s = "Solves of polynomial are ";
        for (auto e : ans) {
            s += std::to_string(e);
            s += " ";
        }
    }
    warning_text_ = s;
    showWarning();
}

void App::derivativePolynomial() {
    int cnt = 0;
    for (auto it = base_.begin(); it != base_.end(); ++it) {
        std::string s = (*it)->text().toStdString();
        if (is_selected_[(*it)]) {
            ++cnt;
        }
    }
    if (cnt != 1) {
        warning_text_ = "You must select one polynomial";
        showWarning();
        return;
    }
    for (auto it = base_.begin(); it != base_.end(); ++it) {
        std::string s = (*it)->text().toStdString();
        if (is_selected_[(*it)]) {
            der_data_pol = back_base_[(*it)];
            break;
        }
    }
    der_data_tablet_->show();
}

void App::setDerSettings() {
    std::string par = der_parameter_->text().toStdString();
    if (par.size() != 1 || (par[0] < 'a' || par[0] > 'z')) {
        warning_text_ = "You set wrong parameter!";
        showWarning();
        return;
    }
    int par_id = par[0] - 'a';
    if (!der_data_pol->inPolynomial(par_id)) {
        warning_text_ = "You set wrong parameter!";
        showWarning();
        return;
    }
    int der_order = der_order_->text().toInt();
    der_pol = der_data_pol->derivative(par_id, der_order);
    der_data_tablet_->hide();
    dialog_text_->setText(QString::fromStdString("Add " + der_pol->getString() + " to base?"));
    dialog_text_->resize(std::max((int)400, (int)dialog_text_->text().size() * 12), 120);
    dialog_window_->raise();
    dialog_window_->show();
    der_order_->clear();
    der_parameter_->clear();
}

void App::divisionPolynomials() {
    int cnt = 0;
    for (auto it = base_.begin(); it != base_.end(); ++it) {
        std::string s = (*it)->text().toStdString();
        if (is_selected_[(*it)]) {
            ++cnt;
        }
    }
    if (cnt != 2) {
        warning_text_ = "You must select two polynomials";
        showWarning();
        return;
    }
    Polynomial *first = nullptr, *second = nullptr;
    for (auto it = base_.begin(); it != base_.end(); ++it) {
        std::string s = (*it)->text().toStdString();
        if (is_selected_[*it] > 0) {
            if (is_selected_[(*it)] == 1) {
                first = back_base_[*it];
            } else {
                second = back_base_[*it];
            }
        }
    }
    if (first == nullptr || second == nullptr) {
        warning_text_ = "You must select one dividend and one divider";
        showWarning();
        return;
    }
    if (second->getString() == "0") {
        warning_text_ = "∞ ;)";
        showWarning();
        return;
    }
    if (!first->canDivPolynomials(second)) {
        warning_text_ = "You chose wrong polynomials";
        showWarning();
        return;
    }
    std::pair<Polynomial*, Polynomial*> res =  first->divisionPolynomials(second);
    auto cur_pol = new QPushButton(base_table_);
    QString pol = QString::fromStdString(res.first->getString());
    back_base_[cur_pol] = res.first;
    base_.push_back(cur_pol);
    base_.back()->setText(pol);
    base_.back()->setFont(QFont(family, 20));
    base_.back()->resize(480, 30);
    base_.back()->setStyleSheet("QPushButton {"
                                "color: #fff;"
                                "background: #9E9B98;"
                                "border-radius: 5px;"
                                "}");
    base_.back()->setProperty("id", (int)base_.size()-1);
    is_selected_[base_.back()] = 0;
    if (base_.size() == 1)
        base_.back()->move(10, 10);
    else {
        base_.back()->move(10, base_[base_.size()-2]->y() + 40);
        if (base_.back()->y() + 80 >= base_table_->height()) {
            base_table_->resize(500, base_table_->height() + 50);
        }
    }
    connect(base_.back(), SIGNAL(clicked(bool)), this, SLOT(clickedOnPolynom()));
    pol_data_->clear();
    auto cur_pol_2 = new QPushButton(base_table_);
    pol = QString::fromStdString(res.second->getString());
    back_base_[cur_pol_2] = res.second;
    base_.push_back(cur_pol_2);
    base_.back()->setText(pol);
    base_.back()->setFont(QFont(family, 20));
    base_.back()->resize(480, 30);
    base_.back()->setStyleSheet("QPushButton {"
                                "color: #fff;"
                                "background: #9E9B98;"
                                "border-radius: 5px;"
                                "}");
    base_.back()->setProperty("id", (int)base_.size()-1);
    is_selected_[base_.back()] = 0;
    if (base_.size() == 1)
        base_.back()->move(10, 10);
    else {
        base_.back()->move(10, base_[base_.size()-2]->y() + 40);
        if (base_.back()->y() + 80 >= base_table_->height()) {
            base_table_->resize(500, base_table_->height() + 50);
        }
    }
    connect(base_.back(), SIGNAL(clicked(bool)), this, SLOT(clickedOnPolynom()));
    pol_data_->clear();
    updBaseTable();

}

void App::saveToFile() {
    QString file = QFileDialog::getSaveFileName(nullptr, "Save to", "", "*.txt");
    QFile outFile(file);
    if (!outFile.open(QIODevice::WriteOnly)) return;
    QTextStream ostream(&outFile);
    std::string out = "";
    for (auto e : base_) {
        out += back_base_[e]->getString() + '\n';
    }
    ostream << QString::fromStdString(out);
    outFile.close();
}

void App::loadFromFile() {
    QString file = QFileDialog::getOpenFileName(nullptr, "Choose txt file", "", "*.txt");
    QFile in(file);
    if (!in.open(QIODevice::ReadOnly)) return;
    while (!in.atEnd()) {
        std::string res = in.readLine().toStdString();
        res.pop_back();
        Polynomial* cur = nullptr;
        try {
            cur = new Polynomial(res);
        } catch (Error error) {
            res = "";
            continue;
        }
        QString pol = QString::fromStdString(cur->getString());
        auto cur_pol = new QPushButton(base_table_);
        back_base_[cur_pol] = cur;
        base_.push_back(cur_pol);
        base_.back()->setText(pol);
        base_.back()->setFont(QFont(family, 20));
        base_.back()->resize(480, 30);
        base_.back()->setStyleSheet("QPushButton {"
                                    "color: #fff;"
                                    "background: #9E9B98;"
                                    "border-radius: 5px;"
                                    "}");
        base_.back()->setProperty("id", (int)base_.size()-1);
        is_selected_[base_.back()] = false;
        if (base_.size() == 1)
            base_.back()->move(10, 10);
        else {
            base_.back()->move(10, base_[base_.size()-2]->y() + 40);
            if (base_.back()->y() + 80 >= base_table_->height()) {
                base_table_->resize(500, base_table_->height() + 50);
            }
        }
        connect(base_.back(), SIGNAL(clicked(bool)), this, SLOT(clickedOnPolynom()));
        pol_data_->clear();
        updBaseTable();

    }
    in.close();
}