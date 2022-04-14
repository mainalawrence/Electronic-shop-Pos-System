
#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H
#include <QObject>
#include<QDataStream>
#include<QJsonArray>
#include<QCryptographicHash>
#include<QString>
#include<QScopedPointer>
#include"navigation-controller.h"
#include "Controller/database_controller.h"
#include <Lib_global.h>
#include<Model/report_model.h>
#include<Model/sales_model.h>
#include<Model/employeemodel.h>
#include<Model/returnsmodel.h>
#include<Model/expenisismodel.h>

namespace Controller {

class LIB_EXPORT MasterController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Controller::NavigationController *ui_navigation READ navigationController CONSTANT)
    Q_PROPERTY(bool ui_visiblebnt READ visible CONSTANT)
    Q_PROPERTY(QString ui_title READ title CONSTANT)
    Q_PROPERTY(QJsonArray ui_data_array READ Itemcategory CONSTANT)
    Q_PROPERTY(Model::Sales_model *ui_Sales READ Sales CONSTANT)
    Q_PROPERTY(Model::Sales_model *ui_MostSold READ MostSold CONSTANT)
    Q_PROPERTY(Model::Sales_model *ui_Returns READ Returns CONSTANT)
    Q_PROPERTY(Model::Sales_model *ui_Cart READ Cat CONSTANT)
    Q_PROPERTY(Model::Report_Model *ui_Stocks READ Stocks CONSTANT)
    Q_PROPERTY(Model::Report_Model *ui_Inventory READ Inventory CONSTANT)
    Q_PROPERTY(Model::EmployeeModel* ui_employee READ employee() CONSTANT)
    Q_PROPERTY(Model::Sales_model * ui_Search_Stock_to_Cart READ Search_Stock_to_Cart CONSTANT)
    Q_PROPERTY(QString ui_companyName READ getCompanyName CONSTANT)
    Q_PROPERTY(QString ui_companyaAddress READ getCompanyAddress CONSTANT)
    Q_PROPERTY(QString ui_companyNumber READ getCompanyNumber CONSTANT)
    Q_PROPERTY(QString ui_companyEmail READ getCompanyEmail CONSTANT)
    Q_PROPERTY(QString ui_companyapolicies READ getPolicy CONSTANT)

    Q_PROPERTY(Model::ReturnsModel* ui_SalesReport READ SalesReport CONSTANT)
    Q_PROPERTY(Model::ReturnsModel* ui_ReturnReport READ ReturnReport CONSTANT)
    Q_PROPERTY(Model::ReturnsModel* ui_MostsoldReport READ MostsoldReport CONSTANT)
    Q_PROPERTY(Model::ExpenisisModel* ui_Expensis READ Expensis CONSTANT)

    Q_PROPERTY(QString ui_font READ getFont CONSTANT)
    Q_PROPERTY(QString ui_Logintheme READ getLoginTheme CONSTANT)
    Q_PROPERTY(QString ui_backgroundtheme READ getBackgroundTheme CONSTANT)
    Q_PROPERTY(QString ui_salestheme READ getSalesTheme CONSTANT)
    Q_PROPERTY(long ui_mProfit READ getSaleProfit WRITE setSaleProfit NOTIFY SaleProfitChanged)
    Q_PROPERTY(long ui_mGrandTotal READ getMsaleTotal WRITE setMsaleTotal NOTIFY saleTotalChanged)
    Q_PROPERTY(long ui_mTotalItem READ getSaleAmount WRITE setSaleAmount NOTIFY SaleAmountChanged)
    //the
    Q_PROPERTY(long ui_totalexpensis READ getTotalexpensis WRITE setTotalexpensis NOTIFY expensistotalChanged)
    Q_PROPERTY(long ui_ExpenisiTransaction READ getExpenisiTransaction  NOTIFY ExpensisTransactionChanged)

    Q_PROPERTY(long ui_mReturnProfit READ getReturnProfit WRITE setReturnProfit NOTIFY ReturnProfitChanged)
    Q_PROPERTY(long ui_mReturnGrandTotal READ getReturnTotal WRITE setReturnTotal NOTIFY ReturnTotalChanged)
    Q_PROPERTY(long ui_mReturnTotalItem READ getReturnAmount WRITE setReturnAmount NOTIFY ReturnAmountChanged)

    Q_PROPERTY(long ui_SaleDProfit READ getSaleDProfit WRITE setSaleDProfit NOTIFY SaleDProfitChanged)
    Q_PROPERTY(long ui_SaleDTotal READ getMmSaleDTotal WRITE setMmSaleDTotal NOTIFY MmSaleDTotalChanged)
    Q_PROPERTY(long ui_SaleDAmount READ getMmSaleDAmount WRITE setMmSaleDAmount NOTIFY MmSaleDAmountChanged)

    Q_PROPERTY(long ui_InventoryDProfit READ getInventoryProfit WRITE setInventoryProfit NOTIFY inverntoryprofitChanged)
    Q_PROPERTY(long ui_InventoryTotal READ getInventoryTotal WRITE setInventoryTotal NOTIFY inverntorytotalChanged)
    Q_PROPERTY(long ui_InventoryAmount READ getMinventoryAmount WRITE setMinventoryAmount NOTIFY inverntoryAmountChanged)

    Q_PROPERTY(long ui_mMstTotalItem READ getMstAmount WRITE setMstAmount NOTIFY MstAmountChanged)
    Q_PROPERTY(long ui_mMstGrandTotal READ getMstTotal WRITE setMstTotal NOTIFY MstTotalChanged)
    Q_PROPERTY(long  ui_mMstProfit READ getMstProfit WRITE setMstProfit NOTIFY MstProfitChanged)


    //profit loss account
    Q_PROPERTY(long ui_mPLExpenisi READ getPLExpenisi WRITE setPLExpenisi NOTIFY PLExpenisiChanged)
    Q_PROPERTY(long ui_PLDiscount READ getPLDiscount WRITE setPLDiscount NOTIFY PLDiscountChanged)
    Q_PROPERTY(long ui_PLInventory READ getPLInventory WRITE setPLInventory NOTIFY PLInventoryChanged)
    Q_PROPERTY(long ui_mPLSales READ getPLSales WRITE setPLSales NOTIFY mPLSalesChanged)
    Q_PROPERTY(long ui_mPLProfits READ getPLProfits WRITE setPLProfits NOTIFY mPLProfitsChanged)
public:
    explicit MasterController(QObject *parent = nullptr,Database_controller *maincontroler=nullptr);
    ~MasterController();
    NavigationController *navigationController()const;
    QString title()const;
    bool visible();
    QJsonArray Itemcategory()const;
    Model::Report_Model* Stocks();
    Model::Report_Model* Inventory();
    Model::Sales_model *Sales();
    Model::Sales_model *Cat();
    Model::Sales_model* MostSold();
    Model::Sales_model* Returns();
    Model::Sales_model* Search_Stock_to_Cart();
    Model::EmployeeModel* employee();
    Model::ReturnsModel* SalesReport();
    Model::ReturnsModel* ReturnReport();
    Model::ReturnsModel* MostsoldReport();
    Model::ExpenisisModel* Expensis();

    QString getCompanyName() const;

    QString getCompanyAddress() const;

    QString getCompanyNumber() const;
    void setCompanyNumber(const QString &value);

    QString getCompanyEmail() const;
    void setCompanyEmail(const QString &value);

    QString getPolicy() const;

    QString getFont() const;

    QString getLoginTheme() const;

    QString getBackgroundTheme() const;

    QString getSalesTheme() const;

    int getMfontSize() const;

    QString getFonttype() const;

    long getSaleProfit() const;
    void setSaleProfit(long saleProfit);

    long getMsaleTotal() const;
    void setMsaleTotal(long value);

    long getSaleAmount() const;
    void setSaleAmount(long saleAmount);

    long getReturnProfit() const;
    void setReturnProfit(long saleProfit);

    long getReturnTotal() const;
    void setReturnTotal(long value);

    long getReturnAmount() const;
    void setReturnAmount(long saleAmount);

    long getMstAmount() const;
    void setMstAmount(long mstAmount);

    long getMstTotal() const;
    void setMstTotal(long mstTotal);

    long getMstProfit() const;
    void setMstProfit(long mstProfit);

    long getMmSaleDAmount() const;
    void setMmSaleDAmount(long value);

    long getMmSaleDTotal() const;
    void setMmSaleDTotal(long value);

    long getSaleDProfit() const;
    void setSaleDProfit(long saleDProfit);

    long getInventoryProfit() const;
    void setInventoryProfit(long value);

    long getInventoryTotal() const;
    void setInventoryTotal(long value);

    long getMinventoryAmount() const;
    void setMinventoryAmount(long value);

    long getTotalexpensis() const;
    void setTotalexpensis(long value);

    long getExpenisiTransaction() const;
    void setExpenisiTransaction(long value);


    long getMSaleprofitloss() const;
    void setMSaleprofitloss(long value);

    long getPLExpenisi() const;
    void setPLExpenisi(long pLExpenisi);

    long getPLDiscount() const;
    void setPLDiscount(long pLDiscount);

    long getPLSales() const;
    void setPLSales(long pLSales);

    long getPLInventory() const;
    void setPLInventory(long pLInventory);

    long getPLProfits() const;
    void setPLProfits(long pLProfits);

private:
    void populate_Cart();


signals:
    void SaleProfitChanged();
    void saleTotalChanged();
    void SaleAmountChanged();

    void ReturnProfitChanged();
    void ReturnTotalChanged();
    void ReturnAmountChanged();

    void MstProfitChanged();
    void MstTotalChanged();
    void MstAmountChanged();

    void SaleDProfitChanged();
    void MmSaleDTotalChanged();
    void MmSaleDAmountChanged();

    void inverntoryprofitChanged();
    void inverntorytotalChanged();
    void inverntoryAmountChanged();

    void expensistotalChanged();
    void ExpensisTransactionChanged();

    void mExpenisiChanged();
    void mProfitsChanged();

    void PLExpenisiChanged();
    void PLDiscountChanged();
    void PLInventoryChanged();
    void mPLSalesChanged();
    void mPLProfitsChanged();





public slots:
    bool onLogin(QString,QString);
    void onLogout();
    //report part
    void onPrint(QString name);
    void onExport(QString name);
    void onSearchChanged(QString name);
    void onSearch(QString ,QString,int);
    void onStock_search(QString text)const;
    void onEmployee_search(QString text)const;

    void onQuantityChanged(QString id, int quantity );
    void onDiscountChanged(QString id, int quantity );
    int onCheckIndexCombo(QString id);
    void onAddtoCart(QString item);
    void onClearcart();
    void onRemoveRow(QString id);
    bool onUpdate_items(int id,const QString name,const QString category,const int quantity,const int price,const int wholeprice ,int discount);
    void onReload();
    void onRemoveEmployerr(int id);
    void onPush_employee(QString fname,QString gender,QString lname,QString role,QString email,QString username, QString password,QString phone);
    void onUpdate_employee(int id,QString fname,QString gender,QString lname,QString role,QString email,QString username, QString password,QString phone);
    //database
    void onExport_to_csvQuery(QString rootid, QString text, int index);
    void onExport_to_csv(const QString table,const QString loc);
    void onImport(QString tname,QString location);
    void onAddcategry(const QString text);
    void onAdd_items(const QString name,const QString category,const int quantity,const int price,const int wholesale,int discount);
    bool onPush_To_cart(QString id,QString name,QString category,int quantity,int cost, int totalcost,QString Date,int profit);
    void onSuspend_sales();
    bool onPayment(int Recipttype,int Grandtotal, QString Paymenttype,int Change,int dicount);
    bool onRemove_ItemRow(int id);
    bool onSaveCompanyinfor( QString CompanyName,QString CompanyAddress,QString CompanyNumber,QString CompanyEmail,QString Policy);
    bool readcompanyinfo();
    bool onSavethemes(QString font,QString login,QString background,QString sales);
    bool onPushExpense(QString _Description, QString _Amount);
    QString onFomatDate(QDate date);

    bool onBackupd(QString);
private:
    class Implimentation;
    QScopedPointer<Implimentation>implimentation;
    QString BusinessName;
    bool dbconnecteds;
    QString m_username;
    int Role;
    int userid;
    bool homebtn=true;

    QString CompanyName;
    QString CompanyAddress;
    QString CompanyNumber;
    QString CompanyEmail;
    QString Policy;


    QString _Font;
    QString mFonttype;
    QString _LoginTheme;
    QString _BackgroundTheme;
    QString _SalesTheme;


    long mSaleProfit=0;
    long msaleTotal=0;
    long mSaleAmount=0;

    long mReturnProfit=0;
    long mReturnTotal=0;
    long mReturnAmount=0;

    long mMstProfit=0;
    long mMstTotal=0;
    long mMstAmount=0;
    int mfontSize=0;

    long mSaleDProfit=0;
    long mmSaleDTotal=0;
    long mmSaleDAmount=0;

    long inventoryProfit=0;
    long inventoryTotal=0;
    long minventoryAmount=0;

    long mPLExpenisi=0;
    long mPLDiscount=0;
    long mPLInventory=0;
    long mPLSales=0;
    long mPLProfits=0;
    long MSaleprofitloss=0;

    long totalexpensis=0;
    long ExpenisiTransaction=0;



    void populate_();
};


}
#endif // MASTERCONTROLLER_H
