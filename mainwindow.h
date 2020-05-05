#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_RED_Slider_valueChanged(int value);

    void on_GREEN_Slider_valueChanged(int value);

    void on_BLUE_Slider_valueChanged(int value);

    void updateRGB(QString);

private:
    Ui::MainWindow *ui;
    QSerialPort*arduino;
    static const quint16 arduino_uno_vendor_ID = 9025;
    static const quint16 arduino_uno_product_ID = 67;
    QString arduino_port_name;
    bool arduino_is_available;
};
#endif // MAINWINDOW_H
