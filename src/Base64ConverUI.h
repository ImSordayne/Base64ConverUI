/*
 * @Author: Sordayne 455248805@qq.com
 * @FilePath: \Base64ConverUI\src\Base64ConverUI.h
 */
#pragma once

#include <QMainWindow>
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QProgressBar>
#include <QProgressDialog>
#include "Base64Conver.h"

class Base64UI : public QMainWindow
{
    Q_OBJECT

public:
    Base64UI(QWidget *parent = nullptr);
    ~Base64UI();

private slots:
    void browseFileDir();
    void enCode();
    void deCode();

private:
    QLineEdit* pathEdit;
    QProgressBar *progressBar;
};
