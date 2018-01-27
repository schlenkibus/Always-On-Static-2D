cmake_minimum_required(VERSION 3.9)
project(GGJ2018)

set(CMAKE_CXX_STANDARD 17)

add_executable(GGJ2018 src/main.cpp src/Application.cpp src/Application.h src/GameStates/GameState.h src/GameStates/MenuGameState.cpp src/GameStates/MenuGameState.h src/Tools/TimeUtils.h src/GUI/Button.cpp src/GUI/Button.h src/ResourceManagement/ResourceManager.cpp src/ResourceManagement/ResourceManager.h src/GUI/Label.cpp src/GUI/Label.h src/Tools/Tools.h src/GameStates/IngameState.cpp src/GameStates/IngameState.h src/Box2D/PhysicsWorld.cpp src/Box2D/PhysicsWorld.h src/Game/GameActor.cpp src/Game/GameActor.h src/Game/GamePosition.h src/Game/PlayerActor.cpp src/Game/PlayerActor.h src/Tools/UDPLayer.h src/Game/staticNoiseActor.cpp src/Game/staticNoiseActor.h src/Game/gameObject.h src/Game/genericGameObject.cpp src/Game/genericGameObject.h src/GameStates/TvGame.cpp src/GameStates/TvGame.h src/Game/tvGameObject.cpp src/Game/tvGameObject.h src/Game/currentSymbolObject.cpp src/Game/currentSymbolObject.h)

TARGET_LINK_LIBRARIES(GGJ2018 pthread)
TARGET_LINK_LIBRARIES(GGJ2018 stdc++fs)
TARGET_LINK_LIBRARIES(GGJ2018 sfml-system)
TARGET_LINK_LIBRARIES(GGJ2018 sfml-audio)
TARGET_LINK_LIBRARIES(GGJ2018 sfml-graphics)
TARGET_LINK_LIBRARIES(GGJ2018 sfml-window)
TARGET_LINK_LIBRARIES(GGJ2018 sfml-network)
TARGET_LINK_LIBRARIES(GGJ2018 Box2D)
TARGET_LINK_LIBRARIES(GGJ2018 m)