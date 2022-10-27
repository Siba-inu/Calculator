#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void translate();

    void addFigure(char figure);

    void on_btnOne_clicked();

    void on_btnTwo_clicked();

    void on_btnthreee_clicked();

    void on_btnFour_clicked();

    void on_btnFive_clicked();

    void on_btnSix_clicked();

    void on_btnSeven_clicked();

    void on_btnEigtht_clicked();

    void on_btnNine_clicked();

    void on_btnPlus_clicked();

    void on_btnMin_clicked();

    void on_btnMultiply_clicked();

    void on_btnDivide_clicked();

    void on_btnNull_clicked();

    void on_btnRemove_clicked();

    void on_btnEqual_clicked();

    void calculate();

private:
    Ui::MainWindow *ui;
    int number = 0;
    QVector<QString> figures;
};
#endif // MAINWINDOW_H
