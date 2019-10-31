#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tools.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_SCF_calculate_clicked();

    void on_EF_calculate_clicked();

    void on_COG_calculate_clicked();

    void on_WF_calculate_clicked();

    void on_Q_calculate_clicked();

    void on_write_into_Wf_clicked();

    void on_Wf_calculate_clicked();

    void on_write_into_Qp_clicked();

    void on_write_into_Qx_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    _Wf Wf;
    _SCF SCF;
    _EF EF;
    _COG COG;
    _WF WF;
    _Qx Qx;
    _Qp Qp;
    _Q Q;
    _Q_ Q_;
};

#endif // MAINWINDOW_H
