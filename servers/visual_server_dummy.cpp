/*************************************************************************/
/*  visual_server_dummy.cpp                                              */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2021 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2021 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "visual_server_dummy.h"

#include "core/method_bind_ext.gen.inc"
#include "core/project_settings.h"
#include "core/os/thread.h"

RID VisualServerDummy::texture_create_from_image(const Ref<Image> &p_image, uint32_t p_flags) {
	return RID();
}

Array VisualServerDummy::_shader_get_param_list_bind(RID p_shader) const {
	Array arr;
	return arr;
}

static Array to_array(const Vector<ObjectID> &ids) {
	Array a;
	return a;
}

Array VisualServerDummy::_instances_cull_aabb_bind(const AABB &p_aabb, RID p_scenario) const {
	Array a;
	return a;
}

Array VisualServerDummy::_instances_cull_ray_bind(const Vector3 &p_from, const Vector3 &p_to, RID p_scenario) const {
	Array a;
	return a;
}

Array VisualServerDummy::_instances_cull_convex_bind(const Array &p_convex, RID p_scenario) const {
	Array a;
	return a;
}

RID VisualServerDummy::get_test_texture() {
	return RID();
}

void VisualServerDummy::_free_internal_rids() {
	// nothing
}

RID VisualServerDummy::_make_test_cube() {
	return RID();
}

RID VisualServerDummy::make_sphere_mesh(int p_lats, int p_lons, float p_radius) {
	return RID();
}

RID VisualServerDummy::get_white_texture() {
	return RID();
}

#define SMALL_VEC2 Vector2(0.00001, 0.00001)
#define SMALL_VEC3 Vector3(0.00001, 0.00001, 0.00001)

Error VisualServerDummy::_surface_set_data(Array p_arrays, uint32_t p_format, uint32_t *p_offsets, uint32_t p_stride, PoolVector<uint8_t> &r_vertex_array, int p_vertex_array_len, PoolVector<uint8_t> &r_index_array, int p_index_array_len, AABB &r_aabb, Vector<AABB> &r_bone_aabb) {
	return OK;
}

uint32_t VisualServerDummy::mesh_surface_get_format_offset(uint32_t p_format, int p_vertex_len, int p_index_len, int p_array_index) const {
	return 0;
}

uint32_t VisualServerDummy::mesh_surface_get_format_stride(uint32_t p_format, int p_vertex_len, int p_index_len) const {
	return 0;
}

uint32_t VisualServerDummy::mesh_surface_make_offsets_from_format(uint32_t p_format, int p_vertex_len, int p_index_len, uint32_t *r_offsets) const {
	return 0;
}

void VisualServerDummy::mesh_add_surface_from_arrays(RID p_mesh, PrimitiveType p_primitive, const Array &p_arrays, const Array &p_blend_shapes, uint32_t p_compress_format) {

}

Array VisualServerDummy::_get_array_from_surface(uint32_t p_format, PoolVector<uint8_t> p_vertex_data, int p_vertex_len, PoolVector<uint8_t> p_index_data, int p_index_len) const {
	Array a;
	return a;
}

Array VisualServerDummy::mesh_surface_get_arrays(RID p_mesh, int p_surface) const {
	Array a;
	return a;
}

Array VisualServerDummy::mesh_surface_get_blend_shape_arrays(RID p_mesh, int p_surface) const {
	Array a;
	return a;
}

Array VisualServerDummy::_mesh_surface_get_skeleton_aabb_bind(RID p_mesh, int p_surface) const {
	Array a;
	return a;
}

void VisualServerDummy::_bind_methods() {

	/*
	ClassDB::bind_method(D_METHOD("force_sync"), &VisualServerDummy::sync);
	ClassDB::bind_method(D_METHOD("force_draw", "swap_buffers", "frame_step"), &VisualServerDummy::draw, DEFVAL(true), DEFVAL(0.0));

	// "draw" and "sync" are deprecated duplicates of "force_draw" and "force_sync"
	// FIXME: Add deprecation messages using GH-4397 once available, and retire
	// once the warnings have been enabled for a full release cycle
	ClassDB::bind_method(D_METHOD("sync"), &VisualServerDummy::sync);
	ClassDB::bind_method(D_METHOD("draw", "swap_buffers", "frame_step"), &VisualServerDummy::draw, DEFVAL(true), DEFVAL(0.0));

	ClassDB::bind_method(D_METHOD("texture_create"), &VisualServerDummy::texture_create);
	ClassDB::bind_method(D_METHOD("texture_create_from_image", "image", "flags"), &VisualServerDummy::texture_create_from_image, DEFVAL(TEXTURE_FLAGS_DEFAULT));
	ClassDB::bind_method(D_METHOD("texture_allocate", "texture", "width", "height", "depth_3d", "format", "type", "flags"), &VisualServerDummy::texture_allocate, DEFVAL(TEXTURE_FLAGS_DEFAULT));
	ClassDB::bind_method(D_METHOD("texture_set_data", "texture", "image", "layer"), &VisualServerDummy::texture_set_data, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("texture_set_data_partial", "texture", "image", "src_x", "src_y", "src_w", "src_h", "dst_x", "dst_y", "dst_mip", "layer"), &VisualServerDummy::texture_set_data_partial, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("texture_get_data", "texture", "cube_side"), &VisualServerDummy::texture_get_data, DEFVAL(CUBEMAP_LEFT));
	ClassDB::bind_method(D_METHOD("texture_set_flags", "texture", "flags"), &VisualServerDummy::texture_set_flags);
	ClassDB::bind_method(D_METHOD("texture_get_flags", "texture"), &VisualServerDummy::texture_get_flags);
	ClassDB::bind_method(D_METHOD("texture_get_format", "texture"), &VisualServerDummy::texture_get_format);
	ClassDB::bind_method(D_METHOD("texture_get_type", "texture"), &VisualServerDummy::texture_get_type);
	ClassDB::bind_method(D_METHOD("texture_get_texid", "texture"), &VisualServerDummy::texture_get_texid);
	ClassDB::bind_method(D_METHOD("texture_get_width", "texture"), &VisualServerDummy::texture_get_width);
	ClassDB::bind_method(D_METHOD("texture_get_height", "texture"), &VisualServerDummy::texture_get_height);
	ClassDB::bind_method(D_METHOD("texture_get_depth", "texture"), &VisualServerDummy::texture_get_depth);
	ClassDB::bind_method(D_METHOD("texture_set_size_override", "texture", "width", "height", "depth"), &VisualServerDummy::texture_set_size_override);
	ClassDB::bind_method(D_METHOD("texture_set_path", "texture", "path"), &VisualServerDummy::texture_set_path);
	ClassDB::bind_method(D_METHOD("texture_get_path", "texture"), &VisualServerDummy::texture_get_path);
	ClassDB::bind_method(D_METHOD("texture_set_shrink_all_x2_on_set_data", "shrink"), &VisualServerDummy::texture_set_shrink_all_x2_on_set_data);
	ClassDB::bind_method(D_METHOD("texture_bind", "texture", "number"), &VisualServerDummy::texture_bind);

	ClassDB::bind_method(D_METHOD("texture_debug_usage"), &VisualServerDummy::_texture_debug_usage_bind);
	ClassDB::bind_method(D_METHOD("textures_keep_original", "enable"), &VisualServerDummy::textures_keep_original);
#ifndef _3D_DISABLED
	ClassDB::bind_method(D_METHOD("sky_create"), &VisualServerDummy::sky_create);
	ClassDB::bind_method(D_METHOD("sky_set_texture", "sky", "cube_map", "radiance_size"), &VisualServerDummy::sky_set_texture);
#endif
	ClassDB::bind_method(D_METHOD("shader_create"), &VisualServerDummy::shader_create);
	ClassDB::bind_method(D_METHOD("shader_set_code", "shader", "code"), &VisualServerDummy::shader_set_code);
	ClassDB::bind_method(D_METHOD("shader_get_code", "shader"), &VisualServerDummy::shader_get_code);
	ClassDB::bind_method(D_METHOD("shader_get_param_list", "shader"), &VisualServerDummy::_shader_get_param_list_bind);
	ClassDB::bind_method(D_METHOD("shader_set_default_texture_param", "shader", "name", "texture"), &VisualServerDummy::shader_set_default_texture_param);
	ClassDB::bind_method(D_METHOD("shader_get_default_texture_param", "shader", "name"), &VisualServerDummy::shader_get_default_texture_param);

	ClassDB::bind_method(D_METHOD("material_create"), &VisualServerDummy::material_create);
	ClassDB::bind_method(D_METHOD("material_set_shader", "shader_material", "shader"), &VisualServerDummy::material_set_shader);
	ClassDB::bind_method(D_METHOD("material_get_shader", "shader_material"), &VisualServerDummy::material_get_shader);
	ClassDB::bind_method(D_METHOD("material_set_param", "material", "parameter", "value"), &VisualServerDummy::material_set_param);
	ClassDB::bind_method(D_METHOD("material_get_param", "material", "parameter"), &VisualServerDummy::material_get_param);
	ClassDB::bind_method(D_METHOD("material_get_param_default", "material", "parameter"), &VisualServerDummy::material_get_param_default);
	ClassDB::bind_method(D_METHOD("material_set_render_priority", "material", "priority"), &VisualServerDummy::material_set_render_priority);
	ClassDB::bind_method(D_METHOD("material_set_line_width", "material", "width"), &VisualServerDummy::material_set_line_width);
	ClassDB::bind_method(D_METHOD("material_set_next_pass", "material", "next_material"), &VisualServerDummy::material_set_next_pass);

	ClassDB::bind_method(D_METHOD("mesh_create"), &VisualServerDummy::mesh_create);
	ClassDB::bind_method(D_METHOD("mesh_surface_get_format_offset", "format", "vertex_len", "index_len", "array_index"), &VisualServerDummy::mesh_surface_get_format_offset);
	ClassDB::bind_method(D_METHOD("mesh_surface_get_format_stride", "format", "vertex_len", "index_len"), &VisualServerDummy::mesh_surface_get_format_stride);
	ClassDB::bind_method(D_METHOD("mesh_add_surface_from_arrays", "mesh", "primitive", "arrays", "blend_shapes", "compress_format"), &VisualServerDummy::mesh_add_surface_from_arrays, DEFVAL(Array()), DEFVAL(ARRAY_COMPRESS_DEFAULT));
	ClassDB::bind_method(D_METHOD("mesh_set_blend_shape_count", "mesh", "amount"), &VisualServerDummy::mesh_set_blend_shape_count);
	ClassDB::bind_method(D_METHOD("mesh_get_blend_shape_count", "mesh"), &VisualServerDummy::mesh_get_blend_shape_count);
	ClassDB::bind_method(D_METHOD("mesh_set_blend_shape_mode", "mesh", "mode"), &VisualServerDummy::mesh_set_blend_shape_mode);
	ClassDB::bind_method(D_METHOD("mesh_get_blend_shape_mode", "mesh"), &VisualServerDummy::mesh_get_blend_shape_mode);
	ClassDB::bind_method(D_METHOD("mesh_surface_update_region", "mesh", "surface", "offset", "data"), &VisualServerDummy::mesh_surface_update_region);
	ClassDB::bind_method(D_METHOD("mesh_surface_set_material", "mesh", "surface", "material"), &VisualServerDummy::mesh_surface_set_material);
	ClassDB::bind_method(D_METHOD("mesh_surface_get_material", "mesh", "surface"), &VisualServerDummy::mesh_surface_get_material);
	ClassDB::bind_method(D_METHOD("mesh_surface_get_array_len", "mesh", "surface"), &VisualServerDummy::mesh_surface_get_array_len);
	ClassDB::bind_method(D_METHOD("mesh_surface_get_array_index_len", "mesh", "surface"), &VisualServerDummy::mesh_surface_get_array_index_len);
	ClassDB::bind_method(D_METHOD("mesh_surface_get_array", "mesh", "surface"), &VisualServerDummy::mesh_surface_get_array);
	ClassDB::bind_method(D_METHOD("mesh_surface_get_index_array", "mesh", "surface"), &VisualServerDummy::mesh_surface_get_index_array);
	ClassDB::bind_method(D_METHOD("mesh_surface_get_arrays", "mesh", "surface"), &VisualServerDummy::mesh_surface_get_arrays);
	ClassDB::bind_method(D_METHOD("mesh_surface_get_blend_shape_arrays", "mesh", "surface"), &VisualServerDummy::mesh_surface_get_blend_shape_arrays);
	ClassDB::bind_method(D_METHOD("mesh_surface_get_format", "mesh", "surface"), &VisualServerDummy::mesh_surface_get_format);
	ClassDB::bind_method(D_METHOD("mesh_surface_get_primitive_type", "mesh", "surface"), &VisualServerDummy::mesh_surface_get_primitive_type);
	ClassDB::bind_method(D_METHOD("mesh_surface_get_aabb", "mesh", "surface"), &VisualServerDummy::mesh_surface_get_aabb);
	ClassDB::bind_method(D_METHOD("mesh_surface_get_skeleton_aabb", "mesh", "surface"), &VisualServerDummy::_mesh_surface_get_skeleton_aabb_bind);
	ClassDB::bind_method(D_METHOD("mesh_remove_surface", "mesh", "index"), &VisualServerDummy::mesh_remove_surface);
	ClassDB::bind_method(D_METHOD("mesh_get_surface_count", "mesh"), &VisualServerDummy::mesh_get_surface_count);
	ClassDB::bind_method(D_METHOD("mesh_set_custom_aabb", "mesh", "aabb"), &VisualServerDummy::mesh_set_custom_aabb);
	ClassDB::bind_method(D_METHOD("mesh_get_custom_aabb", "mesh"), &VisualServerDummy::mesh_get_custom_aabb);
	ClassDB::bind_method(D_METHOD("mesh_clear", "mesh"), &VisualServerDummy::mesh_clear);

	ClassDB::bind_method(D_METHOD("multimesh_create"), &VisualServerDummy::multimesh_create);
	ClassDB::bind_method(D_METHOD("multimesh_allocate", "multimesh", "instances", "transform_format", "color_format", "custom_data_format"), &VisualServerDummy::multimesh_allocate, DEFVAL(MULTIMESH_CUSTOM_DATA_NONE));
	ClassDB::bind_method(D_METHOD("multimesh_get_instance_count", "multimesh"), &VisualServerDummy::multimesh_get_instance_count);
	ClassDB::bind_method(D_METHOD("multimesh_set_mesh", "multimesh", "mesh"), &VisualServerDummy::multimesh_set_mesh);
	ClassDB::bind_method(D_METHOD("multimesh_instance_set_transform", "multimesh", "index", "transform"), &VisualServerDummy::multimesh_instance_set_transform);
	ClassDB::bind_method(D_METHOD("multimesh_instance_set_transform_2d", "multimesh", "index", "transform"), &VisualServerDummy::multimesh_instance_set_transform_2d);
	ClassDB::bind_method(D_METHOD("multimesh_instance_set_color", "multimesh", "index", "color"), &VisualServerDummy::multimesh_instance_set_color);
	ClassDB::bind_method(D_METHOD("multimesh_instance_set_custom_data", "multimesh", "index", "custom_data"), &VisualServerDummy::multimesh_instance_set_custom_data);
	ClassDB::bind_method(D_METHOD("multimesh_get_mesh", "multimesh"), &VisualServerDummy::multimesh_get_mesh);
	ClassDB::bind_method(D_METHOD("multimesh_get_aabb", "multimesh"), &VisualServerDummy::multimesh_get_aabb);
	ClassDB::bind_method(D_METHOD("multimesh_instance_get_transform", "multimesh", "index"), &VisualServerDummy::multimesh_instance_get_transform);
	ClassDB::bind_method(D_METHOD("multimesh_instance_get_transform_2d", "multimesh", "index"), &VisualServerDummy::multimesh_instance_get_transform_2d);
	ClassDB::bind_method(D_METHOD("multimesh_instance_get_color", "multimesh", "index"), &VisualServerDummy::multimesh_instance_get_color);
	ClassDB::bind_method(D_METHOD("multimesh_instance_get_custom_data", "multimesh", "index"), &VisualServerDummy::multimesh_instance_get_custom_data);
	ClassDB::bind_method(D_METHOD("multimesh_set_visible_instances", "multimesh", "visible"), &VisualServerDummy::multimesh_set_visible_instances);
	ClassDB::bind_method(D_METHOD("multimesh_get_visible_instances", "multimesh"), &VisualServerDummy::multimesh_get_visible_instances);
	ClassDB::bind_method(D_METHOD("multimesh_set_as_bulk_array", "multimesh", "array"), &VisualServerDummy::multimesh_set_as_bulk_array);
#ifndef _3D_DISABLED
	ClassDB::bind_method(D_METHOD("immediate_create"), &VisualServerDummy::immediate_create);
	ClassDB::bind_method(D_METHOD("immediate_begin", "immediate", "primitive", "texture"), &VisualServerDummy::immediate_begin, DEFVAL(RID()));
	ClassDB::bind_method(D_METHOD("immediate_vertex", "immediate", "vertex"), &VisualServerDummy::immediate_vertex);
	ClassDB::bind_method(D_METHOD("immediate_vertex_2d", "immediate", "vertex"), &VisualServerDummy::immediate_vertex_2d);
	ClassDB::bind_method(D_METHOD("immediate_normal", "immediate", "normal"), &VisualServerDummy::immediate_normal);
	ClassDB::bind_method(D_METHOD("immediate_tangent", "immediate", "tangent"), &VisualServerDummy::immediate_tangent);
	ClassDB::bind_method(D_METHOD("immediate_color", "immediate", "color"), &VisualServerDummy::immediate_color);
	ClassDB::bind_method(D_METHOD("immediate_uv", "immediate", "tex_uv"), &VisualServerDummy::immediate_uv);
	ClassDB::bind_method(D_METHOD("immediate_uv2", "immediate", "tex_uv"), &VisualServerDummy::immediate_uv2);
	ClassDB::bind_method(D_METHOD("immediate_end", "immediate"), &VisualServerDummy::immediate_end);
	ClassDB::bind_method(D_METHOD("immediate_clear", "immediate"), &VisualServerDummy::immediate_clear);
	ClassDB::bind_method(D_METHOD("immediate_set_material", "immediate", "material"), &VisualServerDummy::immediate_set_material);
	ClassDB::bind_method(D_METHOD("immediate_get_material", "immediate"), &VisualServerDummy::immediate_get_material);
#endif

	ClassDB::bind_method(D_METHOD("skeleton_create"), &VisualServerDummy::skeleton_create);
	ClassDB::bind_method(D_METHOD("skeleton_allocate", "skeleton", "bones", "is_2d_skeleton"), &VisualServerDummy::skeleton_allocate, DEFVAL(false));
	ClassDB::bind_method(D_METHOD("skeleton_get_bone_count", "skeleton"), &VisualServerDummy::skeleton_get_bone_count);
	ClassDB::bind_method(D_METHOD("skeleton_bone_set_transform", "skeleton", "bone", "transform"), &VisualServerDummy::skeleton_bone_set_transform);
	ClassDB::bind_method(D_METHOD("skeleton_bone_get_transform", "skeleton", "bone"), &VisualServerDummy::skeleton_bone_get_transform);
	ClassDB::bind_method(D_METHOD("skeleton_bone_set_transform_2d", "skeleton", "bone", "transform"), &VisualServerDummy::skeleton_bone_set_transform_2d);
	ClassDB::bind_method(D_METHOD("skeleton_bone_get_transform_2d", "skeleton", "bone"), &VisualServerDummy::skeleton_bone_get_transform_2d);

#ifndef _3D_DISABLED
	ClassDB::bind_method(D_METHOD("directional_light_create"), &VisualServerDummy::directional_light_create);
	ClassDB::bind_method(D_METHOD("omni_light_create"), &VisualServerDummy::omni_light_create);
	ClassDB::bind_method(D_METHOD("spot_light_create"), &VisualServerDummy::spot_light_create);

	ClassDB::bind_method(D_METHOD("light_set_color", "light", "color"), &VisualServerDummy::light_set_color);
	ClassDB::bind_method(D_METHOD("light_set_param", "light", "param", "value"), &VisualServerDummy::light_set_param);
	ClassDB::bind_method(D_METHOD("light_set_shadow", "light", "enabled"), &VisualServerDummy::light_set_shadow);
	ClassDB::bind_method(D_METHOD("light_set_shadow_color", "light", "color"), &VisualServerDummy::light_set_shadow_color);
	ClassDB::bind_method(D_METHOD("light_set_projector", "light", "texture"), &VisualServerDummy::light_set_projector);
	ClassDB::bind_method(D_METHOD("light_set_negative", "light", "enable"), &VisualServerDummy::light_set_negative);
	ClassDB::bind_method(D_METHOD("light_set_cull_mask", "light", "mask"), &VisualServerDummy::light_set_cull_mask);
	ClassDB::bind_method(D_METHOD("light_set_reverse_cull_face_mode", "light", "enabled"), &VisualServerDummy::light_set_reverse_cull_face_mode);
	ClassDB::bind_method(D_METHOD("light_set_use_gi", "light", "enabled"), &VisualServerDummy::light_set_use_gi);
	ClassDB::bind_method(D_METHOD("light_set_bake_mode", "light", "bake_mode"), &VisualServerDummy::light_set_bake_mode);

	ClassDB::bind_method(D_METHOD("light_omni_set_shadow_mode", "light", "mode"), &VisualServerDummy::light_omni_set_shadow_mode);
	ClassDB::bind_method(D_METHOD("light_omni_set_shadow_detail", "light", "detail"), &VisualServerDummy::light_omni_set_shadow_detail);

	ClassDB::bind_method(D_METHOD("light_directional_set_shadow_mode", "light", "mode"), &VisualServerDummy::light_directional_set_shadow_mode);
	ClassDB::bind_method(D_METHOD("light_directional_set_blend_splits", "light", "enable"), &VisualServerDummy::light_directional_set_blend_splits);
	ClassDB::bind_method(D_METHOD("light_directional_set_shadow_depth_range_mode", "light", "range_mode"), &VisualServerDummy::light_directional_set_shadow_depth_range_mode);

	ClassDB::bind_method(D_METHOD("reflection_probe_create"), &VisualServerDummy::reflection_probe_create);
	ClassDB::bind_method(D_METHOD("reflection_probe_set_update_mode", "probe", "mode"), &VisualServerDummy::reflection_probe_set_update_mode);
	ClassDB::bind_method(D_METHOD("reflection_probe_set_intensity", "probe", "intensity"), &VisualServerDummy::reflection_probe_set_intensity);
	ClassDB::bind_method(D_METHOD("reflection_probe_set_interior_ambient", "probe", "color"), &VisualServerDummy::reflection_probe_set_interior_ambient);
	ClassDB::bind_method(D_METHOD("reflection_probe_set_interior_ambient_energy", "probe", "energy"), &VisualServerDummy::reflection_probe_set_interior_ambient_energy);
	ClassDB::bind_method(D_METHOD("reflection_probe_set_interior_ambient_probe_contribution", "probe", "contrib"), &VisualServerDummy::reflection_probe_set_interior_ambient_probe_contribution);
	ClassDB::bind_method(D_METHOD("reflection_probe_set_max_distance", "probe", "distance"), &VisualServerDummy::reflection_probe_set_max_distance);
	ClassDB::bind_method(D_METHOD("reflection_probe_set_extents", "probe", "extents"), &VisualServerDummy::reflection_probe_set_extents);
	ClassDB::bind_method(D_METHOD("reflection_probe_set_origin_offset", "probe", "offset"), &VisualServerDummy::reflection_probe_set_origin_offset);
	ClassDB::bind_method(D_METHOD("reflection_probe_set_as_interior", "probe", "enable"), &VisualServerDummy::reflection_probe_set_as_interior);
	ClassDB::bind_method(D_METHOD("reflection_probe_set_enable_box_projection", "probe", "enable"), &VisualServerDummy::reflection_probe_set_enable_box_projection);
	ClassDB::bind_method(D_METHOD("reflection_probe_set_enable_shadows", "probe", "enable"), &VisualServerDummy::reflection_probe_set_enable_shadows);
	ClassDB::bind_method(D_METHOD("reflection_probe_set_cull_mask", "probe", "layers"), &VisualServerDummy::reflection_probe_set_cull_mask);

	ClassDB::bind_method(D_METHOD("gi_probe_create"), &VisualServerDummy::gi_probe_create);
	ClassDB::bind_method(D_METHOD("gi_probe_set_bounds", "probe", "bounds"), &VisualServerDummy::gi_probe_set_bounds);
	ClassDB::bind_method(D_METHOD("gi_probe_get_bounds", "probe"), &VisualServerDummy::gi_probe_get_bounds);
	ClassDB::bind_method(D_METHOD("gi_probe_set_cell_size", "probe", "range"), &VisualServerDummy::gi_probe_set_cell_size);
	ClassDB::bind_method(D_METHOD("gi_probe_get_cell_size", "probe"), &VisualServerDummy::gi_probe_get_cell_size);
	ClassDB::bind_method(D_METHOD("gi_probe_set_to_cell_xform", "probe", "xform"), &VisualServerDummy::gi_probe_set_to_cell_xform);
	ClassDB::bind_method(D_METHOD("gi_probe_get_to_cell_xform", "probe"), &VisualServerDummy::gi_probe_get_to_cell_xform);
	ClassDB::bind_method(D_METHOD("gi_probe_set_dynamic_data", "probe", "data"), &VisualServerDummy::gi_probe_set_dynamic_data);
	ClassDB::bind_method(D_METHOD("gi_probe_get_dynamic_data", "probe"), &VisualServerDummy::gi_probe_get_dynamic_data);
	ClassDB::bind_method(D_METHOD("gi_probe_set_dynamic_range", "probe", "range"), &VisualServerDummy::gi_probe_set_dynamic_range);
	ClassDB::bind_method(D_METHOD("gi_probe_get_dynamic_range", "probe"), &VisualServerDummy::gi_probe_get_dynamic_range);
	ClassDB::bind_method(D_METHOD("gi_probe_set_energy", "probe", "energy"), &VisualServerDummy::gi_probe_set_energy);
	ClassDB::bind_method(D_METHOD("gi_probe_get_energy", "probe"), &VisualServerDummy::gi_probe_get_energy);
	ClassDB::bind_method(D_METHOD("gi_probe_set_bias", "probe", "bias"), &VisualServerDummy::gi_probe_set_bias);
	ClassDB::bind_method(D_METHOD("gi_probe_get_bias", "probe"), &VisualServerDummy::gi_probe_get_bias);
	ClassDB::bind_method(D_METHOD("gi_probe_set_normal_bias", "probe", "bias"), &VisualServerDummy::gi_probe_set_normal_bias);
	ClassDB::bind_method(D_METHOD("gi_probe_get_normal_bias", "probe"), &VisualServerDummy::gi_probe_get_normal_bias);
	ClassDB::bind_method(D_METHOD("gi_probe_set_propagation", "probe", "propagation"), &VisualServerDummy::gi_probe_set_propagation);
	ClassDB::bind_method(D_METHOD("gi_probe_get_propagation", "probe"), &VisualServerDummy::gi_probe_get_propagation);
	ClassDB::bind_method(D_METHOD("gi_probe_set_interior", "probe", "enable"), &VisualServerDummy::gi_probe_set_interior);
	ClassDB::bind_method(D_METHOD("gi_probe_is_interior", "probe"), &VisualServerDummy::gi_probe_is_interior);
	ClassDB::bind_method(D_METHOD("gi_probe_set_compress", "probe", "enable"), &VisualServerDummy::gi_probe_set_compress);
	ClassDB::bind_method(D_METHOD("gi_probe_is_compressed", "probe"), &VisualServerDummy::gi_probe_is_compressed);

	ClassDB::bind_method(D_METHOD("lightmap_capture_create"), &VisualServerDummy::lightmap_capture_create);
	ClassDB::bind_method(D_METHOD("lightmap_capture_set_bounds", "capture", "bounds"), &VisualServerDummy::lightmap_capture_set_bounds);
	ClassDB::bind_method(D_METHOD("lightmap_capture_get_bounds", "capture"), &VisualServerDummy::lightmap_capture_get_bounds);
	ClassDB::bind_method(D_METHOD("lightmap_capture_set_octree", "capture", "octree"), &VisualServerDummy::lightmap_capture_set_octree);
	ClassDB::bind_method(D_METHOD("lightmap_capture_set_octree_cell_transform", "capture", "xform"), &VisualServerDummy::lightmap_capture_set_octree_cell_transform);
	ClassDB::bind_method(D_METHOD("lightmap_capture_get_octree_cell_transform", "capture"), &VisualServerDummy::lightmap_capture_get_octree_cell_transform);
	ClassDB::bind_method(D_METHOD("lightmap_capture_set_octree_cell_subdiv", "capture", "subdiv"), &VisualServerDummy::lightmap_capture_set_octree_cell_subdiv);
	ClassDB::bind_method(D_METHOD("lightmap_capture_get_octree_cell_subdiv", "capture"), &VisualServerDummy::lightmap_capture_get_octree_cell_subdiv);
	ClassDB::bind_method(D_METHOD("lightmap_capture_get_octree", "capture"), &VisualServerDummy::lightmap_capture_get_octree);
	ClassDB::bind_method(D_METHOD("lightmap_capture_set_energy", "capture", "energy"), &VisualServerDummy::lightmap_capture_set_energy);
	ClassDB::bind_method(D_METHOD("lightmap_capture_get_energy", "capture"), &VisualServerDummy::lightmap_capture_get_energy);
	ClassDB::bind_method(D_METHOD("lightmap_capture_set_interior", "capture", "interior"), &VisualServerDummy::lightmap_capture_set_interior);
	ClassDB::bind_method(D_METHOD("lightmap_capture_is_interior", "capture"), &VisualServerDummy::lightmap_capture_is_interior);
#endif
	ClassDB::bind_method(D_METHOD("particles_create"), &VisualServerDummy::particles_create);
	ClassDB::bind_method(D_METHOD("particles_set_emitting", "particles", "emitting"), &VisualServerDummy::particles_set_emitting);
	ClassDB::bind_method(D_METHOD("particles_get_emitting", "particles"), &VisualServerDummy::particles_get_emitting);
	ClassDB::bind_method(D_METHOD("particles_set_amount", "particles", "amount"), &VisualServerDummy::particles_set_amount);
	ClassDB::bind_method(D_METHOD("particles_set_lifetime", "particles", "lifetime"), &VisualServerDummy::particles_set_lifetime);
	ClassDB::bind_method(D_METHOD("particles_set_one_shot", "particles", "one_shot"), &VisualServerDummy::particles_set_one_shot);
	ClassDB::bind_method(D_METHOD("particles_set_pre_process_time", "particles", "time"), &VisualServerDummy::particles_set_pre_process_time);
	ClassDB::bind_method(D_METHOD("particles_set_explosiveness_ratio", "particles", "ratio"), &VisualServerDummy::particles_set_explosiveness_ratio);
	ClassDB::bind_method(D_METHOD("particles_set_randomness_ratio", "particles", "ratio"), &VisualServerDummy::particles_set_randomness_ratio);
	ClassDB::bind_method(D_METHOD("particles_set_custom_aabb", "particles", "aabb"), &VisualServerDummy::particles_set_custom_aabb);
	ClassDB::bind_method(D_METHOD("particles_set_speed_scale", "particles", "scale"), &VisualServerDummy::particles_set_speed_scale);
	ClassDB::bind_method(D_METHOD("particles_set_use_local_coordinates", "particles", "enable"), &VisualServerDummy::particles_set_use_local_coordinates);
	ClassDB::bind_method(D_METHOD("particles_set_process_material", "particles", "material"), &VisualServerDummy::particles_set_process_material);
	ClassDB::bind_method(D_METHOD("particles_set_fixed_fps", "particles", "fps"), &VisualServerDummy::particles_set_fixed_fps);
	ClassDB::bind_method(D_METHOD("particles_set_fractional_delta", "particles", "enable"), &VisualServerDummy::particles_set_fractional_delta);
	ClassDB::bind_method(D_METHOD("particles_is_inactive", "particles"), &VisualServerDummy::particles_is_inactive);
	ClassDB::bind_method(D_METHOD("particles_request_process", "particles"), &VisualServerDummy::particles_request_process);
	ClassDB::bind_method(D_METHOD("particles_restart", "particles"), &VisualServerDummy::particles_restart);
	ClassDB::bind_method(D_METHOD("particles_set_draw_order", "particles", "order"), &VisualServerDummy::particles_set_draw_order);
	ClassDB::bind_method(D_METHOD("particles_set_draw_passes", "particles", "count"), &VisualServerDummy::particles_set_draw_passes);
	ClassDB::bind_method(D_METHOD("particles_set_draw_pass_mesh", "particles", "pass", "mesh"), &VisualServerDummy::particles_set_draw_pass_mesh);
	ClassDB::bind_method(D_METHOD("particles_get_current_aabb", "particles"), &VisualServerDummy::particles_get_current_aabb);
	ClassDB::bind_method(D_METHOD("particles_set_emission_transform", "particles", "transform"), &VisualServerDummy::particles_set_emission_transform);

	ClassDB::bind_method(D_METHOD("camera_create"), &VisualServerDummy::camera_create);
	ClassDB::bind_method(D_METHOD("camera_set_perspective", "camera", "fovy_degrees", "z_near", "z_far"), &VisualServerDummy::camera_set_perspective);
	ClassDB::bind_method(D_METHOD("camera_set_orthogonal", "camera", "size", "z_near", "z_far"), &VisualServerDummy::camera_set_orthogonal);
	ClassDB::bind_method(D_METHOD("camera_set_frustum", "camera", "size", "offset", "z_near", "z_far"), &VisualServerDummy::camera_set_frustum);
	ClassDB::bind_method(D_METHOD("camera_set_transform", "camera", "transform"), &VisualServerDummy::camera_set_transform);
	ClassDB::bind_method(D_METHOD("camera_set_cull_mask", "camera", "layers"), &VisualServerDummy::camera_set_cull_mask);
	ClassDB::bind_method(D_METHOD("camera_set_environment", "camera", "env"), &VisualServerDummy::camera_set_environment);
	ClassDB::bind_method(D_METHOD("camera_set_use_vertical_aspect", "camera", "enable"), &VisualServerDummy::camera_set_use_vertical_aspect);

	ClassDB::bind_method(D_METHOD("viewport_create"), &VisualServerDummy::viewport_create);
	ClassDB::bind_method(D_METHOD("viewport_set_use_arvr", "viewport", "use_arvr"), &VisualServerDummy::viewport_set_use_arvr);
	ClassDB::bind_method(D_METHOD("viewport_set_size", "viewport", "width", "height"), &VisualServerDummy::viewport_set_size);
	ClassDB::bind_method(D_METHOD("viewport_set_active", "viewport", "active"), &VisualServerDummy::viewport_set_active);
	ClassDB::bind_method(D_METHOD("viewport_set_parent_viewport", "viewport", "parent_viewport"), &VisualServerDummy::viewport_set_parent_viewport);
	ClassDB::bind_method(D_METHOD("viewport_attach_to_screen", "viewport", "rect", "screen"), &VisualServerDummy::viewport_attach_to_screen, DEFVAL(Rect2()), DEFVAL(0));
	ClassDB::bind_method(D_METHOD("viewport_set_render_direct_to_screen", "viewport", "enabled"), &VisualServerDummy::viewport_set_render_direct_to_screen);
	ClassDB::bind_method(D_METHOD("viewport_detach", "viewport"), &VisualServerDummy::viewport_detach);
	ClassDB::bind_method(D_METHOD("viewport_set_update_mode", "viewport", "update_mode"), &VisualServerDummy::viewport_set_update_mode);
	ClassDB::bind_method(D_METHOD("viewport_set_vflip", "viewport", "enabled"), &VisualServerDummy::viewport_set_vflip);
	ClassDB::bind_method(D_METHOD("viewport_set_clear_mode", "viewport", "clear_mode"), &VisualServerDummy::viewport_set_clear_mode);
	ClassDB::bind_method(D_METHOD("viewport_get_texture", "viewport"), &VisualServerDummy::viewport_get_texture);
	ClassDB::bind_method(D_METHOD("viewport_set_hide_scenario", "viewport", "hidden"), &VisualServerDummy::viewport_set_hide_scenario);
	ClassDB::bind_method(D_METHOD("viewport_set_hide_canvas", "viewport", "hidden"), &VisualServerDummy::viewport_set_hide_canvas);
	ClassDB::bind_method(D_METHOD("viewport_set_disable_environment", "viewport", "disabled"), &VisualServerDummy::viewport_set_disable_environment);
	ClassDB::bind_method(D_METHOD("viewport_set_disable_3d", "viewport", "disabled"), &VisualServerDummy::viewport_set_disable_3d);
	ClassDB::bind_method(D_METHOD("viewport_attach_camera", "viewport", "camera"), &VisualServerDummy::viewport_attach_camera);
	ClassDB::bind_method(D_METHOD("viewport_set_scenario", "viewport", "scenario"), &VisualServerDummy::viewport_set_scenario);
	ClassDB::bind_method(D_METHOD("viewport_attach_canvas", "viewport", "canvas"), &VisualServerDummy::viewport_attach_canvas);
	ClassDB::bind_method(D_METHOD("viewport_remove_canvas", "viewport", "canvas"), &VisualServerDummy::viewport_remove_canvas);
	ClassDB::bind_method(D_METHOD("viewport_set_canvas_transform", "viewport", "canvas", "offset"), &VisualServerDummy::viewport_set_canvas_transform);
	ClassDB::bind_method(D_METHOD("viewport_set_transparent_background", "viewport", "enabled"), &VisualServerDummy::viewport_set_transparent_background);
	ClassDB::bind_method(D_METHOD("viewport_set_global_canvas_transform", "viewport", "transform"), &VisualServerDummy::viewport_set_global_canvas_transform);
	ClassDB::bind_method(D_METHOD("viewport_set_canvas_stacking", "viewport", "canvas", "layer", "sublayer"), &VisualServerDummy::viewport_set_canvas_stacking);
	ClassDB::bind_method(D_METHOD("viewport_set_shadow_atlas_size", "viewport", "size"), &VisualServerDummy::viewport_set_shadow_atlas_size);
	ClassDB::bind_method(D_METHOD("viewport_set_shadow_atlas_quadrant_subdivision", "viewport", "quadrant", "subdivision"), &VisualServerDummy::viewport_set_shadow_atlas_quadrant_subdivision);
	ClassDB::bind_method(D_METHOD("viewport_set_msaa", "viewport", "msaa"), &VisualServerDummy::viewport_set_msaa);
	ClassDB::bind_method(D_METHOD("viewport_set_use_fxaa", "viewport", "fxaa"), &VisualServerDummy::viewport_set_use_fxaa);
	ClassDB::bind_method(D_METHOD("viewport_set_use_debanding", "viewport", "debanding"), &VisualServerDummy::viewport_set_use_debanding);
	ClassDB::bind_method(D_METHOD("viewport_set_hdr", "viewport", "enabled"), &VisualServerDummy::viewport_set_hdr);
	ClassDB::bind_method(D_METHOD("viewport_set_usage", "viewport", "usage"), &VisualServerDummy::viewport_set_usage);
	ClassDB::bind_method(D_METHOD("viewport_get_render_info", "viewport", "info"), &VisualServerDummy::viewport_get_render_info);
	ClassDB::bind_method(D_METHOD("viewport_set_debug_draw", "viewport", "draw"), &VisualServerDummy::viewport_set_debug_draw);

	ClassDB::bind_method(D_METHOD("environment_create"), &VisualServerDummy::environment_create);
	ClassDB::bind_method(D_METHOD("environment_set_background", "env", "bg"), &VisualServerDummy::environment_set_background);
	ClassDB::bind_method(D_METHOD("environment_set_sky", "env", "sky"), &VisualServerDummy::environment_set_sky);
	ClassDB::bind_method(D_METHOD("environment_set_sky_custom_fov", "env", "scale"), &VisualServerDummy::environment_set_sky_custom_fov);
	ClassDB::bind_method(D_METHOD("environment_set_sky_orientation", "env", "orientation"), &VisualServerDummy::environment_set_sky_orientation);
	ClassDB::bind_method(D_METHOD("environment_set_bg_color", "env", "color"), &VisualServerDummy::environment_set_bg_color);
	ClassDB::bind_method(D_METHOD("environment_set_bg_energy", "env", "energy"), &VisualServerDummy::environment_set_bg_energy);
	ClassDB::bind_method(D_METHOD("environment_set_canvas_max_layer", "env", "max_layer"), &VisualServerDummy::environment_set_canvas_max_layer);
	ClassDB::bind_method(D_METHOD("environment_set_ambient_light", "env", "color", "energy", "sky_contibution"), &VisualServerDummy::environment_set_ambient_light, DEFVAL(1.0), DEFVAL(0.0));
	ClassDB::bind_method(D_METHOD("environment_set_dof_blur_near", "env", "enable", "distance", "transition", "far_amount", "quality"), &VisualServerDummy::environment_set_dof_blur_near);
	ClassDB::bind_method(D_METHOD("environment_set_dof_blur_far", "env", "enable", "distance", "transition", "far_amount", "quality"), &VisualServerDummy::environment_set_dof_blur_far);
	ClassDB::bind_method(D_METHOD("environment_set_glow", "env", "enable", "level_flags", "intensity", "strength", "bloom_threshold", "blend_mode", "hdr_bleed_threshold", "hdr_bleed_scale", "hdr_luminance_cap", "bicubic_upscale"), &VisualServerDummy::environment_set_glow);
	ClassDB::bind_method(D_METHOD("environment_set_tonemap", "env", "tone_mapper", "exposure", "white", "auto_exposure", "min_luminance", "max_luminance", "auto_exp_speed", "auto_exp_grey"), &VisualServerDummy::environment_set_tonemap);
	ClassDB::bind_method(D_METHOD("environment_set_adjustment", "env", "enable", "brightness", "contrast", "saturation", "ramp"), &VisualServerDummy::environment_set_adjustment);
	ClassDB::bind_method(D_METHOD("environment_set_ssr", "env", "enable", "max_steps", "fade_in", "fade_out", "depth_tolerance", "roughness"), &VisualServerDummy::environment_set_ssr);
	ClassDB::bind_method(D_METHOD("environment_set_ssao", "env", "enable", "radius", "intensity", "radius2", "intensity2", "bias", "light_affect", "ao_channel_affect", "color", "quality", "blur", "bilateral_sharpness"), &VisualServerDummy::environment_set_ssao);
	ClassDB::bind_method(D_METHOD("environment_set_fog", "env", "enable", "color", "sun_color", "sun_amount"), &VisualServerDummy::environment_set_fog);

	ClassDB::bind_method(D_METHOD("environment_set_fog_depth", "env", "enable", "depth_begin", "depth_end", "depth_curve", "transmit", "transmit_curve"), &VisualServerDummy::environment_set_fog_depth);

	ClassDB::bind_method(D_METHOD("environment_set_fog_height", "env", "enable", "min_height", "max_height", "height_curve"), &VisualServerDummy::environment_set_fog_height);

	ClassDB::bind_method(D_METHOD("scenario_create"), &VisualServerDummy::scenario_create);
	ClassDB::bind_method(D_METHOD("scenario_set_debug", "scenario", "debug_mode"), &VisualServerDummy::scenario_set_debug);
	ClassDB::bind_method(D_METHOD("scenario_set_environment", "scenario", "environment"), &VisualServerDummy::scenario_set_environment);
	ClassDB::bind_method(D_METHOD("scenario_set_reflection_atlas_size", "scenario", "size", "subdiv"), &VisualServerDummy::scenario_set_reflection_atlas_size);
	ClassDB::bind_method(D_METHOD("scenario_set_fallback_environment", "scenario", "environment"), &VisualServerDummy::scenario_set_fallback_environment);

#ifndef _3D_DISABLED

	ClassDB::bind_method(D_METHOD("instance_create2", "base", "scenario"), &VisualServerDummy::instance_create2);
	ClassDB::bind_method(D_METHOD("instance_create"), &VisualServerDummy::instance_create);
	ClassDB::bind_method(D_METHOD("instance_set_base", "instance", "base"), &VisualServerDummy::instance_set_base);
	ClassDB::bind_method(D_METHOD("instance_set_scenario", "instance", "scenario"), &VisualServerDummy::instance_set_scenario);
	ClassDB::bind_method(D_METHOD("instance_set_layer_mask", "instance", "mask"), &VisualServerDummy::instance_set_layer_mask);
	ClassDB::bind_method(D_METHOD("instance_set_transform", "instance", "transform"), &VisualServerDummy::instance_set_transform);
	ClassDB::bind_method(D_METHOD("instance_attach_object_instance_id", "instance", "id"), &VisualServerDummy::instance_attach_object_instance_id);
	ClassDB::bind_method(D_METHOD("instance_set_blend_shape_weight", "instance", "shape", "weight"), &VisualServerDummy::instance_set_blend_shape_weight);
	ClassDB::bind_method(D_METHOD("instance_set_surface_material", "instance", "surface", "material"), &VisualServerDummy::instance_set_surface_material);
	ClassDB::bind_method(D_METHOD("instance_set_visible", "instance", "visible"), &VisualServerDummy::instance_set_visible);
	ClassDB::bind_method(D_METHOD("instance_set_use_lightmap", "instance", "lightmap_instance", "lightmap", "lightmap_slice", "lightmap_uv_rect"), &VisualServerDummy::instance_set_use_lightmap, DEFVAL(-1), DEFVAL(Rect2(0, 0, 1, 1)));
	ClassDB::bind_method(D_METHOD("instance_set_custom_aabb", "instance", "aabb"), &VisualServerDummy::instance_set_custom_aabb);
	ClassDB::bind_method(D_METHOD("instance_attach_skeleton", "instance", "skeleton"), &VisualServerDummy::instance_attach_skeleton);
	ClassDB::bind_method(D_METHOD("instance_set_exterior", "instance", "enabled"), &VisualServerDummy::instance_set_exterior);
	ClassDB::bind_method(D_METHOD("instance_set_extra_visibility_margin", "instance", "margin"), &VisualServerDummy::instance_set_extra_visibility_margin);
	ClassDB::bind_method(D_METHOD("instance_geometry_set_flag", "instance", "flag", "enabled"), &VisualServerDummy::instance_geometry_set_flag);
	ClassDB::bind_method(D_METHOD("instance_geometry_set_cast_shadows_setting", "instance", "shadow_casting_setting"), &VisualServerDummy::instance_geometry_set_cast_shadows_setting);
	ClassDB::bind_method(D_METHOD("instance_geometry_set_material_override", "instance", "material"), &VisualServerDummy::instance_geometry_set_material_override);
	ClassDB::bind_method(D_METHOD("instance_geometry_set_draw_range", "instance", "min", "max", "min_margin", "max_margin"), &VisualServerDummy::instance_geometry_set_draw_range);
	ClassDB::bind_method(D_METHOD("instance_geometry_set_as_instance_lod", "instance", "as_lod_of_instance"), &VisualServerDummy::instance_geometry_set_as_instance_lod);

	ClassDB::bind_method(D_METHOD("instances_cull_aabb", "aabb", "scenario"), &VisualServerDummy::_instances_cull_aabb_bind, DEFVAL(RID()));
	ClassDB::bind_method(D_METHOD("instances_cull_ray", "from", "to", "scenario"), &VisualServerDummy::_instances_cull_ray_bind, DEFVAL(RID()));
	ClassDB::bind_method(D_METHOD("instances_cull_convex", "convex", "scenario"), &VisualServerDummy::_instances_cull_convex_bind, DEFVAL(RID()));
#endif
	ClassDB::bind_method(D_METHOD("canvas_create"), &VisualServerDummy::canvas_create);
	ClassDB::bind_method(D_METHOD("canvas_set_item_mirroring", "canvas", "item", "mirroring"), &VisualServerDummy::canvas_set_item_mirroring);
	ClassDB::bind_method(D_METHOD("canvas_set_modulate", "canvas", "color"), &VisualServerDummy::canvas_set_modulate);

	ClassDB::bind_method(D_METHOD("canvas_item_create"), &VisualServerDummy::canvas_item_create);
	ClassDB::bind_method(D_METHOD("canvas_item_set_parent", "item", "parent"), &VisualServerDummy::canvas_item_set_parent);
	ClassDB::bind_method(D_METHOD("canvas_item_set_visible", "item", "visible"), &VisualServerDummy::canvas_item_set_visible);
	ClassDB::bind_method(D_METHOD("canvas_item_set_light_mask", "item", "mask"), &VisualServerDummy::canvas_item_set_light_mask);
	ClassDB::bind_method(D_METHOD("canvas_item_set_transform", "item", "transform"), &VisualServerDummy::canvas_item_set_transform);
	ClassDB::bind_method(D_METHOD("canvas_item_set_clip", "item", "clip"), &VisualServerDummy::canvas_item_set_clip);
	ClassDB::bind_method(D_METHOD("canvas_item_set_distance_field_mode", "item", "enabled"), &VisualServerDummy::canvas_item_set_distance_field_mode);
	ClassDB::bind_method(D_METHOD("canvas_item_set_custom_rect", "item", "use_custom_rect", "rect"), &VisualServerDummy::canvas_item_set_custom_rect, DEFVAL(Rect2()));
	ClassDB::bind_method(D_METHOD("canvas_item_set_modulate", "item", "color"), &VisualServerDummy::canvas_item_set_modulate);
	ClassDB::bind_method(D_METHOD("canvas_item_set_self_modulate", "item", "color"), &VisualServerDummy::canvas_item_set_self_modulate);
	ClassDB::bind_method(D_METHOD("canvas_item_set_draw_behind_parent", "item", "enabled"), &VisualServerDummy::canvas_item_set_draw_behind_parent);
	ClassDB::bind_method(D_METHOD("canvas_item_add_line", "item", "from", "to", "color", "width", "antialiased"), &VisualServerDummy::canvas_item_add_line, DEFVAL(1.0), DEFVAL(false));
	ClassDB::bind_method(D_METHOD("canvas_item_add_polyline", "item", "points", "colors", "width", "antialiased"), &VisualServerDummy::canvas_item_add_polyline, DEFVAL(1.0), DEFVAL(false));
	ClassDB::bind_method(D_METHOD("canvas_item_add_rect", "item", "rect", "color"), &VisualServerDummy::canvas_item_add_rect);
	ClassDB::bind_method(D_METHOD("canvas_item_add_circle", "item", "pos", "radius", "color"), &VisualServerDummy::canvas_item_add_circle);
	ClassDB::bind_method(D_METHOD("canvas_item_add_texture_rect", "item", "rect", "texture", "tile", "modulate", "transpose", "normal_map"), &VisualServerDummy::canvas_item_add_texture_rect, DEFVAL(false), DEFVAL(Color(1, 1, 1)), DEFVAL(false), DEFVAL(RID()));
	ClassDB::bind_method(D_METHOD("canvas_item_add_texture_rect_region", "item", "rect", "texture", "src_rect", "modulate", "transpose", "normal_map", "clip_uv"), &VisualServerDummy::canvas_item_add_texture_rect_region, DEFVAL(Color(1, 1, 1)), DEFVAL(false), DEFVAL(RID()), DEFVAL(true));
	ClassDB::bind_method(D_METHOD("canvas_item_add_nine_patch", "item", "rect", "source", "texture", "topleft", "bottomright", "x_axis_mode", "y_axis_mode", "draw_center", "modulate", "normal_map"), &VisualServerDummy::canvas_item_add_nine_patch, DEFVAL(NINE_PATCH_STRETCH), DEFVAL(NINE_PATCH_STRETCH), DEFVAL(true), DEFVAL(Color(1, 1, 1)), DEFVAL(RID()));
	ClassDB::bind_method(D_METHOD("canvas_item_add_primitive", "item", "points", "colors", "uvs", "texture", "width", "normal_map"), &VisualServerDummy::canvas_item_add_primitive, DEFVAL(1.0), DEFVAL(RID()));
	ClassDB::bind_method(D_METHOD("canvas_item_add_polygon", "item", "points", "colors", "uvs", "texture", "normal_map", "antialiased"), &VisualServerDummy::canvas_item_add_polygon, DEFVAL(Vector<Point2>()), DEFVAL(RID()), DEFVAL(RID()), DEFVAL(false));
	ClassDB::bind_method(D_METHOD("canvas_item_add_triangle_array", "item", "indices", "points", "colors", "uvs", "bones", "weights", "texture", "count", "normal_map", "antialiased", "antialiasing_use_indices"), &VisualServerDummy::canvas_item_add_triangle_array, DEFVAL(Vector<Point2>()), DEFVAL(Vector<int>()), DEFVAL(Vector<float>()), DEFVAL(RID()), DEFVAL(-1), DEFVAL(RID()), DEFVAL(false), DEFVAL(false));
	ClassDB::bind_method(D_METHOD("canvas_item_add_mesh", "item", "mesh", "transform", "modulate", "texture", "normal_map"), &VisualServerDummy::canvas_item_add_mesh, DEFVAL(Transform2D()), DEFVAL(Color(1, 1, 1)), DEFVAL(RID()), DEFVAL(RID()));
	ClassDB::bind_method(D_METHOD("canvas_item_add_multimesh", "item", "mesh", "texture", "normal_map"), &VisualServerDummy::canvas_item_add_multimesh, DEFVAL(RID()));
	ClassDB::bind_method(D_METHOD("canvas_item_add_particles", "item", "particles", "texture", "normal_map"), &VisualServerDummy::canvas_item_add_particles);
	ClassDB::bind_method(D_METHOD("canvas_item_add_set_transform", "item", "transform"), &VisualServerDummy::canvas_item_add_set_transform);
	ClassDB::bind_method(D_METHOD("canvas_item_add_clip_ignore", "item", "ignore"), &VisualServerDummy::canvas_item_add_clip_ignore);
	ClassDB::bind_method(D_METHOD("canvas_item_set_sort_children_by_y", "item", "enabled"), &VisualServerDummy::canvas_item_set_sort_children_by_y);
	ClassDB::bind_method(D_METHOD("canvas_item_set_z_index", "item", "z_index"), &VisualServerDummy::canvas_item_set_z_index);
	ClassDB::bind_method(D_METHOD("canvas_item_set_z_as_relative_to_parent", "item", "enabled"), &VisualServerDummy::canvas_item_set_z_as_relative_to_parent);
	ClassDB::bind_method(D_METHOD("canvas_item_set_copy_to_backbuffer", "item", "enabled", "rect"), &VisualServerDummy::canvas_item_set_copy_to_backbuffer);
	ClassDB::bind_method(D_METHOD("canvas_item_clear", "item"), &VisualServerDummy::canvas_item_clear);
	ClassDB::bind_method(D_METHOD("canvas_item_set_draw_index", "item", "index"), &VisualServerDummy::canvas_item_set_draw_index);
	ClassDB::bind_method(D_METHOD("canvas_item_set_material", "item", "material"), &VisualServerDummy::canvas_item_set_material);
	ClassDB::bind_method(D_METHOD("canvas_item_set_use_parent_material", "item", "enabled"), &VisualServerDummy::canvas_item_set_use_parent_material);
	ClassDB::bind_method(D_METHOD("canvas_light_create"), &VisualServerDummy::canvas_light_create);
	ClassDB::bind_method(D_METHOD("canvas_light_attach_to_canvas", "light", "canvas"), &VisualServerDummy::canvas_light_attach_to_canvas);
	ClassDB::bind_method(D_METHOD("canvas_light_set_enabled", "light", "enabled"), &VisualServerDummy::canvas_light_set_enabled);
	ClassDB::bind_method(D_METHOD("canvas_light_set_scale", "light", "scale"), &VisualServerDummy::canvas_light_set_scale);
	ClassDB::bind_method(D_METHOD("canvas_light_set_transform", "light", "transform"), &VisualServerDummy::canvas_light_set_transform);
	ClassDB::bind_method(D_METHOD("canvas_light_set_texture", "light", "texture"), &VisualServerDummy::canvas_light_set_texture);
	ClassDB::bind_method(D_METHOD("canvas_light_set_texture_offset", "light", "offset"), &VisualServerDummy::canvas_light_set_texture_offset);
	ClassDB::bind_method(D_METHOD("canvas_light_set_color", "light", "color"), &VisualServerDummy::canvas_light_set_color);
	ClassDB::bind_method(D_METHOD("canvas_light_set_height", "light", "height"), &VisualServerDummy::canvas_light_set_height);
	ClassDB::bind_method(D_METHOD("canvas_light_set_energy", "light", "energy"), &VisualServerDummy::canvas_light_set_energy);
	ClassDB::bind_method(D_METHOD("canvas_light_set_z_range", "light", "min_z", "max_z"), &VisualServerDummy::canvas_light_set_z_range);
	ClassDB::bind_method(D_METHOD("canvas_light_set_layer_range", "light", "min_layer", "max_layer"), &VisualServerDummy::canvas_light_set_layer_range);
	ClassDB::bind_method(D_METHOD("canvas_light_set_item_cull_mask", "light", "mask"), &VisualServerDummy::canvas_light_set_item_cull_mask);
	ClassDB::bind_method(D_METHOD("canvas_light_set_item_shadow_cull_mask", "light", "mask"), &VisualServerDummy::canvas_light_set_item_shadow_cull_mask);
	ClassDB::bind_method(D_METHOD("canvas_light_set_mode", "light", "mode"), &VisualServerDummy::canvas_light_set_mode);
	ClassDB::bind_method(D_METHOD("canvas_light_set_shadow_enabled", "light", "enabled"), &VisualServerDummy::canvas_light_set_shadow_enabled);
	ClassDB::bind_method(D_METHOD("canvas_light_set_shadow_buffer_size", "light", "size"), &VisualServerDummy::canvas_light_set_shadow_buffer_size);
	ClassDB::bind_method(D_METHOD("canvas_light_set_shadow_gradient_length", "light", "length"), &VisualServerDummy::canvas_light_set_shadow_gradient_length);
	ClassDB::bind_method(D_METHOD("canvas_light_set_shadow_filter", "light", "filter"), &VisualServerDummy::canvas_light_set_shadow_filter);
	ClassDB::bind_method(D_METHOD("canvas_light_set_shadow_color", "light", "color"), &VisualServerDummy::canvas_light_set_shadow_color);
	ClassDB::bind_method(D_METHOD("canvas_light_set_shadow_smooth", "light", "smooth"), &VisualServerDummy::canvas_light_set_shadow_smooth);

	ClassDB::bind_method(D_METHOD("canvas_light_occluder_create"), &VisualServerDummy::canvas_light_occluder_create);
	ClassDB::bind_method(D_METHOD("canvas_light_occluder_attach_to_canvas", "occluder", "canvas"), &VisualServerDummy::canvas_light_occluder_attach_to_canvas);
	ClassDB::bind_method(D_METHOD("canvas_light_occluder_set_enabled", "occluder", "enabled"), &VisualServerDummy::canvas_light_occluder_set_enabled);
	ClassDB::bind_method(D_METHOD("canvas_light_occluder_set_polygon", "occluder", "polygon"), &VisualServerDummy::canvas_light_occluder_set_polygon);
	ClassDB::bind_method(D_METHOD("canvas_light_occluder_set_transform", "occluder", "transform"), &VisualServerDummy::canvas_light_occluder_set_transform);
	ClassDB::bind_method(D_METHOD("canvas_light_occluder_set_light_mask", "occluder", "mask"), &VisualServerDummy::canvas_light_occluder_set_light_mask);

	ClassDB::bind_method(D_METHOD("canvas_occluder_polygon_create"), &VisualServerDummy::canvas_occluder_polygon_create);
	ClassDB::bind_method(D_METHOD("canvas_occluder_polygon_set_shape", "occluder_polygon", "shape", "closed"), &VisualServerDummy::canvas_occluder_polygon_set_shape);
	ClassDB::bind_method(D_METHOD("canvas_occluder_polygon_set_shape_as_lines", "occluder_polygon", "shape"), &VisualServerDummy::canvas_occluder_polygon_set_shape_as_lines);
	ClassDB::bind_method(D_METHOD("canvas_occluder_polygon_set_cull_mode", "occluder_polygon", "mode"), &VisualServerDummy::canvas_occluder_polygon_set_cull_mode);

	ClassDB::bind_method(D_METHOD("black_bars_set_margins", "left", "top", "right", "bottom"), &VisualServerDummy::black_bars_set_margins);
	ClassDB::bind_method(D_METHOD("black_bars_set_images", "left", "top", "right", "bottom"), &VisualServerDummy::black_bars_set_images);

	ClassDB::bind_method(D_METHOD("free_rid", "rid"), &VisualServerDummy::free); // shouldn't conflict with Object::free()

	ClassDB::bind_method(D_METHOD("request_frame_drawn_callback", "where", "method", "userdata"), &VisualServerDummy::request_frame_drawn_callback);
	ClassDB::bind_method(D_METHOD("has_changed"), &VisualServerDummy::has_changed);
	ClassDB::bind_method(D_METHOD("init"), &VisualServerDummy::init);
	ClassDB::bind_method(D_METHOD("finish"), &VisualServerDummy::finish);
	ClassDB::bind_method(D_METHOD("get_render_info", "info"), &VisualServerDummy::get_render_info);
	ClassDB::bind_method(D_METHOD("get_video_adapter_name"), &VisualServerDummy::get_video_adapter_name);
	ClassDB::bind_method(D_METHOD("get_video_adapter_vendor"), &VisualServerDummy::get_video_adapter_vendor);
#ifndef _3D_DISABLED

	ClassDB::bind_method(D_METHOD("make_sphere_mesh", "latitudes", "longitudes", "radius"), &VisualServerDummy::make_sphere_mesh);
	ClassDB::bind_method(D_METHOD("get_test_cube"), &VisualServerDummy::get_test_cube);
#endif
	ClassDB::bind_method(D_METHOD("get_test_texture"), &VisualServerDummy::get_test_texture);
	ClassDB::bind_method(D_METHOD("get_white_texture"), &VisualServerDummy::get_white_texture);

	ClassDB::bind_method(D_METHOD("set_boot_image", "image", "color", "scale", "use_filter"), &VisualServerDummy::set_boot_image, DEFVAL(true));
	ClassDB::bind_method(D_METHOD("set_default_clear_color", "color"), &VisualServerDummy::set_default_clear_color);
	ClassDB::bind_method(D_METHOD("set_shader_time_scale", "scale"), &VisualServerDummy::set_shader_time_scale);

	ClassDB::bind_method(D_METHOD("has_feature", "feature"), &VisualServerDummy::has_feature);
	ClassDB::bind_method(D_METHOD("has_os_feature", "feature"), &VisualServerDummy::has_os_feature);
	ClassDB::bind_method(D_METHOD("set_debug_generate_wireframes", "generate"), &VisualServerDummy::set_debug_generate_wireframes);

	ClassDB::bind_method(D_METHOD("is_render_loop_enabled"), &VisualServerDummy::is_render_loop_enabled);
	ClassDB::bind_method(D_METHOD("set_render_loop_enabled", "enabled"), &VisualServerDummy::set_render_loop_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "render_loop_enabled"), "set_render_loop_enabled", "is_render_loop_enabled");

	BIND_CONSTANT(NO_INDEX_ARRAY);
	BIND_CONSTANT(ARRAY_WEIGHTS_SIZE);
	BIND_CONSTANT(CANVAS_ITEM_Z_MIN);
	BIND_CONSTANT(CANVAS_ITEM_Z_MAX);
	BIND_CONSTANT(MAX_GLOW_LEVELS);
	BIND_CONSTANT(MAX_CURSORS);
	BIND_CONSTANT(MATERIAL_RENDER_PRIORITY_MIN);
	BIND_CONSTANT(MATERIAL_RENDER_PRIORITY_MAX);

	BIND_ENUM_CONSTANT(CUBEMAP_LEFT);
	BIND_ENUM_CONSTANT(CUBEMAP_RIGHT);
	BIND_ENUM_CONSTANT(CUBEMAP_BOTTOM);
	BIND_ENUM_CONSTANT(CUBEMAP_TOP);
	BIND_ENUM_CONSTANT(CUBEMAP_FRONT);
	BIND_ENUM_CONSTANT(CUBEMAP_BACK);

	BIND_ENUM_CONSTANT(TEXTURE_TYPE_2D);
	BIND_ENUM_CONSTANT(TEXTURE_TYPE_CUBEMAP);
	BIND_ENUM_CONSTANT(TEXTURE_TYPE_2D_ARRAY);
	BIND_ENUM_CONSTANT(TEXTURE_TYPE_3D);

	BIND_ENUM_CONSTANT(TEXTURE_FLAG_MIPMAPS);
	BIND_ENUM_CONSTANT(TEXTURE_FLAG_REPEAT);
	BIND_ENUM_CONSTANT(TEXTURE_FLAG_FILTER);
	BIND_ENUM_CONSTANT(TEXTURE_FLAG_ANISOTROPIC_FILTER);
	BIND_ENUM_CONSTANT(TEXTURE_FLAG_CONVERT_TO_LINEAR);
	BIND_ENUM_CONSTANT(TEXTURE_FLAG_MIRRORED_REPEAT);
	BIND_ENUM_CONSTANT(TEXTURE_FLAG_USED_FOR_STREAMING);
	BIND_ENUM_CONSTANT(TEXTURE_FLAGS_DEFAULT);

	BIND_ENUM_CONSTANT(SHADER_SPATIAL);
	BIND_ENUM_CONSTANT(SHADER_CANVAS_ITEM);
	BIND_ENUM_CONSTANT(SHADER_PARTICLES);
	BIND_ENUM_CONSTANT(SHADER_MAX);

	BIND_ENUM_CONSTANT(ARRAY_VERTEX);
	BIND_ENUM_CONSTANT(ARRAY_NORMAL);
	BIND_ENUM_CONSTANT(ARRAY_TANGENT);
	BIND_ENUM_CONSTANT(ARRAY_COLOR);
	BIND_ENUM_CONSTANT(ARRAY_TEX_UV);
	BIND_ENUM_CONSTANT(ARRAY_TEX_UV2);
	BIND_ENUM_CONSTANT(ARRAY_BONES);
	BIND_ENUM_CONSTANT(ARRAY_WEIGHTS);
	BIND_ENUM_CONSTANT(ARRAY_INDEX);
	BIND_ENUM_CONSTANT(ARRAY_MAX);

	BIND_ENUM_CONSTANT(ARRAY_FORMAT_VERTEX);
	BIND_ENUM_CONSTANT(ARRAY_FORMAT_NORMAL);
	BIND_ENUM_CONSTANT(ARRAY_FORMAT_TANGENT);
	BIND_ENUM_CONSTANT(ARRAY_FORMAT_COLOR);
	BIND_ENUM_CONSTANT(ARRAY_FORMAT_TEX_UV);
	BIND_ENUM_CONSTANT(ARRAY_FORMAT_TEX_UV2);
	BIND_ENUM_CONSTANT(ARRAY_FORMAT_BONES);
	BIND_ENUM_CONSTANT(ARRAY_FORMAT_WEIGHTS);
	BIND_ENUM_CONSTANT(ARRAY_FORMAT_INDEX);
	BIND_ENUM_CONSTANT(ARRAY_COMPRESS_VERTEX);
	BIND_ENUM_CONSTANT(ARRAY_COMPRESS_NORMAL);
	BIND_ENUM_CONSTANT(ARRAY_COMPRESS_TANGENT);
	BIND_ENUM_CONSTANT(ARRAY_COMPRESS_COLOR);
	BIND_ENUM_CONSTANT(ARRAY_COMPRESS_TEX_UV);
	BIND_ENUM_CONSTANT(ARRAY_COMPRESS_TEX_UV2);
	BIND_ENUM_CONSTANT(ARRAY_COMPRESS_BONES);
	BIND_ENUM_CONSTANT(ARRAY_COMPRESS_WEIGHTS);
	BIND_ENUM_CONSTANT(ARRAY_COMPRESS_INDEX);
	BIND_ENUM_CONSTANT(ARRAY_FLAG_USE_2D_VERTICES);
	BIND_ENUM_CONSTANT(ARRAY_FLAG_USE_16_BIT_BONES);
	BIND_ENUM_CONSTANT(ARRAY_COMPRESS_DEFAULT);

	BIND_ENUM_CONSTANT(PRIMITIVE_POINTS);
	BIND_ENUM_CONSTANT(PRIMITIVE_LINES);
	BIND_ENUM_CONSTANT(PRIMITIVE_LINE_STRIP);
	BIND_ENUM_CONSTANT(PRIMITIVE_LINE_LOOP);
	BIND_ENUM_CONSTANT(PRIMITIVE_TRIANGLES);
	BIND_ENUM_CONSTANT(PRIMITIVE_TRIANGLE_STRIP);
	BIND_ENUM_CONSTANT(PRIMITIVE_TRIANGLE_FAN);
	BIND_ENUM_CONSTANT(PRIMITIVE_MAX);

	BIND_ENUM_CONSTANT(BLEND_SHAPE_MODE_NORMALIZED);
	BIND_ENUM_CONSTANT(BLEND_SHAPE_MODE_RELATIVE);

	BIND_ENUM_CONSTANT(LIGHT_DIRECTIONAL);
	BIND_ENUM_CONSTANT(LIGHT_OMNI);
	BIND_ENUM_CONSTANT(LIGHT_SPOT);

	BIND_ENUM_CONSTANT(LIGHT_PARAM_ENERGY);
	BIND_ENUM_CONSTANT(LIGHT_PARAM_SPECULAR);
	BIND_ENUM_CONSTANT(LIGHT_PARAM_RANGE);
	BIND_ENUM_CONSTANT(LIGHT_PARAM_ATTENUATION);
	BIND_ENUM_CONSTANT(LIGHT_PARAM_SPOT_ANGLE);
	BIND_ENUM_CONSTANT(LIGHT_PARAM_SPOT_ATTENUATION);
	BIND_ENUM_CONSTANT(LIGHT_PARAM_CONTACT_SHADOW_SIZE);
	BIND_ENUM_CONSTANT(LIGHT_PARAM_SHADOW_MAX_DISTANCE);
	BIND_ENUM_CONSTANT(LIGHT_PARAM_SHADOW_SPLIT_1_OFFSET);
	BIND_ENUM_CONSTANT(LIGHT_PARAM_SHADOW_SPLIT_2_OFFSET);
	BIND_ENUM_CONSTANT(LIGHT_PARAM_SHADOW_SPLIT_3_OFFSET);
	BIND_ENUM_CONSTANT(LIGHT_PARAM_SHADOW_NORMAL_BIAS);
	BIND_ENUM_CONSTANT(LIGHT_PARAM_SHADOW_BIAS);
	BIND_ENUM_CONSTANT(LIGHT_PARAM_SHADOW_BIAS_SPLIT_SCALE);
	BIND_ENUM_CONSTANT(LIGHT_PARAM_MAX);

	BIND_ENUM_CONSTANT(LIGHT_BAKE_DISABLED);
	BIND_ENUM_CONSTANT(LIGHT_BAKE_INDIRECT);
	BIND_ENUM_CONSTANT(LIGHT_BAKE_ALL);

	BIND_ENUM_CONSTANT(LIGHT_OMNI_SHADOW_DUAL_PARABOLOID);
	BIND_ENUM_CONSTANT(LIGHT_OMNI_SHADOW_CUBE);
	BIND_ENUM_CONSTANT(LIGHT_OMNI_SHADOW_DETAIL_VERTICAL);
	BIND_ENUM_CONSTANT(LIGHT_OMNI_SHADOW_DETAIL_HORIZONTAL);

	BIND_ENUM_CONSTANT(LIGHT_DIRECTIONAL_SHADOW_ORTHOGONAL);
	BIND_ENUM_CONSTANT(LIGHT_DIRECTIONAL_SHADOW_PARALLEL_2_SPLITS);
	BIND_ENUM_CONSTANT(LIGHT_DIRECTIONAL_SHADOW_PARALLEL_4_SPLITS);
	BIND_ENUM_CONSTANT(LIGHT_DIRECTIONAL_SHADOW_DEPTH_RANGE_STABLE);
	BIND_ENUM_CONSTANT(LIGHT_DIRECTIONAL_SHADOW_DEPTH_RANGE_OPTIMIZED);

	BIND_ENUM_CONSTANT(VIEWPORT_UPDATE_DISABLED);
	BIND_ENUM_CONSTANT(VIEWPORT_UPDATE_ONCE);
	BIND_ENUM_CONSTANT(VIEWPORT_UPDATE_WHEN_VISIBLE);
	BIND_ENUM_CONSTANT(VIEWPORT_UPDATE_ALWAYS);

	BIND_ENUM_CONSTANT(VIEWPORT_CLEAR_ALWAYS);
	BIND_ENUM_CONSTANT(VIEWPORT_CLEAR_NEVER);
	BIND_ENUM_CONSTANT(VIEWPORT_CLEAR_ONLY_NEXT_FRAME);

	BIND_ENUM_CONSTANT(VIEWPORT_MSAA_DISABLED);
	BIND_ENUM_CONSTANT(VIEWPORT_MSAA_2X);
	BIND_ENUM_CONSTANT(VIEWPORT_MSAA_4X);
	BIND_ENUM_CONSTANT(VIEWPORT_MSAA_8X);
	BIND_ENUM_CONSTANT(VIEWPORT_MSAA_16X);
	BIND_ENUM_CONSTANT(VIEWPORT_MSAA_EXT_2X);
	BIND_ENUM_CONSTANT(VIEWPORT_MSAA_EXT_4X);

	BIND_ENUM_CONSTANT(VIEWPORT_USAGE_2D);
	BIND_ENUM_CONSTANT(VIEWPORT_USAGE_2D_NO_SAMPLING);
	BIND_ENUM_CONSTANT(VIEWPORT_USAGE_3D);
	BIND_ENUM_CONSTANT(VIEWPORT_USAGE_3D_NO_EFFECTS);

	BIND_ENUM_CONSTANT(VIEWPORT_RENDER_INFO_OBJECTS_IN_FRAME);
	BIND_ENUM_CONSTANT(VIEWPORT_RENDER_INFO_VERTICES_IN_FRAME);
	BIND_ENUM_CONSTANT(VIEWPORT_RENDER_INFO_MATERIAL_CHANGES_IN_FRAME);
	BIND_ENUM_CONSTANT(VIEWPORT_RENDER_INFO_SHADER_CHANGES_IN_FRAME);
	BIND_ENUM_CONSTANT(VIEWPORT_RENDER_INFO_SURFACE_CHANGES_IN_FRAME);
	BIND_ENUM_CONSTANT(VIEWPORT_RENDER_INFO_DRAW_CALLS_IN_FRAME);
	BIND_ENUM_CONSTANT(VIEWPORT_RENDER_INFO_2D_ITEMS_IN_FRAME);
	BIND_ENUM_CONSTANT(VIEWPORT_RENDER_INFO_2D_DRAW_CALLS_IN_FRAME);
	BIND_ENUM_CONSTANT(VIEWPORT_RENDER_INFO_MAX);

	BIND_ENUM_CONSTANT(VIEWPORT_DEBUG_DRAW_DISABLED);
	BIND_ENUM_CONSTANT(VIEWPORT_DEBUG_DRAW_UNSHADED);
	BIND_ENUM_CONSTANT(VIEWPORT_DEBUG_DRAW_OVERDRAW);
	BIND_ENUM_CONSTANT(VIEWPORT_DEBUG_DRAW_WIREFRAME);

	BIND_ENUM_CONSTANT(SCENARIO_DEBUG_DISABLED);
	BIND_ENUM_CONSTANT(SCENARIO_DEBUG_WIREFRAME);
	BIND_ENUM_CONSTANT(SCENARIO_DEBUG_OVERDRAW);
	BIND_ENUM_CONSTANT(SCENARIO_DEBUG_SHADELESS);

	BIND_ENUM_CONSTANT(INSTANCE_NONE);
	BIND_ENUM_CONSTANT(INSTANCE_MESH);
	BIND_ENUM_CONSTANT(INSTANCE_MULTIMESH);
	BIND_ENUM_CONSTANT(INSTANCE_IMMEDIATE);
	BIND_ENUM_CONSTANT(INSTANCE_PARTICLES);
	BIND_ENUM_CONSTANT(INSTANCE_LIGHT);
	BIND_ENUM_CONSTANT(INSTANCE_REFLECTION_PROBE);
	BIND_ENUM_CONSTANT(INSTANCE_GI_PROBE);
	BIND_ENUM_CONSTANT(INSTANCE_LIGHTMAP_CAPTURE);
	BIND_ENUM_CONSTANT(INSTANCE_MAX);
	BIND_ENUM_CONSTANT(INSTANCE_GEOMETRY_MASK);

	BIND_ENUM_CONSTANT(INSTANCE_FLAG_USE_BAKED_LIGHT);
	BIND_ENUM_CONSTANT(INSTANCE_FLAG_DRAW_NEXT_FRAME_IF_VISIBLE);
	BIND_ENUM_CONSTANT(INSTANCE_FLAG_MAX);

	BIND_ENUM_CONSTANT(SHADOW_CASTING_SETTING_OFF);
	BIND_ENUM_CONSTANT(SHADOW_CASTING_SETTING_ON);
	BIND_ENUM_CONSTANT(SHADOW_CASTING_SETTING_DOUBLE_SIDED);
	BIND_ENUM_CONSTANT(SHADOW_CASTING_SETTING_SHADOWS_ONLY);

	BIND_ENUM_CONSTANT(NINE_PATCH_STRETCH);
	BIND_ENUM_CONSTANT(NINE_PATCH_TILE);
	BIND_ENUM_CONSTANT(NINE_PATCH_TILE_FIT);

	BIND_ENUM_CONSTANT(CANVAS_LIGHT_MODE_ADD);
	BIND_ENUM_CONSTANT(CANVAS_LIGHT_MODE_SUB);
	BIND_ENUM_CONSTANT(CANVAS_LIGHT_MODE_MIX);
	BIND_ENUM_CONSTANT(CANVAS_LIGHT_MODE_MASK);

	BIND_ENUM_CONSTANT(CANVAS_LIGHT_FILTER_NONE);
	BIND_ENUM_CONSTANT(CANVAS_LIGHT_FILTER_PCF3);
	BIND_ENUM_CONSTANT(CANVAS_LIGHT_FILTER_PCF5);
	BIND_ENUM_CONSTANT(CANVAS_LIGHT_FILTER_PCF7);
	BIND_ENUM_CONSTANT(CANVAS_LIGHT_FILTER_PCF9);
	BIND_ENUM_CONSTANT(CANVAS_LIGHT_FILTER_PCF13);

	BIND_ENUM_CONSTANT(CANVAS_OCCLUDER_POLYGON_CULL_DISABLED);
	BIND_ENUM_CONSTANT(CANVAS_OCCLUDER_POLYGON_CULL_CLOCKWISE);
	BIND_ENUM_CONSTANT(CANVAS_OCCLUDER_POLYGON_CULL_COUNTER_CLOCKWISE);

	BIND_ENUM_CONSTANT(INFO_OBJECTS_IN_FRAME);
	BIND_ENUM_CONSTANT(INFO_VERTICES_IN_FRAME);
	BIND_ENUM_CONSTANT(INFO_MATERIAL_CHANGES_IN_FRAME);
	BIND_ENUM_CONSTANT(INFO_SHADER_CHANGES_IN_FRAME);
	BIND_ENUM_CONSTANT(INFO_SURFACE_CHANGES_IN_FRAME);
	BIND_ENUM_CONSTANT(INFO_DRAW_CALLS_IN_FRAME);
	BIND_ENUM_CONSTANT(INFO_2D_ITEMS_IN_FRAME);
	BIND_ENUM_CONSTANT(INFO_2D_DRAW_CALLS_IN_FRAME);
	BIND_ENUM_CONSTANT(INFO_USAGE_VIDEO_MEM_TOTAL);
	BIND_ENUM_CONSTANT(INFO_VIDEO_MEM_USED);
	BIND_ENUM_CONSTANT(INFO_TEXTURE_MEM_USED);
	BIND_ENUM_CONSTANT(INFO_VERTEX_MEM_USED);

	BIND_ENUM_CONSTANT(FEATURE_SHADERS);
	BIND_ENUM_CONSTANT(FEATURE_MULTITHREADED);

	BIND_ENUM_CONSTANT(MULTIMESH_TRANSFORM_2D);
	BIND_ENUM_CONSTANT(MULTIMESH_TRANSFORM_3D);
	BIND_ENUM_CONSTANT(MULTIMESH_COLOR_NONE);
	BIND_ENUM_CONSTANT(MULTIMESH_COLOR_8BIT);
	BIND_ENUM_CONSTANT(MULTIMESH_COLOR_FLOAT);
	BIND_ENUM_CONSTANT(MULTIMESH_CUSTOM_DATA_NONE);
	BIND_ENUM_CONSTANT(MULTIMESH_CUSTOM_DATA_8BIT);
	BIND_ENUM_CONSTANT(MULTIMESH_CUSTOM_DATA_FLOAT);

	BIND_ENUM_CONSTANT(REFLECTION_PROBE_UPDATE_ONCE);
	BIND_ENUM_CONSTANT(REFLECTION_PROBE_UPDATE_ALWAYS);

	BIND_ENUM_CONSTANT(PARTICLES_DRAW_ORDER_INDEX);
	BIND_ENUM_CONSTANT(PARTICLES_DRAW_ORDER_LIFETIME);
	BIND_ENUM_CONSTANT(PARTICLES_DRAW_ORDER_VIEW_DEPTH);

	BIND_ENUM_CONSTANT(ENV_BG_CLEAR_COLOR);
	BIND_ENUM_CONSTANT(ENV_BG_COLOR);
	BIND_ENUM_CONSTANT(ENV_BG_SKY);
	BIND_ENUM_CONSTANT(ENV_BG_COLOR_SKY);
	BIND_ENUM_CONSTANT(ENV_BG_CANVAS);
	BIND_ENUM_CONSTANT(ENV_BG_KEEP);
	BIND_ENUM_CONSTANT(ENV_BG_MAX);

	BIND_ENUM_CONSTANT(ENV_DOF_BLUR_QUALITY_LOW);
	BIND_ENUM_CONSTANT(ENV_DOF_BLUR_QUALITY_MEDIUM);
	BIND_ENUM_CONSTANT(ENV_DOF_BLUR_QUALITY_HIGH);

	BIND_ENUM_CONSTANT(GLOW_BLEND_MODE_ADDITIVE);
	BIND_ENUM_CONSTANT(GLOW_BLEND_MODE_SCREEN);
	BIND_ENUM_CONSTANT(GLOW_BLEND_MODE_SOFTLIGHT);
	BIND_ENUM_CONSTANT(GLOW_BLEND_MODE_REPLACE);

	BIND_ENUM_CONSTANT(ENV_TONE_MAPPER_LINEAR);
	BIND_ENUM_CONSTANT(ENV_TONE_MAPPER_REINHARD);
	BIND_ENUM_CONSTANT(ENV_TONE_MAPPER_FILMIC);
	BIND_ENUM_CONSTANT(ENV_TONE_MAPPER_ACES);

	BIND_ENUM_CONSTANT(ENV_SSAO_QUALITY_LOW);
	BIND_ENUM_CONSTANT(ENV_SSAO_QUALITY_MEDIUM);
	BIND_ENUM_CONSTANT(ENV_SSAO_QUALITY_HIGH);

	BIND_ENUM_CONSTANT(ENV_SSAO_BLUR_DISABLED);
	BIND_ENUM_CONSTANT(ENV_SSAO_BLUR_1x1);
	BIND_ENUM_CONSTANT(ENV_SSAO_BLUR_2x2);
	BIND_ENUM_CONSTANT(ENV_SSAO_BLUR_3x3);

	ADD_SIGNAL(MethodInfo("frame_pre_draw"));
	ADD_SIGNAL(MethodInfo("frame_post_draw"));
	*/
}

void VisualServerDummy::_canvas_item_add_style_box(RID p_item, const Rect2 &p_rect, const Rect2 &p_source, RID p_texture, const Vector<float> &p_margins, const Color &p_modulate) {

}

void VisualServerDummy::_camera_set_orthogonal(RID p_camera, float p_size, float p_z_near, float p_z_far) {

}

void VisualServerDummy::mesh_add_surface_from_mesh_data(RID p_mesh, const Geometry::MeshData &p_mesh_data) {

}

void VisualServerDummy::mesh_add_surface_from_planes(RID p_mesh, const PoolVector<Plane> &p_planes) {

}

void VisualServerDummy::immediate_vertex_2d(RID p_immediate, const Vector2 &p_vertex) {
	
}

RID VisualServerDummy::instance_create2(RID p_base, RID p_scenario) {
	return RID();
}

bool VisualServerDummy::is_render_loop_enabled() const {
	return false;
}

void VisualServerDummy::set_render_loop_enabled(bool p_enabled) {
	;
}

VisualServerDummy::VisualServerDummy() {

}

VisualServerDummy::~VisualServerDummy() {

}
