#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>  //allows you to use the serial port functions
#include <QSerialPortInfo> //gives you information about the seriaal ports
#include <QDebug>   //
#include <QMessageBox>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    arduino_is_available = false;
    arduino_port_name = "";
    arduino = new QSerialPort;

    /*FIND ARDUINO PRODUCT AND VENDOR ID
     * qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length(); //Tells us which ports are available
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) //searvh through each available port
    {
        qDebug() << "Has vendor ID " << serialPortInfo.hasVendorIdentifier();
        if (serialPortInfo.hasVendorIdentifier()) //if the vendor has an ID
        {
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier(); //gives the ID
        }
        qDebug() << "Has product ID " << serialPortInfo.hasProductIdentifier();
        if (serialPortInfo.hasProductIdentifier()) //if the product has an ID
        {
            qDebug() << "Product ID: " << serialPortInfo.productIdentifier(); //gives the ID
        }
        //Vendor ID is a specific number issued to a COMPANY by official USB manufacturers.
        //Product ID is a specific number issued to Each Product/DEVICE the company registers.
    }*/

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        if (serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()) //is there a port with both vendor & product ID?
        {
            if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_ID) // does the vendor ID match arduino uno?
            {
                if(serialPortInfo.productIdentifier() == arduino_uno_product_ID) // does the product ID also match arduino uno?
                {
                    arduino_port_name = serialPortInfo.portName(); //assign the port name as arduino_uno...
                    arduino_is_available = true; //the arduino is now set as available to be used
                }
            }
        }
    }

    if(arduino_is_available)
    {
        //open and configure the serialport
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::WriteOnly); //setting it to write only because we are only sending commands
        arduino->setBaudRate(QSerialPort::Baud9600); //make sure you set the baudrate to the same value on arduinoIDE!
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
    }
    else
    {
        //give an error message if not available
        QMessageBox::warning(this,"Port Error","Couldn't find Arduino!");
    }
}

MainWindow::~MainWindow()
{
    if(arduino->isOpen())
    {
        arduino->close(); //closes the serialport
    }
    delete ui;
}

void MainWindow::on_RED_Slider_valueChanged(int value)
{
    ui->red_value_label->setText(QString("<span style=\" font-size:16pt; font-weight:600;\">%1</span>").arg(value));
    MainWindow::updateRGB(QString("r%1").arg(value));
    qDebug() << value;
}
void MainWindow::on_GREEN_Slider_valueChanged(int value)
{
    ui->green_value_label->setText(QString("<span style=\" font-size:16pt; font-weight:600;\">%1</span>").arg(value));
    MainWindow::updateRGB(QString("g%1").arg(value));
    qDebug() << value;
}

void MainWindow::on_BLUE_Slider_valueChanged(int value)
{
    ui->blue_value_label->setText(QString("<span style=\" font-size:16pt; font-weight:600;\">%1</span>").arg(value));
    MainWindow::updateRGB(QString("b%1").arg(value));
    qDebug() << value;
}

void MainWindow::updateRGB(QString command)
{
   if(arduino->isWritable())
   {
       arduino->write(command.toStdString().c_str());
   }
   else
   {
       qDebug() << "Couldn't Write to SerialPort!";
   }
}
