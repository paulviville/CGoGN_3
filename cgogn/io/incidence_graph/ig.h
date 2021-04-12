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

#ifndef CGOGN_IO_INCIDENCE_GRAPH_IG_H_
#define CGOGN_IO_INCIDENCE_GRAPH_IG_H_

#include <cgogn/io/incidence_graph/incidence_graph_import.h>
#include <cgogn/io/utils.h>

#include <cgogn/core/functions/attributes.h>
#include <cgogn/core/types/mesh_traits.h>
#include <cgogn/core/utils/numerics.h>

#include <cgogn/geometry/types/vector_traits.h>

#include <fstream>
#include <vector>

namespace cgogn
{

namespace io
{

template <typename MESH>
bool import_IG(MESH& m, const std::string& filename)
{
	static_assert(mesh_traits<MESH>::dimension == 2, "MESH dimension should be 1");

	using Vertex = typename MESH::Vertex;

	Scoped_C_Locale loc;

	IncidenceGraphImportData incidence_graph_data;

	std::ifstream fp(filename.c_str(), std::ios::in);

	std::string line;
	line.reserve(512);

	getline_safe(fp, line);
	if (line.rfind("IG") == std::string::npos)
	{
		std::cerr << "File \"" << filename << "\" is not a valid ig file." << std::endl;
		return false;
	}

	// read number of vertices, edges, faces
	// getline_safe(fp, line);
	const uint32 nb_vertices = read_uint(fp, line);
	const uint32 nb_edges = read_uint(fp, line);
	const uint32 nb_faces = read_uint(fp, line);

	std::cout << "import ig: " << nb_vertices << " " << nb_edges << " " << nb_faces << std::endl;

	if (nb_vertices == 0u)
	{
		std::cerr << "File \"" << filename << " has no vertices." << std::endl;
		return false;
	}

	incidence_graph_data.reserve(nb_vertices);
	auto position = add_attribute<geometry::Vec3, Vertex>(m, "position");

	// // read vertices
	// for (uint32 i = 0; i < nb_vertices; ++i)
	// {
	// 	getline_safe(fp, line);
	// 	std::stringstream iss(line);

	// 	std::string tag;
	// 	iss >> tag;

	// 	if (tag == std::string("v"))
	// 	{
	// 		float64 x, y, z;
	// 		iss >> x;
	// 		iss >> y;
	// 		iss >> z;

	// 		uint32 vertex_id = new_index<Vertex>(m);
	// 		(*position)[vertex_id] = {x, y, z};

	// 		incidence_graph_data.vertices_id_.push_back(vertex_id);
	// 	}
	// }

	// // read edges
	// for (uint32 i = 0; i < nb_edges; ++i)
	// {
	// 	getline_safe(fp, line);
	// 	std::stringstream iss(line);

	// 	std::string tag;
	// 	iss >> tag;

	// 	if (tag == std::string("e"))
	// 	{
	// 		uint32 a, b;
	// 		iss >> a;
	// 		iss >> b;

	// 		incidence_graph_data.edges_vertex_indices_.push_back(incidence_graph_data.vertices_id_[a - 1]);
	// 		incidence_graph_data.edges_vertex_indices_.push_back(incidence_graph_data.vertices_id_[b - 1]);
	// 		// graph_data.edges_vertex_indices_.push_back(graph_data.vertices_id_[a]);
	// 		// graph_data.edges_vertex_indices_.push_back(graph_data.vertices_id_[b]);
	// 	}
	// }

	// import_incidence_graph_data(m, incidence_graph_data);

	return true;
}

template <typename MESH>
void export_IG(MESH& m, const typename mesh_traits<MESH>::template Attribute<geometry::Vec3>* vertex_position,
			   const std::string& filename)
{
	// static_assert(mesh_traits<MESH>::dimension == 1, "MESH dimension should be 1");

	// using Vertex = typename MESH::Vertex;
	// using Edge = typename MESH::Edge;

	// auto vertex_id = add_attribute<uint32, Vertex>(m, "__vertex_id");

	// uint32 nb_vertices = nb_cells<Vertex>(m);
	// uint32 nb_edges = nb_cells<Edge>(m);

	// std::ofstream out_file;
	// out_file.open(filename);
	// out_file << "# D:3 NV:" << nb_vertices << " NE:" << nb_edges << "\n";

	// uint32 id = 0;
	// // uint32 id = 1;
	// foreach_cell(m, [&](Vertex v) -> bool {
	// 	const geometry::Vec3& pos = value<geometry::Vec3>(m, vertex_position, v);
	// 	value<uint32>(m, vertex_id, v) = id++;
	// 	out_file << "v " << pos[0] << " " << pos[1] << " " << pos[2] << " "
	// 			 << "\n";
	// 	return true;
	// });

	// foreach_cell(m, [&](Edge e) -> bool {
	// 	out_file << "e";
	// 	foreach_incident_vertex(m, e, [&](Vertex v) -> bool {
	// 		out_file << " " << value<uint32>(m, vertex_id, v);
	// 		return true;
	// 	});
	// 	out_file << "\n";
	// 	return true;
	// });

	// remove_attribute<Vertex>(m, vertex_id);

	// out_file.close();
}

} // namespace io

} // namespace cgogn

#endif // CGOGN_IO_INCIDENCE_GRAPH_IG_H_
