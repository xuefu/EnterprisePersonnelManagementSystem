#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "WelcomeWorkers.h"
#include "WelcomeManagers.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    WelcomeWorkers welworkers;
    WelcomeManagers welmanagers;

private slots:
    void backToLogin();
    void on_login_login_clicked();
};

#endif // MAINWINDOW_H
