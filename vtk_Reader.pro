######################################################################
# Automatically generated by qmake (2.01a) Mo 9. Mai 14:43:15 2011
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += mainwindow.h myvtkanimator.h myvtkinteractor.h myvtkreader.h
FORMS += mainwindow.ui
SOURCES += main.cpp \
           mainwindow.cpp \
           myvtkanimator.cpp \
           myvtkinteractor.cpp \
           myvtkreader.cpp

INCLUDEPATH += C:\Programme\VTK\bin \
C:\Programme\VTK\include\vtk-5.6

LIBS    += -L"C:\Programme\VTK\bin" -lvtkCommon -lvtksys -lQVTK -lvtkQtChart -lvtkViews -lvtkWidgets -lvtkInfovis -lvtkRendering -lvtkGraphics -lvtkImaging -lvtkIO -lvtkFiltering -lvtklibxml2 -lvtkDICOMParser -lvtkpng -lvtkpng -lvtktiff -lvtkzlib -lvtkjpeg -lvtkalglib -lvtkexpat -lvtkverdict -lvtkmetaio -lvtkNetCDF -lvtkexoIIc -lvtkftgl -lvtkfreetype -lvtkHybrid