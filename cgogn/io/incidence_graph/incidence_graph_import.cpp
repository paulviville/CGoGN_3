/*******************************************************************************
 * CGoGN: Combinatorial and Geometric modeling with Generic N-dimensional Maps  *
 * Copyright (C), IGG Group, ICube, University of Strasbourg, France            *
 *                                                                              *
 * This library is free software; you can redistribute it and/or modify it      *
 * under the terms of the GNU Lesser General Public License as published by the *
 * Free Software Foundation; either version 2.1 of the License, or (at your     *
 * option) any later version.                                                   *
 *                                                                              *
 * This library is distributed in the hope that it will be useful, but WITHOUT  *
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or        *
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License  *
 * for more details.                                                            *
 *                                                                              *
 * You should have received a copy of the GNU Lesser General Public License     *
 * along with this library; if not, write to the Free Software Foundation,      *
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.           *
 *                                                                              *
 * Web site: http://cgogn.unistra.fr/                                           *
 * Contact information: cgogn@unistra.fr                                        *
 *                                                                              *
 *******************************************************************************/

#include <cgogn/io/incidence_graph/incidence_graph_import.h>

#include <cgogn/core/functions/attributes.h>
#include <cgogn/core/functions/mesh_ops/vertex.h>
#include <cgogn/core/types/mesh_traits.h>

#include <cgogn/core/types/incidence_graph/incidence_graph_ops.h>

#include <vector>

namespace cgogn
{

namespace io
{

void import_incidence_graph_data(IncidenceGraph& ig, const IncidenceGraphImportData& incidence_graph_data)
{
	using Vertex = IncidenceGraph::Vertex;

	for (uint32 vertex_id : incidence_graph_data.vertices_id_)
	{
	}

	for (uint32 i = 0; i < uint32(incidence_graph_data.edges_vertex_indices_.size()); i += 2)
	{
	}

	for (uint32 i = 0; i < uint32(incidence_graph_data.faces_edge_indices_.size()); i += 2)
	{
	}


	// remove_attribute<Vertex>(ig, vertex_dart);
}

} // namespace io

} // namespace cgogn