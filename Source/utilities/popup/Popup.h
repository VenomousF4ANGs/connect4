#ifndef __POPUP_H__
#define __POPUP_H__

#include "axmol.h"
using namespace ax;

class Popup : public Object
{
private:
    Node* scene;

    Sprite* popupWindow;
    Label* popupCaption;
    Sprite* popupButton;

public:
    bool init() { return true; };
    void initialize(Node* scene);
    void show(const char* text, std::function<void()> action = nullptr);

    std::function<void()> action;
};

#endif