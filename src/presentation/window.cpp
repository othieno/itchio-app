#include "window.h"

using itchio::Window;

Window::Window(Application& application) :
application_(application),
modalDialog_(this)
{
    setObjectName("window"); // Note: If the object name is changed, remember to update the stylesheet.
}
