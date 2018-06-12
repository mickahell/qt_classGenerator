#include "fencodegenere.h"

FenCodeGenere::FenCodeGenere() {
    //Page H
    m_codeH = new QTextEdit;
    m_codeH->setReadOnly(1);

    // Page CPP
        m_codeCpp = new QTextEdit;
        m_codeCpp->setReadOnly(1);

    // Fenetre générale
    m_layoutCode = new QVBoxLayout(this);
    m_layoutTab = new QTabWidget;
        //Onglets
//        m_nomFen = new QString;
        QString fichier = m_nomFen;
        m_layoutTab->addTab(m_codeH, (fichier + ".h"));
        m_layoutTab->addTab(m_codeCpp, (m_nomFen + ".cpp"));

    m_boutonFermer = new QPushButton("Fermer");
    QWidget::connect(m_boutonFermer, SIGNAL(clicked()), this, SLOT(accept()));
    m_boutonEnregistrer = new QPushButton("Enregistrer");
    QWidget::connect(m_boutonEnregistrer, SIGNAL(clicked()), this, SLOT(enregistrerSous()));

    m_layoutCode->addWidget(m_layoutTab);
    m_layoutCode->addWidget(m_boutonEnregistrer);
    m_layoutCode->addWidget(m_boutonFermer);

}

void FenCodeGenere::setCodeH(QString codeH){
    m_codeH->setText(codeH);
}
void FenCodeGenere::setCodeCpp(QString codeCpp){
    m_codeCpp->setText(codeCpp);
}
void FenCodeGenere::setNomClass(QString nomClassSet){
    m_nomFen= nomClassSet;
}

void FenCodeGenere::enregistrerSous(){
    QString fSaveH=QFileDialog::getSaveFileName(this, "Enregister Sous fichier .h", QString(), "Tous les fichiers (*.*)");
    QString fSaveCpp=QFileDialog::getSaveFileName(this, "Enregister Sous fichier .h", QString(), "Tous les fichiers (*.*)");

    QFile fileH(fSaveH);
    QFile fileCpp(fSaveCpp);

    if (fileH.open(QFile::WriteOnly)) {
        QTextStream out(&fileH);
        out << m_codeH->toPlainText() << endl;
        QMessageBox::information(this, "Bravo", fSaveH + " a aété enregistré !");
    }

    if (fileCpp.open(QFile::WriteOnly)) {
        QTextStream out(&fileCpp);
        out << m_codeCpp->toPlainText() << endl;
        QMessageBox::information(this, "Bravo", fSaveCpp + " a aété enregistré !");
    }
}
