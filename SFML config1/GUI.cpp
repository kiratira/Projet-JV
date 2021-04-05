#include "GUI.h"
#include < assert.h>

GUI* GUI::sInstance = nullptr;

GUI::GUI()
{
	assert(sInstance == nullptr);
	sInstance = this;
}

GUI::~GUI()
{
}
