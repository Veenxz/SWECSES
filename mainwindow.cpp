#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tools.h"
#include <QDebug>

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

void MainWindow::setInstructionText(QString str)
{
    this->ui->instructions->setText(str);
}
/** 下标
 * @brief sub
 * @param s
 * @return
 */
QString sub(QString s) {
    return QString("<sub>") + s + QString("</sub>");
}
/** 上标
 * @brief sup
 * @param s
 * @return
 */
QString sup(QString s) {
    return QString("<sup>") + s + QString("</sup>");
}
/** 换行
 * @brief br
 * @return
 */
QString br() {
    return QString("<br>");
}

/**
    Wf的说明
 * @brief MainWindow::on_pushButton_2_clicked
 */
void MainWindow::on_pushButton_2_clicked()
{
    auto text = QString("Wf: 风因子<br>u<sub>2</sub>: 2m处的风速(m/s)") +
           QString("<br>u<sub>t</sub>: 2m处的临界风速(假定5m/s)<br>") +
           QString("N: 风速的观察次数(一般用试验期间天数1~15d的500次测定数值)<br>") +
           QString("N<sub>d</sub>: 试验期间天数");
    this->setInstructionText(text);
}
/**
  SCF的输入说明
 * @brief MainWindow::on_pushButton_3_clicked
 */
void MainWindow::on_pushButton_3_clicked()
{
    auto text = QString("土壤结皮因子SCF<br>CI——粘土含量（%）<br>OM——有机质含量（%）");
    this->setInstructionText(text);
}
/**
  EF的输入说明
 * @brief MainWindow::on_pushButton_4_clicked
 */
void MainWindow::on_pushButton_4_clicked()
{
    auto text = QString("EF:土壤可蚀性成分<br>Sa——沙粒含量（%）<br>Si——粉粒含量（%）<br>Sa/CI——沙粒与粘粒比例<br>CaCO<sub>3</sub>——碳酸钙含量（%）");
    this->setInstructionText(text);
}
/**
  COG的输入说明
 * @brief MainWindow::on_pushButton_5_clicked
 */
void MainWindow::on_pushButton_5_clicked()
{
    auto text = QString("COG：植被因子<br>P<sub>gca</sub>——植物生长系数a<br>P<sub>gcb</sub>——植物生长系数b<br>SC——土壤表层平铺覆盖率（%）<br>Pd——种植天数<br>SA——倾斜覆盖面积＝1m<sup>2</sup>上直立秸秆数量×秸秆平均直径（cm）×直立高度（cm）<br>");
    setInstructionText(text);
}
/**
 * WF的输入说明
 * @brief MainWindow::on_pushButton_6_clicked
 */
void MainWindow::on_pushButton_6_clicked()
{
    auto text = QString("WF——气象因子（kg/m)<br>Wf——风因子（m/s）<sup>3</sup>；（该项前面计算过）<br>ρ——空气密度（kg/m<sup>3</sup>）；<br>g——重力加速度（m/s<sup>2</sup>）；<br>SD——雪覆盖因子；<br>ETp——潜在相对蒸散量（mm）；<br>Rd——降雨日数和/或灌溉次数；<br>R+I——降雨量和灌溉量（mm）；<br>N<sub>d</sub>——日数（一般为15d）。<br>");
    setInstructionText(text);
}
/**
  Q和Q`的输入说明
 * @brief MainWindow::on_pushButton_7_clicked
 */
void MainWindow::on_pushButton_7_clicked()
{
    auto text = QString("x为地块长度（m），K′——土壤粗糙度<br>Qx为土壤风蚀量（g·m<sup>-2</sup>·a）<br>Qx计算公式与Qx一致，只是COG直接数值为1， WF中Rd——降雨日数次数；R+I——降雨量（mm）；<br>土壤保持量Q和土壤保有率Q’ ");
    setInstructionText(text);
}
