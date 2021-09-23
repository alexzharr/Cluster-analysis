//Zharikov Alexey 211

#include "FormElement.h"

FormElement::FormElement()
{
	fe_p = {};
}

FormElement::FormElement(MyPoint c, double radius) :
	center(c), r(radius)
{}
