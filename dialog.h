#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QString>
#include <QFile>

#include "md5.h"
#include "sha1.h"
#include "ripemd.h"
#include "elgamal.h"
#include "rsa.h"

namespace Ui
{
class Dialog;
}
class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
private slots:
    void on_quitButton_clicked();
    void on_clearButton_clicked();
    void on_inputFileButton_clicked();
    void on_outputFileButton_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_md5Button_clicked();
    void on_sha1Button_clicked();
    void on_ripemd160Button_clicked();
    void on_elgamalComboBox_currentIndexChanged(int index);
    void on_elgamalPublicKeyFileButton_clicked();
    void on_elgamalPrivateKeyFileButton_clicked();
    void on_elgamalRandomizeFileButton_clicked();
    void on_elgamalDoItButton_clicked();
    void on_rsaComboBox_currentIndexChanged(int index);
    void on_rsaPublicKeyFileButton_clicked();
    void on_rsaPrivateKeyFileButton_clicked();
    void on_rsaRandomizeFileButton_clicked();
    void on_rsaDoItButton_clicked();

private:
    Ui::Dialog *ui;

    QString inputFileName;
    QString outputFileName;
    QString elgamalPublicKeyFileName;
    QString elgamalPrivateKeyFileName;
    QString elgamalRandomizeFileName;
    QString rsaPublicKeyFileName;
    QString rsaPrivateKeyFileName;
    QString rsaRandomizeFileName;
    QFile inputFile;
    QFile outputFile;
    QFile elgamalPublicKeyFile;
    QFile elgamalPrivateKeyFile;
    QFile elgamalRandomizeFile;
    QFile rsaPublicKeyFile;
    QFile rsaPrivateKeyFile;
    QFile rsaRandomizeFile;
    bool isInputFile;
    bool isOutputFile;
    bool isElgamalPublicKeyFile;
    bool isElgamalPrivateKeyFile;
    bool isElgamalRandomizeFile;
    bool isRsaPublicKeyFile;
    bool isRsaPrivateKeyFile;
    bool isRsaRandomizeFile;
    void elgamalGenerateModeSelected();
    void elgamalEncryptModeSelected();
    void elgamalDecryptModeSelected();
    void rsaGenerateModeSelected();
    void rsaEncryptModeSelected();
    void rsaDecryptModeSelected();
};
#endif // DIALOG_H
