set(PROJECT_NAME WolfLife)

add_executable(${PROJECT_NAME} main.cpp)

set(SOURCE_FILES Application.cpp Application.h 
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

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}Lib)
target_link_libraries(${PROJECT_NAME}Lib raylib eventpp::eventpp)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}Lib PROPERTIES FOLDER ${PROJECT_NAME})