QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addbook.cpp \
    addmember.cpp \
    authorslist.cpp \
    booklist.cpp \
    deletebook.cpp \
    deletemember.cpp \
    digitallibrary.cpp \
    editbook.cpp \
    editmember.cpp \
    genrelist.cpp \
    issuebook.cpp \
    login.cpp \
    main.cpp \
    manageauthors.cpp \
    managebooks.cpp \
    memberslist.cpp \
    newpasswd.cpp \
    returnbook.cpp \
    signup.cpp

HEADERS += \
    addbook.h \
    addmember.h \
    authorslist.h \
    booklist.h \
    deletebook.h \
    deletemember.h \
    digitallibrary.h \
    editbook.h \
    editmember.h \
    genrelist.h \
    issuebook.h \
    login.h \
    manageauthors.h \
    managebooks.h \
    memberslist.h \
    newpasswd.h \
    returnbook.h \
    signup.h

FORMS += \
    addbook.ui \
    addmember.ui \
    authorslist.ui \
    booklist.ui \
    deletebook.ui \
    deletemember.ui \
    digitallibrary.ui \
    editbook.ui \
    editmember.ui \
    genrelist.ui \
    issuebook.ui \
    login.ui \
    manageauthors.ui \
    managebooks.ui \
    memberslist.ui \
    newpasswd.ui \
    returnbook.ui \
    signup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

DISTFILES +=
