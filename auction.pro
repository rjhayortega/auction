DYNAMIC = 0
#DYNAMIC = 1

# clear out CONFIG variable
CONFIG      -= debug release static staticlib

contains(DYNAMIC, 1) {
    message("Compiling DYNAMIC")
    QTDIR = /usr/lib64/qt4
    MYSQLDIR = /usr/include/mysql
} else {
    message("Compiling STATIC")
    contains(QMAKE_CFLAGS, -m32) {
        message("Building 32 bit!")
        error("Not building 32 bit at this time!")
#        QTDIR = /opt/qt487-32
#        MYSQLDIR = /opt/mysql32/include
#        CFLAGS   += -m32
#        CXXFLAGS += -m32
#        LDFLAGS  += -m32
    } else {
        message("Building 64 bit")
        QTDIR = /usr/share/qt4
        LIBS += /usr/lib/x86_64-linux-gnu
        MYSQLDIR = /usr/include/mysql
        #CFLAGS   += -m64
        #CXXFLAGS += -m64
       # LDFLAGS  += -m64
    }
    CONFIG += static staticlib $(BUILDTYPE)
}

#error("Only testing DYNAMIC envvar")



#QMAKE_CXXFLAGS += -Wno-deprecated

TEMPLATE    = app
TARGET      = auction

#CONFIG      -= debug release static staticlib
#CONFIG      += static staticlib $(BUILDTYPE)

QTPLUGIN    += qsqlmysql
DEFINES     += _USE_qsqlmysql

QT          += core gui qt3support sql network

#INCLUDEPATH += $$STATICDIR/include
#INCLUDEPATH += $$FFMPEGDIR/include
INCLUDEPATH += $$MYSQLDIR
#INCLUDEPATH += $$QTDIR/include

#LIBS        += -lx264
LIBS        += -lz
#LIBS        += -lpng12

LIBS        += -lbz2
LIBS        += -llzma
LIBS        += -lm

#LIBS        += -L$$MYSQLDIR/lib
LIBS        += -lmysqlclient_r

#LIBS        += -L$$QTDIR/lib
LIBS        += -lQt3Support -lQtXml -lQtNetwork -lQtSql -lQtGui -lQtCore

RESOURCES += auction.qrc
RESOURCES += fonts.qrc


message("DYNAMIC: $$DYNAMIC")
message("CONFIG: $$CONFIG")
message("QMAKE_CFLAGS: $$QMAKE_CFLAGS")

message("LIBS: $$LIBS")
message("QTDIR: $$QTDIR")
message("MYSQLDIR: $$MYSQLDIR")
#message("FFMPEGDIR: $$FFMPEGDIR")
#message("STATICDIR: $$STATICDIR")
message("INCLUDEPATH: $$INCLUDEPATH")
message("CFLAGS: $$CFLAGS")
message("CXXFLAGS: $$CXXFLAGS")
message("LDFLAGS: $$LDFLAGS")
message("RESOURCES: $$RESOURCES")

#error("Only testing environment stuff")

SOURCES += \
    main.cpp \
    textdialog.cpp \
    oki2pixmap.cpp \
    lineprinter.cpp \
    serialport.cpp \
    scalesetupdialog.cpp \
    reportsetupdialog.cpp \
    displaybrowserdialog.cpp \
    displaysetupdialog.cpp \
    chargecreditdialog.cpp \
    marketreportsetupdialog.cpp \
    proratesexdialog.cpp \
    proratetransactiondialog.cpp \
    printersetupdialog.cpp \
    clerksetupdialog.cpp \
    codedialog.cpp \
    chargedialog.cpp \
    brandwidget.cpp \
    vetformmetricsdialog.cpp \
    vetdatadialog.cpp \
    tablebrowserdialog.cpp \
    vetreportdialog.cpp \
    vetreportdialogbase.cpp \
    vetdialog.cpp \
    tagbrowser.cpp \
    tageditdialog.cpp \
    tablerepairdialog.cpp \
    brandinputdialog.cpp \
    brandbrowserdialog.cpp \
    history.cpp \
    transfercheckdialog.cpp \
    buyerchecksdialog.cpp \
    buyercommissiondialog.cpp \
    buyercount.cpp \
    truckerchecksdialog.cpp \
    lienimportdialog.cpp \
    salemanagersetupdialog.cpp \
    salemanagerdialog.cpp \
    permanantdialog.cpp \
    checkregister.cpp \
    checkeditdialog.cpp \
    checksetup.cpp \
    checksetup_frame.cpp \
    postcheckdialog.cpp \
    depositeditdialog.cpp \
    commissiondialog.cpp \
    breakeditdialog.cpp \
    transactionbrowser.cpp \
    setupdialog.cpp \
    zipcodedialog.cpp \
    permsearchdialog.cpp \
    readysellerdialog.cpp \
    chargeadjustmentdialog.cpp \
    truckingdialog.cpp \
    proratedialog.cpp \
    previewdialog.cpp \
    dailydialog.cpp \
    invoicesetup.cpp \
    invoicedialog.cpp \
    transactiondialog.cpp \
    auctionmain.cpp \
    buyerrecapdialog.cpp \
    marketreportdialog.cpp \
    timer.cpp \
    rational.cpp \
    types/address.cpp \
    types/animalcode.cpp \
    types/brand.cpp \
    types/charge.cpp \
    types/chargerecord.cpp \
    types/check.cpp \
    types/checkfactory.cpp \
    types/commission.cpp \
    types/contactlist.cpp \
    types/customer.cpp \
    types/date.cpp \
    types/datetime.cpp \
    types/display.cpp \
    types/expressionparser.cpp \
    types/healthrecord.cpp \
    types/historyitem.cpp \
    types/invoice.cpp \
    types/name.cpp \
    types/numbers.cpp \
    types/person.cpp \
    types/prorate.cpp \
    types/radiotag.cpp \
    types/summaryrecord.cpp \
    types/tag.cpp \
    types/timeclass.cpp \
    types/transaction.cpp \
    types/truckingrecord.cpp \
    reports/allflexreport.cpp \
    reports/brucellosistestrecord.cpp \
    reports/buyerar.cpp \
    reports/buyercheckreport.cpp \
    reports/buyercommissionreport.cpp \ 
    reports/buyerrecap.cpp \
    reports/checkinreport.cpp \
    reports/checkreport.cpp \
    reports/codereport.cpp \
    reports/customerreport.cpp \
    reports/detailsummaryreport.cpp \
    reports/discrepancyreport.cpp \
    reports/historyreport.cpp \
    reports/mailinglabels.cpp \
    reports/marketreport.cpp \
    reports/minnesotavetcertificate.cpp \
    reports/penreport.cpp \
    reports/southdakotahealthcertificate.cpp \
    reports/summaryreport.cpp \
    reports/tagreport.cpp \
    reports/textcheck.cpp \
    reports/textinvoice.cpp \
    reports/textreport.cpp \
    reports/transactionlist.cpp \
    reports/transactionticket.cpp \
    reports/truckercheckreport.cpp \
    reports/truckingreport.cpp \
    reports/tuberculosisrecord.cpp \
    dao/animalcodedao.cpp \
    dao/branddao.cpp \
    dao/chargedao.cpp \
    dao/checkdao.cpp \
    dao/commissiondao.cpp \
    dao/customerdao.cpp \
    dao/databasemanager.cpp \
    dao/databaseverifier.cpp \
    dao/historydao.cpp \
    dao/invoicedao.cpp \
    dao/printerdao.cpp \
    dao/proratedao.cpp \
    dao/radiotagdao.cpp \
    dao/salemanager.cpp \
    dao/setupdao.cpp \
    dao/tagdao.cpp \
    dao/transactiondao.cpp \
    dao/truckingrecorddao.cpp \
    dao/zipcodedao.cpp \
    reports/textsellerinvoice.cpp \
    reports/textbuyerinvoice.cpp \
    printerbase.cpp \
    laserprinter.cpp \
    printerfactory.cpp \
    types/appexception.cpp \
    types/sqlexception.cpp \
    auctionapp.cpp \
    types/buyerinvoice.cpp \
    types/sellerinvoice.cpp \
    types/dragwidget.cpp \
    types/draglabel.cpp \
#    video/videofiltersmodel.cpp \
#    video/webcampreview.cpp \
#    video/videosetupdialog.cpp \
#    video/videosaver.cpp \
    faxsetupdialog.cpp \
    okiml320image.cpp

HEADERS += \
    textdialog.h \
    oki2pixmap.h \
    lineprinter.h \
    serialport.h \
    scalesetupdialog.h \
    reportsetupdialog.h \
    displaybrowserdialog.h \
    displaysetupdialog.h \
    chargecreditdialog.h \
    marketreportsetupdialog.h \
    proratesexdialog.h \
    proratetransactiondialog.h \
    printersetupdialog.h \
    clerksetupdialog.h \
    codedialog.h \
    chargedialog.h \
    brandwidget.h \
    vetformmetricsdialog.h \
    vetdatadialog.h \
    tablebrowserdialog.h \
    vetreportdialog.h \
    vetreportdialogbase.h \
    vetdialog.h \
    tagbrowser.h\
    tageditdialog.h \
    tablerepairdialog.h \
    brandinputdialog.h \
    brandbrowserdialog.h \
    history.h \
    transfercheckdialog.h \
    buyerchecksdialog.h \
    buyercommissiondialog.h \
    buyercount.h \
    truckerchecksdialog.h \
    lienimportdialog.h \
    salemanagersetupdialog.h \
    salemanagerdialog.h \
    permanantdialog.h \
    checkregister.h \
    checkeditdialog.h \
    checksetup.h \
    checksetup_frame.h \
    postcheckdialog.h \
    depositeditdialog.h \
    commissiondialog.h \
    breakeditdialog.h \
    transactionbrowser.h \
    setupdialog.h \
    zipcodedialog.h \
    permsearchdialog.h \
    readysellerdialog.h \
    chargeadjustmentdialog.h \
    truckingdialog.h \
    proratedialog.h \
    previewdialog.h \
    dailydialog.h \
    auctionmain.h \
    invoicesetup.h \
    invoicedialog.h \
    buyerrecapdialog.h \
    marketreportdialog.h \
    transactiondialog.h \
    timer.h \
    rational.h \
    types/address.h \
    types/animalcode.h \
    types/brand.h \
    types/charge.h \
    types/chargerecord.h \
    types/check.h \
    types/checkfactory.h \
    types/commission.h \
    types/contactlist.h \
    types/customer.h \
    types/date.h \
    types/datetime.h \
    types/dbug.h \
    types/display.h \
    types/displayrow.h \
    types/expressionparser.h \
    types/healthrecord.h \
    types/historyitem.h \
    types/invoice.h \
    types/name.h \
    types/numbers.h \
    types/person.h \
    types/prorate.h \
    types/radiotag.h \
    types/summaryrecord.h \
    types/tag.h \
    types/timeclass.h \
    types/transaction.h \
    types/truckingrecord.h \
    reports/allflexreport.h \
    reports/brucellosistestrecord.h \
    reports/buyerar.h \
    reports/buyercheckreport.h \
    reports/buyercommissionreport.h \
    reports/buyerrecap.h \
    reports/checkinreport.h \
    reports/checkreport.h \
    reports/codereport.h \
    reports/customerreport.h \
    reports/detailsummaryreport.h \
    reports/discrepancyreport.h \
    reports/historyreport.h \
    reports/mailinglabels.h \
    reports/marketreport.h \
    reports/minnesotavetcertificate.h \
    reports/penreport.h \ 
    reports/southdakotahealthcertificate.h \
    reports/summaryreport.h \
    reports/tagreport.h \
    reports/textcheck.h \
    reports/textinvoice.h \
    reports/textreport.h \
    reports/transactionlist.h \
    reports/transactionticket.h \ 
    reports/truckercheckreport.h \
    reports/truckingreport.h \
    reports/tuberculosisrecord.h \
    dao/animalcodedao.h \
    dao/auctiondatabase.h \
    dao/branddao.h \
    dao/chargedao.h \
    dao/checkdao.h \
    dao/commissiondao.h \
    dao/customerdao.h \
    dao/databasemanager.h \
    dao/databaseverifier.h \
    dao/displaydao.h \
    dao/historydao.h \
    dao/invoicedao.h \
    dao/printerdao.h \
    dao/proratedao.h \
    dao/radiotagdao.h \
    dao/salemanager.h \
    dao/setupdao.h \
    dao/tagdao.h \
    dao/transactiondao.h \
    dao/truckingrecorddao.h \
    dao/zipcodedao.h \
    reports/textsellerinvoice.h \
    reports/textbuyerinvoice.h \
    printerbase.h \
    laserprinter.h \
    printerfactory.h \
    types/appexception.h \
    types/sqlexception.h \
    auctionapp.h \
    types/buyerinvoice.h \
    types/sellerinvoice.h \
    types/dragwidget.h \
    types/draglabel.h \
#    video/webcampreview.h \
#    video/videofiltersmodel.h \
#    video/videosetupdialog.h \
#    video/videosaver.h \
    faxsetupdialog.h \
    okiml320image.h \
    globals.h

FORMS = \
    auctiondatabasewizard.ui \
    auctionmain.ui \
    brandbrowserdialog.ui \
    brandinputdialog.ui \
    breakeditdialog.ui \
    buyerchecksdialog.ui \
    buyerrecapdialog.ui \
    chargeadjustmentdialog.ui \
    chargecreditdialog.ui \
    chargedialog.ui \
    checkeditdialog.ui \
    checkregister.ui \
    checksetup.ui \
    clerksetupdialog.ui \
    codedialog.ui \
    commissiondialog.ui \
    dailydialog.ui \
    depositeditdialog.ui \
    displaybrowserdialog.ui \
    displaysetupdialog.ui \
    faxsenddialog.ui \
    faxsetupdialog.ui \
    history.ui \
    invoicedialog.ui \
    invoicesetup.ui \
    lienimportdialog.ui \
    marketreportdialog.ui \
    marketreportsetupdialog.ui \
    permanantdialog.ui \
    permbuyersearchdialog.ui \
    permsearchdialog.ui \
    postcheckdialog.ui \
    previewdialog.ui \
    printersetupdialog.ui \
    proratedialog.ui \
    proratesexdialog.ui \
    proratetransactiondialog.ui \
    readysellerdialog.ui \
    reportsetupdialog.ui \
    salemanagerdialog.ui \
    salemanagersetupdialog.ui \
    scalesetupdialog.ui \
    setupdialog.ui \
    tablebrowserdialog.ui \
    tablerepairdialog.ui \
    tagbrowser.ui \
    tageditdialog.ui \
    textdialog.ui \
    transactionbrowser.ui \
    transactiondialog.ui \
    transfercheckdialog.ui \
    truckerchecksdialog.ui \
    truckingdialog.ui \
    vetdatadialog.ui \
    vetdialog.ui \
    vetformmetricsdialog.ui \
    vetreportdialogbase.ui \
    zipcodedialog.ui \
#    video/videosetupdialog.ui

#IMAGES = \
#    images/filenew \
#    images/fileopen \
#    images/filesave \
#    images/print \
#    images/undo \
#    images/redo \
#    images/editcut \
#    images/editcopy \
#    images/editpaste \
#    images/searchfind \
#    images/filenew_1 \
#    images/fileopen_1 \
#    images/filesave_1 \
#    images/print_1 \
#    images/undo_1 \
#    images/redo_1 \
#    images/editcut_1 \
#    images/editcopy_1 \
#    images/editpaste_1 \
#    images/searchfind_1 \
#    images/filenew_2 \
#    images/fileopen_2 \
#    images/filesave_2 \
#    images/print_2 \
#    images/undo_2 \
#    images/redo_2 \
#    images/editcut_2 \
#    images/editcopy_2 \
#    images/editpaste_2 \
#    images/searchfind_2


#unix:!macx: LIBS += -L$$OUT_PWD/smplayer-0.8.6/src/ -lsmplayer

#INCLUDEPATH += $$PWD/smplayer-0.8.6/src
#DEPENDPATH += $$PWD/smplayer-0.8.6/src

#PRE_TARGETDEPS += $$OUT_PWD/smplayer-0.8.6/src/libsmplayer.a

#RESOURCES += smplayer-0.8.6/src/icons.qrc

