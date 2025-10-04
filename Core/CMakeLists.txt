file(GLOB_RECURSE TARGET_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

file(GLOB_RECURSE SHADER_FILES CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/*.glsl
    ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/*.frag
    ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/*.vert
)

file(GLOB_RECURSE ASSET_FILES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/Assets/**/*.obj
    ${CMAKE_CURRENT_SOURCE_DIR}/Assets/**/*.tga
    ${CMAKE_CURRENT_SOURCE_DIR}/Assets/**/*.jpg
    ${CMAKE_CURRENT_SOURCE_DIR}/Assets/**/*.png
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_FILES} ${SHADER_FILES} ${ASSET_FILES})

add_executable(${EXE_NAME})
target_sources(${EXE_NAME} PRIVATE ${TARGET_FILES})

foreach(file IN LISTS SHADER_FILES ASSET_FILES)
    set_source_files_properties(${file} PROPERTIES HEADER_FILE_ONLY TRUE)
    target_sources(${EXE_NAME} PRIVATE ${file})
endforeach()

target_include_directories(${EXE_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Header
    PRIVATE ${DEPENDENCIES_INCLUDE_DIR}
    PRIVATE ${LIB_INCLUDE_DIR}
    PRIVATE ${DATA_STRUCT_INCLUDE_DIR}
    PRIVATE ${LOW_RENDERER_INCLUDE_DIR}
    PRIVATE ${PHYSICS_INCLUDE_DIR}
    PRIVATE ${RESOURCES_INCLUDE_DIR}
)

target_link_directories(${EXE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Dependencies/lib)
target_link_libraries(${EXE_NAME}
    PRIVATE ${LIB_NAME}
    PRIVATE ${DATA_STRUCT}
    PRIVATE ${DEPENDENCIES_NAME}
    PRIVATE ${LOW_RENDERER}
    PRIVATE ${PHYSICS_NAME}
    PRIVATE ${RESOURCES_NAME}
    PRIVATE glfw3
    PRIVATE opengl32
    PRIVATE user32
    PRIVATE gdi32
    PRIVATE shell32
)

add_custom_command(TARGET ${EXE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Shaders"
        "$<TARGET_FILE_DIR:${EXE_NAME}>/Shaders"
)

add_custom_command(TARGET ${EXE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Assets"
        "$<TARGET_FILE_DIR:${EXE_NAME}>/Assets"
)

add_custom_command(TARGET ${EXE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Dependencies/binairies"
        $<TARGET_FILE_DIR:${EXE_NAME}>
)
