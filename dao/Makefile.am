INCLUDES = -I$(top_srcdir)/src/reports -I$(top_srcdir)/src/types \
	$(all_includes)
METASOURCES = AUTO
lib_LIBRARIES =  libdao.a
libdao_a_SOURCES = customerdao.cpp customerdao.h databasemanager.cpp \
		databasemanager.h invoicedao.cpp invoicedao.h transactiondao.cpp transactiondao.h \
		animalcodedao.cpp commissiondao.cpp chargedao.cpp chargedao.h checkdao.cpp checkdao.h \
	truckingrecorddao.cpp truckingrecorddao.h setupdao.cpp setupdao.h proratedao.cpp proratedao.h \
	printerdao.cpp printerdao.h salemanager.cpp salemanager.h tagdao.cpp tagdao.h \
	radiotagdao.cpp radiotagdao.h zipcodedao.cpp zipcodedao.h branddao.cpp branddao.h \
	historydao.cpp historydao.h databaseverifier.cpp databaseverifier.h

noinst_HEADERS = animalcodedao.cpp chargedao.cpp chargedao.h commissiondao.cpp \
	customerdao.cpp customerdao.h databasemanager.cpp databasemanager.h invoicedao.cpp \
	invoicedao.h transactiondao.cpp transactiondao.h


libdao_a_LIBADD = $(top_builddir)/src/reports/libreports.a \
	$(top_builddir)/src/types/libtypes.a





