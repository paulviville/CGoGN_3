/*******************************************************************************
* CGoGN: Combinatorial and Geometric modeling with Generic N-dimensional Maps  *
* Copyright (C) 2015, IGG Group, ICube, University of Strasbourg, France       *
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

#ifndef CGOGN_MODELING_ALGOS_DECIMATION_EDGE_APPROXIMATOR_H_
#define CGOGN_MODELING_ALGOS_DECIMATION_EDGE_APPROXIMATOR_H_

#include <cgogn/core/types/mesh_traits.h>
#include <cgogn/geometry/types/vector_traits.h>

#include <cgogn/core/functions/attributes.h>
#include <cgogn/core/functions/traversals/edge.h>

namespace cgogn
{

namespace modeling
{

using Vec3 = geometry::Vec3;
using Scalar = typename geometry::vector_traits<Vec3>::Scalar;

template <typename MESH>
Vec3 mid_edge(const MESH& m, typename mesh_traits<MESH>::template AttributePtr<Vec3> vertex_position, typename mesh_traits<MESH>::Edge e)
{
	auto vertices = incident_vertices(m, e);
	return Scalar(0.5) * (value<Vec3>(m, vertex_position, vertices[0]) + value<Vec3>(m, vertex_position, vertices[1]));
}

} // namespace modeling

} // namespace cgogn

#endif // CGOGN_MODELING_ALGOS_DECIMATION_EDGE_APPROXIMATOR_H_
