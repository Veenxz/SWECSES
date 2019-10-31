//
// Created by hp on 2019/10/23.
//

#ifndef DONGMENDB_TOOLS_H
#define DONGMENDB_TOOLS_H


#include <cmath>
#include <vector>
#include <cstring>
#include <QString>

struct _base_value {
    virtual double getValue() const = 0;

    double operator*(const _base_value &v) const {
        return getValue() * v.getValue();
    }

    double operator*(const double &v) const {
        return getValue() * v;
    }

    friend double operator*(const double &v, const _base_value &value) {
        return v * value.getValue();
    }

    double operator-(const _base_value &v) const {
        return getValue() - v.getValue();
    }


    double operator-(const double &v) const {
        return getValue() - v;
    }

    friend double operator-(const double &v, const _base_value &value) {
        return v - value.getValue();
    }

    double operator+(const _base_value &v) const {
        return getValue() + v.getValue();
    }

    double operator+(double &v) const {
        return v + getValue();
    }

    friend double operator+(const double &v, const _base_value &value) {
        return v + value.getValue();
    }

    double operator/(const _base_value &value) const {
        return getValue() / value.getValue();
    }

    double operator/(const double &v) const {
        return getValue() / v;
    }

    friend double operator/(const double &v, const _base_value &value) {
        return v / value.getValue();
    }
};

struct parse_double : _base_value {
    char *parse_str;
    int len, nowIter;
    double nowValue;

    parse_double(const char *s) {
        len = strlen(s), nowIter = 0;
        parse_str = new char[len];
        strcpy(parse_str, s);
    }

    parse_double(QString s) {
        len = s.size();
        nowIter = 0;
        parse_str = new char[len];
        for (int i = 0;i < len; ++i)
            parse_str[i] = char(s[i].unicode());
    }

    double getValue() const override {
        return nowValue;
    }

    bool next() {
        nowValue = 0;
        int minus = 1;
        double temp = 1;
        bool afterPoint = false, catchValue = false;
        for (; nowIter < len; ++nowIter) {
            char c = parse_str[nowIter];
            if (c == '-') {
                catchValue = true;
                minus = -1;
            } else if (c >= '0' && c <= '9') {
                catchValue = true;
                if (afterPoint)temp /= 10.0;
                nowValue = nowValue * 10 + c - '0';
            } else if (c == '.') {
                catchValue = true;
                afterPoint = true;
            } else if (catchValue)break;
        }
        if (!catchValue)return false;
        nowValue = nowValue * temp * minus;
        return true;
    }
};

struct _Wf : public _base_value {
    double ut, Nd, N;
    std::vector<double> u2;

    _Wf() = default;

    double getUt() const {
        return ut;
    }

    void setUt(double ut) {
        _Wf::ut = ut;
    }

    double getNd() const {
        return Nd;
    }

    void setNd(double nd) {
        Nd = nd;
    }

    double getN() const {
        return N;
    }

    void setN(double n) {
        N = n;
    }

    const std::vector<double> &getU2() const {
        return u2;
    }

    void setU2(const std::vector<double> &u2) {
        _Wf::u2 = u2;
    }

    double getValue() const override {
        double sum = 0;
        for (int i = 0; i < u2.size(); ++i) sum += u2[i] * (u2[i] - ut) * (u2[i] - ut);
        return sum * Nd / N;
    }
};

struct _SCF : public _base_value {
    double CI, OM;

    _SCF() = default;

    double getValue() const override {
        return 1.0 / (1.0 + 0.0066 * CI * CI + 0.021 * OM * OM);
    }

    double getCi() const {
        return CI;
    }

    void setCi(double ci) {
        CI = ci;
    }

    double getOm() const {
        return OM;
    }

    void setOm(double om) {
        OM = om;
    }
};

struct _EF : public _base_value {
    double Sa, Sa_divide_CI, Si, CaCO3, OM;

    _EF() = default;

    double getValue() const override {
        return (29.09 + 0.31 * Sa + 0.17 * Si + 0.33 * Sa_divide_CI - 2.59 * OM - 0.95 * CaCO3) / 100;
    }

    double getSa() const {
        return Sa;
    }

    void setSa(double sa) {
        Sa = sa;
    }

    double getSaDivideCi() const {
        return Sa_divide_CI;
    }

    void setSaDivideCi(double saDivideCi) {
        Sa_divide_CI = saDivideCi;
    }

    double getSi() const {
        return Si;
    }

    void setSi(double si) {
        Si = si;
    }

    double getCaCo3() const {
        return CaCO3;
    }

    void setCaCo3(double caCo3) {
        CaCO3 = caCo3;
    }

    double getOm() const {
        return OM;
    }

    void setOm(double om) {
        OM = om;
    }
};

struct _COG : public _base_value {
    double Pd, Pgcb, Pgca, SA, SC;

    _COG() = default;

    double getValue() const override {
        double SLRf = exp(-0.0438 * SC);
        double SLRs = exp(-0.0344 * pow(SA, 0.6413));
        double cc = exp(Pgca + Pgcb / (Pd * Pd));
        double SLRc = exp(-5.614 * pow(cc, 0.7366));
        return SLRc * SLRf * SLRs;
    }

    double getPd() const {
        return Pd;
    }

    void setPd(double pd) {
        Pd = pd;
    }

    double getPgcb() const {
        return Pgcb;
    }

    void setPgcb(double pgcb) {
        Pgcb = pgcb;
    }

    double getPgca() const {
        return Pgca;
    }

    void setPgca(double pgca) {
        Pgca = pgca;
    }

    double getSa() const {
        return SA;
    }

    void setSa(double sa) {
        SA = sa;
    }

    double getSc() const {
        return SC;
    }

    void setSc(double sc) {
        SC = sc;
    }
};

struct _WF : public _base_value {
    double Wf, R_plus_I, denisity, ETp, SD, Nd, g, Rd;

    double getValue() const override {
        double SW = (ETp - (R_plus_I) * Rd / Nd) / ETp;
        return Wf * denisity / g * SW * SD;
    }

    double getWf() const {
        return Wf;
    }

    void setWf(double wf) {
        Wf = wf;
    }

    void setWf(const _Wf &wf) {
        Wf = wf.getValue();
    }

    double getRPlusI() const {
        return R_plus_I;
    }

    void setRPlusI(double rPlusI) {
        R_plus_I = rPlusI;
    }

    double getDenisity() const {
        return denisity;
    }

    void setDenisity(double denisity) {
        _WF::denisity = denisity;
    }

    double getETp() const {
        return ETp;
    }

    void setETp(double eTp) {
        ETp = eTp;
    }

    double getSd() const {
        return SD;
    }

    void setSd(double sd) {
        SD = sd;
    }

    double getNd() const {
        return Nd;
    }

    void setNd(double nd) {
        Nd = nd;
    }

    double getG() const {
        return g;
    }

    void setG(double g) {
        _WF::g = g;
    }

    double getRd() const {
        return Rd;
    }

    void setRd(double rd) {
        Rd = rd;
    }
};

struct _Qx : public _base_value {
    double x, k_;
    _WF WF;
    _EF EF;
    _SCF SCF;
    _COG COG;

    _Qx() = default;

    double getValue() const override {
        double Qmax = 109.8 * (WF * EF * SCF * COG * k_);
        double s = 150.71 * pow((WF * EF * k_ * COG), -0.3711);
        return 2 * x / (s * s) * Qmax * exp(-1 * x * x / s / s);
    }

    double getX() const {
        return x;
    }

    void setX(double x) {
        _Qx::x = x;
    }

    double getK() const {
        return k_;
    }

    void setK(double k) {
        k_ = k;
    }

    const _WF &getWf() const {
        return WF;
    }

    void setWf(const _WF &wf) {
        WF = wf;
    }

    const _EF &getEf() const {
        return EF;
    }

    void setEf(const _EF &ef) {
        EF = ef;
    }

    const _SCF &getScf() const {
        return SCF;
    }

    void setScf(const _SCF &scf) {
        SCF = scf;
    }

    const _COG &getCog() const {
        return COG;
    }

    void setCog(const _COG &cog) {
        COG = cog;
    }
};

struct _Qp : public _base_value {
    double x, k_, COG = 1;
    _WF WF;
    _EF EF;
    _SCF SCF;

    _Qp() = default;

    double getValue() const override {
        double Qmax = 109.8 * (WF * EF * SCF * COG * k_);
        double s = 150.71 * pow((WF * EF * k_ * COG), -0.3711);
        return 2 * x / (s * s) * Qmax * exp(-1 * x * x / s / s);
    }

    double getX() const {
        return x;
    }

    void setX(double x) {
        _Qp::x = x;
    }

    double getK() const {
        return k_;
    }

    void setK(double k) {
        k_ = k;
    }

    const _WF &getWf() const {
        return WF;
    }

    void setWF(const _WF &wf) {
        WF = wf;
    }

    const _EF &getEf() const {
        return EF;
    }

    void setEf(const _EF &ef) {
        EF = ef;
    }

    const _SCF &getScf() const {
        return SCF;
    }

    void setScf(const _SCF &scf) {
        SCF = scf;
    }
};

struct _Q : public _base_value {
    _Qp Qp;
    _Qx Qx;

    _Q() = default;

    double getValue() const override {
        return Qp - Qx;
    }

    const _Qp &getQp() const {
        return Qp;
    }

    void setQp(const _Qp &qp) {
        Qp = qp;
    }

    const _Qx &getQx() const {
        return Qx;
    }

    void setQx(const _Qx &qx) {
        Qx = qx;
    }
};

struct _Q_ : public _base_value {
    _Qp Qp;
    _Qx Qx;

    double getValue() const override {
        return (Qp - Qx) / Qp;
    }

    _Q_() = default;

    const _Qp &getQp() const {
        return Qp;
    }

    void setQp(const _Qp &qp) {
        Qp = qp;
    }

    const _Qx &getQx() const {
        return Qx;
    }

    void setQx(const _Qx &qx) {
        Qx = qx;
    }
};

#endif //DONGMENDB_TOOLS_H
