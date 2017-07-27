#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCloseEvent>
#include <QLabel>

class QLineEdit;
class QDialog;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void newFile();
    bool maybeSave();
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    bool loadFile(const QString &fileName);

private slots:
    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionOPen_triggered();

    void on_actionClose_triggered();

    void on_actionExit_triggered();

    void on_actionUndo_triggered();

    void on_actionCute_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void showFindText();

    void on_actionFind_triggered();

private:
    Ui::MainWindow *ui;
    bool isUntitled;
    QString curFile;
    QLineEdit *findLineEdit;
    QDialog *findDlg;
    QLabel *statusLabel;
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
