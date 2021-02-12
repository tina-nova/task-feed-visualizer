//#include "activetab.h"
//#include "ui_activetab.h"
//
//ActiveTab::ActiveTab(QWidget *parent) :
//    QWidget(parent),
//    ui(new Ui::ActiveTab)
//{
//    ui->setupUi(this);
//}
//
//ActiveTab::~ActiveTab()
//{
//    delete ui;
//}
//
//
//class MainWindow : public QMainWindow
//{
//Q_OBJECT
//
//public:
//    explicit MainWindow(QWidget *parent = 0);
//    ~MainWindow();
//
//private slots:
//    void on_add_clicked();
//
//private:
//    Ui::MainWindow *ui;
//};
//
//MainWindow::MainWindow(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::MainWindow)
//{
//    ui->setupUi(this);
//    MyTabPage *myNewTab = new MyTabPage;
//    ui-> myTabWidget ->removeTab(0);
//    ui-> myTabWidget ->addTab(myNewTab, tr("name"))
//    myNewTab->functionDeclaredInMyTabPage (); //access parameters of myNewTab
//}
//
