/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Screen.h"
#include <iostream>
#include <iomanip>

using std::cout; using std::endl; using std::setw;


Screen::Screen(int width, int height) : m_width {width}, m_height {height} 
{
    m_screen = new char[m_width*m_height];
}


Screen::Screen(const Screen& other) 
    : m_width {other.m_width}, m_height {other.m_height} 
{
    for (int i = 0; i < other.m_screens.size(); ++i)
    {
        m_screens.push_back(other.m_screens[i]);    
    }
}

Screen::~Screen() 
{
    delete[] m_screen;
}


char Screen::getChar(Pos2d pos) const
{
    return m_screen[pos.x + m_width * pos.y];
}

char& Screen::getChar(Pos2d pos)
{
    return m_screen[pos.x + m_width * pos.y];
}

void Screen::setChar(Pos2d pos, char c)
{
    m_screen[pos.x + m_width * pos.y] = c;
}

void Screen::setString(Pos2d pos, const string& item)
{
    for (int i = 0; i < item.size(); ++i) {
        //m_screen[i + pos.x + m_width * pos.y] = item[i];
        setChar({pos.x + i, pos.y}, item[i]); 
    }
}

void Screen::setInt(Pos2d pos, const int& item)
{
    string str = std::to_string(item);
    for (int i = 0; i < str.size(); ++i) {
        //m_screen[i + pos.x + m_width * pos.y] = str[i];
        setString(pos, str);
    }
}

void Screen::fill(char c)
{
    for (int i = 0; i < m_height; ++i)
        for (int j = 0; j < m_width; ++j) {
        setChar({j,i},c);
        }
}

void Screen::addSubScreen(Screen* subs, Pos2d anchor, const string& name)
{
    subs->m_anchor = anchor;
    subs->m_name = name;
    m_screens.push_back(subs);
}

Screen* Screen::getSubScreen(const string& name)
{
    for (int i = 0; i < m_screens.size(); ++i)
        if (m_screens[i]->m_name == name) return m_screens[i];
    return nullptr;
}


void Screen::setAnchor(Pos2d anchor)
{
    m_anchor = anchor;
}


void Screen::draw(Screen& s)
{
    for (int i = 0; i < s.m_height; ++i){
        for (int j = 0; j < s.m_width; ++j)
        {
            setChar({j + s.m_anchor.x, i + s.m_anchor.y}, s.getChar({j,i}));
            //m_screen[j + s.m_anchor.x + (i + s.m_anchor.y) * m_width] = s.m_screen[j + s.m_width * i];
        }
    }
    
}

void Screen::draw()
{
    for (int i = 0; i < m_screens.size(); ++i)
        draw(*m_screens[i]);
    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j){
            cout << setw(2) << m_screen[j + i * m_width];
        }
        cout << endl;
    }
}