/*******************************************************************************
* CGoGN                                                                        *
* Copyright (C) 2019, IGG Group, ICube, University of Strasbourg, France       *
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

#ifndef CGOGN_MODULE_MESH_PROVIDER_MESH_DATA_H_
#define CGOGN_MODULE_MESH_PROVIDER_MESH_DATA_H_

#include <cgogn/core/types/mesh_traits.h>
#include <cgogn/geometry/types/vector_traits.h>

#include <cgogn/core/functions/mesh_info.h>

#include <cgogn/rendering/mesh_render.h>
#include <cgogn/rendering/vbo_update.h>

#include <unordered_map>

namespace cgogn
{

namespace ui
{

template <typename MESH>
struct MeshData
{
    template <typename T>
    using Attribute = typename mesh_traits<MESH>::template Attribute<T>;
    using AttributeGen = typename mesh_traits<MESH>::AttributeGen;

    using Vec3 = geometry::Vec3;

	MeshData() : mesh_(nullptr)
	{}
	MeshData(const MeshData& m) :
		mesh_(m.mesh_),
		nb_cells_(m.nb_cells_)
	{}
	MeshData(const MESH* mesh) : mesh_(mesh)
	{
		update_nb_cells();
	}
	
	void draw(rendering::DrawingType primitive)
	{
		if (!render_.is_primitive_uptodate(primitive))
			render_.init_primitives(*mesh_, primitive);
		render_.draw(primitive);
	}

	void init_primitives(rendering::DrawingType primitive)
	{
		render_.init_primitives(*mesh_, primitive);
	}

	void set_primitives_dirty(rendering::DrawingType primitive)
	{
		render_.set_primitive_dirty(primitive);
	}

private:

	template <class ...T>
	void internal_update_nb_cells(const std::tuple<T...>&)
	{
		nb_cells_ = { cgogn::nb_cells<T>(*mesh_)... };
	}

public:

	void update_nb_cells()
	{
		internal_update_nb_cells(typename mesh_traits<MESH>::Cells{});
	}

	template <typename CELL>
	uint32 nb_cells()
	{
		return nb_cells_[tuple_type_index<CELL, typename mesh_traits<MESH>::Cells>::value];
	}

	void set_bb_attribute(const std::shared_ptr<Attribute<Vec3>>& vertex_attribute)
	{
		bb_attribute_ = vertex_attribute;
		update_bb();
	}

	void update_bb()
	{
		if (!bb_attribute_)
		{
			bb_min_ = { 0, 0, 0 };
			bb_max_ = { 0, 0, 0 };
			return;
		}

		for (uint32 i = 0; i < 3; ++i)
		{
			bb_min_[i] = std::numeric_limits<float64>::max();
			bb_max_[i] = std::numeric_limits<float64>::lowest();
		}
		for (const Vec3& v : *bb_attribute_)
		{
			for (uint32 i = 0; i < 3; ++i)
			{
				if (v[i] < bb_min_[i])
					bb_min_[i] = v[i];
				if (v[i] > bb_max_[i])
					bb_max_[i] = v[i];
			}
		}
	}

	rendering::VBO* vbo(AttributeGen* attribute)
	{
		if (auto it = vbos_.find(attribute); it != vbos_.end())
			return it->second.get();
		else
			return nullptr;
	}

	template <typename T>
	void update_vbo(Attribute<T>* attribute, bool create_if_needed = false)
	{
		rendering::VBO* v = vbo(attribute);
		if (!v && create_if_needed)
		{
			const auto [it, inserted] = vbos_.emplace(attribute, std::make_unique<rendering::VBO>());
			v = it->second.get();
		}
		if (v)
			rendering::update_vbo<T>(attribute, v);
	}

	const MESH* mesh_;
	std::shared_ptr<Attribute<Vec3>> bb_attribute_;
	Vec3 bb_min_, bb_max_;
	std::array<uint32, std::tuple_size<typename mesh_traits<MESH>::Cells>::value> nb_cells_;

private:

	rendering::MeshRender render_;
	std::unordered_map<AttributeGen*, std::unique_ptr<rendering::VBO>> vbos_;
};

} // namespace ui

} // namespace cgogn

#endif // CGOGN_MODULE_MESH_PROVIDER_MESH_DATA_H_