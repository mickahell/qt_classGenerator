#include "fenprincipale.h"

FenPrincipale::FenPrincipale() : QWidget() {
    // Def class
    QGroupBox *m_groupDef = new QGroupBox("Définission de la classe");
        QFormLayout *m_layoutFormDef = new QFormLayout;
            m_nom = new QLineEdit;
            QRegExp rx("^[A-Za-z_-]+$");
            QValidator *validator = new QRegExpValidator(rx, this);
            m_nom->setValidator(validator);
            m_classMere = new QLineEdit;
            m_classMere->setValidator(validator);

            m_layoutFormDef->addRow("Nom : ", m_nom);
            m_layoutFormDef->addRow("Classe mère : ", m_classMere);

    m_groupDef->setLayout(m_layoutFormDef);

    // Options
    QGroupBox *m_groupOpt = new QGroupBox("Options");
        QVBoxLayout *m_boxOpt = new QVBoxLayout;
            m_checkProtec = new QCheckBox("Protéger le header contre les inclusions multiples");
            QLabel *headers = new QLabel("Headers : ");
            m_protectHeader = new QLineEdit;
            connect(m_checkProtec,SIGNAL(stateChanged(int)),this,SLOT(updateHeader()));
            m_checkConstructeur = new QCheckBox("Générer un constructeur par defaut");
            m_checkDestructeur = new QCheckBox("Générer un destructeur");

        m_boxOpt->addWidget(m_checkProtec);
        m_boxOpt->addWidget(headers);
        m_boxOpt->addWidget(m_protectHeader);
        m_boxOpt->addWidget(m_checkConstructeur);
        m_boxOpt->addWidget(m_checkDestructeur);

    m_groupOpt->setLayout(m_boxOpt);

    // Add commentaires
    m_groupCom = new QGroupBox("Ajouter des commentaires");
    m_groupCom->setCheckable(true);
    m_groupCom->setChecked(false);
        QFormLayout *m_layoutFormCom = new QFormLayout;
            m_auteur = new QLineEdit;
            m_dateCreation = new QDateEdit(QDate::currentDate());
            m_roleClass = new QTextEdit;

        m_layoutFormCom->addRow("Auteur : ", m_auteur);
        m_layoutFormCom->addRow("Date de création : ", m_dateCreation);
        m_layoutFormCom->addRow("Rôle de la class : ", m_roleClass);

    m_groupCom->setLayout(m_layoutFormCom);

    // Layout général
    QVBoxLayout *m_layoutGeneral = new QVBoxLayout(this);
        m_layoutGeneral->addWidget(m_groupDef); // Ajout du layout Def Class
        m_layoutGeneral->addWidget(m_groupOpt); // Ajout du layout Options
        m_layoutGeneral->addWidget(m_groupCom); // Ajout du layout Add comm

        QPushButton *m_boutonQuitter = new QPushButton("Quitter");
        QWidget::connect(m_boutonQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));
        QPushButton *m_boutonGenerer = new QPushButton("Générer");
        QWidget::connect(m_boutonGenerer, SIGNAL(clicked()), this, SLOT(genereDialog()));

    m_layoutGeneral->addWidget(m_boutonGenerer);
    m_layoutGeneral->addWidget(m_boutonQuitter);

    this->setLayout(m_layoutGeneral);
}

void FenPrincipale::updateHeader(){
    m_protectHeader->setText("#ifndef " + m_nom->text() + "\n#define " + m_nom->text());
}

void FenPrincipale::genereDialog(){
    if(m_nom->text().isEmpty()){
        QMessageBox::information(this, "Attention", "Tu dois donner un nom à ta classe !");
    }
    else{
        QString nomCLass = "class " + m_nom->text();
        QString classMere = "";
        QString debutProtecteur = "";
        QString finProtecteur = "";
        QString constructeur = "";
        QString destructeur = "";
        QString commentaire = "";
        QString auteur = "";
        QString roleClass = "";

        if(m_checkProtec->isChecked()){
            debutProtecteur = m_protectHeader->text() + "\n\n\n";
            finProtecteur = "\n\n#endif\n";
        }
        if(!m_classMere->text().isEmpty()){
            classMere = " : public " + m_classMere->text();
        }
        if(m_checkConstructeur->isChecked()){
            constructeur = m_nom->text() + "();\n";
        }
        if(m_checkDestructeur->isChecked()){
            destructeur = "        ~" + m_nom->text() + "();\n";
        }

        //Commentaires
        if(m_groupCom->isChecked()){
            if(!m_classMere->text().isEmpty()){
                auteur = "Auteur : " + m_auteur->text() + "\n";
            }
            m_dateCreation->setObjectName(QString::fromUtf8("date"));
            m_dateCreation->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            QString date = m_dateCreation->text();
            if(!m_classMere->text().isEmpty()){
                roleClass = "Role : " + m_roleClass->toPlainText() + "\n";
            }
            commentaire = "/* \n" + auteur + "Date de création : " + date + "\n" + roleClass + "*/\n\n\n";
        }

        //Class + Protecteur
            //Debut class
            QString debutClass = debutProtecteur + nomCLass + classMere + " {\n\n";
            //Content classe
            QString contentClass = "    public :\n        " + constructeur + destructeur + "\n    protected :\n\n    private :\n\n};";
            //Fin Protecteur
            QString finClass = finProtecteur;

        QString codeClass = commentaire + debutClass + contentClass + finClass;
        QString codeSource = "#include " + m_nom->text() + ".h;\n\n" + m_nom->text() + "::" + m_nom->text() + "() {\n\n}\n";



        FenCodeGenere codeFenetre;

        codeFenetre.setNomClass(m_nom->text());

        codeFenetre.setCodeH(codeClass);
        codeFenetre.setCodeCpp(codeSource);

        codeFenetre.exec();
    }
}
