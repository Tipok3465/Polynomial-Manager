#include "header.h"
#include "Polynomial.h"

class App : public QMainWindow {
    Q_OBJECT

public:
    App(int width, int height);
    ~App() override;
    void render() {
        window_->show();
    };
private slots:
    void updBaseTable();
    void addPolynom();
    void clickedOnPolynom();
    void deleteSelectedPol();
    void showWarning();
    void getValueatPoint();
    void setParamValues();
    void clearValueData();
    void additionPolynomials();
    void accept();
    void reject();
    void multiplyPolynomials();
    void comparisonPolynomials();
    void solvePolynomial();
    void derivativePolynomial();
    void setDerSettings();
    void divisionPolynomials();
    void saveToFile();
    void loadFromFile();
private:
    QMainWindow* window_;
    QString family;
    QLabel* background_;
    QLabel* base_table_header_;
    QLabel* base_table_;
    QScrollArea* base_table_scroll_;
    QLabel* header_pol_adding_;
    QLineEdit* pol_data_;
    QPushButton* set_pol_;
    QPushButton* del_pol_;
    QPushButton* save_polynomial_;
    QPushButton* delete_polynomial_;
    QPushButton* download_polynomial_;
    QLabel* header_operations_;
    QPushButton* point_value_;
    QPushButton* addition_;
    QPushButton* multiplication_;
    QPushButton* comparison_;
    QPushButton* derivative_;
    QPushButton* division_;
    QPushButton* equation_solves_;
    std::vector<QPushButton*> base_;
    std::map<QPushButton*, int> is_selected_;
    std::map<QPushButton*, Polynomial*> back_base_;
    QMainWindow* warning_;
    QLabel* warning_label_;
    std::string warning_text_;
    QLabel* value_data_;
    std::vector<QLineEdit*> param_values_tablet_;
    QPushButton* set_param_values_;
    QLabel* dialog_window_;
    QLabel* dialog_text_;
    QPushButton* accept_;
    QPushButton* reject_;
    Polynomial* sum_pol = nullptr;
    Polynomial* mul_pol = nullptr;
    Polynomial* der_data_pol = nullptr;
    Polynomial* der_pol = nullptr;
    QScrollArea* dialog_window_scroll_;
    QMainWindow* der_data_tablet_;
    QLineEdit* der_parameter_;
    QLineEdit* der_order_;
    QPushButton* der_data_setter_;
};