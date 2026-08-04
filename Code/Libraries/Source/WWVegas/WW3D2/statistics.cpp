// cl: /DNDEBUG
/*
**	Command & Conquer Generals(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Debug_Statistics counters from WW3D2/statistics.cpp, verbatim from the Zero
// Hour reference. Only the accumulators this function touches are declared: the
// real statistics.h drags in dx8wrapper.h and the DirectX 8 SDK headers, which
// the fleet toolchains do not have, and the counters are file-static either way
// so their addresses are relocated from retail, not from this TU.

namespace Debug_Statistics
{
	void Record_Sorting_Polys_And_Vertices(int pcount, int vcount);
}

static int sorting_polygons;
static int sorting_vertices;
static int draw_calls;

void Debug_Statistics::Record_Sorting_Polys_And_Vertices(int pcount,int vcount)
{
	sorting_polygons+=pcount;
	sorting_vertices+=vcount;
	draw_calls++;
}
