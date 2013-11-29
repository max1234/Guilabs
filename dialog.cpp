#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->isInputFile = this->isOutputFile = this->isElgamalPublicKeyFile \
            = this->isElgamalPrivateKeyFile = this->isElgamalRandomizeFile \
            = this->isRsaPublicKeyFile = this->isRsaPrivateKeyFile \
            = this->isRsaRandomizeFile= false;
    ui->elgamalComboBox->setCurrentIndex(0);
    ui->rsaComboBox->setCurrentIndex(0);
    ui->md5Button->setDisabled(true);
    ui->sha1Button->setDisabled(true);
    ui->ripemd160Button->setDisabled(true);
    ui->elgamalDoItButton->setDisabled(true);
    ui->rsaDoItButton->setDisabled(true);
    ui->tabWidget->setCurrentIndex(0);
}
Dialog::~Dialog()
{
    delete ui;
}
void Dialog::on_quitButton_clicked()
{
    QApplication::closeAllWindows();
}
void Dialog::on_clearButton_clicked()
{
    ui->textBrowser->clear();
}
void Dialog::on_inputFileButton_clicked()
{
    this->inputFileName = QFileDialog::getOpenFileName(this, "Select Input File", ui->inputFileLineEdit->text(), "All Files (*)");
    if(!this->inputFileName.isEmpty())
    {
        ui->inputFileLineEdit->setText(this->inputFileName);
        this->inputFile.setFileName(this->inputFileName);
        this->isInputFile = true;
    }
    if(this->isInputFile && this->isOutputFile)
    {
        ui->md5Button->setEnabled(true);
        ui->sha1Button->setEnabled(true);
        ui->ripemd160Button->setEnabled(true);
    }
    else
    {
        ui->md5Button->setDisabled(true);
        ui->sha1Button->setDisabled(true);
        ui->ripemd160Button->setDisabled(true);
    }
    switch(ui->elgamalComboBox->currentIndex())
    {
    case 0:
        if(this->isElgamalPublicKeyFile && this->isElgamalPrivateKeyFile && this->isElgamalRandomizeFile)
            ui->elgamalDoItButton->setEnabled(true);
        else
            ui->elgamalDoItButton->setDisabled(true);
        break;
    case 1:
        if(this->isElgamalPublicKeyFile && this->isInputFile && this->isOutputFile)
            ui->elgamalDoItButton->setEnabled(true);
        else
            ui->elgamalDoItButton->setDisabled(true);
        break;
    case 2:
        if(this->isElgamalPrivateKeyFile && this->isInputFile && this->isOutputFile)
            ui->elgamalDoItButton->setEnabled(true);
        else
            ui->elgamalDoItButton->setDisabled(true);
        break;
    }
    switch(ui->rsaComboBox->currentIndex())
    {
    case 0:
        if(this->isRsaPublicKeyFile && this->isRsaPrivateKeyFile && this->isRsaRandomizeFile)
            ui->rsaDoItButton->setEnabled(true);
        else
            ui->rsaDoItButton->setDisabled(true);
        break;
    case 1:
        if(this->isRsaPublicKeyFile && this->isInputFile && this->isOutputFile)
            ui->rsaDoItButton->setEnabled(true);
        else
            ui->rsaDoItButton->setDisabled(true);
        break;
    case 2:
        if(this->isRsaPrivateKeyFile && this->isInputFile && this->isOutputFile)
            ui->rsaDoItButton->setEnabled(true);
        else
            ui->rsaDoItButton->setDisabled(true);
        break;
    }
}
void Dialog::on_outputFileButton_clicked()
{
    this->outputFileName = QFileDialog::getSaveFileName(this, "Select output File", ui->outputFileLineEdit->text());
    if(!this->outputFileName.isEmpty())
    {
        ui->outputFileLineEdit->setText(this->outputFileName);
        this->outputFile.setFileName(this->outputFileName);
        this->isOutputFile = true;
    }
    if(this->isInputFile && this->isOutputFile)
    {
        ui->md5Button->setEnabled(true);
        ui->sha1Button->setEnabled(true);
        ui->ripemd160Button->setEnabled(true);
    }
    else
    {
        ui->md5Button->setDisabled(true);
        ui->sha1Button->setDisabled(true);
        ui->ripemd160Button->setDisabled(true);
    }
    switch(ui->elgamalComboBox->currentIndex())
    {
    case 0:
        if(this->isElgamalPublicKeyFile && this->isElgamalPrivateKeyFile && this->isElgamalRandomizeFile)
            ui->elgamalDoItButton->setEnabled(true);
        else
            ui->elgamalDoItButton->setDisabled(true);
        break;
    case 1:
        if(this->isElgamalPublicKeyFile && this->isInputFile && this->isOutputFile)
            ui->elgamalDoItButton->setEnabled(true);
        else
            ui->elgamalDoItButton->setDisabled(true);
        break;
    case 2:
        if(this->isElgamalPrivateKeyFile && this->isInputFile && this->isOutputFile)
            ui->elgamalDoItButton->setEnabled(true);
        else
            ui->elgamalDoItButton->setDisabled(true);
        break;
    }
    switch(ui->rsaComboBox->currentIndex())
    {
    case 0:
        if(this->isRsaPublicKeyFile && this->isRsaPrivateKeyFile && this->isRsaRandomizeFile)
            ui->rsaDoItButton->setEnabled(true);
        else
            ui->rsaDoItButton->setDisabled(true);
        break;
    case 1:
        if(this->isRsaPublicKeyFile && this->isInputFile && this->isOutputFile)
            ui->rsaDoItButton->setEnabled(true);
        else
            ui->rsaDoItButton->setDisabled(true);
        break;
    case 2:
        if(this->isRsaPrivateKeyFile && this->isInputFile && this->isOutputFile)
            ui->rsaDoItButton->setEnabled(true);
        else
            ui->rsaDoItButton->setDisabled(true);
        break;
    }
}
void Dialog::on_tabWidget_currentChanged(int index)
{
    switch(index)
    {
    case 0:
        ui->textBrowser->insertPlainText("MD5: algorithm selected\n");
        break;
    case 1:
        ui->textBrowser->insertPlainText("SHA1: algorithm selected\n");
        break;
    case 2:
        ui->textBrowser->insertPlainText("RIPEMD160: algorithm selected\n");
        break;
    case 3:
        ui->textBrowser->insertPlainText("RSA: algorithm selected\n");
        switch(ui->rsaComboBox->currentIndex())
        {
        case 0:
            rsaGenerateModeSelected();
            break;
        case 1:
            rsaEncryptModeSelected();
            break;
        case 2:
            rsaDecryptModeSelected();
            break;
        }
        break;
    case 4:
        ui->textBrowser->insertPlainText("Elgamal: algorithm selected\n");

        switch(ui->elgamalComboBox->currentIndex())
        {
        case 0:
            elgamalGenerateModeSelected();
            break;
        case 1:
            elgamalEncryptModeSelected();
            break;
        case 2:
            elgamalDecryptModeSelected();
            break;
        }
        break;
    }
}
void Dialog::on_md5Button_clicked()
{
    if(this->outputFile.open(QIODevice::WriteOnly) && this->inputFile.open(QIODevice::ReadOnly))
    {
        QString buf;
        MD5 md5;
        buf = md5.digestFile(&this->inputFile);
        ui->textBrowser->insertPlainText("MD5 hash sum = " + buf + "\n");
        outputFile.write(buf.toAscii());
        this->outputFile.close();
        this->inputFile.close();
    }
    else
        ui->textBrowser->insertPlainText("Error: some files can't be opened\n");
}
void Dialog::on_sha1Button_clicked()
{
    if(this->outputFile.open(QIODevice::WriteOnly) && this->inputFile.open(QIODevice::ReadOnly))
    {
        QString buf;
        SHA1 sha1;
        buf = sha1.digestFile(&this->inputFile);
        ui->textBrowser->insertPlainText("SHA1 hash sum = " + buf + "\n");
        outputFile.write(buf.toAscii());
        this->outputFile.close();
        this->inputFile.close();
    }
    else
        ui->textBrowser->insertPlainText("Error: some files can't be opened\n");
}
void Dialog::on_ripemd160Button_clicked()
{
    if(this->outputFile.open(QIODevice::WriteOnly) && this->inputFile.open(QIODevice::ReadOnly))
    {
        QString buf;
        RIPEMD ripemd;
        buf = ripemd.digestFile(&this->inputFile);
        ui->textBrowser->insertPlainText("RIPEMD160 hash sum = " + buf + "\n");
        outputFile.write(buf.toAscii());
        this->outputFile.close();
        this->inputFile.close();
    }
    else
        ui->textBrowser->insertPlainText("Error: some files can't be opened\n");
}
void Dialog::on_elgamalComboBox_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
        elgamalGenerateModeSelected();
        if(this->isElgamalPublicKeyFile && this->isElgamalPrivateKeyFile && this->isElgamalRandomizeFile)
            ui->elgamalDoItButton->setEnabled(true);
        else
            ui->elgamalDoItButton->setDisabled(true);
        break;
    case 1:
        elgamalEncryptModeSelected();
        if(this->isElgamalPublicKeyFile && this->isInputFile && this->isOutputFile)
            ui->elgamalDoItButton->setEnabled(true);
        else
            ui->elgamalDoItButton->setDisabled(true);
        break;
    case 2:
        elgamalDecryptModeSelected();
        if(this->isElgamalPrivateKeyFile && this->isInputFile && this->isOutputFile)
            ui->elgamalDoItButton->setEnabled(true);
        else
            ui->elgamalDoItButton->setDisabled(true);
        break;
    }
}
void Dialog::elgamalGenerateModeSelected()
{
    ui->textBrowser->insertPlainText("Elgamal: Generate mode\n");
    ui->inputFileButton->setDisabled(true);
    ui->inputFileLabel->setDisabled(true);
    ui->inputFileLineEdit->setDisabled(true);
    ui->outputFileButton->setDisabled(true);
    ui->outputFileLabel->setDisabled(true);
    ui->outputFileLineEdit->setDisabled(true);
    ui->elgamalPublicKeyFileButton->setEnabled(true);
    ui->elgamalPublicKeyFileLabel->setEnabled(true);
    ui->elgamalPublicKeyFileLineEdit->setEnabled(true);
    ui->elgamalPrivateKeyFileButton->setEnabled(true);
    ui->elgamalPrivateKeyFileLabel->setEnabled(true);
    ui->elgamalPrivateKeyFileLineEdit->setEnabled(true);
    ui->elgamalRandomizeFileButton->setEnabled(true);
    ui->elgamalRandomizeFileLabel->setEnabled(true);
    ui->elgamalRandomizeFileLineEdit->setEnabled(true);
    ui->elgamalKeySizeLabel->setEnabled(true);
    ui->elgamalKeySizeSpinBox->setEnabled(true);
}
void Dialog::elgamalEncryptModeSelected()
{
    ui->textBrowser->insertPlainText("Elgamal: Encrypt mode\n");
    ui->inputFileButton->setEnabled(true);
    ui->inputFileLabel->setEnabled(true);
    ui->inputFileLineEdit->setEnabled(true);
    ui->outputFileButton->setEnabled(true);
    ui->outputFileLabel->setEnabled(true);
    ui->outputFileLineEdit->setEnabled(true);
    ui->elgamalPublicKeyFileButton->setEnabled(true);
    ui->elgamalPublicKeyFileLabel->setEnabled(true);
    ui->elgamalPublicKeyFileLineEdit->setEnabled(true);
    ui->elgamalPrivateKeyFileButton->setDisabled(true);
    ui->elgamalPrivateKeyFileLabel->setDisabled(true);
    ui->elgamalPrivateKeyFileLineEdit->setDisabled(true);
    ui->elgamalRandomizeFileButton->setDisabled(true);
    ui->elgamalRandomizeFileLabel->setDisabled(true);
    ui->elgamalRandomizeFileLineEdit->setDisabled(true);
    ui->elgamalKeySizeLabel->setDisabled(true);
    ui->elgamalKeySizeSpinBox->setDisabled(true);
}
void Dialog::elgamalDecryptModeSelected()
{
    ui->textBrowser->insertPlainText("Elgamal: Decrypt mode\n");
    ui->inputFileButton->setEnabled(true);
    ui->inputFileLabel->setEnabled(true);
    ui->inputFileLineEdit->setEnabled(true);
    ui->outputFileButton->setEnabled(true);
    ui->outputFileLabel->setEnabled(true);
    ui->outputFileLineEdit->setEnabled(true);
    ui->elgamalPrivateKeyFileButton->setEnabled(true);
    ui->elgamalPrivateKeyFileLabel->setEnabled(true);
    ui->elgamalPrivateKeyFileLineEdit->setEnabled(true);
    ui->elgamalPublicKeyFileButton->setDisabled(true);
    ui->elgamalPublicKeyFileLabel->setDisabled(true);
    ui->elgamalPublicKeyFileLineEdit->setDisabled(true);
    ui->elgamalRandomizeFileButton->setDisabled(true);
    ui->elgamalRandomizeFileLabel->setDisabled(true);
    ui->elgamalRandomizeFileLineEdit->setDisabled(true);
    ui->elgamalKeySizeLabel->setDisabled(true);
    ui->elgamalKeySizeSpinBox->setDisabled(true);
}
void Dialog::on_elgamalPublicKeyFileButton_clicked()
{
    if(0 == ui->elgamalComboBox->currentIndex())
    {
        this->elgamalPublicKeyFileName = QFileDialog::getSaveFileName(this, "Select Public Key File", ui->elgamalPublicKeyFileLineEdit->text());
    }
    else
    {
        this->elgamalPublicKeyFileName = QFileDialog::getOpenFileName(this, "Select Public Key File", ui->elgamalPublicKeyFileLineEdit->text(), "All Files (*)");
    }
    if(!this->elgamalPublicKeyFileName.isEmpty())
    {
        ui->elgamalPublicKeyFileLineEdit->setText(this->elgamalPublicKeyFileName);
        this->elgamalPublicKeyFile.setFileName(this->elgamalPublicKeyFileName);
        this->isElgamalPublicKeyFile = true;
    }
    switch(ui->elgamalComboBox->currentIndex())
    {
    case 0:
        if(this->isElgamalPublicKeyFile && this->isElgamalPrivateKeyFile && this->isElgamalRandomizeFile)
            ui->elgamalDoItButton->setEnabled(true);
        else
            ui->elgamalDoItButton->setDisabled(true);
        break;
    case 1:
        if(this->isElgamalPublicKeyFile && this->isInputFile && this->isOutputFile)
            ui->elgamalDoItButton->setEnabled(true);
        else
            ui->elgamalDoItButton->setDisabled(true);
        break;
    case 2:
        if(this->isElgamalPrivateKeyFile && this->isInputFile && this->isOutputFile)
            ui->elgamalDoItButton->setEnabled(true);
        else
            ui->elgamalDoItButton->setDisabled(true);
        break;
    }
}
void Dialog::on_elgamalPrivateKeyFileButton_clicked()
{
    if(0 == ui->elgamalComboBox->currentIndex())
    {
        this->elgamalPrivateKeyFileName = QFileDialog::getSaveFileName(this, "Select Private Key File", ui->elgamalPrivateKeyFileLineEdit->text());
    }
    else
    {
        this->elgamalPrivateKeyFileName = QFileDialog::getOpenFileName(this, "Select Private Key File", ui->elgamalPrivateKeyFileLineEdit->text(), "All Files (*)");
    }
    if(!this->elgamalPrivateKeyFileName.isEmpty())
    {
        ui->elgamalPrivateKeyFileLineEdit->setText(this->elgamalPrivateKeyFileName);
        this->elgamalPrivateKeyFile.setFileName(this->elgamalPrivateKeyFileName);
        this->isElgamalPrivateKeyFile = true;
    }
    switch(ui->elgamalComboBox->currentIndex())
    {
    case 0:
        if(this->isElgamalPublicKeyFile && this->isElgamalPrivateKeyFile && this->isElgamalRandomizeFile)
            ui->elgamalDoItButton->setEnabled(true);
        else
            ui->elgamalDoItButton->setDisabled(true);
        break;
    case 1:
        if(this->isElgamalPublicKeyFile && this->isInputFile && this->isOutputFile)
            ui->elgamalDoItButton->setEnabled(true);
        else
            ui->elgamalDoItButton->setDisabled(true);
        break;
    case 2:
        if(this->isElgamalPrivateKeyFile && this->isInputFile && this->isOutputFile)
            ui->elgamalDoItButton->setEnabled(true);
        else
            ui->elgamalDoItButton->setDisabled(true);
        break;
    }
}
void Dialog::on_elgamalRandomizeFileButton_clicked()
{
    this->elgamalRandomizeFileName = QFileDialog::getOpenFileName(this, "Select Randomize Key File", ui->elgamalRandomizeFileLineEdit->text(), "All Files (*)");
    if(!this->elgamalRandomizeFileName.isEmpty())
    {
        ui->elgamalRandomizeFileLineEdit->setText(this->elgamalRandomizeFileName);
        this->elgamalRandomizeFile.setFileName(this->elgamalRandomizeFileName);
        this->isElgamalRandomizeFile = true;
    }
    switch(ui->elgamalComboBox->currentIndex())
    {
    case 0:
        if(this->isElgamalPublicKeyFile && this->isElgamalPrivateKeyFile && this->isElgamalRandomizeFile)
            ui->elgamalDoItButton->setEnabled(true);
        else
            ui->elgamalDoItButton->setDisabled(true);
        break;
    case 1:
        if(this->isElgamalPublicKeyFile && this->isInputFile && this->isOutputFile)
            ui->elgamalDoItButton->setEnabled(true);
        else
            ui->elgamalDoItButton->setDisabled(true);
        break;
    case 2:
        if(this->isElgamalPrivateKeyFile && this->isInputFile && this->isOutputFile)
            ui->elgamalDoItButton->setEnabled(true);
        else
            ui->elgamalDoItButton->setDisabled(true);
        break;
    }
}
void Dialog::on_elgamalDoItButton_clicked()
{
    ElGamal elgamal;
    switch(ui->elgamalComboBox->currentIndex())
    {
    case 0:
        if(this->elgamalPublicKeyFile.open(QIODevice::WriteOnly) && \
                this->elgamalPrivateKeyFile.open(QIODevice::WriteOnly) && \
                this->elgamalRandomizeFile.open(QIODevice::ReadOnly))
        {
            int keySize = ui->elgamalKeySizeSpinBox->value();
            elgamal.GenerateKeys(&this->elgamalPublicKeyFile, &this->elgamalPrivateKeyFile,\
                                 &this->elgamalRandomizeFile, keySize);
            ui->textBrowser->insertPlainText(\
                        QString("Elgamal: key of size = %1 bits successfully generated\n").arg(keySize));
            this->elgamalPublicKeyFile.close();
            this->elgamalPrivateKeyFile.close();
            this->elgamalRandomizeFile.close();
        }
        else
            ui->textBrowser->insertPlainText("Error: some files can't be opened\n");
        break;
    case 1:
        if(this->elgamalPublicKeyFile.open(QIODevice::ReadOnly) && \
                this->inputFile.open(QIODevice::ReadOnly) && \
                this->outputFile.open(QIODevice::WriteOnly))
        {
            elgamal.Encrypt(&this->inputFile, &this->outputFile, &this->elgamalPublicKeyFile);
            ui->textBrowser->insertPlainText(\
                        QString("Elgamal: data encryption of successfully\n"));
            this->elgamalPublicKeyFile.close();
            this->inputFile.close();
            this->outputFile.close();
        }
        else
            ui->textBrowser->insertPlainText("Error: some files can't be opened\n");
        break;
    case 2:
        if(this->elgamalPrivateKeyFile.open(QIODevice::ReadOnly) && \
                this->inputFile.open(QIODevice::ReadOnly) && \
                this->outputFile.open(QIODevice::WriteOnly))
        {
            elgamal.Decrypt(&this->inputFile, &this->outputFile, &this->elgamalPrivateKeyFile);
            ui->textBrowser->insertPlainText(\
                        QString("Elgamal: data decryption of successfully\n"));
            this->elgamalPrivateKeyFile.close();
            this->inputFile.close();
            this->outputFile.close();
        }
        else
            ui->textBrowser->insertPlainText("Error: some files can't be opened\n");
        break;
    }
}
void Dialog::on_rsaComboBox_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
        rsaGenerateModeSelected();
        if(this->isRsaPublicKeyFile && this->isRsaPrivateKeyFile && this->isRsaRandomizeFile)
            ui->rsaDoItButton->setEnabled(true);
        else
            ui->rsaDoItButton->setDisabled(true);
        break;
    case 1:
        rsaEncryptModeSelected();
        if(this->isRsaPublicKeyFile && this->isInputFile && this->isOutputFile)
            ui->rsaDoItButton->setEnabled(true);
        else
            ui->rsaDoItButton->setDisabled(true);
        break;
    case 2:
        rsaDecryptModeSelected();
        if(this->isRsaPrivateKeyFile && this->isInputFile && this->isOutputFile)
            ui->rsaDoItButton->setEnabled(true);
        else
            ui->rsaDoItButton->setDisabled(true);
        break;
    }
}
void Dialog::rsaGenerateModeSelected()
{
    ui->textBrowser->insertPlainText("RSA: Generate mode\n");
    ui->inputFileButton->setDisabled(true);
    ui->inputFileLabel->setDisabled(true);
    ui->inputFileLineEdit->setDisabled(true);
    ui->outputFileButton->setDisabled(true);
    ui->outputFileLabel->setDisabled(true);
    ui->outputFileLineEdit->setDisabled(true);
    ui->rsaPublicKeyFileButton->setEnabled(true);
    ui->rsaPublicKeyFileLabel->setEnabled(true);
    ui->rsaPublicKeyFileLineEdit->setEnabled(true);
    ui->rsaPrivateKeyFileButton->setEnabled(true);
    ui->rsaPrivateKeyFileLabel->setEnabled(true);
    ui->rsaPrivateKeyFileLineEdit->setEnabled(true);
    ui->rsaRandomizeFileButton->setEnabled(true);
    ui->rsaRandomizeFileLabel->setEnabled(true);
    ui->rsaRandomizeFileLineEdit->setEnabled(true);
    ui->rsaKeySizeLabel->setEnabled(true);
    ui->rsaKeySizeSpinBox->setEnabled(true);
}
void Dialog::rsaEncryptModeSelected()
{
    ui->textBrowser->insertPlainText("RSA: Encrypt mode\n");
    ui->inputFileButton->setEnabled(true);
    ui->inputFileLabel->setEnabled(true);
    ui->inputFileLineEdit->setEnabled(true);
    ui->outputFileButton->setEnabled(true);
    ui->outputFileLabel->setEnabled(true);
    ui->outputFileLineEdit->setEnabled(true);
    ui->rsaPublicKeyFileButton->setEnabled(true);
    ui->rsaPublicKeyFileLabel->setEnabled(true);
    ui->rsaPublicKeyFileLineEdit->setEnabled(true);
    ui->rsaPrivateKeyFileButton->setDisabled(true);
    ui->rsaPrivateKeyFileLabel->setDisabled(true);
    ui->rsaPrivateKeyFileLineEdit->setDisabled(true);
    ui->rsaRandomizeFileButton->setDisabled(true);
    ui->rsaRandomizeFileLabel->setDisabled(true);
    ui->rsaRandomizeFileLineEdit->setDisabled(true);
    ui->rsaKeySizeLabel->setDisabled(true);
    ui->rsaKeySizeSpinBox->setDisabled(true);
}
void Dialog::rsaDecryptModeSelected()
{
    ui->textBrowser->insertPlainText("RSA: Decrypt mode\n");
    ui->inputFileButton->setEnabled(true);
    ui->inputFileLabel->setEnabled(true);
    ui->inputFileLineEdit->setEnabled(true);
    ui->outputFileButton->setEnabled(true);
    ui->outputFileLabel->setEnabled(true);
    ui->outputFileLineEdit->setEnabled(true);
    ui->rsaPrivateKeyFileButton->setEnabled(true);
    ui->rsaPrivateKeyFileLabel->setEnabled(true);
    ui->rsaPrivateKeyFileLineEdit->setEnabled(true);
    ui->rsaPublicKeyFileButton->setDisabled(true);
    ui->rsaPublicKeyFileLabel->setDisabled(true);
    ui->rsaPublicKeyFileLineEdit->setDisabled(true);
    ui->rsaRandomizeFileButton->setDisabled(true);
    ui->rsaRandomizeFileLabel->setDisabled(true);
    ui->rsaRandomizeFileLineEdit->setDisabled(true);
    ui->rsaKeySizeLabel->setDisabled(true);
    ui->rsaKeySizeSpinBox->setDisabled(true);
}
void Dialog::on_rsaPublicKeyFileButton_clicked()
{
    if(0 == ui->rsaComboBox->currentIndex())
    {
        this->rsaPublicKeyFileName = QFileDialog::getSaveFileName(this, "Select Public Key File", ui->rsaPublicKeyFileLineEdit->text());
    }
    else
    {
        this->rsaPublicKeyFileName = QFileDialog::getOpenFileName(this, "Select Public Key File", ui->rsaPublicKeyFileLineEdit->text(), "All Files (*)");
    }
    if(!this->rsaPublicKeyFileName.isEmpty())
    {
        ui->rsaPublicKeyFileLineEdit->setText(this->rsaPublicKeyFileName);
        this->rsaPublicKeyFile.setFileName(this->rsaPublicKeyFileName);
        this->isRsaPublicKeyFile = true;
    }
    switch(ui->rsaComboBox->currentIndex())
    {
    case 0:
        if(this->isRsaPublicKeyFile && this->isRsaPrivateKeyFile && this->isRsaRandomizeFile)
            ui->rsaDoItButton->setEnabled(true);
        else
            ui->rsaDoItButton->setDisabled(true);
        break;
    case 1:
        if(this->isRsaPublicKeyFile && this->isInputFile && this->isOutputFile)
            ui->rsaDoItButton->setEnabled(true);
        else
            ui->rsaDoItButton->setDisabled(true);
        break;
    case 2:
        if(this->isRsaPrivateKeyFile && this->isInputFile && this->isOutputFile)
            ui->rsaDoItButton->setEnabled(true);
        else
            ui->rsaDoItButton->setDisabled(true);
        break;
    }
}
void Dialog::on_rsaPrivateKeyFileButton_clicked()
{
    if(0 == ui->rsaComboBox->currentIndex())
    {
        this->rsaPrivateKeyFileName = QFileDialog::getSaveFileName(this, "Select Private Key File", ui->rsaPrivateKeyFileLineEdit->text());
    }
    else
    {
        this->rsaPrivateKeyFileName = QFileDialog::getOpenFileName(this, "Select Private Key File", ui->rsaPrivateKeyFileLineEdit->text(), "All Files (*)");
    }
    if(!this->rsaPrivateKeyFileName.isEmpty())
    {
        ui->rsaPrivateKeyFileLineEdit->setText(this->rsaPrivateKeyFileName);
        this->rsaPrivateKeyFile.setFileName(this->rsaPrivateKeyFileName);
        this->isRsaPrivateKeyFile = true;
    }
    switch(ui->rsaComboBox->currentIndex())
    {
    case 0:
        if(this->isRsaPublicKeyFile && this->isRsaPrivateKeyFile && this->isRsaRandomizeFile)
            ui->rsaDoItButton->setEnabled(true);
        else
            ui->rsaDoItButton->setDisabled(true);
        break;
    case 1:
        if(this->isRsaPublicKeyFile && this->isInputFile && this->isOutputFile)
            ui->rsaDoItButton->setEnabled(true);
        else
            ui->rsaDoItButton->setDisabled(true);
        break;
    case 2:
        if(this->isRsaPrivateKeyFile && this->isInputFile && this->isOutputFile)
            ui->rsaDoItButton->setEnabled(true);
        else
            ui->rsaDoItButton->setDisabled(true);
        break;
    }
}
void Dialog::on_rsaRandomizeFileButton_clicked()
{
    this->rsaRandomizeFileName = QFileDialog::getOpenFileName(this, "Select Randomize Key File", ui->rsaRandomizeFileLineEdit->text(), "All Files (*)");
    if(!this->rsaRandomizeFileName.isEmpty())
    {
        ui->rsaRandomizeFileLineEdit->setText(this->rsaRandomizeFileName);
        this->rsaRandomizeFile.setFileName(this->rsaRandomizeFileName);
        this->isRsaRandomizeFile = true;
    }
    switch(ui->rsaComboBox->currentIndex())
    {
    case 0:
        if(this->isRsaPublicKeyFile && this->isRsaPrivateKeyFile && this->isRsaRandomizeFile)
            ui->rsaDoItButton->setEnabled(true);
        else
            ui->rsaDoItButton->setDisabled(true);
        break;
    case 1:
        if(this->isRsaPublicKeyFile && this->isInputFile && this->isOutputFile)
            ui->rsaDoItButton->setEnabled(true);
        else
            ui->rsaDoItButton->setDisabled(true);
        break;
    case 2:
        if(this->isRsaPrivateKeyFile && this->isInputFile && this->isOutputFile)
            ui->rsaDoItButton->setEnabled(true);
        else
            ui->rsaDoItButton->setDisabled(true);
        break;
    }
}
void Dialog::on_rsaDoItButton_clicked()
{
    RSA rsa;
    switch(ui->rsaComboBox->currentIndex())
    {
    case 0:
        if(this->rsaPublicKeyFile.open(QIODevice::WriteOnly) && \
                this->rsaPrivateKeyFile.open(QIODevice::WriteOnly) && \
                this->rsaRandomizeFile.open(QIODevice::ReadOnly))
        {
            int keySize = ui->rsaKeySizeSpinBox->value();
            rsa.GenerateKeys(&this->rsaPublicKeyFile, &this->rsaPrivateKeyFile,\
                                 &this->rsaRandomizeFile, keySize);
            ui->textBrowser->insertPlainText(\
                        QString("RSA: key of size = %1 bits successfully generated\n").arg(keySize));
            this->rsaPublicKeyFile.close();
            this->rsaPrivateKeyFile.close();
            this->rsaRandomizeFile.close();
        }
        else
            ui->textBrowser->insertPlainText("Error: some files can't be opened\n");
        break;
    case 1:
        if(this->rsaPublicKeyFile.open(QIODevice::ReadOnly) && \
                this->inputFile.open(QIODevice::ReadOnly) && \
                this->outputFile.open(QIODevice::WriteOnly))
        {
            rsa.Encrypt(&this->inputFile, &this->outputFile, &this->rsaPublicKeyFile);
            ui->textBrowser->insertPlainText(\
                        QString("RSA: data encryption of successfully\n"));
            this->rsaPublicKeyFile.close();
            this->inputFile.close();
            this->outputFile.close();
        }
        else
            ui->textBrowser->insertPlainText("Error: some files can't be opened\n");
        break;
    case 2:
        if(this->rsaPrivateKeyFile.open(QIODevice::ReadOnly) && \
                this->inputFile.open(QIODevice::ReadOnly) && \
                this->outputFile.open(QIODevice::WriteOnly))
        {
            rsa.Decrypt(&this->inputFile, &this->outputFile, &this->rsaPrivateKeyFile);
            ui->textBrowser->insertPlainText(\
                        QString("RSA: data decryption of successfully\n"));
            this->rsaPrivateKeyFile.close();
            this->inputFile.close();
            this->outputFile.close();
        }
        else
            ui->textBrowser->insertPlainText("Error: some files can't be opened\n");
        break;
    }
}
