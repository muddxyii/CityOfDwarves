#include <array>
#include <iostream>
#include <ctime>
#include <memory>
#include <random>
#include <vector>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "Engine/Engine.h"
#include "Game/Tile/Tile.h"

struct GameScene {
    Camera camera = Camera();
    int grassId = -1;
    int treeId = -1;
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
    glm::vec2 gridSize{12.0f, 8.0f};
    const float TREE_PROBABILITY = 0.2f;
};

void InitScene(GameScene& gameScene);
void GenerateMap(GameScene& gameScene);
void UpdateScene(GameScene& gameScene);
void RenderScene(const GameScene& gameScene);

Engine engine =  Engine("City of Dwarves" ,800, 600);

void drawMap(glm::vec2 gridSize);

int main()
{
    GameScene gameScene = GameScene();
    InitScene(gameScene);

    engine.setTargetFPS(60);
    while (!engine.windowShouldClose()) {
        engine.limitFrameRate();

        // Update logic
        UpdateScene(gameScene);

        // Clear background for render
        engine.clearBackground(100, 149, 237);

        // Render objects Here
        RenderScene(gameScene);

        // Present Render
        engine.presentRender();

        engine.capFrameRate();
    }

    return 0;
}

void InitScene(GameScene &gameScene) {
    // Load Textures
    gameScene.grassId = engine.loadTexture("assets/environment/grass.png");
    gameScene.treeId = engine.loadTexture("assets/environment/tree.png");

    // Set Camera
    engine.setCurrentCamera(&gameScene.camera);

    // Generate the map
    GenerateMap(gameScene);
}

void GenerateMap(GameScene &gameScene) {
    std::mt19937 rng(std::time(nullptr));
    std::uniform_real_distribution<float> dist(0.0, 1.0);

    gameScene.tiles.resize(static_cast<size_t>(gameScene.gridSize.y));
    for (int y = 0; y < static_cast<int>(gameScene.gridSize.y); ++y) {
        gameScene.tiles[y].resize(static_cast<size_t>(gameScene.gridSize.x));
        for (int x = 0; x < static_cast<int>(gameScene.gridSize.x); ++x) {
            if (dist(rng) < gameScene.TREE_PROBABILITY) {
                gameScene.tiles[y][x] = std::make_unique<Tile>(TileType::TREE);
            } else {
                gameScene.tiles[y][x] = std::make_unique<Tile>(TileType::GRASS);
            }
        }
    }
}

void UpdateScene(GameScene &gameScene) {
    // Move Camera
    glm::vec2 moveDir{0.0f, 0.0f};
    constexpr std::array<std::pair<SDL_Scancode, glm::vec2>, 4> keyDirections = {{
        {SDL_SCANCODE_W, {0.0f, -1.0f}},
        {SDL_SCANCODE_S, {0.0f, 1.0f}},
        {SDL_SCANCODE_A, {-1.0f, 0.0f}},
        {SDL_SCANCODE_D, {1.0f, 0.0f}}
    }};
    for (const auto& [key, dir] : keyDirections) {
        if (engine.isKeyPressed(key)) {
            moveDir += dir;
        }
    }
    if (moveDir != glm::vec2{0.0f, 0.0f}) {
        gameScene.camera.move(glm::normalize(moveDir) * 10.0f);
    }
}

void RenderScene(const GameScene &gameScene) {
    for (int y = 0; y < static_cast<int>(gameScene.gridSize.y); ++y) {
        for (int x = 0; x < static_cast<int>(gameScene.gridSize.x); ++x) {
            const SDL_Rect destRect = {x * 128, y * 128, 128, 128};

            // Always draw grass
            engine.drawTextureRect(destRect, gameScene.grassId);

            // If it's a tree tile, draw the tree on top of the grass
            if (gameScene.tiles[y][x]->getType() == TileType::TREE) {
                engine.drawTextureRect(destRect, gameScene.treeId);
            }
        }
    }
}
