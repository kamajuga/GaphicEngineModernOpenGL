#Core

file(GLOB_RECURSE TARGET_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

# Collect non-code files
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

get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
add_executable(${TARGET_NAME})
target_sources(${TARGET_NAME} PRIVATE ${TARGET_FILES})

# Add shaders & assets as header-only sources (so they show in IDE but aren't compiled)
foreach(file IN LISTS SHADER_FILES ASSET_FILES)
    set_source_files_properties(${file} PROPERTIES HEADER_FILE_ONLY TRUE)
    target_sources(${EXE_NAME} PRIVATE ${file})
endforeach()


target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Header)
target_include_directories(${TARGET_NAME} PRIVATE ${ASSETS_FILES})
target_include_directories(${TARGET_NAME} PRIVATE ${SHADER_FILES})
target_include_directories(${TARGET_NAME} PRIVATE ${DEPENDENCIES_INCLUDE_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${LIB_INCLUDE_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${DATA_STRUCT_INCLUDE_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${LOW_RENDERER_INCLUDE_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${PHYSICS_INCLUDE_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${RESOURCES_INCLUDE_DIR})


target_link_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Dependencies/lib)
target_link_libraries(${TARGET_NAME} PRIVATE ${LIB_NAME})
target_link_libraries(${TARGET_NAME} PRIVATE ${DATA_STRUCT})
target_link_libraries(${TARGET_NAME} PRIVATE ${DEPENDENCIES_NAME})
target_link_libraries(${TARGET_NAME} PRIVATE ${LOW_RENDERER})
target_link_libraries(${TARGET_NAME} PRIVATE ${PHYSICS_NAME})
target_link_libraries(${TARGET_NAME} PRIVATE ${RESOURCES_NAME})
target_link_libraries(${TARGET_NAME} PRIVATE glfw3)
target_link_libraries(${TARGET_NAME} PRIVATE opengl32)
target_link_libraries(${TARGET_NAME} PRIVATE user32)
target_link_libraries(${TARGET_NAME} PRIVATE gdi32)
target_link_libraries(${TARGET_NAME} PRIVATE shell32)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Shaders"
        "$<TARGET_FILE_DIR:${TARGET_NAME}>/Shaders"
)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Assets"
        "$<TARGET_FILE_DIR:${TARGET_NAME}>/Assets"
)

add_custom_command(TARGET ${EXE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Dependencies/binairies"
        $<TARGET_FILE_DIR:${EXE_NAME}>
)