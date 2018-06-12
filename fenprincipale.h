#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QApplication>
#include <QWidget>
#include <QtWidgets>
#include "fencodegenere.h"

class FenPrincipale : public QWidget {
    Q_OBJECT

public:
    FenPrincipale();

public slots:
    void genereDialog();
    void updateHeader();

signals:


protected:
    // Def class
    QGroupBox *m_groupDef;
        QFormLayout *m_layoutFormDef;
            QLineEdit *m_nom;
            QLineEdit *m_classMere;

    // Options
    QGroupBox *m_groupOpt;
        QVBoxLayout *m_boxOpt;
            QCheckBox *m_checkProtec;
            QLineEdit *m_protectHeader;
            QCheckBox *m_checkConstructeur;
            QCheckBox *m_checkDestructeur;

    // Add commentaires
    QGroupBox *m_groupCom;
    QFormLayout *m_layoutFormCom;
        QLineEdit *m_auteur;
        QDateEdit *m_dateCreation;
        QTextEdit *m_roleClass;

    // Layout général
    QVBoxLayout *m_layoutGeneral;
        QPushButton *m_boutonQuitter;
        QPushButton *m_boutonGenerer;
};

#endif // FENPRINCIPALE_H
