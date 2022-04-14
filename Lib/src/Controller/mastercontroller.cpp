#include "mastercontroller.h"
#include<QDebug>
namespace Controller {

class MasterController::Implimentation
{
public:
    Implimentation(MasterController* _masterc,Database_controller *_maindatabaec)
        :masterC(_masterc), database(_maindatabaec)
    {
        navigation=new NavigationController(masterC);
        database=new Database_controller(masterC);
        Stocks=new Model::Report_Model(masterC);
        Inventory=new Model::Report_Model(masterC);
        sales  =new Model::Sales_model (masterC);
        returns  =new Model::Sales_model (masterC);
        mostsold  =new Model::Sales_model (masterC);
        Cart=new Model::Sales_model(masterC);
        Search_Stock_to_Cart=new Model::Sales_model(masterC);
        employee=new Model::EmployeeModel(masterC);
        SalesReport=new Model::ReturnsModel(masterC);
        ReturnReport=new Model::ReturnsModel(masterC);
        MostsoldReport=new Model::ReturnsModel(masterC);
        Expensis=new Model::ExpenisisModel(masterC);

    }
    MasterController *masterC=new MasterController{nullptr};
    NavigationController * navigation=new NavigationController{nullptr};
    Database_controller * database=new Database_controller{nullptr};
    Model::Report_Model *Stocks=new Model::Report_Model(nullptr);
    Model::Report_Model *Inventory=new Model::Report_Model(nullptr);
    Model::Sales_model *sales=new Model::Sales_model(nullptr);
    Model::Sales_model *returns=new Model::Sales_model(nullptr);
    Model::Sales_model *mostsold=new Model::Sales_model(nullptr);
    Model::Sales_model *Cart=new Model::Sales_model(nullptr);
    Model::Sales_model *Search_Stock_to_Cart =new Model::Sales_model(nullptr);
    Model::EmployeeModel* employee=new Model::EmployeeModel(nullptr);
    Model::ReturnsModel* SalesReport=new Model::ReturnsModel(nullptr);
    Model::ReturnsModel* ReturnReport=new Model::ReturnsModel(nullptr);
    Model::ReturnsModel* MostsoldReport=new Model::ReturnsModel(nullptr);
    Model::ExpenisisModel* Expensis=new Model::ExpenisisModel(nullptr);


};

MasterController::MasterController(QObject *parent, Database_controller *maincontroler)
    :QObject(parent)
{
    implimentation.reset(new Implimentation(this,maincontroler));

    populate_();
    readcompanyinfo();


}

MasterController::~MasterController()
{

}

NavigationController *MasterController::navigationController() const
{
    return implimentation->navigation;
}

QString MasterController::title() const
{
    return m_username;
}

bool MasterController::visible()
{
    return homebtn;
}

QJsonArray MasterController::Itemcategory() const
{

    return implimentation->database->read_Category();
}

Model::Report_Model *MasterController::Stocks()
{

    return implimentation->Stocks;
}

Model::Report_Model *MasterController::Inventory()
{
    return implimentation->Inventory;
}

Model::Sales_model *MasterController::Sales()
{
    return implimentation->sales;
}

Model::Sales_model *MasterController::Cat()
{
    return implimentation->Cart;
}

Model::Sales_model *MasterController::MostSold()
{
    return implimentation->mostsold;
}

Model::Sales_model *MasterController::Returns()
{
    return implimentation->returns;
}

Model::Sales_model *MasterController::Search_Stock_to_Cart()
{
    return implimentation->Search_Stock_to_Cart;
}

Model::EmployeeModel *MasterController::employee()
{
    return implimentation->employee;
}

Model::ReturnsModel *MasterController::SalesReport()
{
    return implimentation->SalesReport;
}

Model::ReturnsModel *MasterController::ReturnReport()
{
    return implimentation->ReturnReport;
}

Model::ReturnsModel *MasterController::MostsoldReport()
{
    return implimentation->MostsoldReport;
}

Model::ExpenisisModel *MasterController::Expensis()
{
    return implimentation->Expensis;
}
void MasterController::populate_Cart()
{
    auto data=implimentation->database->Read_Cart("cart");
    implimentation->Cart->populate(data);
    
}

bool MasterController::onLogin(QString username, QString pass)
{
 implimentation->navigation->goCreatedashboardView();
    m_username.clear();
    Role=7;
    userid=0;
    auto data=  implimentation->database->logincheck(username,pass);
    if(data.isEmpty()) return false;

    userid=data[0].toInt();
    Role=data[2].toInt();
    m_username=data[1];
    if(Role==1){
        homebtn=true;
        implimentation->navigation->goCreatedashboardView();
    }
    else if(Role==0){
        homebtn=false;
        implimentation->navigation->goCreateSales();
    }
    return true;
}

void MasterController::onLogout()
{

}

void MasterController::onPrint(QString name)
{


}

void MasterController::onExport(QString name)
{

}

void MasterController::onSearchChanged(QString text)
{
    Q_UNUSED(text);

}

void MasterController::onSearch(QString rootid, QString text, int index)
{   mSaleProfit=0;
    msaleTotal=0;
    mSaleAmount=0;
    mReturnProfit=0;
    mReturnTotal=0;
    mReturnAmount=0;
    mMstProfit=0;
    mMstTotal=0;
    mMstAmount=0;
    mSaleDProfit=0;
    mmSaleDTotal=0;
    mmSaleDAmount=0;
    totalexpensis=0;
    ExpenisiTransaction=0;

     mPLExpenisi=0;
     mPLDiscount=0;
    mPLInventory=0;
    mPLSales=0;
    mPLProfits=0;
    if(rootid=="sales"){
        implimentation->SalesReport->empty_data();

        if(!text.isEmpty()){
            auto sales=implimentation->database->read_Sales_report(QVariant(text).toInt(),0);
            implimentation->SalesReport->populate(sales);
            for(auto &d:sales){
                mSaleProfit+=d->profit();
                SaleProfitChanged();
                msaleTotal+=d->totalCost();
                saleTotalChanged();
                mSaleAmount=sales.count();
                SaleAmountChanged();
            }

        }
        else {
            auto sales=implimentation->database->read_Sales_report(0,index);
            implimentation->SalesReport->populate(sales);
            for(auto &d:sales){
                mSaleProfit+=d->profit();
                SaleProfitChanged();
                msaleTotal+=d->totalCost();
                saleTotalChanged();
                mSaleAmount=sales.count();
                SaleAmountChanged();
            }
        }
    }
    if(rootid=="most sold"){
        if(!text.isEmpty()){
            auto moststpld=implimentation->database->read_mostsold_report(QVariant(text).toInt(),0);
            implimentation->MostsoldReport->populate(moststpld);
            for(auto &d:moststpld){
                mMstProfit+=d->profit();
                MstProfitChanged();
                mMstTotal+=d->totalCost();
                MstTotalChanged();
                mMstAmount=moststpld.count();
                MstAmountChanged();
            }
        }
        else {
            auto moststpld=implimentation->database->read_mostsold_report(0,index);
            implimentation->MostsoldReport->populate(moststpld);
            for(auto &d:moststpld){
                mMstProfit+=d->profit();
                MstProfitChanged();
                mMstTotal+=d->totalCost();
                MstTotalChanged();
                mMstAmount=moststpld.count();
                MstAmountChanged();
            }
        }
    }
    if(rootid=="returns"){
        if(!text.isEmpty()){
            auto returns=implimentation->database->read_returns_report(QVariant(text).toInt(),0);
            implimentation->ReturnReport->populate(returns);
            for(auto &d:returns){
                mReturnProfit+=d->profit();
                ReturnProfitChanged();
                mReturnTotal+=d->totalCost();
                ReturnTotalChanged();
                mReturnAmount=returns.count();
                ReturnAmountChanged();
            }
        }else {
            auto returns=implimentation->database->read_returns_report(0,index);
            implimentation->ReturnReport->populate(returns);
            for(auto &d:returns){
                mReturnProfit+=d->profit();
                ReturnProfitChanged();
                mReturnTotal+=d->totalCost();
                ReturnTotalChanged();
                mReturnAmount=returns.count();
                ReturnAmountChanged();
            }
        }

    }
    inventoryProfit=0;
    inventoryTotal=0;
    minventoryAmount=0;

    if(rootid=="inventory"){
        if(!text.isEmpty()){
            auto inventory=implimentation->database->Read_Inventory(QVariant(text).toInt());
            implimentation->Inventory->populate(inventory);
            for(auto &d:inventory){
                inventoryProfit+=(d->Price()-d->Wholesaleprice())*d->Quantity();
                emit inverntoryprofitChanged();
                inventoryTotal+=d->Profit();
                emit inverntorytotalChanged();
                minventoryAmount=inventory.count();
                emit inverntoryAmountChanged();
            }
        }
        else {
            auto inventory=implimentation->database->Read_Inventory(0);
            implimentation->Inventory->populate(inventory);
            for(auto &d:inventory){
                inventoryProfit+=d->Profit();
                emit inverntoryprofitChanged();
                inventoryTotal+=d->Price();
                emit inverntorytotalChanged();
                minventoryAmount=inventory.count();
                emit inverntoryAmountChanged();
            }
        }
    }

    if(rootid=="saleDetails"){
        implimentation->sales->clear_data();

        if(!text.isEmpty()){
            auto dataitem=implimentation->database->Read_Sales_items(QVariant(text).toInt(),0);
            implimentation->sales->populate(dataitem);
            for(auto &d:dataitem){
                mSaleDProfit+=d->getProfit();
                emit SaleDProfitChanged();
                mmSaleDTotal+=d->Total_cost();
                emit MmSaleDTotalChanged();
                mmSaleDAmount=dataitem.count();
                emit MmSaleDAmountChanged();
            }
        }
        else {
            auto dataitem=implimentation->database->Read_Sales_items(0,index);
            implimentation->sales->populate(dataitem);
            for(auto &d:dataitem){
                mSaleDProfit+=d->getProfit();
                emit SaleDProfitChanged();
                mmSaleDTotal+=d->Total_cost();
                emit MmSaleDTotalChanged();
                mmSaleDAmount=dataitem.count();
                emit MmSaleDAmountChanged();
            }
        }
    }
    if(rootid=="Expensis"){
        if(!text.isEmpty()){
            auto dataitem=implimentation->database->read_expensis(QVariant(text).toInt(),0);
            implimentation->Expensis->populate(dataitem);
            for(auto &d:dataitem){
               totalexpensis+=d->Amount();
                emit expensistotalChanged();
                ExpenisiTransaction=dataitem.count();
                emit expensistotalChanged();
            }
        }
        else {
            auto dataitem=implimentation->database->read_expensis(0,index);
            implimentation->Expensis->populate(dataitem);
            for(auto &d:dataitem){
                totalexpensis+=d->Amount();
                emit expensistotalChanged();
                ExpenisiTransaction=dataitem.count();
                emit ExpensisTransactionChanged();
            }
        }
    }
    if(rootid=="ProfitLoss"){

        if(!text.isEmpty()){
            auto dataitem=implimentation->database->read_expensis(QVariant(text).toInt(),0);
        }
        else {
               //expensis stock sales discount
            auto dataitem=implimentation->database->readProfitLoss(0,index);
            mPLExpenisi=dataitem[0].toInt();
            emit PLExpenisiChanged();
            mPLInventory=dataitem[1].toInt();
            emit PLInventoryChanged();
            mPLDiscount=dataitem[3].toInt();
            emit PLDiscountChanged();
            mPLSales=dataitem[2].toInt();
            emit mPLSalesChanged();
            mPLProfits=dataitem[2].toInt()-dataitem[0].toInt();
            emit mPLProfitsChanged();



    }

}



}

void MasterController::onStock_search( QString text)const
{
    if(!text.isEmpty()){
        auto data= implimentation->database->Read_Stock_Search(text);
        implimentation->Stocks->populate(data);
    }
    else {
        auto data= implimentation->database->Read_Stock("");
        implimentation->Stocks->populate(data);
    }
}

void MasterController::onEmployee_search(QString text) const
{
    if(!text.isEmpty()){
        auto data= implimentation->database->search_employee(text);
        implimentation->employee->populate(data);
    }
    else {
        auto data= implimentation->database->readEmployee();
        implimentation->employee->populate(data);
    }
}

void MasterController::onQuantityChanged(QString id, int quantity)
{

    implimentation->Cart->update(id,quantity);

}

void MasterController::onDiscountChanged(QString id, int quantity)
{
    implimentation->Cart->Discount(id,quantity);
}

int MasterController::onCheckIndexCombo(QString id)
{
    int index=0;
    auto data= implimentation->database->read_Category();

    for(int i=0;i<data.count();i++){
        if(id==data[i].toString()){
            index=i;
            break;
        }
    }
    return index;
}

void MasterController::onAddtoCart(QString item)
{
    auto data=implimentation->database->Read_Stock_Search(item);
    if(data.size()==0){
        data.clear();
    }
    else if( data.size()>2){
        data.clear();
    }
    else {
        implimentation->Search_Stock_to_Cart->populate_item_single(QString::number(data[0]->id()),data[0]->Name(),data[0]->Category(),0,data[0]->Price(),data[0]->Price(),QDate::currentDate().toString(),"","",data[0]->Profit());
        data.clear();
    }
}

void MasterController::onClearcart()
{
    implimentation->Cart->clear_data();
}

void MasterController::onRemoveRow(QString id)
{

    implimentation->Cart->Remove(id);
}


bool MasterController::onUpdate_items(int id, const QString name, const QString category, const int quantity, const int price, const int wholeprice, int discount)
{
    if(!implimentation->database->update_items(id,name,category,quantity,price,wholeprice,discount)) return false;
    return true;
}

void MasterController::onReload()
{
    auto data_stock= implimentation->database->Read_Stock("");
    implimentation->Stocks->populate(data_stock);
    Itemcategory();
    auto data_employee=implimentation->database->readEmployee();
    implimentation->employee->populate(data_employee);
    auto sales_report=implimentation->database->read_Sales_report(0,0);
    implimentation->SalesReport->populate(sales_report);

    auto inventory=implimentation->database->Read_Inventory(0);
    implimentation->Inventory->populate(inventory);

}

void MasterController::onRemoveEmployerr(int id)
{
    implimentation->employee->removeRow_(id);
    implimentation->database->remove_employee(id);


}
void MasterController::onPush_employee(QString fname, QString gender, QString lname, QString role, QString email, QString username, QString password,QString phone)
{
    implimentation->database->push_employee(fname,gender,lname,role,email,username,password,phone);
}

void MasterController::onUpdate_employee(int id, QString fname, QString gender, QString lname, QString role, QString email, QString username, QString password,QString phone)
{
    implimentation->database->update_employee(id,fname,gender,lname,role,email,username,password,phone);

}

void MasterController::onExport_to_csvQuery(QString rootid, QString text, int index)
{
    Q_UNUSED(text)
    Q_UNUSED(index)
    if(rootid=="sales"){
        implimentation->database->Csvread_Sales_report();

    }
    if(rootid=="most sold"){

        implimentation->database->Csvread_mostsold_report();


    }
    if(rootid=="returns"){

        implimentation->database->Csvread_returns_report();

    }
    if(rootid=="inventory"){
        implimentation->database->Export_toCsv();
    }

    if(rootid=="saleDetails"){

        implimentation->database->Export_toCsv_SalesDetails();

    }

}


void MasterController::onExport_to_csv(const QString table, const QString loc)
{
    Q_UNUSED(loc)

    implimentation->database->Export_toCsv();

}

void MasterController::onImport(QString tname, QString location)
{
    QString floc;
    floc.clear();
    for(int i=0;i<location.size();i++){
        if(i>7){
            floc.append(location[i]);
        }
    }
    implimentation->database->import(tname,floc);

}

void MasterController::onAddcategry(const QString text)
{
    implimentation->database->add_Category(text);
}

void MasterController::onAdd_items(const QString name, const QString category, const int quantity, const int price, const int wholesale, int discount)
{

    implimentation->database->push_Items(name,category,quantity,price,wholesale,discount);
}

bool MasterController::onPush_To_cart(QString id, QString name, QString category, int quantity, int cost, int totalcost, QString Date, int profit)
{
    try {
        implimentation->Cart->populate_item(id,name,category,quantity,cost,totalcost,Date,"","",profit);
         auto data=implimentation->Cart->getData();
    } catch (errno_t) {
        qDebug()<<"there was an error";
    }
    return true;

}
void MasterController::onSuspend_sales()
{

}

bool MasterController::onPayment(int Recipttype, int Grandtotal, QString Paymenttype, int Change,int discount)
{
    int profit=0;
    Q_UNUSED(Recipttype)
    int sales_id= implimentation->database->push_sale(userid,QDateTime::currentDateTime().toString());

    auto data=  implimentation->Cart->getData();
    for(auto &d:data)
    {
        implimentation->database->push_sales_items(sales_id,QVariant(d->Id()).toInt(),d->Quantity(),d->Total_cost(),d->Cost(),d->getProfit()*d->Quantity());
        implimentation->database->updatestock(QVariant(d->Id()).toInt(),d->Quantity());
        profit+=d->getProfit()*d->Quantity();
    }
    if(Recipttype==0){

        implimentation->database->PushDiscount(sales_id,userid,discount,QDateTime::currentDateTime().toString());
        implimentation->database->push_sales_payment(sales_id,Paymenttype,Grandtotal,userid,QVariant(Change).toInt(),QDateTime::currentDateTime().toString(),profit);
    }

    else if(Recipttype==1) {
        implimentation->database->push_return_payment(sales_id,Paymenttype,Grandtotal,userid,QVariant(Change).toInt(),QDateTime::currentDateTime().toString(),0);

    }
    else {
        //implimentation->database;
    }
    return  true;
}

bool MasterController::onRemove_ItemRow(int id)
{
    implimentation->Stocks->removeRow_(id);
    implimentation->database->droprow(id);
    return true;
}
bool MasterController::onSaveCompanyinfor(QString CompanyName, QString CompanyAddress, QString CompanyNumber, QString CompanyEmail, QString Policy)
{
    implimentation->database->saveCompanyinfor(CompanyName,CompanyAddress,CompanyNumber,CompanyEmail,Policy);
    return true;
}

bool MasterController::readcompanyinfo()
{
    auto data=implimentation->database->ReadCompnayinfor();
    CompanyName=data[0].toString().toUpper();
    CompanyAddress=data[1].toString();
    CompanyNumber=data[2].toString();
    CompanyEmail=data[3].toString();
    Policy=data[4].toString();

    auto theme=implimentation->database->readthemes();

    _Font=theme[0].toString();
    _LoginTheme=theme[1].toString();
    _BackgroundTheme=theme[2].toString();
    _SalesTheme=theme[3].toString();


    QString m,n;
    int index=0;
    for(int i=0;i<_Font.size();i++){
        if(_Font[i]==','){index=i; break;}
        if(_Font[i]!=','){
            mFonttype+=_Font[i];
        }
    }
    for(int i=index+1;i<_Font.size();i++){
        if(_Font[i]==','){index=i; break;}
        if(_Font[i]!=','){
            n+=_Font[i];

        }
    }
    mfontSize=QVariant(n).toInt();
    return true;
}

bool MasterController::onSavethemes(QString font, QString login, QString background, QString sales)
{

    implimentation->database->pushthemes(font,login,background,sales);
    return true;
}

bool MasterController::onPushExpense(QString _Description, QString _Amount)
{
    if( implimentation->database->write_expensis(QDateTime::currentDateTime().toString(),_Description,_Amount,3)) return true;

       return true;
}

QString MasterController::onFomatDate(QDate date)
{
    return date.toString();
}

bool MasterController::onBackupd(QString)
{
    implimentation->database->Backupdata("");
}

long MasterController::getPLProfits() const
{
    return mPLProfits;
}

void MasterController::setPLProfits(long pLProfits)
{
    mPLProfits = pLProfits;
}

long MasterController::getPLInventory() const
{
    return mPLInventory;
}

void MasterController::setPLInventory(long pLInventory)
{
    mPLInventory = pLInventory;
}

long MasterController::getPLSales() const
{
    return mPLSales;
}

void MasterController::setPLSales(long pLSales)
{
    mPLSales = pLSales;
}

long MasterController::getPLDiscount() const
{
    return mPLDiscount;
}

void MasterController::setPLDiscount(long pLDiscount)
{
    mPLDiscount = pLDiscount;
}

long MasterController::getPLExpenisi() const
{
    return mPLExpenisi;
}

void MasterController::setPLExpenisi(long pLExpenisi)
{
    mPLExpenisi = pLExpenisi;
}

long MasterController::getMSaleprofitloss() const
{
    return MSaleprofitloss;
}

void MasterController::setMSaleprofitloss(long value)
{
    MSaleprofitloss = value;
}


long MasterController::getExpenisiTransaction() const
{
    return ExpenisiTransaction;
}

void MasterController::setExpenisiTransaction(long value)
{
    ExpenisiTransaction = value;
}

long MasterController::getTotalexpensis() const
{
    return totalexpensis;
}

void MasterController::setTotalexpensis(long value)
{
    totalexpensis = value;
}

long MasterController::getMinventoryAmount() const
{
    return minventoryAmount;
}

void MasterController::setMinventoryAmount(long value)
{
    minventoryAmount = value;
}

long MasterController::getInventoryTotal() const
{
    return inventoryTotal;
}

void MasterController::setInventoryTotal(long value)
{
    inventoryTotal = value;
}

long MasterController::getInventoryProfit() const
{
    return inventoryProfit;
}

void MasterController::setInventoryProfit(long value)
{
    inventoryProfit = value;
}

long MasterController::getSaleDProfit() const
{
    return mSaleDProfit;
}

void MasterController::setSaleDProfit(long saleDProfit)
{
    mSaleDProfit = saleDProfit;
}

long MasterController::getMmSaleDTotal() const
{
    return mmSaleDTotal;
}

void MasterController::setMmSaleDTotal(long value)
{
    mmSaleDTotal = value;
}

long MasterController::getMmSaleDAmount() const
{
    return mmSaleDAmount;
}

void MasterController::setMmSaleDAmount(long value)
{
    mmSaleDAmount = value;
}

long MasterController::getMstProfit() const
{
    return mMstProfit;
}

void MasterController::setMstProfit(long mstProfit)
{
    mMstProfit = mstProfit;
}

long MasterController::getMstTotal() const
{
    return mMstTotal;
}

void MasterController::setMstTotal(long mstTotal)
{
    mMstTotal = mstTotal;
}

long MasterController::getMstAmount() const
{
    return mMstAmount;
}

void MasterController::setMstAmount(long mstAmount)
{
    mMstAmount = mstAmount;
}

long MasterController::getSaleAmount() const
{
    return mSaleAmount;
}

void MasterController::setSaleAmount(long saleAmount)
{
    mSaleAmount = saleAmount;
}

long MasterController::getReturnProfit() const
{
    return mReturnProfit;
}

void MasterController::setReturnProfit(long saleProfit)
{
    mReturnProfit=saleProfit;
}

long MasterController::getReturnTotal() const
{
    return mReturnTotal;
}

void MasterController::setReturnTotal(long value)
{
    mReturnTotal=value;
}

long MasterController::getReturnAmount() const
{
    return mReturnAmount;
}

void MasterController::setReturnAmount(long saleAmount)
{
    mReturnAmount=saleAmount;
}

long MasterController::getMsaleTotal() const
{
    return msaleTotal;
}

void MasterController::setMsaleTotal(long value)
{
    msaleTotal = value;
}

long MasterController::getSaleProfit() const
{
    return mSaleProfit;
}

void MasterController::setSaleProfit(long saleProfit)
{
    mSaleProfit = saleProfit;
}

QString MasterController::getFonttype() const
{
    return mFonttype;
}

int MasterController::getMfontSize() const
{
    return mfontSize;
}

QString MasterController::getSalesTheme() const
{
    return _SalesTheme;
}


QString MasterController::getBackgroundTheme() const
{
    return _BackgroundTheme;
}

QString MasterController::getLoginTheme() const
{
    return _LoginTheme;
}

QString MasterController::getFont() const
{
    return _Font;
}



QString MasterController::getPolicy() const
{
    return Policy;
}

QString MasterController::getCompanyEmail() const
{
    return CompanyEmail;
}

void MasterController::setCompanyEmail(const QString &value)
{
    CompanyEmail = value;
}

QString MasterController::getCompanyNumber() const
{
    return CompanyNumber;
}

void MasterController::setCompanyNumber(const QString &value)
{
    CompanyNumber = value;
}

QString MasterController::getCompanyAddress() const
{
    return CompanyAddress;
}

QString MasterController::getCompanyName() const
{
    return CompanyName;
}


void MasterController::populate_()
{
    auto data= implimentation->database->Read_Stock("");
    implimentation->Stocks->populate(data);

    auto data_employee=implimentation->database->readEmployee();
    implimentation->employee->populate(data_employee);
    auto sales=implimentation->database->read_Sales_report(0,0);
    implimentation->SalesReport->populate(sales);
    for(auto &d:sales){
        mSaleProfit+=d->profit();
        SaleProfitChanged();
        msaleTotal+=d->totalCost();
        saleTotalChanged();
        mSaleAmount=sales.count();
        SaleAmountChanged();
    }

    auto moststpld=implimentation->database->read_mostsold_report(0,0);
    implimentation->MostsoldReport->populate(moststpld);
    for(auto &d:moststpld){
        mMstProfit+=d->profit();
        MstProfitChanged();
        mMstTotal+=d->totalCost();
        MstTotalChanged();
        mMstAmount=moststpld.count();
        MstAmountChanged();
    }

    auto returns=implimentation->database->read_returns_report(0,0);
    implimentation->ReturnReport->populate(returns);

    for(auto &d:returns){
        mReturnProfit+=d->profit();
        ReturnProfitChanged();
        mReturnTotal+=d->totalCost();
        ReturnTotalChanged();
        mReturnAmount=returns.count();
        ReturnAmountChanged();
    }
    auto data_stock= implimentation->database->Read_Stock("");
    implimentation->Stocks->populate(data_stock);

    auto inventory=implimentation->database->Read_Inventory(0);
    implimentation->Inventory->populate(inventory);

    auto dataitem=implimentation->database->Read_Sales_items(0,0);
    implimentation->sales->populate(dataitem);

    auto Expensis=implimentation->database->read_expensis(0,0);
    implimentation->Expensis->populate(Expensis);

}


}
