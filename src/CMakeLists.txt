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

if(ENABLE_PDCURSES AND ENABLE_SDL)
target_link_libraries(${PROJECT_NAME} pdcurses ${SDL_LIBRARIES})
elseif(ENABLE_PDCURSES AND ${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
target_link_libraries(${PROJECT_NAME} pdcurses winmm -static)
else()
target_link_libraries(${PROJECT_NAME} ncurses)
endif()


install(TARGETS ${PROJECT_NAME} DESTINATION ${PREFIX}/bin)
