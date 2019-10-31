#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tools.h"
#include <qDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Wf_calculate_clicked()
{
    Wf.setUt(ui->ut_value->value());
    Wf.setNd(ui->Nd_value->value());
    Wf.setN(ui->N_value->value());
    parse_double parse(ui->u2_value->toPlainText());
    std::vector<double> u2_values;
    while (parse.next()) {
        u2_values.push_back(parse.getValue());
//        qDebug() << parse.getValue();
    }
    Wf.setU2(u2_values);
    ui->Wf_result->setText(QString::number(Wf.getValue()));
}

void MainWindow::on_SCF_calculate_clicked()
{
    SCF.setCi(ui->CI_value->value());
    SCF.setOm(ui->OM_value->value());
    ui->SCF_result->setText(QString::number(SCF.getValue()));
}

void MainWindow::on_EF_calculate_clicked()
{
    EF.setCaCo3(ui->CaCO3_value->value());
    EF.setOm(ui->OM_value->value());
    EF.setSa(ui->Sa_value->value());
    EF.setSaDivideCi(ui->Sa_divide_CI_value->value());
    EF.setSi(ui->Si_value->value());
    ui->EF_result->setText(QString::number(EF.getValue()));
}

void MainWindow::on_COG_calculate_clicked()
{
    COG.setPd(ui->Pd_value->value());
    COG.setPgca(ui->Pgca_value->value());
    COG.setPgcb(ui->Pgcb_value->value());
    COG.setSa(ui->Sa_value->value());
    COG.setSc(ui->SC_value->value());
    ui->COG_result->setText(QString::number(COG.getValue()));
}

void MainWindow::on_WF_calculate_clicked()
{
    WF.setDenisity(ui->density_value->value());
    WF.setETp(ui->ETp_value->value());
    WF.setG(ui->g_value->value());
    WF.setNd(ui->Nd_value_2->value());
    WF.setRd(ui->Rd_value->value());
    WF.setRPlusI(ui->R_add_I_value->value());
    WF.setSd(ui->SD_value->value());
    WF.setWf(ui->Wf_value->value());
    ui->WF_result->setText(QString::number(WF.getValue()));
}

void MainWindow::on_Q_calculate_clicked()
{
    Q.setQp(Qp);
    Q.setQx(Qx);
    Q_.setQp(Qp);
    Q_.setQx(Qx);
    ui->Q_value->setText(QString::number(Q.getValue()));
    ui->Q_plus_value->setText(QString::number(Q_.getValue()));
}

void MainWindow::on_write_into_Wf_clicked()
{
    ui->Wf_value->setValue(Wf.getValue());
}

void MainWindow::on_write_into_Qp_clicked()
{
    Qp.setEf(EF);
    Qp.setK(ui->K_value->value());
    Qp.setScf(SCF);
    Qp.setWF(WF);
    Qp.setX(ui->x_value->value());
    ui->Qp_value->setValue(Qp.getValue());
}

void MainWindow::on_write_into_Qx_clicked()
{
    Qx.setCog(COG);
    Qx.setEf(EF);
    Qx.setK(ui->K_value->value());
    Qx.setScf(SCF);
    Qx.setWf(WF);
    Qx.setX(ui->x_value->value());
    ui->Qx_value->setValue(Qx.getValue());
}

void MainWindow::on_pushButton_clicked()
{
    on_Wf_calculate_clicked();
    on_SCF_calculate_clicked();
    on_EF_calculate_clicked();
    on_COG_calculate_clicked();
    on_write_into_Wf_clicked();
    on_WF_calculate_clicked();
    on_write_into_Qx_clicked();
    on_write_into_Qp_clicked();
    on_Q_calculate_clicked();
}
