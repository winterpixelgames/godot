/*************************************************************************/
/*  visual_server.h                                                      */
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

#ifndef VISUAL_SERVER_DUMMY_H
#define VISUAL_SERVER_DUMMY_H

#include "core/image.h"
#include "core/math/bsp_tree.h"
#include "core/math/geometry.h"
#include "core/math/transform_2d.h"
#include "core/object.h"
#include "core/rid.h"
#include "core/variant.h"
#include "visual_server.h"

class VisualServerDummy : public VisualServer {

	//GDCLASS(VisualServerDummy, VisualServer);

	void _camera_set_orthogonal(RID p_camera, float p_size, float p_z_near, float p_z_far);
	void _canvas_item_add_style_box(RID p_item, const Rect2 &p_rect, const Rect2 &p_source, RID p_texture, const Vector<float> &p_margins, const Color &p_modulate = Color(1, 1, 1));
	Array _get_array_from_surface(uint32_t p_format, PoolVector<uint8_t> p_vertex_data, int p_vertex_len, PoolVector<uint8_t> p_index_data, int p_index_len) const;

protected:
	RID _make_test_cube();
	void _free_internal_rids();
	RID test_texture;
	RID white_texture;
	RID test_material;

	Error _surface_set_data(Array p_arrays, uint32_t p_format, uint32_t *p_offsets, uint32_t p_stride, PoolVector<uint8_t> &r_vertex_array, int p_vertex_array_len, PoolVector<uint8_t> &r_index_array, int p_index_array_len, AABB &r_aabb, Vector<AABB> &r_bone_aabb);

	static void _bind_methods();

public:

	enum {

		NO_INDEX_ARRAY = -1,
		ARRAY_WEIGHTS_SIZE = 4,
		CANVAS_ITEM_Z_MIN = -4096,
		CANVAS_ITEM_Z_MAX = 4096,
		MAX_GLOW_LEVELS = 7,

		MAX_CURSORS = 8,
	};

	virtual RID texture_create(){ return RID(); }
	RID texture_create_from_image(const Ref<Image> &p_image, uint32_t p_flags = TEXTURE_FLAGS_DEFAULT); // helper
	virtual void texture_allocate(RID p_texture,
			int p_width,
			int p_height,
			int p_depth_3d,
			Image::Format p_format,
			TextureType p_type,
			uint32_t p_flags = TEXTURE_FLAGS_DEFAULT){  };

	virtual void texture_set_data(RID p_texture, const Ref<Image> &p_image, int p_layer = 0){  };
	virtual void texture_set_data_partial(RID p_texture,
			const Ref<Image> &p_image,
			int src_x, int src_y,
			int src_w, int src_h,
			int dst_x, int dst_y,
			int p_dst_mip,
			int p_layer = 0){  };

	virtual Ref<Image> texture_get_data(RID p_texture, int p_layer = 0) const{ return Ref<Image>(); };
	virtual void texture_set_flags(RID p_texture, uint32_t p_flags){  };
	virtual uint32_t texture_get_flags(RID p_texture) const{ return 0; };
	virtual Image::Format texture_get_format(RID p_texture) const{ return Image::Format::FORMAT_RGBA8; };
	virtual TextureType texture_get_type(RID p_texture) const{ return TextureType::TEXTURE_TYPE_2D; };
	virtual uint32_t texture_get_texid(RID p_texture) const{ return 0; };
	virtual uint32_t texture_get_width(RID p_texture) const{ return 0; };
	virtual uint32_t texture_get_height(RID p_texture) const{ return 0; };
	virtual uint32_t texture_get_depth(RID p_texture) const{ return 0; };
	virtual void texture_set_size_override(RID p_texture, int p_width, int p_height, int p_depth_3d){  };
	virtual void texture_bind(RID p_texture, uint32_t p_texture_no){  };

	virtual void texture_set_path(RID p_texture, const String &p_path){  };
	virtual String texture_get_path(RID p_texture) const{ return ""; };

	virtual void texture_set_shrink_all_x2_on_set_data(bool p_enable){  };

	typedef void (*TextureDetectCallback)(void *);

	virtual void texture_set_detect_3d_callback(RID p_texture, TextureDetectCallback p_callback, void *p_userdata){  };
	virtual void texture_set_detect_srgb_callback(RID p_texture, TextureDetectCallback p_callback, void *p_userdata){  };
	virtual void texture_set_detect_normal_callback(RID p_texture, TextureDetectCallback p_callback, void *p_userdata){  };

	struct TextureInfo {
		RID texture;
		uint32_t width;
		uint32_t height;
		uint32_t depth;
		Image::Format format;
		int bytes;
		String path;
	};

	virtual void texture_debug_usage(List<VisualServer::TextureInfo> *r_info){  };
	Array _texture_debug_usage_bind() { return Array(); };

	virtual void textures_keep_original(bool p_enable){  };

	virtual void texture_set_proxy(RID p_proxy, RID p_base){  };
	virtual void texture_set_force_redraw_if_visible(RID p_texture, bool p_enable){  };

	/* SKY API */

	virtual RID sky_create(){ return RID(); };
	virtual void sky_set_texture(RID p_sky, RID p_cube_map, int p_radiance_size){  };

	virtual RID shader_create(){ return RID(); };

	virtual void shader_set_code(RID p_shader, const String &p_code){  };
	virtual String shader_get_code(RID p_shader) const{ return ""; };
	virtual void shader_get_param_list(RID p_shader, List<PropertyInfo> *p_param_list) const{  };
	Array _shader_get_param_list_bind(RID p_shader) const;

	virtual void shader_set_default_texture_param(RID p_shader, const StringName &p_name, RID p_texture){  };
	virtual RID shader_get_default_texture_param(RID p_shader, const StringName &p_name) const{ return RID(); };

	virtual void shader_add_custom_define(RID p_shader, const String &p_define){  };
	virtual void shader_get_custom_defines(RID p_shader, Vector<String> *p_defines) const{  };
	virtual void shader_remove_custom_define(RID p_shader, const String &p_define){  };

	/* COMMON MATERIAL API */

	enum {
		MATERIAL_RENDER_PRIORITY_MIN = -128,
		MATERIAL_RENDER_PRIORITY_MAX = 127,

	};
	virtual RID material_create(){ return RID(); };

	virtual void material_set_shader(RID p_shader_material, RID p_shader){  };
	virtual RID material_get_shader(RID p_shader_material) const{ return RID(); };

	virtual void material_set_param(RID p_material, const StringName &p_param, const Variant &p_value){  };
	virtual Variant material_get_param(RID p_material, const StringName &p_param) const{ return Variant(); };
	virtual Variant material_get_param_default(RID p_material, const StringName &p_param) const{ return Variant(); };

	virtual void material_set_render_priority(RID p_material, int priority){  };

	virtual void material_set_line_width(RID p_material, float p_width){  };
	virtual void material_set_next_pass(RID p_material, RID p_next_material){  };

	virtual RID mesh_create(){ return RID(); };

	virtual uint32_t mesh_surface_get_format_offset(uint32_t p_format, int p_vertex_len, int p_index_len, int p_array_index) const;
	virtual uint32_t mesh_surface_get_format_stride(uint32_t p_format, int p_vertex_len, int p_index_len) const;
	/// Returns stride
	virtual uint32_t mesh_surface_make_offsets_from_format(uint32_t p_format, int p_vertex_len, int p_index_len, uint32_t *r_offsets) const;
	virtual void mesh_add_surface_from_arrays(RID p_mesh, PrimitiveType p_primitive, const Array &p_arrays, const Array &p_blend_shapes = Array(), uint32_t p_compress_format = ARRAY_COMPRESS_DEFAULT);
	virtual void mesh_add_surface(RID p_mesh, uint32_t p_format, PrimitiveType p_primitive, const PoolVector<uint8_t> &p_array, int p_vertex_count, const PoolVector<uint8_t> &p_index_array, int p_index_count, const AABB &p_aabb, const Vector<PoolVector<uint8_t> > &p_blend_shapes = Vector<PoolVector<uint8_t> >(), const Vector<AABB> &p_bone_aabbs = Vector<AABB>()){  };

	virtual void mesh_set_blend_shape_count(RID p_mesh, int p_amount){  };
	virtual int mesh_get_blend_shape_count(RID p_mesh) const{ return 0; };



	virtual void mesh_set_blend_shape_mode(RID p_mesh, BlendShapeMode p_mode){  };
	virtual VisualServer::BlendShapeMode mesh_get_blend_shape_mode(RID p_mesh) const{ return VisualServer::BlendShapeMode::BLEND_SHAPE_MODE_NORMALIZED; };

	virtual void mesh_surface_update_region(RID p_mesh, int p_surface, int p_offset, const PoolVector<uint8_t> &p_data){  };

	virtual void mesh_surface_set_material(RID p_mesh, int p_surface, RID p_material){  };
	virtual RID mesh_surface_get_material(RID p_mesh, int p_surface) const{ return RID(); };

	virtual int mesh_surface_get_array_len(RID p_mesh, int p_surface) const{ return 0; };
	virtual int mesh_surface_get_array_index_len(RID p_mesh, int p_surface) const{ return 0; };

	virtual PoolVector<uint8_t> mesh_surface_get_array(RID p_mesh, int p_surface) const{ return PoolVector<uint8_t>(); };
	virtual PoolVector<uint8_t> mesh_surface_get_index_array(RID p_mesh, int p_surface) const{ return PoolVector<uint8_t>(); };

	virtual Array mesh_surface_get_arrays(RID p_mesh, int p_surface) const;
	virtual Array mesh_surface_get_blend_shape_arrays(RID p_mesh, int p_surface) const;

	virtual uint32_t mesh_surface_get_format(RID p_mesh, int p_surface) const{ return 0; };
	virtual VisualServer::PrimitiveType mesh_surface_get_primitive_type(RID p_mesh, int p_surface) const{ return VisualServer::PrimitiveType::PRIMITIVE_LINES; };

	virtual AABB mesh_surface_get_aabb(RID p_mesh, int p_surface) const{ return AABB(Vector3(0,0,0), Vector3(0,0,0)); };
	virtual Vector<PoolVector<uint8_t> > mesh_surface_get_blend_shapes(RID p_mesh, int p_surface) const{ return Vector<PoolVector<uint8_t>>(); };
	virtual Vector<AABB> mesh_surface_get_skeleton_aabb(RID p_mesh, int p_surface) const{ return Vector<AABB>(); };
	Array _mesh_surface_get_skeleton_aabb_bind(RID p_mesh, int p_surface) const;

	virtual void mesh_remove_surface(RID p_mesh, int p_index){  };
	virtual int mesh_get_surface_count(RID p_mesh) const{ return 0; };

	virtual void mesh_set_custom_aabb(RID p_mesh, const AABB &p_aabb){  };
	virtual AABB mesh_get_custom_aabb(RID p_mesh) const{ return AABB(Vector3(0,0,0), Vector3(0,0,0)); };

	virtual void mesh_clear(RID p_mesh){  };

	/* MULTIMESH API */

	virtual RID multimesh_create(){ return RID(); };

	virtual void multimesh_allocate(RID p_multimesh, int p_instances, MultimeshTransformFormat p_transform_format, MultimeshColorFormat p_color_format, MultimeshCustomDataFormat p_data_format = MULTIMESH_CUSTOM_DATA_NONE){  };
	virtual int multimesh_get_instance_count(RID p_multimesh) const{ return 0; };

	virtual void multimesh_set_mesh(RID p_multimesh, RID p_mesh){  };
	virtual void multimesh_instance_set_transform(RID p_multimesh, int p_index, const Transform &p_transform){  };
	virtual void multimesh_instance_set_transform_2d(RID p_multimesh, int p_index, const Transform2D &p_transform){  };
	virtual void multimesh_instance_set_color(RID p_multimesh, int p_index, const Color &p_color){  };
	virtual void multimesh_instance_set_custom_data(RID p_multimesh, int p_index, const Color &p_color){  };

	virtual RID multimesh_get_mesh(RID p_multimesh) const{ return RID(); };
	virtual AABB multimesh_get_aabb(RID p_multimesh) const{ return AABB(Vector3(0,0,0), Vector3(0,0,0)); };

	virtual Transform multimesh_instance_get_transform(RID p_multimesh, int p_index) const{ return Transform(); };
	virtual Transform2D multimesh_instance_get_transform_2d(RID p_multimesh, int p_index) const{ return Transform2D(); };
	virtual Color multimesh_instance_get_color(RID p_multimesh, int p_index) const{ return Color(); };
	virtual Color multimesh_instance_get_custom_data(RID p_multimesh, int p_index) const{ return Color(); };

	virtual void multimesh_set_as_bulk_array(RID p_multimesh, const PoolVector<float> &p_array){  };

	virtual void multimesh_set_visible_instances(RID p_multimesh, int p_visible){  };
	virtual int multimesh_get_visible_instances(RID p_multimesh) const{ return 0; };

	/* IMMEDIATE API */

	virtual RID immediate_create(){ return RID(); };
	virtual void immediate_begin(RID p_immediate, PrimitiveType p_rimitive, RID p_texture = RID()){  };
	virtual void immediate_vertex(RID p_immediate, const Vector3 &p_vertex){  };
	virtual void immediate_vertex_2d(RID p_immediate, const Vector2 &p_vertex);
	virtual void immediate_normal(RID p_immediate, const Vector3 &p_normal){  };
	virtual void immediate_tangent(RID p_immediate, const Plane &p_tangent){  };
	virtual void immediate_color(RID p_immediate, const Color &p_color){  };
	virtual void immediate_uv(RID p_immediate, const Vector2 &tex_uv){  };
	virtual void immediate_uv2(RID p_immediate, const Vector2 &tex_uv){  };
	virtual void immediate_end(RID p_immediate){  };
	virtual void immediate_clear(RID p_immediate){  };
	virtual void immediate_set_material(RID p_immediate, RID p_material){  };
	virtual RID immediate_get_material(RID p_immediate) const{ return RID(); };

	/* SKELETON API */

	virtual RID skeleton_create(){ return RID(); };
	virtual void skeleton_allocate(RID p_skeleton, int p_bones, bool p_2d_skeleton = false){  };
	virtual int skeleton_get_bone_count(RID p_skeleton) const{ return 0; };
	virtual void skeleton_bone_set_transform(RID p_skeleton, int p_bone, const Transform &p_transform){  };
	virtual Transform skeleton_bone_get_transform(RID p_skeleton, int p_bone) const{ return Transform(); };
	virtual void skeleton_bone_set_transform_2d(RID p_skeleton, int p_bone, const Transform2D &p_transform){  };
	virtual Transform2D skeleton_bone_get_transform_2d(RID p_skeleton, int p_bone) const{ return Transform2D(); };
	virtual void skeleton_set_base_transform_2d(RID p_skeleton, const Transform2D &p_base_transform){  };

	virtual RID directional_light_create(){ return RID(); };
	virtual RID omni_light_create(){ return RID(); };
	virtual RID spot_light_create(){ return RID(); };

	virtual void light_set_color(RID p_light, const Color &p_color){  };
	virtual void light_set_param(RID p_light, LightParam p_param, float p_value){  };
	virtual void light_set_shadow(RID p_light, bool p_enabled){  };
	virtual void light_set_shadow_color(RID p_light, const Color &p_color){  };
	virtual void light_set_projector(RID p_light, RID p_texture){  };
	virtual void light_set_negative(RID p_light, bool p_enable){  };
	virtual void light_set_cull_mask(RID p_light, uint32_t p_mask){  };
	virtual void light_set_reverse_cull_face_mode(RID p_light, bool p_enabled){  };
	virtual void light_set_use_gi(RID p_light, bool p_enable){  };

	virtual void light_set_bake_mode(RID p_light, LightBakeMode p_bake_mode){  };

	virtual void light_omni_set_shadow_mode(RID p_light, LightOmniShadowMode p_mode){  };

	virtual void light_omni_set_shadow_detail(RID p_light, LightOmniShadowDetail p_detail){  };


	virtual void light_directional_set_shadow_mode(RID p_light, LightDirectionalShadowMode p_mode){  };
	virtual void light_directional_set_blend_splits(RID p_light, bool p_enable){  };

	virtual void light_directional_set_shadow_depth_range_mode(RID p_light, LightDirectionalShadowDepthRangeMode p_range_mode){  };

	virtual RID reflection_probe_create(){ return RID(); };

	virtual void reflection_probe_set_update_mode(RID p_probe, ReflectionProbeUpdateMode p_mode){  };
	virtual void reflection_probe_set_intensity(RID p_probe, float p_intensity){  };
	virtual void reflection_probe_set_interior_ambient(RID p_probe, const Color &p_color){  };
	virtual void reflection_probe_set_interior_ambient_energy(RID p_probe, float p_energy){  };
	virtual void reflection_probe_set_interior_ambient_probe_contribution(RID p_probe, float p_contrib){  };
	virtual void reflection_probe_set_max_distance(RID p_probe, float p_distance){  };
	virtual void reflection_probe_set_extents(RID p_probe, const Vector3 &p_extents){  };
	virtual void reflection_probe_set_origin_offset(RID p_probe, const Vector3 &p_offset){  };
	virtual void reflection_probe_set_as_interior(RID p_probe, bool p_enable){  };
	virtual void reflection_probe_set_enable_box_projection(RID p_probe, bool p_enable){  };
	virtual void reflection_probe_set_enable_shadows(RID p_probe, bool p_enable){  };
	virtual void reflection_probe_set_cull_mask(RID p_probe, uint32_t p_layers){  };
	virtual void reflection_probe_set_resolution(RID p_probe, int p_resolution){  };

	/* GI PROBE API */

	virtual RID gi_probe_create(){ return RID(); };

	virtual void gi_probe_set_bounds(RID p_probe, const AABB &p_bounds){  };
	virtual AABB gi_probe_get_bounds(RID p_probe) const{ return AABB(Vector3(0,0,0), Vector3(0,0,0)); };

	virtual void gi_probe_set_cell_size(RID p_probe, float p_range){  };
	virtual float gi_probe_get_cell_size(RID p_probe) const{ return 1.0; };

	virtual void gi_probe_set_to_cell_xform(RID p_probe, const Transform &p_xform){  };
	virtual Transform gi_probe_get_to_cell_xform(RID p_probe) const{ return Transform(); };

	virtual void gi_probe_set_dynamic_data(RID p_probe, const PoolVector<int> &p_data){  };
	virtual PoolVector<int> gi_probe_get_dynamic_data(RID p_probe) const{ return PoolVector<int>(); };

	virtual void gi_probe_set_dynamic_range(RID p_probe, int p_range){  };
	virtual int gi_probe_get_dynamic_range(RID p_probe) const{ return 0; };

	virtual void gi_probe_set_energy(RID p_probe, float p_range){  };
	virtual float gi_probe_get_energy(RID p_probe) const{ return 1.0; };

	virtual void gi_probe_set_bias(RID p_probe, float p_range){  };
	virtual float gi_probe_get_bias(RID p_probe) const{ return 1.0; };

	virtual void gi_probe_set_normal_bias(RID p_probe, float p_range){  };
	virtual float gi_probe_get_normal_bias(RID p_probe) const{ return 1.0; };

	virtual void gi_probe_set_propagation(RID p_probe, float p_range){  };
	virtual float gi_probe_get_propagation(RID p_probe) const{ return 1.0; };

	virtual void gi_probe_set_interior(RID p_probe, bool p_enable){  };
	virtual bool gi_probe_is_interior(RID p_probe) const{ return false; };

	virtual void gi_probe_set_compress(RID p_probe, bool p_enable){  };
	virtual bool gi_probe_is_compressed(RID p_probe) const{ return false; };

	/* LIGHTMAP CAPTURE */

	virtual RID lightmap_capture_create(){ return RID(); };
	virtual void lightmap_capture_set_bounds(RID p_capture, const AABB &p_bounds){  };
	virtual AABB lightmap_capture_get_bounds(RID p_capture) const{ return AABB(Vector3(0,0,0), Vector3(0,0,0)); };
	virtual void lightmap_capture_set_octree(RID p_capture, const PoolVector<uint8_t> &p_octree){  };
	virtual void lightmap_capture_set_octree_cell_transform(RID p_capture, const Transform &p_xform){  };
	virtual Transform lightmap_capture_get_octree_cell_transform(RID p_capture) const{ return Transform(); };
	virtual void lightmap_capture_set_octree_cell_subdiv(RID p_capture, int p_subdiv){  };
	virtual int lightmap_capture_get_octree_cell_subdiv(RID p_capture) const{ return 0; };
	virtual PoolVector<uint8_t> lightmap_capture_get_octree(RID p_capture) const{ return PoolVector<uint8_t>(); };
	virtual void lightmap_capture_set_energy(RID p_capture, float p_energy){  };
	virtual float lightmap_capture_get_energy(RID p_capture) const{ return 1.0; };
	virtual void lightmap_capture_set_interior(RID p_capture, bool p_interior){  };
	virtual bool lightmap_capture_is_interior(RID p_capture) const{ return false; };

	/* PARTICLES API */

	virtual RID particles_create(){ return RID(); };

	virtual void particles_set_emitting(RID p_particles, bool p_emitting){  };
	virtual bool particles_get_emitting(RID p_particles){ return false;  };
	virtual void particles_set_amount(RID p_particles, int p_amount){  };
	virtual void particles_set_lifetime(RID p_particles, float p_lifetime){  };
	virtual void particles_set_one_shot(RID p_particles, bool p_one_shot){  };
	virtual void particles_set_pre_process_time(RID p_particles, float p_time){  };
	virtual void particles_set_explosiveness_ratio(RID p_particles, float p_ratio){  };
	virtual void particles_set_randomness_ratio(RID p_particles, float p_ratio){  };
	virtual void particles_set_custom_aabb(RID p_particles, const AABB &p_aabb){  };
	virtual void particles_set_speed_scale(RID p_particles, float p_scale){  };
	virtual void particles_set_use_local_coordinates(RID p_particles, bool p_enable){  };
	virtual void particles_set_process_material(RID p_particles, RID p_material){  };
	virtual void particles_set_fixed_fps(RID p_particles, int p_fps){  };
	virtual void particles_set_fractional_delta(RID p_particles, bool p_enable){  };
	virtual bool particles_is_inactive(RID p_particles){ return false; };
	virtual void particles_request_process(RID p_particles){  };
	virtual void particles_restart(RID p_particles){  };


	virtual void particles_set_draw_order(RID p_particles, VisualServer::ParticlesDrawOrder p_order){  };

	virtual void particles_set_draw_passes(RID p_particles, int p_count){  };
	virtual void particles_set_draw_pass_mesh(RID p_particles, int p_pass, RID p_mesh){  };

	virtual AABB particles_get_current_aabb(RID p_particles){ return AABB(Vector3(0,0,0), Vector3(0,0,0)); };

	virtual void particles_set_emission_transform(RID p_particles, const Transform &p_transform){  }; //this is only used for 2D, in 3D it's automatic

	/* CAMERA API */

	virtual RID camera_create(){ return RID(); };
	virtual void camera_set_perspective(RID p_camera, float p_fovy_degrees, float p_z_near, float p_z_far){  };
	virtual void camera_set_orthogonal(RID p_camera, float p_size, float p_z_near, float p_z_far){  };
	virtual void camera_set_frustum(RID p_camera, float p_size, Vector2 p_offset, float p_z_near, float p_z_far){  };
	virtual void camera_set_transform(RID p_camera, const Transform &p_transform){  };
	virtual void camera_set_cull_mask(RID p_camera, uint32_t p_layers){  };
	virtual void camera_set_environment(RID p_camera, RID p_env){  };
	virtual void camera_set_use_vertical_aspect(RID p_camera, bool p_enable){  };

	/*
	enum ParticlesCollisionMode {
		PARTICLES_COLLISION_NONE,
		PARTICLES_COLLISION_TEXTURE,
		PARTICLES_COLLISION_CUBEMAP,
	};

	virtual void particles_set_collision(RID p_particles,ParticlesCollisionMode p_mode,const Transform&, p_xform,const RID p_depth_tex,const RID p_normal_tex)=0;
*/
	/* VIEWPORT TARGET API */

	virtual RID viewport_create(){ return RID(); };

	virtual void viewport_set_use_arvr(RID p_viewport, bool p_use_arvr){  };
	virtual void viewport_set_size(RID p_viewport, int p_width, int p_height){  };
	virtual void viewport_set_active(RID p_viewport, bool p_active){  };
	virtual void viewport_set_parent_viewport(RID p_viewport, RID p_parent_viewport){  };

	virtual void viewport_attach_to_screen(RID p_viewport, const Rect2 &p_rect = Rect2(), int p_screen = 0){  };
	virtual void viewport_set_render_direct_to_screen(RID p_viewport, bool p_enable){  };
	virtual void viewport_detach(RID p_viewport){  };

	virtual void viewport_set_update_mode(RID p_viewport, VisualServer::ViewportUpdateMode p_mode){  };
	virtual void viewport_set_vflip(RID p_viewport, bool p_enable){  };

	virtual void viewport_set_clear_mode(RID p_viewport, VisualServer::ViewportClearMode p_clear_mode){  };

	virtual RID viewport_get_texture(RID p_viewport) const{ return RID(); };

	virtual void viewport_set_hide_scenario(RID p_viewport, bool p_hide){  };
	virtual void viewport_set_hide_canvas(RID p_viewport, bool p_hide){  };
	virtual void viewport_set_disable_environment(RID p_viewport, bool p_disable){  };
	virtual void viewport_set_disable_3d(RID p_viewport, bool p_disable){  };
	virtual void viewport_set_keep_3d_linear(RID p_viewport, bool p_disable){  };

	virtual void viewport_attach_camera(RID p_viewport, RID p_camera){  };
	virtual void viewport_set_scenario(RID p_viewport, RID p_scenario){  };
	virtual void viewport_attach_canvas(RID p_viewport, RID p_canvas){  };
	virtual void viewport_remove_canvas(RID p_viewport, RID p_canvas){  };
	virtual void viewport_set_canvas_transform(RID p_viewport, RID p_canvas, const Transform2D &p_offset){  };
	virtual void viewport_set_transparent_background(RID p_viewport, bool p_enabled){  };

	virtual void viewport_set_global_canvas_transform(RID p_viewport, const Transform2D &p_transform){  };
	virtual void viewport_set_canvas_stacking(RID p_viewport, RID p_canvas, int p_layer, int p_sublayer){  };

	virtual void viewport_set_shadow_atlas_size(RID p_viewport, int p_size){  };
	virtual void viewport_set_shadow_atlas_quadrant_subdivision(RID p_viewport, int p_quadrant, int p_subdiv){  };

	virtual void viewport_set_msaa(RID p_viewport, VisualServer::ViewportMSAA p_msaa){  };
	virtual void viewport_set_use_fxaa(RID p_viewport, bool p_fxaa){  };
	virtual void viewport_set_use_debanding(RID p_viewport, bool p_debanding){  };
	virtual void viewport_set_sharpen_intensity(RID p_viewport, float p_intensity){ };

	virtual void viewport_set_hdr(RID p_viewport, bool p_enabled){  };
	virtual void viewport_set_usage(RID p_viewport, VisualServer::ViewportUsage p_usage){  };

	virtual int viewport_get_render_info(RID p_viewport, VisualServer::ViewportRenderInfo p_info){ return 0; };

	virtual void viewport_set_debug_draw(RID p_viewport, VisualServer::ViewportDebugDraw p_draw){  };

	/* ENVIRONMENT API */

	virtual RID environment_create(){ return RID(); };

	virtual void environment_set_background(RID p_env, VisualServer::EnvironmentBG p_bg){  };
	virtual void environment_set_sky(RID p_env, RID p_sky){  };
	virtual void environment_set_sky_custom_fov(RID p_env, float p_scale){  };
	virtual void environment_set_sky_orientation(RID p_env, const Basis &p_orientation){  };
	virtual void environment_set_bg_color(RID p_env, const Color &p_color){  };
	virtual void environment_set_bg_energy(RID p_env, float p_energy){  };
	virtual void environment_set_canvas_max_layer(RID p_env, int p_max_layer){  };
	virtual void environment_set_ambient_light(RID p_env, const Color &p_color, float p_energy = 1.0, float p_sky_contribution = 0.0){  };
	virtual void environment_set_camera_feed_id(RID p_env, int p_camera_feed_id){  };

	virtual void environment_set_dof_blur_near(RID p_env, bool p_enable, float p_distance, float p_transition, float p_far_amount, VisualServer::EnvironmentDOFBlurQuality p_quality){  };
	virtual void environment_set_dof_blur_far(RID p_env, bool p_enable, float p_distance, float p_transition, float p_far_amount, VisualServer::EnvironmentDOFBlurQuality p_quality){  };


	virtual void environment_set_glow(RID p_env, bool p_enable, int p_level_flags, float p_intensity, float p_strength, float p_bloom_threshold, VisualServer::EnvironmentGlowBlendMode p_blend_mode, float p_hdr_bleed_threshold, float p_hdr_bleed_scale, float p_hdr_luminance_cap, bool p_bicubic_upscale, bool p_high_quality){  };

	virtual void environment_set_tonemap(RID p_env, VisualServer::EnvironmentToneMapper p_tone_mapper, float p_exposure, float p_white, bool p_auto_exposure, float p_min_luminance, float p_max_luminance, float p_auto_exp_speed, float p_auto_exp_grey){  };
	virtual void environment_set_adjustment(RID p_env, bool p_enable, float p_brightness, float p_contrast, float p_saturation, RID p_ramp){  };

	virtual void environment_set_ssr(RID p_env, bool p_enable, int p_max_steps, float p_fade_in, float p_fade_out, float p_depth_tolerance, bool p_roughness){  };

	virtual void environment_set_ssao(RID p_env, bool p_enable, float p_radius, float p_intensity, float p_radius2, float p_intensity2, float p_bias, float p_light_affect, float p_ao_channel_affect, const Color &p_color, VisualServer::EnvironmentSSAOQuality p_quality, VisualServer::EnvironmentSSAOBlur p_blur, float p_bilateral_sharpness){  };

	virtual void environment_set_fog(RID p_env, bool p_enable, const Color &p_color, const Color &p_sun_color, float p_sun_amount){  };
	virtual void environment_set_fog_depth(RID p_env, bool p_enable, float p_depth_begin, float p_depth_end, float p_depth_curve, bool p_transmit, float p_transmit_curve){  };
	virtual void environment_set_fog_height(RID p_env, bool p_enable, float p_min_height, float p_max_height, float p_height_curve){  };

	/* SCENARIO API */

	virtual RID scenario_create(){ return RID(); };

	virtual void scenario_set_debug(RID p_scenario, VisualServer::ScenarioDebugMode p_debug_mode){  };
	virtual void scenario_set_environment(RID p_scenario, RID p_environment){  };
	virtual void scenario_set_reflection_atlas_size(RID p_scenario, int p_size, int p_subdiv){  };
	virtual void scenario_set_fallback_environment(RID p_scenario, RID p_environment){  };

	/* INSTANCING API */


	virtual RID instance_create2(RID p_base, RID p_scenario);

	virtual RID instance_create(){ return RID(); };

	virtual void instance_set_base(RID p_instance, RID p_base){  };
	virtual void instance_set_scenario(RID p_instance, RID p_scenario){  };
	virtual void instance_set_layer_mask(RID p_instance, uint32_t p_mask){  };
	virtual void instance_set_transform(RID p_instance, const Transform &p_transform){  };
	virtual void instance_attach_object_instance_id(RID p_instance, ObjectID p_id){  };
	virtual void instance_set_blend_shape_weight(RID p_instance, int p_shape, float p_weight){  };
	virtual void instance_set_surface_material(RID p_instance, int p_surface, RID p_material){  };
	virtual void instance_set_visible(RID p_instance, bool p_visible){  };

	virtual void instance_set_use_lightmap(RID p_instance, RID p_lightmap_instance, RID p_lightmap, int p_lightmap_slice, const Rect2 &p_lightmap_uv_rect){  };

	virtual void instance_set_custom_aabb(RID p_instance, AABB aabb){  };

	virtual void instance_attach_skeleton(RID p_instance, RID p_skeleton){  };
	virtual void instance_set_exterior(RID p_instance, bool p_enabled){  };

	virtual void instance_set_extra_visibility_margin(RID p_instance, real_t p_margin){  };

	virtual void instance_set_portal_mode(RID p_instance, VisualServer::InstancePortalMode p_mode){ };

	virtual RID ghost_create(){ return RID(); }
	virtual void ghost_set_scenario(RID p_ghost, RID p_scenario, ObjectID p_id, const AABB &p_aabb){ };
	virtual void ghost_update(RID p_ghost, const AABB &p_aabb){ };

	virtual RID portal_create(){ return RID(); }
	virtual void portal_set_scenario(RID p_portal, RID p_scenario){ };
	virtual void portal_set_geometry(RID p_portal, const Vector<Vector3> &p_points, real_t p_margin){ };
	virtual void portal_link(RID p_portal, RID p_room_from, RID p_room_to, bool p_two_way){ };
	virtual void portal_set_active(RID p_portal, bool p_active){ };

	// Roomgroups
	virtual RID roomgroup_create(){ return RID(); }
	virtual void roomgroup_prepare(RID p_roomgroup, ObjectID p_roomgroup_object_id){ };
	virtual void roomgroup_set_scenario(RID p_roomgroup, RID p_scenario){ };
	virtual void roomgroup_add_room(RID p_roomgroup, RID p_room){ };

	virtual RID occluder_create(){ return RID(); }
	virtual void occluder_set_scenario(RID p_occluder, RID p_scenario, VisualServer::OccluderType p_type){ };
	virtual void occluder_spheres_update(RID p_occluder, const Vector<Plane> &p_spheres){ };
	virtual void occluder_set_transform(RID p_occluder, const Transform &p_xform){ };
	virtual void occluder_set_active(RID p_occluder, bool p_active){ };
	virtual void set_use_occlusion_culling(bool p_enable){ };

	virtual RID room_create(){ return RID(); }
	virtual void room_set_scenario(RID p_room, RID p_scenario){ };
	virtual void room_add_instance(RID p_room, RID p_instance, const AABB &p_aabb, const Vector<Vector3> &p_object_pts){ };
	virtual void room_add_ghost(RID p_room, ObjectID p_object_id, const AABB &p_aabb){ };
	virtual void room_set_bound(RID p_room, ObjectID p_room_object_id, const Vector<Plane> &p_convex, const AABB &p_aabb, const Vector<Vector3> &p_verts){ };
	virtual void room_prepare(RID p_room, int32_t p_priority){ };
	virtual void rooms_and_portals_clear(RID p_scenario){ };
	virtual void rooms_unload(RID p_scenario, String p_reason){ };
	virtual void rooms_finalize(RID p_scenario, bool p_generate_pvs, bool p_cull_using_pvs, bool p_use_secondary_pvs, bool p_use_signals, String p_pvs_filename, bool p_use_simple_pvs, bool p_log_pvs_generation){ };
	virtual void rooms_override_camera(RID p_scenario, bool p_override, const Vector3 &p_point, const Vector<Plane> *p_convex){ };
	virtual void rooms_set_active(RID p_scenario, bool p_active){ };
	virtual void rooms_set_params(RID p_scenario, int p_portal_depth_limit){ };
	virtual void rooms_set_debug_feature(RID p_scenario, RoomsDebugFeature p_feature, bool p_active){ };
	virtual void rooms_update_gameplay_monitor(RID p_scenario, const Vector<Vector3> &p_camera_positions){ };

	// don't use this in a game!
	virtual bool rooms_is_loaded(RID p_scenario) const { return false; };

	// callbacks are used to send messages back from the visual server to scene tree in thread friendly manner
	virtual void callbacks_register(VisualServerCallbacks *p_callbacks) { };


	// don't use these in a game!
	virtual Vector<ObjectID> instances_cull_aabb(const AABB &p_aabb, RID p_scenario = RID()) const{ return Vector<ObjectID>(); };
	virtual Vector<ObjectID> instances_cull_ray(const Vector3 &p_from, const Vector3 &p_to, RID p_scenario = RID()) const{ return Vector<ObjectID>(); };
	virtual Vector<ObjectID> instances_cull_convex(const Vector<Plane> &p_convex, RID p_scenario = RID()) const{ return Vector<ObjectID>(); };

	Array _instances_cull_aabb_bind(const AABB &p_aabb, RID p_scenario = RID()) const;
	Array _instances_cull_ray_bind(const Vector3 &p_from, const Vector3 &p_to, RID p_scenario = RID()) const;
	Array _instances_cull_convex_bind(const Array &p_convex, RID p_scenario = RID()) const;



	virtual void instance_geometry_set_flag(RID p_instance, VisualServer::InstanceFlags p_flags, bool p_enabled){  };
	virtual void instance_geometry_set_cast_shadows_setting(RID p_instance, VisualServer::ShadowCastingSetting p_shadow_casting_setting){  };
	virtual void instance_geometry_set_material_override(RID p_instance, RID p_material){  };

	virtual void instance_geometry_set_draw_range(RID p_instance, float p_min, float p_max, float p_min_margin, float p_max_margin){  };
	virtual void instance_geometry_set_as_instance_lod(RID p_instance, RID p_as_lod_of_instance){  };

	/* CANVAS (2D) */

	virtual RID canvas_create(){ return RID(); };
	virtual void canvas_set_item_mirroring(RID p_canvas, RID p_item, const Point2 &p_mirroring){  };
	virtual void canvas_set_modulate(RID p_canvas, const Color &p_color){  };
	virtual void canvas_set_parent(RID p_canvas, RID p_parent, float p_scale){  };

	virtual void canvas_set_disable_scale(bool p_disable){  };

	virtual RID canvas_item_create(){ return RID(); };
	virtual void canvas_item_set_parent(RID p_item, RID p_parent){  };

	virtual void canvas_item_set_visible(RID p_item, bool p_visible){  };
	virtual void canvas_item_set_light_mask(RID p_item, int p_mask){  };

	virtual void canvas_item_set_update_when_visible(RID p_item, bool p_update){  };

	virtual void canvas_item_set_transform(RID p_item, const Transform2D &p_transform){  };
	virtual void canvas_item_set_clip(RID p_item, bool p_clip){  };
	virtual void canvas_item_set_distance_field_mode(RID p_item, bool p_enable){  };
	virtual void canvas_item_set_custom_rect(RID p_item, bool p_custom_rect, const Rect2 &p_rect = Rect2()){  };
	virtual void canvas_item_set_modulate(RID p_item, const Color &p_color){  };
	virtual void canvas_item_set_self_modulate(RID p_item, const Color &p_color){  };

	virtual void canvas_item_set_draw_behind_parent(RID p_item, bool p_enable){  };


	virtual void canvas_item_add_line(RID p_item, const Point2 &p_from, const Point2 &p_to, const Color &p_color, float p_width = 1.0, bool p_antialiased = false){  };
	virtual void canvas_item_add_polyline(RID p_item, const Vector<Point2> &p_points, const Vector<Color> &p_colors, float p_width = 1.0, bool p_antialiased = false){  };
	virtual void canvas_item_add_multiline(RID p_item, const Vector<Point2> &p_points, const Vector<Color> &p_colors, float p_width = 1.0, bool p_antialiased = false){  };
	virtual void canvas_item_add_rect(RID p_item, const Rect2 &p_rect, const Color &p_color){  };
	virtual void canvas_item_add_circle(RID p_item, const Point2 &p_pos, float p_radius, const Color &p_color){  };
	virtual void canvas_item_add_texture_rect(RID p_item, const Rect2 &p_rect, RID p_texture, bool p_tile = false, const Color &p_modulate = Color(1, 1, 1), bool p_transpose = false, RID p_normal_map = RID()){  };
	virtual void canvas_item_add_texture_rect_region(RID p_item, const Rect2 &p_rect, RID p_texture, const Rect2 &p_src_rect, const Color &p_modulate = Color(1, 1, 1), bool p_transpose = false, RID p_normal_map = RID(), bool p_clip_uv = false){  };
	virtual void canvas_item_add_nine_patch(RID p_item, const Rect2 &p_rect, const Rect2 &p_source, RID p_texture, const Vector2 &p_topleft, const Vector2 &p_bottomright, VisualServer::NinePatchAxisMode p_x_axis_mode = NINE_PATCH_STRETCH, VisualServer::NinePatchAxisMode p_y_axis_mode = NINE_PATCH_STRETCH, bool p_draw_center = true, const Color &p_modulate = Color(1, 1, 1), RID p_normal_map = RID()){  };
	virtual void canvas_item_add_primitive(RID p_item, const Vector<Point2> &p_points, const Vector<Color> &p_colors, const Vector<Point2> &p_uvs, RID p_texture, float p_width = 1.0, RID p_normal_map = RID()){  };
	virtual void canvas_item_add_polygon(RID p_item, const Vector<Point2> &p_points, const Vector<Color> &p_colors, const Vector<Point2> &p_uvs = Vector<Point2>(), RID p_texture = RID(), RID p_normal_map = RID(), bool p_antialiased = false){  };
	virtual void canvas_item_add_triangle_array(RID p_item, const Vector<int> &p_indices, const Vector<Point2> &p_points, const Vector<Color> &p_colors, const Vector<Point2> &p_uvs = Vector<Point2>(), const Vector<int> &p_bones = Vector<int>(), const Vector<float> &p_weights = Vector<float>(), RID p_texture = RID(), int p_count = -1, RID p_normal_map = RID(), bool p_antialiased = false, bool p_antialiasing_use_indices = false){  };
	virtual void canvas_item_add_mesh(RID p_item, const RID &p_mesh, const Transform2D &p_transform = Transform2D(), const Color &p_modulate = Color(1, 1, 1), RID p_texture = RID(), RID p_normal_map = RID()){  };
	virtual void canvas_item_add_multimesh(RID p_item, RID p_mesh, RID p_texture = RID(), RID p_normal_map = RID()){  };
	virtual void canvas_item_add_particles(RID p_item, RID p_particles, RID p_texture, RID p_normal_map){  };
	virtual void canvas_item_add_set_transform(RID p_item, const Transform2D &p_transform){  };
	virtual void canvas_item_add_clip_ignore(RID p_item, bool p_ignore){  };
	virtual void canvas_item_set_sort_children_by_y(RID p_item, bool p_enable){  };
	virtual void canvas_item_set_z_index(RID p_item, int p_z){  };
	virtual void canvas_item_set_z_as_relative_to_parent(RID p_item, bool p_enable){  };
	virtual void canvas_item_set_copy_to_backbuffer(RID p_item, bool p_enable, const Rect2 &p_rect){  };

	virtual void canvas_item_attach_skeleton(RID p_item, RID p_skeleton){  };

	virtual void canvas_item_clear(RID p_item){  };
	virtual void canvas_item_set_draw_index(RID p_item, int p_index){  };

	virtual void canvas_item_set_material(RID p_item, RID p_material){  };

	virtual void canvas_item_set_use_parent_material(RID p_item, bool p_enable){  };

	virtual RID canvas_light_create(){ return RID(); };
	virtual void canvas_light_attach_to_canvas(RID p_light, RID p_canvas){  };
	virtual void canvas_light_set_enabled(RID p_light, bool p_enabled){  };
	virtual void canvas_light_set_scale(RID p_light, float p_scale){  };
	virtual void canvas_light_set_transform(RID p_light, const Transform2D &p_transform){  };
	virtual void canvas_light_set_texture(RID p_light, RID p_texture){  };
	virtual void canvas_light_set_texture_offset(RID p_light, const Vector2 &p_offset){  };
	virtual void canvas_light_set_color(RID p_light, const Color &p_color){  };
	virtual void canvas_light_set_height(RID p_light, float p_height){  };
	virtual void canvas_light_set_energy(RID p_light, float p_energy){  };
	virtual void canvas_light_set_z_range(RID p_light, int p_min_z, int p_max_z){  };
	virtual void canvas_light_set_layer_range(RID p_light, int p_min_layer, int p_max_layer){  };
	virtual void canvas_light_set_item_cull_mask(RID p_light, int p_mask){  };
	virtual void canvas_light_set_item_shadow_cull_mask(RID p_light, int p_mask){  };

	virtual void canvas_light_set_mode(RID p_light, VisualServer::CanvasLightMode p_mode){  };

	virtual void canvas_light_set_shadow_enabled(RID p_light, bool p_enabled){  };
	virtual void canvas_light_set_shadow_buffer_size(RID p_light, int p_size){  };
	virtual void canvas_light_set_shadow_gradient_length(RID p_light, float p_length){  };
	virtual void canvas_light_set_shadow_filter(RID p_light, VisualServer::CanvasLightShadowFilter p_filter){  };
	virtual void canvas_light_set_shadow_color(RID p_light, const Color &p_color){  };
	virtual void canvas_light_set_shadow_smooth(RID p_light, float p_smooth){  };

	virtual RID canvas_light_occluder_create(){ return RID(); };
	virtual void canvas_light_occluder_attach_to_canvas(RID p_occluder, RID p_canvas){  };
	virtual void canvas_light_occluder_set_enabled(RID p_occluder, bool p_enabled){  };
	virtual void canvas_light_occluder_set_polygon(RID p_occluder, RID p_polygon){  };
	virtual void canvas_light_occluder_set_transform(RID p_occluder, const Transform2D &p_xform){  };
	virtual void canvas_light_occluder_set_light_mask(RID p_occluder, int p_mask){  };

	virtual RID canvas_occluder_polygon_create(){ return RID(); };
	virtual void canvas_occluder_polygon_set_shape(RID p_occluder_polygon, const PoolVector<Vector2> &p_shape, bool p_closed){  };
	virtual void canvas_occluder_polygon_set_shape_as_lines(RID p_occluder_polygon, const PoolVector<Vector2> &p_shape){  };


	virtual void canvas_occluder_polygon_set_cull_mode(RID p_occluder_polygon, CanvasOccluderPolygonCullMode p_mode){  };

	/* BLACK BARS */

	virtual void black_bars_set_margins(int p_left, int p_top, int p_right, int p_bottom){  };
	virtual void black_bars_set_images(RID p_left, RID p_top, RID p_right, RID p_bottom){  };

	/* FREE */

	virtual void free(RID p_rid){ }; ///< free RIDs associated with the visual server

	virtual void request_frame_drawn_callback(Object *p_where, const StringName &p_method, const Variant &p_userdata){  };

	/* EVENT QUEUING */

	virtual void draw(bool p_swap_buffers = true, double frame_step = 0.0){  };
	virtual void sync(){  };
	virtual bool has_changed() const{ return false; };
	virtual void init(){  };
	virtual void finish(){  };

	/* STATUS INFORMATION */

	virtual uint64_t get_render_info(VisualServer::RenderInfo p_info){ return 0; };
	virtual String get_video_adapter_name() const{ return ""; };
	virtual String get_video_adapter_vendor() const{ return ""; };

	/* Materials for 2D on 3D */

	/* TESTING */

	virtual RID get_test_cube(){ return RID(); };

	virtual RID get_test_texture();
	virtual RID get_white_texture();

	virtual RID make_sphere_mesh(int p_lats, int p_lons, float p_radius);

	virtual void mesh_add_surface_from_mesh_data(RID p_mesh, const Geometry::MeshData &p_mesh_data);
	virtual void mesh_add_surface_from_planes(RID p_mesh, const PoolVector<Plane> &p_planes);

	virtual void set_boot_image(const Ref<Image> &p_image, const Color &p_color, bool p_scale, bool p_use_filter = true){  };
	virtual void set_default_clear_color(const Color &p_color){  };
	virtual void set_shader_time_scale(float p_scale){  };

	virtual bool has_feature(VisualServer::Features p_feature) const{ return false; };

	virtual bool has_os_feature(const String &p_feature) const{ return false; };

	virtual void set_debug_generate_wireframes(bool p_generate){  };

	virtual void call_set_use_vsync(bool p_enable){  };

	virtual bool is_low_end() const{ return false; };

	bool is_render_loop_enabled() const;
	void set_render_loop_enabled(bool p_enabled);

	VisualServerDummy();
	virtual ~VisualServerDummy();
};

//typedef VisualServer VS; // makes it easier to use
//#define VS VisualServer

#endif
