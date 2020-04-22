#include "mainwindow.h"
//https://www.draw.io/?state=%7B%22ids%22:%5B%221j2n3zKBZTiV1pvSBbawUL633ih3vfUtN%22%5D,%22action%22:%22open%22,%22userId%22:%22111131452457637558449%22%7D#G1j2n3zKBZTiV1pvSBbawUL633ih3vfUtN
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initLayout();
    initSignalsAndSlots();
    authorizationForm->show();

}

void MainWindow::initLayout()
{
    setWindowTitle("Система штрих-кодирования");

    authorizationForm = new AuthorizationForm();
    tabWidget = new QTabWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout;
    addProductTypesForm = new AddProductTypesForm();
    addProductForm = new AddProductForm();
    addProtuctBtn = new QPushButton("Добавить изделие");
    addProtuctTypeBtn = new QPushButton("Добавить модель");
    QWidget* body = new QWidget;
    prodTypesTab = new ProductTypesTab();
    allProductsTab = new AllProductsTab();
    prodByTypesTab = new ProductsByTypesTab();
    prodTab = new ProductTab();

    tabWidget->addTab(prodTypesTab, "Модели");
    tabWidget->addTab(allProductsTab, "Все изделия");
    tabWidget->addTab(prodByTypesTab, "Изделия по моделям");
    tabWidget->addTab(prodTab, "Изделие");

    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(addProtuctBtn);
    mainLayout->addWidget(addProtuctTypeBtn);

    body->setLayout(mainLayout);
    setCentralWidget(body);
}

void MainWindow::initSignalsAndSlots()
{
    connect(addProtuctTypeBtn, SIGNAL(clicked()), this, SLOT(onClickedAddProtuctTypeBtn()));
    connect(addProtuctBtn, SIGNAL(clicked()), this, SLOT(onClickedAddProtuctBtn()));
    connect(tabWidget,SIGNAL(tabBarClicked(int)),this, SLOT(onClickedTabBar(int)));

    connect(addProductForm->getSubmitButton(), SIGNAL(clicked()), this, SLOT(formAddProdOnClickedSubmit()));
    connect(addProductTypesForm->getSubmitButton(),SIGNAL(clicked()), this, SLOT(formAddProdTypeClickedSubmit()));

    connect(prodByTypesTab->getProductTypesComboBox(), SIGNAL(currentTextChanged(const QString&)),
            this, SLOT(tabProdByTypesChangedTypes(const QString&)));

    connect( prodTab->getProductTypesComboBox(), SIGNAL(currentTextChanged(const QString&)),
             this, SLOT(tabProdChangeTypes(const QString &)));
    connect( prodTab->getProductIdsComboBox(), SIGNAL(currentTextChanged(const QString&)),
             this, SLOT(tabProdChangeId(const QString &)));
    connect(addProductForm, SIGNAL(needPrintBarecode(const QList<QImage>& )), this, SLOT(printBarecode(const QList<QImage> &)));
    connect(addProductForm, SIGNAL(needSaveBarecode(const QList<QImage>& )), this, SLOT(saveBarecode(const QList<QImage> &)));

    connect(prodTab, SIGNAL(needPrintBarecode(const QList<QImage>& )), this, SLOT(printBarecode(const QList<QImage> &)));
    connect(prodTab, SIGNAL(needSaveBarecode(const QList<QImage>& )), this, SLOT(saveBarecode(const QList<QImage> &)));

    connect(authorizationForm->getButtonEnter(), SIGNAL(clicked()),this, SLOT(authorizate()));

    connect(prodTypesTab->getProductTypeTable(), SIGNAL(cellDoubleClicked(int, int)), this, SLOT(tabProdTypesOnDoubleClicked(int, int)));
    connect(prodByTypesTab->getProductsTable(), SIGNAL(cellDoubleClicked(int, int)), this, SLOT(tabProdByTypesOnDoubleClicked(int, int)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::onClickedAddProtuctTypeBtn(){

    this->addProductTypesForm->show();
}

void MainWindow::onClickedAddProtuctBtn(){
    this->addProductForm->show();
}

void MainWindow::onClickedTabBar(int index){
    //тут через контроллер бд надо будет обновить данные в таблицах
    qDebug()<<"click "<<index<<" \n";
}

void MainWindow::formAddProdOnClickedSubmit()
{
    qDebug()<<"tabAddProdOnClickedSubmit\n";
    qDebug()<<this->addProductForm->getCurrentProductType()<<" "<<this->addProductForm->getCurrentAmount()<<"\n";
    this->addProductForm->updateAfterSubmit({"1","2"}, {});
}

void MainWindow::formAddProdTypeClickedSubmit()
{
    qDebug()<<"formAddProdTypeClickedSubmit";
    qDebug()<<this->addProductTypesForm->getCurrentProductTypeNameInput()<<"\n";
    this->addProductTypesForm->hide();
}

void MainWindow::tabProdByTypesChangedTypes(const QString &text)
{
    qDebug()<<"tabProdByTypesChangedTypes  "<<text<<"\n";
    prodByTypesTab->updateProductTypes({});
    prodByTypesTab->updateTableData({});
}



void MainWindow::tabProdChangeTypes(const QString &text)
{
    qDebug()<<"tabProdChangeTypes "<<text<<"\n";
    prodTab->updateIds({});

}

void MainWindow::tabProdChangeId(const QString &text)
{
     qDebug()<<"tabProdChangeId "<<text<<"\n";
     prodTab->updateTableData({});
}

void MainWindow::printBarecode(const QList<QImage> &img)
{
   qDebug()<<"print barecode\n";
}

void MainWindow::saveBarecode(const QList<QImage> &img)
{
    qDebug()<<"save Barecode\n";
}

void MainWindow::authorizate()
{
     qDebug()<<"Login "<<authorizationForm->getUserName();
     qDebug()<<"Password "<<authorizationForm->getPassword()<<"\n";
     bool flag = !authorizationForm->getUserName().isEmpty() && !authorizationForm->getPassword().isEmpty();
     authorizationForm->afterLoginRequest(flag);
}



void MainWindow::tabProdTypesOnDoubleClicked(int row, int column)
{
    qDebug()<<"tabProdTypesOnDoubleClicked"<<row<<" "<<column<<" " <<((QLabel*)(prodTypesTab->getProductTypeTable()->cellWidget(row,column)))->text()<<"\n";
    //prodByTypesTab->updateProductTypes({prodTypesTab->getProductTypeTable()->cellWidget(row,column)});
    prodByTypesTab->updateTableData({});
    prodTab->updateProductTypes({});
    prodTab->updateIds({});
    tabWidget->setCurrentWidget(prodByTypesTab);
}

void MainWindow::tabProdByTypesOnDoubleClicked(int row, int column)
{
    qDebug()<<"tabProdTypesOnDoubleClicked"<<row<<" "<<column<<" " <<((QLabel*)(prodByTypesTab->getProductsTable()->cellWidget(row,column)))->text()<<"\n";
    tabWidget->setCurrentWidget(prodTab);
}
