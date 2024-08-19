#ifndef TILE_H
#define TILE_H

enum class TileType {
    GRASS,
    TREE,
};

class Tile {
public:
    explicit Tile(TileType type);
    [[nodiscard]] TileType getType() const;
private:
    TileType type;
};



#endif //TILE_H
