#pragma GCC optimize("Ofast,unroll-loops,mfma,mavx,mavx2")
#pragma GCC target("avx,avx2,fma")
#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "buttton.h"
#include "text_backend.h"

int main() {
    sf::RenderWindow main_window(sf::VideoMode(600, 900), "my_word :)");
    /////////////////////////////////////////////////////////////////////
    sf::Font font;
    font.loadFromFile("Agbalumo-Regular.ttf");
    /////////////////////////////////////////////////////////////////////
    sf::Text input;
    input.setPosition(0, 510);
    input.setFont(font);
    input.setFillColor(sf::Color::Red);
    /////////////////////////////////////////////////////////////////////
    sf::RectangleShape text_field(sf::Vector2f(320, 500));
    text_field.setFillColor(sf::Color(255, 255, 236));
    /////////////////////////////////////////////////////////////////////
    sf::RectangleShape text_field_inp(sf::Vector2f(320, 280));
    text_field_inp.setPosition(0, 510);
    text_field_inp.setFillColor(sf::Color(255, 255, 236));
    /////////////////////////////////////////////////////////////////////
    Button insertLineBtn(180, 40, 410, 10, sf::Color(150, 190, 150));
    insertLineBtn.setText("insert line");

    Button insertLinesBtn(180, 40, 410, 60, sf::Color(150, 190, 150));
    insertLinesBtn.setText("insert lines");

    Button deleteLineBtn(180, 40, 410, 110, sf::Color(150, 190, 150));
    deleteLineBtn.setText("delete line");

    Button insertSublineBtn(180, 40, 410, 160, sf::Color(150, 190, 150));
    insertSublineBtn.setText("insert subline");

    Button replaceCharBtn(180, 40, 410, 210, sf::Color(150, 190, 150));
    replaceCharBtn.setText("replace char");

    Button replaceSublineBtn(180, 40, 410, 260, sf::Color(150, 190, 150));
    replaceSublineBtn.setText("replace subline");

    Button delZeroBtn(180, 40, 410, 310, sf::Color(150, 190, 150));
    delZeroBtn.setText("delete zero");

    Button starToPlusBtn(180, 40, 410, 360, sf::Color(150, 190, 150));
    starToPlusBtn.setText("stars to pluses");

    Button delBtn(180, 40, 410, 410, sf::Color(150, 190, 150));
    delBtn.setText("delete brackets");

    Button numberFBtn(180, 40, 410, 460, sf::Color(150, 190, 150));
    numberFBtn.setSZ(15);
    numberFBtn.setText("only increasing\n sequences");

    Button fileBtn(180, 40, 410, 510, sf::Color(150, 190, 150));
    fileBtn.setText("file");
    /////////////////////////////////////////////////////////////////////
    Text main_text;
    std::ifstream fin("Text.txt");
    while (!fin.eof()) {
        std::string str = "";
        if (getline(fin, str)) {
            main_text.pushLine((int) main_text.size(), str);
        }
    }
    std::string input_text = "";
    int sz_last_line = 0;
    int i = 0;
    int tmp = 0;
    int begin = 0, end = std::min((int)main_text.size(), 19);
    /////////////////////////////////////////////////////////////////////
    while (main_window.isOpen())
    {
        sf::Vector2i m_pozition = sf::Mouse::getPosition(main_window);
        sf::Event event;
        while (main_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                main_window.close();
        }
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128) {
                if (tmp == 0) {
                    tmp = 200;
                    if (event.text.unicode == 8) {
                        if ((int) input_text.size()) {
                            input_text.pop_back();
                            --sz_last_line;
                            if (sz_last_line < 0) {
                                sz_last_line = 19;
                            }
                        }
                    } else {
                        input_text += static_cast<char>(event.text.unicode);
                        ++sz_last_line;
                        if (event.text.unicode == 10) {
                            sz_last_line = 0;
                        }
                        if (sz_last_line >= 19) {
                            input_text.push_back('\n');
                            sz_last_line = 0;
                        }
                    }
                } else {
                    --tmp;
                }
            }
        } else if (event.type == sf::Event::KeyPressed) {
            if (tmp == 0) {
                if (event.key.code == sf::Keyboard::Down) {
                    if (end < (int) main_text.size()) {
                        ++end;
                        if (end - begin > 19) {
                            ++begin;
                        }
                        tmp = 200;
                    }
                } else if (event.key.code == sf::Keyboard::Up) {
                    if (begin) {
                        --end;
                        --begin;
                        tmp = 200;
                    }
                }
            }
            --tmp;
        } else {
            tmp = 0;
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (insertLineBtn.Pressed(m_pozition.x, m_pozition.y)) {
                std::stringstream ssin(input_text);
                if ((int)input_text.size()) {
                    int n;
                    std::string s;
                    if (ssin >> n) {
                        while (getline(ssin, s)) {
                            if (s.empty()) continue;
                            main_text.pushLine(n - 1, s);
                            ++end;
                            if (end - begin > 19) {
                                ++begin;
                            }
                            input_text = "";
                            sz_last_line = 0;
                            ++n;
                        }
                    }
                }
            } else if (insertLinesBtn.Pressed(m_pozition.x, m_pozition.y)) {
                std::stringstream ssin(input_text);
                if ((int)input_text.size()) {
                    int n;
                    std::string s;
                    if (ssin >> n) {
                        while (getline(ssin, s)) {
                            if (s.empty()) continue;
                            main_text.pushLine(n - 1, s);
                            ++end;
                            if (end - begin > 19) {
                                ++begin;
                            }
                            input_text = "";
                            sz_last_line = 0;
                            ++n;
                        }
                    }
                }
            } else if (deleteLineBtn.Pressed(m_pozition.x, m_pozition.y)) {
                std::stringstream ssin(input_text);
                if ((int)input_text.size()) {
                    int n;
                    if (ssin >> n) {
                        if ((int)main_text.size() >= n) {
                            main_text.popLine(n);
                            --end;
                            if (begin) {
                                --begin;
                            }
                            input_text = "";
                            sz_last_line = 0;
                        }
                    }
                }
            } else if (insertSublineBtn.Pressed(m_pozition.x, m_pozition.y)) {
                std::stringstream ssin(input_text);
                if ((int)input_text.size()) {
                    int n, m;
                    std::string s;
                    if (ssin >> n >> m >> s) {
                        main_text.pushSubstring(n-1, m, s);
                        input_text = "";
                        sz_last_line = 0;
                    }
                }
            } else if (replaceCharBtn.Pressed(m_pozition.x, m_pozition.y)) {
                std::stringstream ssin(input_text);
                if ((int)input_text.size()) {
                    int n, m;
                    char s;
                    if (ssin >> n >> m >> s) {
                        main_text.replaceCharacte(n-1, m-1, s);
                        input_text = "";
                        sz_last_line = 0;
                    }
                }
            } else if (replaceSublineBtn.Pressed(m_pozition.x, m_pozition.y)) {
                std::stringstream ssin(input_text);
                if ((int)input_text.size()) {
                    int n, m;
                    std::string s1, s2;
                    if (ssin >> n >> m >> s1 >> s2) {
                        main_text.replaceSubines(n-1, m-1, s1, s2);
                        input_text = "";
                        sz_last_line = 0;
                    } else {
                        std::stringstream ssin2(input_text);
                        if (ssin2 >> s1 >> s2) {
                            n = 1, m = (int)main_text.size();
                            main_text.replaceSubines(n-1, m-1, s1, s2);
                            input_text = "";
                            sz_last_line = 0;
                        }
                    }
                }
            } else if (delZeroBtn.Pressed(m_pozition.x, m_pozition.y)) {
                std::stringstream ssin(input_text);
                if ((int)input_text.size()) {
                    int n, m;
                    if (ssin >> n >> m) {
                        for (int i = n; i <= m; ++i) {
                            main_text.delZero(i - 1);
                        }
                        input_text = "";
                        sz_last_line = 0;
                    }
                }
            } else if (starToPlusBtn.Pressed(m_pozition.x, m_pozition.y)) {
                std::stringstream ssin(input_text);
                if ((int)input_text.size()) {
                    int n, m;
                    if (ssin >> n >> m) {
                        main_text.StarToPlus(n-1, m-1);
                        input_text = "";
                        sz_last_line = 0;
                    }
                }
            } else if (delBtn.Pressed(m_pozition.x, m_pozition.y)) {
                std::stringstream ssin(input_text);
                if ((int)input_text.size()) {
                    int n, m;
                    if (ssin >> n >> m) {
                        main_text.del(n-1, m-1);
                    }
                }
            } else if (numberFBtn.Pressed(m_pozition.x, m_pozition.y)) {
                std::stringstream ssin(input_text);
                if ((int)input_text.size()) {
                    int n, m;
                    if (ssin >> n >> m) {
                        main_text.NumbersF(n-1, m-1);
                        input_text = "";
                        sz_last_line = 0;
                    }
                }
            } else if (fileBtn.Pressed(m_pozition.x, m_pozition.y)) {
                std::ofstream fout("Text.txt");
                for (int i = 0; i < main_text.size(); ++i) {
                    fout << main_text.getLine(i) << '\n';
                }
            }
        }
        input.setString(input_text);
        input.setCharacterSize(17);
        main_window.clear();
        main_window.draw(text_field);
        main_window.draw(text_field_inp);
        main_window.draw(input);
        for (int i = begin; i < end; ++i) {
            sf::Text text;
            std::string str = main_text.getLine(i);
            text.setString(str);
            if ((int)str.size() >= 20) {
                main_text.popLine(i+1);
                int temp = 0;
                std::string str2 = "";
                for (auto& e : str) {
                    if ((int)str2.size() == 19) {
                        main_text.pushLine(i+temp++, str2);
                        str2 = "";
                        ++end;
                        if (end - begin > 19) {
                            ++begin;
                        }
                    }
                    str2.push_back(e);
                }
                --end;
                if (begin) {
                    --begin;
                }
                if ((int)str2.size() > 0) {
                    main_text.pushLine(i + temp, str2);
                    ++end;
                    if (end - begin > 19) {
                        ++begin;
                    }
                }
            }
            text.setPosition(0, 10+25*(i-begin));
            text.setFont(font);
            text.setCharacterSize(17);
            text.setFillColor(sf::Color(0, 0, 115));
            main_window.draw(text);
        }
        insertLineBtn.draw(main_window);
        insertLinesBtn.draw(main_window);
        deleteLineBtn.draw(main_window);
        insertSublineBtn.draw(main_window);
        replaceCharBtn.draw(main_window);
        replaceSublineBtn.draw(main_window);
        delZeroBtn.draw(main_window);
        starToPlusBtn.draw(main_window);
        delBtn.draw(main_window);
        fileBtn.draw(main_window);
        numberFBtn.draw(main_window);
        main_window.display();
    }

    return 0;
}