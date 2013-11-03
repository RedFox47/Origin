#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "Map.h"

/*
========
=NOTES:=
========
The 'World' data container holds all 'Map' sectors and organizes them into Height Levels. Height levels hold a map_data
map vector, which basically contains information of all the maps in that height level without having the load the
entire map into memory.

A sector of the world map is defined as a single Map with an x and y coordinate relative to the point of origin (0,0)
following a topright-to-bottomright increasing trend.

Geometric functions are to be handled in individual Map sector. Geometric functions can then automatically 'bleed' into
neighboring map sectors as necessary.

When cur_map is altered via Translate() or DeltaTranslate(dx, dy), getNeighbors() is called and the _neighbors container
is repopulated. The method it is repopulated is simply searching for WORLD_SAVE_DIR/level z/x,y.map. If the file is not found
then the map is generated (relative to information in cur_level->map_data)
*/

// The location in which to save world data in
#define WORLD_SAVE_DIR  "save/world"

// The height of a map sector
#define SECTOR_WIDTH    200
#define SECTOR_HEIGHT   200

/* A simple container for a height level in a world */
struct HeightLevel {
    int height;
    World* world;

    /* _map_data container is a 2D grid containing information of all available Map sectors in this level */
        // This is only really used to keep track of very basic data on all maps generated by the game.
    std::vector<std::map<std::string, std::string> > map_data;
        // Map data entry properties:
        //  Biome
        //  Subbiome
        //  x
        //  y

    /* Adds some map data to this height level */
    void AddMap(Map* map) {
        std::map<std::string, std::string> data;
        data["biome"] = "null";
        data["subbiome"] = "null";
        data["x"] = Helper::int2str(map->x);
        data["y"] = Helper::int2str(map->y);
        map_data.push_back(data);
    }
};

class World {

    public:
        World();
        ~World();

        /* Move the world over to x and y */
        void Translate(int x, int y);

        /* Clears the current neighbor container and populates it relative to cur_map */
        void PopulateNeighbors();

        /* Move the world over delative to cur_map by dx and dy */
        void DeltaTranslate(int dx, int dy);

        /* Save the cur_map and all neighbors */
        void SaveWorld();

        /* Load the cur_map and all its neighbors */
        void LoadWorld();

        /* Generate maps that need to be based off a global range relative to cur_map */
        void GenMaps(int range, Turf fill);

        /* Save a map with the specified path */
        void SaveMap(Map* map, std::string path);

        /* Save a map */
        void SaveMap(Map* map);

        /* Gets the HeightLevel at this z */
        HeightLevel* getHeightLevel(int level);

        /* Gets the current neighbors */
        std::vector<Map*> getNeighbors()        { return _neighbors; }

        Map* cur_map;                     // the current map that the player is in
        Game* game;                       // the main game object

        HeightLevel* cur_level;           // the current height level / z layer

    private:

        std::vector<Map*> _neighbors;     // maps that neighbor the current map
            /* Relative neighbor coordinates:

                (-1, -1)     (0, -1)     (1, -1)
                (-1, 0)     (cur_map)    (1, 0)
                (-1, 1)      (0, 1)      (1, 1)
            */

        std::vector<HeightLevel*> _levels;  // height levels available
};

#endif // WORLD_H_INCLUDED