#ifndef FENCODEGENERE_H
#define FENCODEGENERE_H

#include <QApplication>
#include <QWidget>
#include <QtWidgets>
#include "fenprincipale.h"

class FenCodeGenere : public QDialog {
    Q_OBJECT

public:
    FenCodeGenere();

    void setCodeH(QString codeH);
    void setCodeCpp(QString codeCpp);
    void setNomClass(QString nomClassSet);

public slots:
    void enregistrerSous();

signals:


protected:
    QVBoxLayout *m_layoutCode;
        QTabWidget *m_layoutTab;
            QTextEdit *m_codeH;
            QTextEdit *m_codeCpp;
        QPushButton *m_boutonFermer;
        QPushButton *m_boutonEnregistrer;

        QString m_nomFen;

};

#endif // FENCODEGENERE_H
