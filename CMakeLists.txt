cmake_minimum_required(VERSION 3.17)
project(SFMLTileMap)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(SOURCE_FILES main.cpp Tile.cpp Tile.h UI/Point.h UI/Dimensions.h TileMap.cpp TileMap.h TileMapRenderer.cpp TileMapRenderer.h TileRenderer.cpp TileRenderer.h TileMapEditor.cpp TileMapEditor.h BuilderTile.cpp BuilderTile.h UI/TextInput.cpp UI/TextInput.h UI/UIElement.cpp UI/UIElement.h UI/Label.cpp UI/Label.h UI/Button.cpp UI/Button.h UI/UIStack.cpp UI/UIStack.h UI/Dimensions.cpp TileMapFileInfo.h TileMapFileInfo.cpp UI/TextureContainer.cpp UI/TextureContainer.h UI/ImageSelector.cpp UI/ImageSelector.h UI/Alignment.h UI/ScrollableUIElement.cpp UI/ScrollableUIElement.h)
add_executable(TileMapEditor ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(TileMapEditor sfml-system sfml-window sfml-graphics sfml-audio sfml-network)


