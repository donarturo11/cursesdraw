# project(CursesDraw)

set(HEADERS
    UserInterface.h
    KeyboardInput.h
    CursorHandle.h
    )
    
set(SOURCES 
    main.cpp
    UserInterface.cpp
    KeyboardInput.cpp
    CursorHandle.cpp
    )

add_executable(
    ${PROJECT_NAME}
    ${HEADERS}
    ${SOURCES}
    )

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
target_link_libraries(${PROJECT_NAME} pdcurses)
else()
target_link_libraries(${PROJECT_NAME} ncurses)
endif()


install(TARGETS ${PROJECT_NAME} DESTINATION ${PREFIX}/bin)
