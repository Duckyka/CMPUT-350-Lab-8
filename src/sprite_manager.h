#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "sprite.h"
#include <SFML/Graphics.hpp>
#include <tuple>

using SpriteID = size_t;

class SpriteManager
{
public: 
    SpriteManager() = default;
    ~SpriteManager() = default;

    sf::Texture& registerTexture(const std::string& filepath)
    {
        auto seen_string = mTextures.find(filepath);
        if (seen_string != mTextures.end())
        {
            return seen_string->second;
        }
        else
        {
            sf::Texture texture(filepath);
            mTextures.insert({filepath, texture});
            return texture;
        }
    }

    template <typename... Args>
    SpriteID createSprite(Args&&... args)
    {   
        auto myTuple = std::forward_as_tuple(std::forward<Args>(args)...);
        sf::Texture& texture = std::get<sf::Texture&>(myTuple);
        mSprites.push_back(Sprite(texture));
        return mSprites.size() - 1;
    }

    Sprite& getSprite(SpriteID id)
    {
        return mSprites.at(id);
    }
private: 
    std::unordered_map<std::string, sf::Texture> mTextures;
    std::vector<Sprite> mSprites;
};

#endif  // SPRITE_MANAGER_H
