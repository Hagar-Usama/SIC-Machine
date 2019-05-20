#ifndef WELCOME_H
#define WELCOME_H

#include <QMainWindow>

namespace Ui {
class Welcome;
}

class Welcome : public QMainWindow
{
    Q_OBJECT

public:
    explicit Welcome(QWidget *parent = nullptr);
    ~Welcome();

private slots:
    void on_exe_btn_clicked();

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

    void on_actionAssemble_triggered();

    void on_actionList_File_triggered();

    void on_actionObject_File_triggered();

    void on_actionSave_as_triggered();

    void on_actionLoad_Srcfile_triggered();

private:
    Ui::Welcome *ui;
};

#endif // WELCOME_H
