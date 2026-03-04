#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "calculatormodel.h"

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class Calculator: public QWidget
{
    Q_OBJECT
public:
    Calculator();
    void UpdateDisplay(const QString& text);
    void AddToDisplay(const QString& text);
    void ClearDisplay();

    void UpdateActiveNumber(const QString& text);
    void AddToActiveNumber(const QString& text);
    void ClearActiveNumber();

private:
    QLabel* display;
    QLabel* active_number;

    CalculatorModel model_;

    void SetupUI();

    void SetupDisplay(QGridLayout* layout);
    void SetupActiveNumber(QGridLayout* layout);
    void SetupButtons(QGridLayout* layout);

    QPushButton* CreateButton(const QString& str);
public slots:
    void onButtonClicked(const QString& buttonText) {
        try {
            CalculatorModel::Display result = model_.PreprocessInput(buttonText);
            UpdateDisplay(result.expression);
            UpdateActiveNumber(result.result);
        } catch (const std::exception& e) {
            //ShowError(e.what());
        }
    }
};

#endif // CALCULATOR_H
