#include "Base64ConverUI.h"

Base64UI::Base64UI(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("文件Base64编解码器");

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    QFormLayout* formLayout = new QFormLayout();

    pathEdit = new QLineEdit(this);
    QPushButton* BrowseGameDirBtn = new QPushButton("浏览...", this);
    connect(BrowseGameDirBtn, &QPushButton::clicked, this, &Base64UI::browseFileDir);
    QHBoxLayout* DirLayout = new QHBoxLayout();
    DirLayout->addWidget(pathEdit);
    DirLayout->addWidget(BrowseGameDirBtn);
    formLayout->addRow("文件路径:", DirLayout);

    progressBar->setValue(0);
    QHBoxLayout *progressLayout = new QHBoxLayout();
    progressLayout->addWidget(progressBar);
    formLayout->addRow("进度:", progressLayout);


    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* enCodeButton = new QPushButton("编码");
    connect(enCodeButton, &QPushButton::clicked, this, &Base64UI::enCode);
    buttonLayout->addWidget(enCodeButton);
    QPushButton* deCodeButton = new QPushButton("解码");
    connect(deCodeButton, &QPushButton::clicked, this, &Base64UI::deCode);
    buttonLayout->addWidget(deCodeButton);
    formLayout->addRow(buttonLayout);
    mainLayout->addLayout(formLayout);
    
    resize(600, 150);
}

Base64UI::~Base64UI()
{}
void Base64UI::browseFileDir()
{
    QString Dir = QFileDialog::getOpenFileName(this, "选择文件路径ַ");
    if (!Dir.isEmpty()) {
        pathEdit->setText(Dir);
    }
}

void Base64UI::enCode() {
    QString filePath = pathEdit->text();
    if (filePath.isEmpty())QMessageBox::warning(this, "错误", "文件名不能为空");
    else try {
        QMessageBox::information(this, "编码", "开始编码...");
        bool res = Base64Conver::encFile(filePath.toStdString(), filePath.toStdString() + ".base64.txt", [this](size_t total, size_t convered) -> void* {
            progressBar->setValue(convered / total);
            return nullptr;
        });
        if(res)
            QMessageBox::information(this, "完成", "编码成功");
        else
            QMessageBox::information(this, "完成", "编码失败");
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "错误", e.what());
    }
}

void Base64UI::deCode() {

    QString filePath = pathEdit->text();
    std::string s_filePath = filePath.toStdString();
    if (filePath.isEmpty())QMessageBox::warning(this, "错误", "文件名不能为空");
    else if (s_filePath.size() < 11 || s_filePath.substr(s_filePath.size() - 11, 11) != ".base64.txt")QMessageBox::warning(this, "错误", "文件名不合法");
    else try {
        QMessageBox::information(this, "解码", "开始解码...");
        bool res = Base64Conver::decFile(filePath.toStdString(), s_filePath.substr(0, s_filePath.size() - 11), [this](size_t total, size_t convered) -> void* {
            progressBar->setValue(convered / total);
            return nullptr;
        });
        if(res)
            QMessageBox::information(this, "完成", "解码成功");
        else
            QMessageBox::information(this, "完成", "解码失败");
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "错误", e.what());
    }

}