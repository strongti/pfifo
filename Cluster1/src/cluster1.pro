QT += quick
CONFIG += c++11
QT += multimedia
QT += network
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += ../../src-gen-cluster/
SOURCES += main.cpp \
    ../../src-gen-cluster/v1/commonapi/Cluster1SomeIPDeployment.cpp \
    ../../src-gen-cluster/v1/commonapi/Cluster1SomeIPProxy.cpp \
    ../../src-gen-cluster/v1/commonapi/Cluster1SomeIPStubAdapter.cpp \
    Cluster1StubImpl.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L/usr/local/lib/release/ -lCommonAPI
else:win32:CONFIG(debug, debug|release): LIBS += -L/usr/local/lib/debug/ -lCommonAPI
else:unix: LIBS += -L/usr/local/lib/ -lCommonAPI

INCLUDEPATH += /usr/local/include/CommonAPI-3.2
DEPENDPATH += /usr/local/include/CommonAPI-3.2

win32:CONFIG(release, debug|release): LIBS += -L/usr/local/lib/release/ -lCommonAPI-SomeIP
else:win32:CONFIG(debug, debug|release): LIBS += -L/usr/local/lib/debug/ -lCommonAPI-SomeIP
else:unix: LIBS += -L/usr/local/lib/ -lCommonAPI-SomeIP

INCLUDEPATH += /usr/local/include/CommonAPI-3.2
DEPENDPATH += /usr/local/include/CommonAPI-3.2

win32:CONFIG(release, debug|release): LIBS += -L/usr/local/lib/release/ -lvsomeip3
else:win32:CONFIG(debug, debug|release): LIBS += -L/usr/local/lib/debug/ -lvsomeip3
else:unix: LIBS += -L/usr/local/lib/ -lvsomeip3

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

HEADERS += \
    ../../src-gen-cluster/v1/commonapi/Cluster1.hpp \
    ../../src-gen-cluster/v1/commonapi/Cluster1Proxy.hpp \
    ../../src-gen-cluster/v1/commonapi/Cluster1ProxyBase.hpp \
    ../../src-gen-cluster/v1/commonapi/Cluster1SomeIPDeployment.hpp \
    ../../src-gen-cluster/v1/commonapi/Cluster1SomeIPProxy.hpp \
    ../../src-gen-cluster/v1/commonapi/Cluster1SomeIPStubAdapter.hpp \
    ../../src-gen-cluster/v1/commonapi/Cluster1Stub.hpp \
    ../../src-gen-cluster/v1/commonapi/Cluster1StubDefault.hpp \
    Cluster1StubImpl.hpp

INCLUDEPATH += /usr/include/opencv4/
DEPENDPATH += /usr/include/opencv4/

LIBS += -L/usr/lib/x86_64-linux-gnu/
LIBS += \
-lopencv_core \
-lopencv_videoio \
-lopencv_ml \
-lopencv_objdetect \
-lopencv_stitching \
-lopencv_calib3d \
-lopencv_photo \
-lopencv_video \
-lopencv_dnn \
-lopencv_imgcodecs \
-lopencv_flann \
-lopencv_features2d \
-lopencv_imgproc \
-lopencv_highgui
