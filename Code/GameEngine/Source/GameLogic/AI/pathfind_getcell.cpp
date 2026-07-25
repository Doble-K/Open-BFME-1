// cl: /EHsc /Ireference/shims/pathfind
#include "GameLogic/AIPathfind.h"

// Retail rejects type==5 (CELL_BRIDGE_IMPASSABLE in this tree's ordinal - see
// PathfindCell::getRawType's comment) rather than ZH's CELL_IMPASSABLE(6).
PathfindCell *PathfindLayer::getCell(Int x, Int y)
{
	if (m_layerCells == 0)
		return 0;
	x -= m_xOrigin;
	y -= m_yOrigin;
	if (x < 0 || x >= m_width)
		return 0;
	if (y < 0 || y >= m_height)
		return 0;
	PathfindCell *cell = &m_layerCells[x][y];
	if (cell->getRawType() == 5)
		return 0;
	return cell;
}

PathfindCell *Pathfinder::getCell(PathfindLayerEnum layer, Int x, Int y)
{
	if (x >= m_extent.lo.x && x <= m_extent.hi.x &&
		y >= m_extent.lo.y && y <= m_extent.hi.y)
	{
		if (layer > 1 && layer <= 15)
		{
			PathfindCell *cell = m_layers[layer].getCell(x, y);
			if (cell)
				return cell;
		}
		return &m_map[x][y];
	}
	return 0;
}
