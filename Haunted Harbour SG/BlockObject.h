#pragma once
#include "graphicsobject.h"
enum class blockType{
bigblock,
smallblock
 };
class BlockObject :
	public GraphicsObject
{
public:
	BlockObject(int xpos,int ypos, int w, int h);
	blockType type;
	virtual ~BlockObject(void);
};

