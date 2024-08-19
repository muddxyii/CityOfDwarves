#include "Tile.h"

Tile::Tile(const TileType type) : type(type) {
}

TileType Tile::getType() const {
    return type;
}
