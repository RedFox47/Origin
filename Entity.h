#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "EntityData.h"
#include "libtcod.hpp"
#include "Helper.h"
#include "depend/AMEFProtocol/AMEFDecoder.h"
#include "depend/AMEFProtocol/AMEFEncoder.h"
#include <string>
#include <vector>

class Game;
class Map;

// Entity class; makes up visible game objects
class Entity {

    public:
        Entity();
        virtual ~Entity();

        /* If enough energy, call this function */
        virtual void DoLogic(Game* game);

        /* Initialize all the variables */
        virtual void init();

        /* Save the entity's variables into a tokenized string */
        virtual std::string SaveEntity(Game* g);

        /* Reload the entity's variables from a tokenized string */
        virtual void LoadEntity(std::string tokenized_data, Game* g);

        std::string name;   // The name of the entity
        std::string desc;   // The description of this entity

        e_type etype;       // (EntityData.h) The enumerated "type" of this entity
        std::string id;     // generic id; tells what subtype this entity is

        int x;  // x position
        int y;  // y position

        char symbol;        // c-string representation of the Entity
        int c_symbol;       // ASCII representation of the Entity (libtcod.hpp)
                            // c_symbol used instead of symbol if c_symbol != 0
        TCODColor color;    // The foreground color of the cell   (libtcod.hpp)
        TCODColor bgcolor;  // The background color of the cell   (libtcod.hpp)
        char layer;         // display layer (higher layers will be displayed on top of lower layers)

        unsigned int flags; // bitfield dictating miscellaneous characteristics (EntityData.h)
        std::vector<std::string> groups; // container of groups the entity pertains to
        bool deleting;      // true if stored in the game DeleteBuff list
};

#endif // ENTITY_H_INCLUDED
