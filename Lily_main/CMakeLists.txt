cmake_minimum_required(VERSION 3.13)
project(Lily_main)

set(CMAKE_CXX_STANDARD 20)

set(Headers /home/pi/C-Programmes/)
set(QT_INCLUDE_PATH /usr/include/arm-linux-gnueabihf/qt5)

include_directories(${Headers})
find_package(CURL REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Core REQUIRED)
set(Dependencies ${Headers}/functions/LilyStdFuncs.cpp ${Headers}/functions/LilyStdFuncs.hpp ${Headers}/functions/LilyStdFuncsString.cpp ${Headers}/functions/LilyStdFuncsString.hpp ${Headers}/espeak/speak.hpp ${Headers}/search/listQuest.hpp ${Headers}/listen/Speach_recognizer.hpp ${Headers}/espeak/speak.cpp ${Headers}/search/listQuest.cpp ${Headers}/listen/Speach_recognizer.cpp ${Headers}/search/questInterface.hpp ${Headers}/search/questInterface.cpp ${Headers}/search/questFunc.hpp ${Headers}/search/questFunc.cpp ${Headers}/search/NormalQuestion.cpp ${Headers}/search/NormalQuestion.hpp ${Headers}/search/questFuncString.cpp ${Headers}/search/questFuncString.hpp ${Headers}/search/questType.hpp ${Headers}/addGUI/Database_handler.hpp ${Headers}/addGUI/Database_handler.cpp ${Headers}/listen/Dictionary_txt.cpp ${Headers}/listen/Dictionary_txt.hpp )
add_executable(Lily_main main.cpp Lily_Speach_Assistant.cpp Lily_Speach_Assistant.hpp ${Dependencies})
target_link_libraries(Lily_main PUBLIC ${CURL_LIBRARIES} jsoncpp pocketsphinx sphinxbase sphinxad asound Qt5Sql Qt5Core)
target_include_directories(Lily_main PUBLIC ${Headers} ${QT_INCLUDE_PATH} ${QT_INCLUDE_PATH}/QtSql ${QT_INCLUDE_PATH}/QtCore)