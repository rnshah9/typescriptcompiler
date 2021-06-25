macro(set_Options)

if(MSVC)
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
else()
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-switch -Wno-unused-function -Wno-unused-result -Wno-unused-variable -Wno-unused-private-field -Wno-sign-compare -Wno-implicit-fallthrough -Wno-logical-op-parentheses -Wno-parentheses -Wno-unused-command-line-argument -lstdc++fs")
endif()

endmacro()

macro(set_Libs list)

if(MSVC)
else()
    set(list "${list} stdc++fs")
endif()

endmacro()

