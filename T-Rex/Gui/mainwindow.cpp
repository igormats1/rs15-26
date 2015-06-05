#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "uvodframe.h"
#include "editorframe.h"
#include "automatframe.h"
#include "diagramframe.h"
#include "guibuilder.h"
#include "maildialog.h"

#include <QPushButton>
#include <QDockWidget>
#include <QMessageBox>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/images/icon/progIcon.png"));
    this->setWindowTitle("T-Rex");
    this->setMinimumSize(QSize(600, 450));

    createStatusBar();
    createMainView();
    createButtonGroup();

    //samo konekcije
    setUpMenuActions();

    /*
     * istorija moze da se cuva npr u XML formatu
     * ovde bi mogla da se ucitava
     * da se npr trazi od korisnika da cekira workspace
     * i tako to
     * mozda u engine imati posebnu klasu za istoriju
     */
}

void MainWindow::closeEvent(QCloseEvent *event){
    if(GuiBuilder::leaveProgramDialog())
        event->accept();
    else
        event->ignore();
}

void MainWindow::updateStatusBar(QString& s){
    lStatus->setText(s);
}

 void MainWindow::createStatusBar(){

     lStatus = new QLabel("");
     lStatus->setMinimumSize(lStatus->sizeHint());
     ui->statusBar->addWidget(lStatus, 1);

 }

void MainWindow::setUpMenuActions(){

    //postavljanje dogadjaja za celine
    connect(&switchForm, SIGNAL(mapped(int)), this, SLOT(go_to_form(int)));

    connect(bUvod, SIGNAL(clicked()), &switchForm, SLOT(map()));
    switchForm.setMapping(bUvod, 0);

    connect(bEditor, SIGNAL(clicked()), &switchForm, SLOT(map()));
    switchForm.setMapping(bEditor, 1);

    connect(bAutomat, SIGNAL(clicked()), &switchForm, SLOT(map()));
    switchForm.setMapping(bAutomat, 2);

    //postavljanje dogadjaja za menu bar
    connect(ui->actionNapusti_program, SIGNAL(triggered()), this, SLOT(napustiProgram()));
    connect(ui->actionAbout_T_Rex, SIGNAL(triggered()), this, SLOT(about_app()));
    connect(ui->actionCeline, SIGNAL(triggered(bool)), this, SLOT(prikazCeline(bool)));
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), this, SLOT(menuAboutQt()));

    connect(content,SIGNAL(visibilityChanged(bool)), this, SLOT(azurirajMeniContent(bool)));

    //konekcije za prikazi menu bar
    connect(ui->actionUvod, SIGNAL(triggered()), &switchForm, SLOT(map()));
    switchForm.setMapping(ui->actionUvod, 0);

    connect(ui->actionEditor, SIGNAL(triggered()), &switchForm, SLOT(map()));
    switchForm.setMapping(ui->actionEditor, 1);

    connect(ui->actionAutomat, SIGNAL(triggered()), &switchForm, SLOT(map()));
    switchForm.setMapping(ui->actionAutomat, 2);

    connect(ui->actionDiagram, SIGNAL(triggered()), &switchForm, SLOT(map()));
    switchForm.setMapping(ui->actionDiagram, 3);

    //konekcije za prikazi menu bar
    connect(ui->actionBroj_prepoznatih, SIGNAL(triggered(bool)), _editor, SLOT(showNumMatched(bool)));

    //slotovi za net
    connect(&goToWeb, SIGNAL(mapped(QString)), this, SLOT(loadWebPage(QString)));

    connect(ui->actionT_Rex_GitHub, SIGNAL(triggered()), &goToWeb, SLOT(map()));
    goToWeb.setMapping(ui->actionT_Rex_GitHub, "https://github.com/MATF-RS15/rs15-26");

    connect(ui->actionT_Rex_Fb, SIGNAL(triggered()), &goToWeb, SLOT(map()));
    goToWeb.setMapping(ui->actionT_Rex_Fb, "https://www.facebook.com");

    connect(ui->actionT_Rex_Twitter, SIGNAL(triggered()), &goToWeb, SLOT(map()));
    goToWeb.setMapping(ui->actionT_Rex_Twitter, "https://www.twitter.com");

    connect(ui->actionPodrska, SIGNAL(triggered()), this, SLOT(sendMail()));
    //----------------


    //konekcije za boje
    connect(&changeAutomataColor, SIGNAL(mapped(QString)), _automat, SLOT(colorChanged(QString)));

    connect(ui->actionCrvena, SIGNAL(triggered()), &changeAutomataColor, SLOT(map()));
    changeAutomataColor.setMapping(ui->actionCrvena, "crvena");

    connect(ui->actionZelena, SIGNAL(triggered()), &changeAutomataColor, SLOT(map()));
    changeAutomataColor.setMapping(ui->actionZelena, "zelena");

    connect(ui->actionZuta, SIGNAL(triggered()), &changeAutomataColor, SLOT(map()));
    changeAutomataColor.setMapping(ui->actionZuta, "zuta");
}

void MainWindow::sendMail(){

    MailDialog mail;
    mail.exec();

}

void MainWindow::loadWebPage(QString id){

    bool anw = QDesktopServices::openUrl(QUrl(id, QUrl::StrictMode));

    if(!anw)
        GuiBuilder::throwErrorMessage("Proverite internet konekciju ili ispravnost podrazumevanog web pretrazivaca.");
}

void MainWindow::azurirajMeniContent(bool tmp){
    ui->actionCeline->setChecked(tmp);
}

void MainWindow::prikazCeline(bool chk){
    if(chk)
        content->show();
    else
        content->hide();
}

void MainWindow::about_app(){
    QMessageBox::about(this, tr("About T-Rex"),
    tr("<h2>T-Rex 0.1</h2>"
    "<p>Copyright &copy; 2015 Software Inc."
    "<p>T-Rex is a small application that "
    "help us understand and learn regular expressions."
    "<p>Implement in Qt."));
}

void MainWindow::napustiProgram(){

    if(GuiBuilder::leaveProgramDialog())
        QApplication::exit();

}

void MainWindow::menuAboutQt(){
    QMessageBox::aboutQt(this, "T-Rex");
}

void MainWindow::createMainView(){

    mainw = new QStackedWidget();
    mainw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    _uvod = new UvodFrame();
    _editor = new EditorFrame();
    _automat = new AutomatFrame();
    _diagram = new DiagramFrame();

    mainw->addWidget(_uvod);
    mainw->addWidget(_editor);
    mainw->addWidget(_automat);
    mainw->addWidget(_diagram);

    this->setCentralWidget(mainw);
}


QPushButton* MainWindow::createButton(const char *name, const char *info){

    QString path = QString(":/images/icon/") + QString(name) + QString(".png");
    return GuiBuilder::createIconButton(path, QString(info), 50);

}

void MainWindow::createButtonGroup(){

    bttnGroup = new QButtonGroup();
    bttnBar = new QToolBar(tr("Celine"));

    bttnBar->setOrientation(Qt::Vertical);

    bUvod = createButton("uvod", "Uvod u svet regularnih izraza");
    bEditor = createButton("editor", "Pronadji regularne izraze u tekstu");
    bAutomat = createButton("automat", "Konstruisi automat za regularni izraz");

    bttnGroup->addButton(bUvod);
    bttnGroup->addButton(bEditor);
    bttnGroup->addButton(bAutomat);


    bttnBar->addWidget(bUvod);
    bttnBar->addWidget(bEditor);
    bttnBar->addWidget(bAutomat);


    //centritati button-e na sredinu kolone?!

    content = new QDockWidget(tr("Celine"));
    content->setWidget(bttnBar);
    content->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    content->setMinimumWidth(90);
    addDockWidget(Qt::LeftDockWidgetArea, content);

    /*
     * napraviti neku novu formu, da inicijalno nju prikazije
     * ne mora da ima mehanizam povratka na nju
     * ui->stackedWidget->setCurrentIndex();
     */

}

void MainWindow::go_to_form(int i){
    mainw->setCurrentIndex(i);
    if(i == 0)
        this->setWindowTitle("T-Rex: Uvod");
    else if(i == 1)
        this->setWindowTitle("T-Rex: Editor");
    else if(i == 2)
            this->setWindowTitle("T-Rex: Automat");
    else if(i == 3)
        this->setWindowTitle("T-Rex: Diagram");
}


MainWindow::~MainWindow()
{
    delete ui;
    delete bUvod; delete bEditor; delete bAutomat; delete lStatus;
    delete bttnGroup; delete bttnBar; delete content;
    delete mainw;
}
