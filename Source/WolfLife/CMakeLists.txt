set(PROJECT_NAME WolfLife)

add_executable(${PROJECT_NAME} main.cpp)

set(SOURCE_FILES Application.cpp Application.h 
                 ResourceManager.cpp ResourceManager.h
                 TextureObject.cpp TextureObject.h
                 World.cpp World.h
                 Agents/Vehicle.cpp Agents/Vehicle.h 
                 Agents/Wolf.cpp Agents/Wolf.h
                 Agents/AIVehicle.cpp Agents/AIVehicle.h
                 Agents/Dog.cpp Agents/Dog.h
                 Agents/Sheep.cpp Agents/Sheep.h
                 Components/Component.cpp Components/Component.h
                 Components/Collision.cpp Components/Collision.h
                 Components/Eyeshot.cpp Components/Eyeshot.h
                 Components/Path.cpp Components/Path.h
                 )
add_library(${PROJECT_NAME}Lib STATIC ${SOURCE_FILES})
add_library(${PROJECT_NAME}Utils STATIC Utils.cpp Utils.h)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}Lib)
target_link_libraries(${PROJECT_NAME}Lib raylib eventpp::eventpp ${PROJECT_NAME}Utils)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}Lib PROPERTIES FOLDER ${PROJECT_NAME})

include_directories(Source)
include_directories(Resources)
# COPY RESOURCES
set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/Resources)
set(DEST_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/Resources)

add_custom_command(
    OUTPUT ${DEST_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCE_DIR} ${DEST_DIR}
    COMMENT "Копирование ресурсов в папку сборки"
)

add_custom_target(copy_resources ALL
    DEPENDS ${DEST_DIR}
)

add_dependencies(${PROJECT_NAME} copy_resources)