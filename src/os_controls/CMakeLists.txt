add_subdirectory(os_api)

if(BUILD_QT_UI)
        add_subdirectory(qt)
elseif(WIN32)
        add_subdirectory(windows)
else()
        add_subdirectory(stub)
endif()
