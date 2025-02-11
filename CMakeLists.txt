cmake_minimum_required(VERSION 3.16)
project(OOP_LABS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(third_party/symcpp)

# Подключаем подпроекты
add_subdirectory(cpp)
add_subdirectory(stable_vector)




#add_subdirectory(mvc)
#add_subdirectory(visual_editor)
