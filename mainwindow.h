#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QFileDialog>
#include <DataDecoder.h>
#include <GraphPainter.h>
#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    DataDecoder decoder;
    QFileDialog* m_pFileDialog;
    GraphPainter* m_dGraphWidget;

    QPushButton* m_pButton;
    QMessageBox* m_pMessageBox;

private slots:
    void loadFile();
    void OpenDialog();
    void resizeEvent(QResizeEvent* event);
public:
    MainWindow(QWidget *parent = nullptr);
};
#endif // MAINWINDOW_H
