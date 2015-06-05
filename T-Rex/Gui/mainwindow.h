#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QDockWidget>
#include <QStackedWidget>

#include "uvodframe.h"
#include "editorframe.h"
#include "automatframe.h"
#include "diagramframe.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private Q_SLOTS:
    void go_to_form(int i);
    void napustiProgram();
    void updateStatusBar(QString& s);
    void about_app();
    void prikazCeline(bool chk);
    void azurirajMeniContent(bool tmp);
    void loadWebPage(QString id);
    void sendMail();
    void menuAboutQt();

private:

    Ui::MainWindow *ui;

    QButtonGroup *bttnGroup;
    QToolBar *bttnBar;
    QPushButton *bUvod, *bEditor, *bAutomat;
    QLabel *lStatus;
    QDockWidget *content;
    QStackedWidget *mainw;

    QSignalMapper switchForm, goToWeb, changeAutomataColor;

    //ako zatreba, a ako ne bude trebalo izbrisati
    UvodFrame *_uvod;
    EditorFrame *_editor;
    AutomatFrame *_automat;
    DiagramFrame *_diagram;

    QPushButton* createButton(const char *name, const char *info);
    void createButtonGroup();
    void createMainView();
    void createStatusBar();
    void setUpMenuActions();

    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
