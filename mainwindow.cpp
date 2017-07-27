#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QLineEdit>
#include <QDialog>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isUntitled = true;
    curFile = tr("unname.txt");
    setWindowTitle(curFile);
    findDlg = new QDialog(this);
    findDlg ->setWindowTitle(tr("find"));
    findLineEdit = new QLineEdit(findDlg);
    QPushButton *btn = new QPushButton(tr("find the next one"),findDlg);
    QVBoxLayout *layout= new QVBoxLayout(findDlg);
    layout->addWidget(findLineEdit);
    layout->addWidget(btn);
    connect(btn,&QPushButton::clicked,this,&MainWindow::showFindText);
    //ui->statusBar->showMessage("Welcome to Open Source community!",2000);
    statusLabel=new QLabel;
    statusLabel->setMinimumSize(150,20);
    statusLabel->setFrameShape(QFrame::WinPanel);
    statusLabel->setFrameShadow(QFrame::Sunken);
    ui->statusBar->addWidget(statusLabel);
    statusLabel->setText(tr("Welcome to OPen Source community!"));
    QLabel *permanent =new QLabel;
    permanent->setFrameStyle(QFrame::Box|QFrame::Sunken);
    permanent->setText(tr("xiaolingu@163.com"));
    permanent->setTextFormat(Qt::RichText);
    permanent->setOpenExternalLinks(true);
    ui->statusBar->addPermanentWidget(permanent);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::newFile()
{
    if(maybeSave()){
        isUntitled =true;
        curFile=tr("unname.txt");
        setWindowTitle(curFile);
        ui->textEdit->clear();
        ui->textEdit->setVisible(true);

    }
}
bool MainWindow::maybeSave()
{
  if(ui->textEdit->document()->isModified())
  {
      QMessageBox box;
      box.setWindowTitle(tr("warning"));
      box.setIcon(QMessageBox::Warning);
      box.setText(curFile+tr("is not saved,DO you want to save it?"));
      QPushButton *yesBtn = box.addButton(tr("Yes(&Y)"),
                                        QMessageBox::YesRole);
      box.addButton(tr("NO(&N)"),QMessageBox::NoRole);
      QPushButton *cancelBut = box.addButton(tr("Cancel"),
                                             QMessageBox::RejectRole);
      box.exec();
      if(box.clickedButton()==yesBtn)
          return save();
      else if(box.clickedButton()==cancelBut)
          return false;



  }
  return true;
}
bool MainWindow::save()
{
    if(isUntitled){
        return saveAs();
    }else{
        return saveFile(curFile);
    }
}
bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("save as"),curFile);
    if(fileName.isEmpty())return false;
    return saveFile(fileName);
}
bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,tr("multi-doc edit"),
                             tr("Can not write in file %1:/n %2")
                             .arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out<<ui->textEdit->toPlainText();
    QApplication::restoreOverrideCursor();
    isUntitled = false;
    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;
}
bool MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,tr("Multi-doc edit"),
                             tr("Can not read the File %1:\n%2.")
                             .arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    ui->textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();
    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;


}
void MainWindow::closeEvent(QCloseEvent *event)
{
    if(maybeSave()){
        event->accept();
    }
    else{
        event->ignore();
    }
}
void MainWindow::showFindText()
{
    QString str=findLineEdit->text();
    if(!ui->textEdit->find(str,QTextDocument::FindBackward))
    {
       QMessageBox::warning(this,tr("Find"),
                            tr("Can not find %1").arg(str));

    }
}

void MainWindow::on_actionNew_triggered()
{
    newFile();
}

void MainWindow::on_actionSave_triggered()
{
    save();
}

void MainWindow::on_actionSave_As_triggered()
{
    saveAs();
}


void MainWindow::on_actionOPen_triggered()
{
    if(maybeSave()){
        QString fileName=QFileDialog::getOpenFileName(this);
        if(!fileName.isEmpty()){
            loadFile(fileName);
            ui->textEdit->setVisible(true);
        }
    }
}


void MainWindow::on_actionClose_triggered()
{
    if(maybeSave()){
        ui->textEdit->setVisible(false);
    }
}


void MainWindow::on_actionExit_triggered()
{
    on_actionClose_triggered();
    qApp->quit();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionCute_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionFind_triggered()
{
    findDlg->show();
}
