#pragma GCC optimize("Ofast,unroll-loops,mfma,mavx,mavx2")
#pragma GCC target("avx,avx2,fma")
#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#ifndef TEXT_EDIT_BUTTTON_H
#define TEXT_EDIT_BUTTTON_H

#endif //TEXT_EDIT_BUTTTON_H

class Button {
 private:
    int height_, width_;
    float x_, y_;
    std::string txt_;
    sf::Color clr_;
    int sz_;
 public:
    Button(int width = 1, int height = 1, int x = 0, int y = 0, sf::Color clr = sf::Color::White) {
        height_ = height;
        width_ = width;
        clr_ = clr;
        x_ = x;
        y_ = y;
        txt_ = "";
        sz_ = 25;
    }
    Button(const Button& other) {
        height_ = other.height_;
        width_ = other.width_;
        clr_ = other.clr_;
        x_ = other.x_;
        y_ = other.y_;
        txt_ = other.txt_;
    }
    ~Button() = default;
    void draw (sf::RenderWindow& window) {
        sf::Font font;
        font.loadFromFile("Agbalumo-Regular.ttf");
        sf::RectangleShape tmp(sf::Vector2f(width_, height_));
        tmp.setPosition(x_, y_);
        tmp.setFillColor(clr_);
        window.draw(tmp);
        sf::Text txt;
        txt.setString(txt_);
        txt.setFont(font);
        txt.setColor(sf::Color::Blue);
        txt.setCharacterSize(sz_);
        txt.setPosition(x_, y_);
        window.draw(txt);
    }
    void setSZ(int sz) {
        sz_ = sz;
    }
    bool Pressed(float x, float y) {
        return x <= x_+width_ && x >= x_ && y <= y_+height_ && y >= y_;
    }
    void setText(std::string s) {
        txt_ = s;
    }
};