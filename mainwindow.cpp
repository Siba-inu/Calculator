#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStack>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::addFigure(char figure)
{
    QString val = ui->label->text();
    val.append(figure);
    if (figures.size() == 0 && val.front() == '0' && (figure != '*' && figure != '/'))
        val.remove(0, 1);
    ui->label->setText(val);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnOne_clicked()
{
    addFigure('1');
}

void MainWindow::on_btnTwo_clicked()
{
    addFigure('2');
}

void MainWindow::on_btnthreee_clicked()
{
    addFigure('3');
}

void MainWindow::on_btnFour_clicked()
{
    addFigure('4');
}

void MainWindow::on_btnFive_clicked()
{
    addFigure('5');
}

void MainWindow::on_btnSix_clicked()
{
    addFigure('6');
}

void MainWindow::on_btnSeven_clicked()
{
    addFigure('7');
}

void MainWindow::on_btnEigtht_clicked()
{
    addFigure('8');
}

void MainWindow::on_btnNine_clicked()
{
    addFigure('9');
}

void MainWindow::on_btnPlus_clicked()
{
    QString s = ui->label->text();
    if (s.back().isDigit())
    {
        addFigure('+');
        QString str;
        for (int i = s.size() - 1; i >= 0; i--)
        {
            if (!s[i].isDigit()) break;
            str.push_front(s[i]);
        }
        figures.push_back(str);
        figures.push_back("+");
    }

}

void MainWindow::on_btnMin_clicked()
{
    QString s = ui->label->text();
    if (s.back().isDigit())
    {
        addFigure('-');
        QString str;
        for (int i = s.size() - 1; i >= 0; i--)
        {
            if (!s[i].isDigit()) break;
            str.push_front(s[i]);
        }
        figures.push_back(str);
        figures.push_back("-");
    }

}

void MainWindow::on_btnMultiply_clicked()
{
    QString s = ui->label->text();
    if (s.front().isDigit())
    { 
        QString str;
        for (int i = s.size() - 1; i >= 0; i--)
        {
            if (!s[i].isDigit() && !(s[i] == '0' && i == 0)) break;
            str.push_front(s[i]);
        }
        s.append('*');
        figures.push_back(str);
        figures.push_back("*");
    }
    ui->label->setText(s);

}

void MainWindow::on_btnDivide_clicked()
{
    QString s = ui->label->text();
    if (s.front( ).isDigit())
    {     
        QString str;
        for (int i = s.size() - 1; i >= 0; i--)
        {
            if (!s[i].isDigit()) break;
            str.push_front(s[i]);

        }
        s.append('/');
        figures.push_back("/");
        figures.push_back(str);
    }
    ui->label->setText(s);

}

void MainWindow::on_btnNull_clicked()
{
    addFigure('0');
}

void MainWindow::on_btnRemove_clicked()
{
    ui->label->setText("0");
    figures.clear();
}

bool isStringDigit(QString a)
{
    for (int i = 0; i < a.size(); i++)
    {
        if (!a[i].isDigit()) return false;
    }
    return true;
}

void MainWindow::on_btnEqual_clicked()
{
    QString s = ui->label->text();
    QString str;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        if (!s[i].isDigit()) break;
        str.push_front(s[i]);
    }
    figures.push_back(str);
    translate();
    calculate();
    std::string f = std::to_string(number);
    QString a = QString::fromStdString(f);
    ui->label->setText(QString::fromStdString(f));
    figures.clear();
    figures.push_back(a);
}

int prior(QString a)
{
    if (a == "+" || a == "-") return 0;
    if (a == "*" || a == "/") return 1;
}

void MainWindow::translate()
{
    QStack<QString> mStack;
    QVector<QString> output;

    for (int i = 0; i < figures.size(); i++)
    {
        if (isStringDigit(figures[i]))
            output.push_back(figures[i]);
        else
        {
            if (mStack.isEmpty())
                mStack.push(figures[i]);
            else
            {
                if (prior(figures[i]) <= prior(mStack.top()))
                {
                    QString a = figures[i];
                    while(!mStack.isEmpty())
                    {
                        if (prior(a) > prior(mStack.top()))
                            break;
                        output.push_back(mStack.top());
                        mStack.pop();
                    }
                    mStack.push(a);
                }
                if (prior(figures[i]) > prior(mStack.top()))
                   mStack.push(figures[i]);
            }
        }
    }
    figures.clear();
    for (auto &i : output)
        figures.push_back(i);

    while (!mStack.isEmpty())
    {
        figures.push_back(mStack.back());
        mStack.pop();
    }

}

int calc(int a, int b, QString op)
{
    if (op == '*') return a * b;
    if (op == '/') return a / b;
    if (op == '+') return a + b;
    if (op == '-') return a - b;
}

void MainWindow::calculate()
{
    QStack<QString> mStack;
    for (int i = 0; i < figures.size(); i++)
    {
        if (isStringDigit(figures[i]))
            mStack.push(figures[i]);
        else
        {
            QString a = mStack.back();
            mStack.pop();
            QString b = mStack.back();
            mStack.pop();
            int result = calc(b.toInt(), a.toInt(), figures[i]);
            std::string s = std::to_string(result);
            QString str = QString::fromStdString(s);
            mStack.push(str);
        }
    }
    number = mStack.top().toInt();
}
