cmake_minimum_required (VERSION 2.6 FATAL_ERROR)

project      (Multi-ply-manipulator)
find_package (OpenCV REQUIRED)
find_package (PCL 1.8.1 REQUIRED)

include_directories (${PCL_INCLUDE_DIRS})
link_directories    (${PCL_LIBRARY_DIRS})
add_definitions     (${PCL_DEFINITIONS})

find_package (VTK REQUIRED)
include(${VTK_USE_FILE})

#set  (project_SOURCES main.cpp mainwindow.cpp)
#set  (project_HEADERS mainwindow.h)
#set  (project_FORMS   mainwindow.ui)
set   (VTK_LIBRARIES)

file(GLOB project_SOURCES *.cpp)
file(GLOB project_HEADERS *.h)
file(GLOB project_FORMS *.ui)


QT5_WRAP_CPP (project_HEADERS_MOC   ${project_HEADERS})
QT5_WRAP_UI  (project_FORMS_HEADERS ${project_FORMS})

ADD_DEFINITIONS (${QT_DEFINITIONS})

ADD_EXECUTABLE  (Multi-ply-manipulator ${project_SOURCES}
${project_FORMS_HEADERS}
${project_HEADERS_MOC})

TARGET_LINK_LIBRARIES (Multi-ply-manipulator ${PCL_LIBRARIES} ${VTK_LIBRARIES} ${OpenCV_LIBS})
qt5_use_modules (Multi-ply-manipulator Widgets)
