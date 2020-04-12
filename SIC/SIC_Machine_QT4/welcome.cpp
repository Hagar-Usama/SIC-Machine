#include "welcome.h"
#include "ui_welcome.h"

#include<QFileDialog>
#include<QMessageBox>
#include<QDir>
#include<QFile>
#include<QTextStream>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

string check_assembly(){

    ifstream infile;
    string read_file_name("state.txt");
    infile.open(read_file_name);
    vector<string> sLine;
    string str;
    while (!infile.eof())
    {
        infile >> str;
        sLine.push_back(str);
    }

    infile.close();
    return sLine[0];

}
QString write_in_file(QString file_name){
    QFile file(file_name);
    QTextStream in(&file);
    QString text =in.readAll();
    file.close();
    return text;
}

string convert_to_string(QString qs);

Welcome::Welcome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Welcome)
{
    ui->setupUi(this);
}

Welcome::~Welcome()
{
    delete ui;
}

void Welcome::on_exe_btn_clicked()
{
    //QString path = QDir::currentPath();
    //QMessageBox::warning(this,"Title",path);
    //system("g++ -o run run.cpp");
    system("./run");

    QString file_name = QDir::currentPath()+"/listfile.txt";
    QFile file(file_name);
        if(!file.open(QFile::ReadOnly|QFile::Text)){
            QMessageBox::warning(this,"Error","File not Found!");
        }
        QTextStream in(&file);
        QString text =in.readAll();
        ui->list_txt->setPlainText(text);
        file.close();


}


string convert_to_string(QString qs){
    // Either this if you use UTF-8 anywhere
    std::string text = qs.toUtf8().constData();
    // or this if you're on Windows :-)
    //std::string current_locale_text = qs.toLocal8Bit().constData();
    return  text;
}

/*
QString file_name = QFileDialog::getOpenFileName(this,"open source file",QDir::currentPath());
  QMessageBox::information(this,"..",file_name);
*/

void write_dic(string filename , string str){

      FILE *fp;

        fp = fopen(filename.c_str(),"w");
        if(fp == NULL) {
        //perror("Error");
        //exit(1);
        }
        else{

                fprintf (fp, "%s", str.c_str() );
            }

  fclose(fp);

    }

void Welcome::on_actionSave_triggered()
{
        QString text = ui->src_txt->toPlainText();
        string st_txt = convert_to_string(text);
        write_dic("src.txt",st_txt);


}

void Welcome::on_actionLoad_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,"open source file",QDir::currentPath());

    QFile file(file_name);
        if(!file.open(QFile::ReadOnly|QFile::Text)){
            QMessageBox::warning(this,"Title","File not Found!");
        }
        QTextStream in(&file);
        QString text =in.readAll();
        ui->src_txt->setPlainText(text);
        file.close();

        ui->toolBox->setCurrentIndex(0);
}

void Welcome::on_actionAssemble_triggered()
{
    system("g++ -o run run.cpp");
    system("./run");

    ui->toolBox->setCurrentIndex(0);

    QString file_name = QDir::currentPath()+"/state.txt";
    QFile file(file_name);
        if(!file.open(QFile::ReadOnly|QFile::Text)){
            QMessageBox::warning(this,"Error","File not Found!");
        }
        QTextStream in(&file);
        QString text =in.readAll();
        file.close();

        QMessageBox msgBox;
        msgBox.setText(text);
        msgBox.setWindowTitle("Info");
        msgBox.exec();



}


void Welcome::on_actionList_File_triggered()
{
    QString file_name = QDir::currentPath()+"/listfile.txt";
    QFile file(file_name);
        if(!file.open(QFile::ReadOnly|QFile::Text)){
            QMessageBox::warning(this,"Error","File not Found!");
        }
        QTextStream in(&file);
        QString text =in.readAll();
        ui->list_txt->setPlainText(text);
        file.close();

        ui->toolBox->setCurrentIndex(1);
}

void Welcome::on_actionObject_File_triggered()
{
    QString file_name = QDir::currentPath()+"/objectfile.txt";
    QFile file(file_name);
        if(!file.open(QFile::ReadOnly|QFile::Text)){
            QMessageBox::warning(this,"Error","File not Found!");
        }
        QTextStream in(&file);
        QString text =in.readAll();
        ui->obj_txt->setPlainText(text);
        file.close();

      ui->toolBox->setCurrentIndex(2);

}

void Welcome::on_actionSave_as_triggered()
{

    //QString file_name = QFileDialog::getOpenFileName(this,"open source file",QDir::currentPath());

   QString file_name = QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::currentPath());
    file_name.append("/untitled.txt");

    cout<<convert_to_string(file_name);
    QString text = ui->src_txt->toPlainText();
    string st_txt = convert_to_string(text);
    write_dic(convert_to_string(file_name),st_txt);


}

void Welcome::on_actionLoad_Srcfile_triggered()
{
        QString file_name = QDir::currentPath()+"/src.txt";
        QFile file(file_name);
        if(!file.open(QFile::ReadOnly|QFile::Text)){
            QMessageBox::warning(this,"Title","File not Found!");
        }
        QTextStream in(&file);
        QString text =in.readAll();
        ui->src_txt->setPlainText(text);
        file.close();

        ui->toolBox->setCurrentIndex(0);
}
