#include "widget.h"
#include "ui_widget.h"
#include <cmath>

int num = 0;
double z, s, c, v, a, b;
int piece_time[MAX] = { 0 };
double w[MAX] = { 0 };
double W[MAX] = { 0 };
double P[MAX] = { 0 };
double T[MAX] = { 0 };
double t = 0;
double sum = 0;
double F = 0;

double before(double r)
{
    double ret = num * c + (r - 1) * z;
    return ret;
}

double normal()
{
    double ret = num * v;
    return ret;
}

double delay(double r)
{
    double ret = (num + 1 - r) * s;
    return ret;
}

double getmin(double d1, double d2, double d3)
{
    double ret = (d1 < d2) ? d1 : d2;
    ret = (ret < d3) ? ret : d3;
    return ret;
}

double GetW(int r)
{
    if (r == num)
    {
        return  pow(r, a) * w[r - 1];
    }
    else
    {
        double xx = 0;
        for (int j = r; j < v; j++)
        {
            xx += GetW(j + 1);
        }
        return pow(r, a) * (w[r - 1] + b * xx);
    }
}

double GetF()
{
    double sum = 0;
    for (int i = 0; i < num; ++i)
    {
        sum += W[i] * piece_time[i];
    }
    return sum;
}

double Getp(int r)
{
    return (piece_time[r] + b * t) * pow(r + 1, a);
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    num = ui->num_lineedit->text().toInt();
    if (!num)
    {
        QMessageBox::information(nullptr, nullptr, "num is 0");
    }

    QMessageBox::information(nullptr, nullptr, "请输入加工各工件所需要的时间");
    QString piece_time_str = ui->piece_time_textedit->toPlainText();
    QStringList piece_time_list = piece_time_str.split(",");
    for (int i = 0; i < num; ++i)
    {
        piece_time_str = piece_time_list.at(i);
        piece_time[i] = piece_time_str.toInt();
    }

    z = ui->alpha_lineEdit->text().toDouble();
    s = ui->beta_lineEdit->text().toDouble();
    c = ui->delta_lineEdit->text().toDouble();
    v = ui->gamma_lineEdit->text().toDouble();
    a = ui->a_lineEdit->text().toDouble();
    b = ui->b_lineEdit->text().toDouble();

    //w
    for (int r = 0; r < num; ++r)
    {
        double d1 = before(r + 1);
        double d2 = normal();
        double d3 = delay(r + 1);
        w[r] = getmin(d1, d2, d3);
    }

    //W
    for (int r = 0; r < num; ++r)
    {
        W[r] = GetW(r + 1);
        double ssss = W[r];
        ssss++;
    }

    F = GetF();
    ui->F_lineEdit->setText(QString::number(F, 'g', 8));

    for (int r = 0; r < num; ++r)
    {
        P[r] = Getp(r);
        t += P[r];
        T[r] = t;
    }

    for(int r = 0; r < num; ++r)
    {
        if(piece_time[r] < T[r])
        {
            ui->before_listWidget->addItem(QString::number(r+1));
        }
        else if(piece_time[r] > T[r])
        {
            ui->delay_listWidget->addItem(QString::number(r+1));
        }
        else
        {
            ui->on_listWidget->addItem(QString::number(r+1));
        }
    }
}
