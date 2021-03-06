#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QtCore>
#include <QDebug>
#include <QColor>
#include <QTextEdit>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    setWindowTitle("SimpleText v0.1.4 | Programmed by: Hayden Hildreth");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open file");
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Unable to open file: " + file.errorString());
        return;
    }
    setWindowTitle("SimpleText v0.1.4 | Programmed by: Hayden Hildreth | Open location: " + fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Unable to save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle("SimpleText v0.1.4 | Programmed by: Hayden Hildreth | Open location: " + fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog pDialog(&printer, this);
    if(pDialog.exec() == QDialog::Rejected)
    {
        QMessageBox::warning(this, "Warning", "Cannot access printer");
        return;
    }
    ui->textEdit->print(&printer);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();

}

void MainWindow::on_actionLight_triggered()
{
    qApp->setStyleSheet("QTextEdit { background-color: white; color: black; }");
}

void MainWindow::on_actionDark_triggered()
{
    qApp->setStyleSheet("QTextEdit { background-color: #A9A9A9; color: white; }");
}

void MainWindow::on_actionSalmon_triggered()
{
    qApp->setStyleSheet("QTextEdit { background-color: pink; color: white; }");
}

void MainWindow::on_actionHacker_triggered()
{
    qApp->setStyleSheet("QTextEdit { background-color: black; color: green; }");
}
