#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(QApplication::desktop()->width() * 0.7, QApplication::desktop()->height() * 0.7);

    m_pMessageBox = new QMessageBox;
    m_pMessageBox->setIcon(QMessageBox::Information);
    m_pMessageBox->setStandardButtons(QMessageBox::Ok);
    m_pMessageBox->setFocusPolicy(Qt::NoFocus);

    m_pFileDialog = new QFileDialog(this);
    QObject::connect(m_pFileDialog, SIGNAL(accepted()), SLOT(loadFile()), Qt::QueuedConnection);

    m_pFileDialog->setNameFilter("*.ssd *.rsd *.txt");

    m_dGraphWidget= new GraphPainter(&decoder, this);

    m_pButton = new QPushButton("Open file", this);
    QObject::connect(m_pButton, SIGNAL(clicked()), SLOT(OpenDialog()), Qt::QueuedConnection);

};
void MainWindow::loadFile()
{
    QStringList SelectedList = m_pFileDialog->selectedFiles();
    if(SelectedList.isEmpty() == true)
    {
        return;
    }

    decoder.Clear();

    uint16_t mask = decoder.load(SelectedList.at(0).toStdString());
    if(mask & 0x01)
    {
        m_pMessageBox->setText("File cannot be opened");
        m_pMessageBox->show();
    }
    if(mask & 0x02)
    {
        m_pMessageBox->setText("Wrong data format");
        m_pMessageBox->show();
    }
    if(mask & 0x04)
    {
        m_pMessageBox->setText("Unable to convert string to double");
        m_pMessageBox->show();
    }
    if(mask & 0x08)
    {
        m_pMessageBox->setText("The file does not contain measurement data");
        m_pMessageBox->show();
    }
    update();
}
void MainWindow::OpenDialog()
{
    m_pFileDialog->show();
}
void MainWindow::resizeEvent(QResizeEvent* event)
{
    m_dGraphWidget->setMinimumSize(width(), height() * 0.9);
    m_pMessageBox->setFixedSize(width() * 0.3 , height() * 0.3);

    QWidget::resizeEvent(event);
}
