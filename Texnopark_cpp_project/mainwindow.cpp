#include "mainwindow.h"


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
    connect(addProductForm, SIGNAL(needSaveBarecode(const QList<QImage>&, const QString&)), this, SLOT(saveBarecode(const QList<QImage>&, const QString&)));

    connect(prodTab, SIGNAL(needPrintBarecode(const QList<QImage>& )), this, SLOT(printBarecode(const QList<QImage> &)));
    connect(prodTab, SIGNAL(needSaveBarecode(const QList<QImage>& , const QString& )), this, SLOT(saveBarecode(const QList<QImage>&, const QString&)));

    connect(authorizationForm->getButtonEnter(), SIGNAL(clicked()),this, SLOT(authorizate()));

    connect(prodTypesTab->getProductTypeTable(), SIGNAL(cellDoubleClicked(int, int)), this, SLOT(tabProdTypesOnDoubleClicked(int, int)));
    connect(prodByTypesTab->getProductsTable(), SIGNAL(cellDoubleClicked(int, int)), this, SLOT(tabProdByTypesOnDoubleClicked(int, int)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::onClickedAddProtuctTypeBtn(){

    addProductTypesForm->show();
}

void MainWindow::onClickedAddProtuctBtn(){
    addProductForm->getSubmitButton()->setHidden(false);
    addProductForm->updateProductTypes(controllerForDataBase.getTypesList());
    addProductForm->show();
}

void MainWindow::onClickedTabBar(int index){
    qDebug()<<"click "<<index<<" \n";
    switch (index) {
    case 0:
    {
        qDebug()<<"0\n";
        prodTypesTab->updateTableData(controllerForDataBase.getAllProductsType());
        break;
    };

    case 1:
    {
        qDebug()<<"1\n";
        allProductsTab->updateTableData(controllerForDataBase.getAllProducts());
        break;
    };
    }
}

void MainWindow::formAddProdOnClickedSubmit()
{
    qDebug()<<"tabAddProdOnClickedSubmit\n";
    qDebug()<<addProductForm->getCurrentProductType()<<" "<<this->addProductForm->getCurrentAmount()<<"\n";
    QStringList ids = controllerForDataBase.addProduct(addProductForm->getCurrentProductType(),this->addProductForm->getCurrentAmount());
    if(ids.empty()){
        (new QErrorMessage())->showMessage("Возникла ошибка, проверьте соединение с интернетом и попробуйте снова");
    }
    QList<QImage> imgs;
    for(auto i:ids){
        imgs.push_back(controllerForBarecode.transformIdToBarecode(i));
    }
    addProductForm->updateAfterSubmit(ids,imgs);
}

void MainWindow::formAddProdTypeClickedSubmit()
{
    qDebug()<<"formAddProdTypeClickedSubmit";
    qDebug()<<addProductTypesForm->getCurrentProductTypeNameInput()<<"\n";
    bool correct =  controllerForDataBase.addProductType(addProductTypesForm->getCurrentProductTypeNameInput());
    if(!correct){
        (new QErrorMessage())->showMessage("Возникла ошибка, проверьте соединение с интернетом и попробуйте снова");
    }
    addProductTypesForm->hide();
}


void MainWindow::tabProdChangeTypes(const QString &type)
{
    qDebug()<<"tabProdChangeTypes "<<type<<"\n";
    prodTab->updateIds(controllerForDataBase.getIdByType(type));

}

void MainWindow::tabProdChangeId(const QString &id)
{
    qDebug()<<"tabProdChangeId "<<id<<"\n";
    QString productType = prodTab->getProductTypesComboBox()->currentText();
    prodTab->updateTableDateAndBarecode(controllerForDataBase.getProductHistory(productType, id), controllerForBarecode.transformIdToBarecode(id));
}

void MainWindow::printBarecode(const QList<QImage> &img)
{
    qDebug()<<"print barecode\n";
    for(auto image: img){
        controllerForBarecode.printBarecode(image);
    }

}

void MainWindow::saveBarecode(const QList<QImage>& img, const QString& filename)
{
    int i = 1;
    for(auto imgage: img){
        controllerForBarecode.saveBarecodeInFile(imgage, filename+QString::number(i++));
    }
    qDebug()<<"save Barecode\n";
}

void MainWindow::authorizate()
{
    qDebug()<<"Login "<<authorizationForm->getUserName();
    qDebug()<<"Password "<<authorizationForm->getPassword()<<"\n";
    bool authorized = controllerForDataBase.isAuthorized(authorizationForm->getUserName(), authorizationForm->getPassword());
    if(authorized){
        prodTypesTab->updateTableData(controllerForDataBase.getAllProductsType());
        allProductsTab->updateTableData(controllerForDataBase.getAllProducts());
        prodByTypesTab->updateProductTypes(controllerForDataBase.getTypesList());
        prodTab->updateProductTypes(controllerForDataBase.getTypesList());
    }
    authorizationForm->afterLoginRequest(authorized);
}



void MainWindow::tabProdTypesOnDoubleClicked(int row, int column)
{
    qDebug()<<"tabProdTypesOnDoubleClicked"<<row<<" "<<column<<" " <<((QLabel*)(prodTypesTab->getProductTypeTable()->cellWidget(row,column)))->text()<<"\n";
    if(column!=0)
        return;
    QString productType = ((QLabel*)(prodTypesTab->getProductTypeTable()->cellWidget(row,column)))->text();
    prodByTypesTab->updateProductTypes(controllerForDataBase.getTypesList());
    prodByTypesTab->getProductTypesComboBox()->setCurrentText(productType);
    tabWidget->setCurrentWidget(prodByTypesTab);
}

void MainWindow::tabProdByTypesChangedTypes(const QString &productType)
{
    qDebug()<<"tabProdByTypesChangedTypes  "<<productType<<"\n";
    prodByTypesTab->updateTableData(controllerForDataBase.getProductsByType(productType));
}

void MainWindow::tabProdByTypesOnDoubleClicked(int row, int column)
{
    QString productType = ((QLabel*)(prodByTypesTab->getProductsTable()->cellWidget(row,0)))->text();
    QString id = ((QLabel*)(prodByTypesTab->getProductsTable()->cellWidget(row,column)))->text();

    qDebug()<<"tabProdByTypesOnDoubleClicked"<<row<<" "<<column<<" " <<productType<< id<<"\n";
    if(column!=2)
        return;
    prodTab->updateIds(controllerForDataBase.getIdByType(productType));
    prodTab->updateProductTypes(controllerForDataBase.getTypesList());
    prodTab->getProductIdsComboBox()->setCurrentText(id);
    prodTab->getProductTypesComboBox()->setCurrentText(productType);
    prodTab->updateTableDateAndBarecode(controllerForDataBase.getProductHistory(productType, id),controllerForBarecode.transformIdToBarecode(id));
    tabWidget->setCurrentWidget(prodTab);
}
