cmake_minimum_required (VERSION 3.0)

project (TMP CXX)

# Включение высокого уровня предупреждений
if(MSVC) # Компилятор MSVC /W3
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_compile_options(/experimental:external /external:anglebrackets /external:W0)
elseif(CMAKE_COMPILER_IS_GNUCC) # Компилятор GCC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wconversion -Wextra -Wpedantic")
endif()

add_subdirectory(lab-2)
add_subdirectory(lab-3)
add_subdirectory(other)
