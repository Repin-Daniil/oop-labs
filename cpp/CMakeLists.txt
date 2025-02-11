cmake_minimum_required(VERSION 3.16)
project(cpp_scripts)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Собираем все .cpp файлы в списке
file(GLOB cpp_files *.cpp)

# Для каждого файла создаём отдельный исполняемый таргет
foreach(file ${cpp_files})
    get_filename_component(exe_name ${file} NAME_WE)
    add_executable(${exe_name} ${file})
    target_link_libraries(${exe_name} PRIVATE SYMCPP)
endforeach()
