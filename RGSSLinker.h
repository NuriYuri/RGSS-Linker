#pragma once
//---
//RGSSLinker.h
// Fichier d'entête du Linker RGSS pour RGSS104E.dll
// © 2014-2015 Nuri Yuri
//---
#ifdef BUILDING_DLL
#include <stdarg.h>
#define MULTIPLE_ARG va_list vaList
#define _exportRGSSLinker __declspec(dllexport)
#else
#define MULTIPLE_ARG ...
#define _exportRGSSLinker 
#endif

typedef long* VALUE;
typedef long ID;
typedef int* global_entry;

extern "C" {
	//---
	//Initialisation du RGSSLinker
	//---
	_exportRGSSLinker unsigned long RGSSLinker_Initialize(char* library_name);
	//---
	//Export d'un objet commun de Ruby
	//---
	_exportRGSSLinker VALUE RGSSLinker_GetObject(long _internal_object_link);
	//---
	//Link des fonctions primaires du RGSS
	//---
	_exportRGSSLinker void rb_warning(const char*, MULTIPLE_ARG);
	_exportRGSSLinker void rb_raise2(VALUE,const char*, MULTIPLE_ARG);
	_exportRGSSLinker ID rb_to_id(VALUE name);
	_exportRGSSLinker ID global_id(char* name);
	_exportRGSSLinker global_entry rb_global_entry(ID id);
	_exportRGSSLinker ID rb_intern(char* name);
	_exportRGSSLinker const char* rb_id2name(ID id);
	_exportRGSSLinker void rb_attr(VALUE klass,ID id,int read,int write,VALUE extra);
	_exportRGSSLinker void rb_check_type(VALUE x, int t);
	_exportRGSSLinker VALUE rb_obj_alloc(VALUE klass);
	_exportRGSSLinker VALUE str_new(VALUE klass,char* ptr,long length);
	_exportRGSSLinker VALUE rb_str_new(char* ptr,long length);
	_exportRGSSLinker VALUE rb_str_new2(char* ptr);
	_exportRGSSLinker VALUE ary_new(VALUE klass,long length);
	_exportRGSSLinker VALUE rb_ary_new();
	_exportRGSSLinker VALUE rb_ary_new2(long length);
	_exportRGSSLinker VALUE rb_ary_new3(long n, MULTIPLE_ARG);
	_exportRGSSLinker VALUE rb_ary_new4(long n, VALUE* elts);
	_exportRGSSLinker VALUE rb_f_eval(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE eval(VALUE self,VALUE src, VALUE scope, char* filename, int line);
	_exportRGSSLinker VALUE rb_eval_string(char* str);
	_exportRGSSLinker VALUE rb_class_new_instance(int argc,VALUE* argv, VALUE klass);
	_exportRGSSLinker VALUE rb_mod_remove_cvar(VALUE mod,VALUE name);
	_exportRGSSLinker void rb_define_class_variable(VALUE klass,char* name,VALUE val);
	_exportRGSSLinker VALUE rb_cvar_defined(VALUE klass, ID id);
	_exportRGSSLinker void mod_av_set(VALUE klass,ID id,VALUE val,int isconst);
	_exportRGSSLinker VALUE rb_cvar_get(VALUE klass,ID id);
	_exportRGSSLinker void rb_cvar_set(VALUE klass,ID id,VALUE val, int warn);
	_exportRGSSLinker VALUE rb_cv_get(VALUE klass,char* name);
	_exportRGSSLinker void rb_cv_set(VALUE klass,char* name,VALUE val);
	_exportRGSSLinker void rb_const_set(VALUE klass,ID id,VALUE val);
	_exportRGSSLinker void rb_define_const(VALUE klass,char* name,VALUE val);
	_exportRGSSLinker VALUE rb_const_defined_at(VALUE klass,ID id);
	_exportRGSSLinker VALUE rb_const_defined(VALUE klass,ID id);
	_exportRGSSLinker VALUE rb_const_defined_from(VALUE klass,ID id);
	_exportRGSSLinker VALUE rb_const_defined_0(VALUE klass,ID id,VALUE exclude,VALUE recurse);
	_exportRGSSLinker VALUE rb_mod_remove_const(VALUE mod,VALUE name);
	_exportRGSSLinker VALUE rb_const_get_at(VALUE klass,ID id);
	_exportRGSSLinker VALUE rb_const_get(VALUE klass,ID id);
	_exportRGSSLinker VALUE rb_const_get_from(VALUE klass,ID id);
	_exportRGSSLinker VALUE rb_const_get_0(VALUE klass,ID id,VALUE exclude,VALUE recurse);
	_exportRGSSLinker void rb_define_global_const(char* name,VALUE val);
	_exportRGSSLinker VALUE rb_ivar_get(VALUE obj,ID id);
	_exportRGSSLinker VALUE rb_attr_get(VALUE obj,ID id);
	_exportRGSSLinker VALUE rb_ivar_set(VALUE obj,ID id,VALUE val);
	_exportRGSSLinker VALUE rb_ivar_defined(VALUE obj,ID id);
	_exportRGSSLinker VALUE rb_obj_remove_instance_variable(VALUE obj,VALUE name);
	_exportRGSSLinker VALUE rb_iv_get(VALUE obj,char* name);
	_exportRGSSLinker VALUE rb_iv_set(VALUE obj,char* name,VALUE val);
	_exportRGSSLinker VALUE rb_gv_set(char* name,VALUE* val);
	_exportRGSSLinker VALUE rb_gv_get(char* name);
	_exportRGSSLinker VALUE rb_gvar_defined(global_entry entry);
	_exportRGSSLinker VALUE rb_obj_clone(VALUE obj);
	_exportRGSSLinker VALUE rb_obj_dup(VALUE obj);
	_exportRGSSLinker VALUE rb_funcall2(VALUE obj, ID id,int argc,VALUE* argv);
	_exportRGSSLinker VALUE rb_funcall3(VALUE obj, ID id,int argc,VALUE* argv);
	_exportRGSSLinker void rb_define_sigleton_method(VALUE klass,char* name,VALUE(*func)(...),int argc);
	_exportRGSSLinker void rb_define_method(VALUE klass,char* name,VALUE(*func)(...),int argc);
	_exportRGSSLinker void rb_define_global_function(char* name,VALUE(*func)(...),int argc);
	_exportRGSSLinker VALUE rb_define_module(char *name);
	_exportRGSSLinker VALUE rb_define_class_under(VALUE under,char* name,VALUE superclass);
	_exportRGSSLinker VALUE rb_define_class(char* name,VALUE superclass);
	_exportRGSSLinker void rb_undef_method(VALUE klass,char* name);
	_exportRGSSLinker void rb_define_alias(VALUE klass,char* name1,char* name2);
	_exportRGSSLinker void rb_define_attr(VALUE klass,char* name,int read,int write);
	_exportRGSSLinker void rb_define_private_method(VALUE klass,char* name,VALUE(*func)(...),int argc);
	_exportRGSSLinker VALUE rb_data_object_alloc(VALUE klass,void* data,void* dmark,void(*dfree)(...));
#define Data_Wrap_Struct(klass,dmark,dfree,data) \
	rb_data_object_alloc(klass,data,dmark,dfree)
	_exportRGSSLinker void rb_define_alloc_func(VALUE klass,VALUE(*func)(...));
	_exportRGSSLinker void rb_undef_alloc_func(VALUE klass);
	_exportRGSSLinker void* ruby_xmalloc(long size);
	_exportRGSSLinker void* ruby_xcalloc(long n,long size);
	_exportRGSSLinker void* ruby_xrealloc(void* ptr,long size);
	_exportRGSSLinker void ruby_xfree(void* ptr);
	_exportRGSSLinker VALUE rb_protect(VALUE(*proc)(...),VALUE data,long* state);
	_exportRGSSLinker VALUE rb_str_cmp_m(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_str_equal(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_str_hash_m(VALUE self);
	_exportRGSSLinker VALUE rb_str_casecmp(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_str_plus(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_str_times(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_str_format_m(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_str_aref_m(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_aset_m(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_insert(VALUE self, VALUE arg1, VALUE arg2);
	_exportRGSSLinker VALUE rb_str_length(VALUE self);
	_exportRGSSLinker VALUE rb_str_empty(VALUE self);
	_exportRGSSLinker VALUE rb_str_match(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_str_match_m(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_str_succ(VALUE self);
	_exportRGSSLinker VALUE rb_str_succ_bang(VALUE self);
	_exportRGSSLinker VALUE rb_str_upto_m(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_index_m(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_rindex_m(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_replace(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_str_to_i(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_to_f(VALUE self);
	_exportRGSSLinker VALUE rb_str_to_s(VALUE self);
	_exportRGSSLinker VALUE rb_str_inspect(VALUE self);
	_exportRGSSLinker VALUE rb_str_dump(VALUE self);
	_exportRGSSLinker VALUE rb_str_upcase(VALUE self);
	_exportRGSSLinker VALUE rb_str_downcase(VALUE self);
	_exportRGSSLinker VALUE rb_str_capitalize(VALUE self);
	_exportRGSSLinker VALUE rb_str_swapcase(VALUE self);
	_exportRGSSLinker VALUE rb_str_upcase_bang(VALUE self);
	_exportRGSSLinker VALUE rb_str_downcase_bang(VALUE self);
	_exportRGSSLinker VALUE rb_str_capitalize_bang(VALUE self);
	_exportRGSSLinker VALUE rb_str_swapcase_bang(VALUE self);
	_exportRGSSLinker VALUE rb_str_hex(VALUE self);
	_exportRGSSLinker VALUE rb_str_oct(VALUE self);
	_exportRGSSLinker VALUE rb_str_split_m(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_reverse(VALUE self);
	_exportRGSSLinker VALUE rb_str_reverse_bang(VALUE self);
	_exportRGSSLinker VALUE rb_str_concat(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_str_crypt(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_str_intern(VALUE self);
	_exportRGSSLinker VALUE rb_str_include(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_str_scan(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_str_ljust(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_rjust(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_center(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_sub(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_gsub(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_chop(VALUE self);
	_exportRGSSLinker VALUE rb_str_chomp(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_strip(VALUE self);
	_exportRGSSLinker VALUE rb_str_lstrip(VALUE self);
	_exportRGSSLinker VALUE rb_str_rstrip(VALUE self);
	_exportRGSSLinker VALUE rb_str_sub_bang(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_gsub_bang(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_chop_bang(VALUE self);
	_exportRGSSLinker VALUE rb_str_chomp_bang(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_strip_bang(VALUE self);
	_exportRGSSLinker VALUE rb_str_lstrip_bang(VALUE self);
	_exportRGSSLinker VALUE rb_str_rstrip_bang(VALUE self);
	_exportRGSSLinker VALUE rb_str_tr(VALUE self, VALUE arg1, VALUE arg2);
	_exportRGSSLinker VALUE rb_str_tr_s(VALUE self, VALUE arg1, VALUE arg2);
	_exportRGSSLinker VALUE rb_str_delete(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_squeeze(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_count(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_tr_bang(VALUE self, VALUE arg1, VALUE arg2);
	_exportRGSSLinker VALUE rb_str_tr_s_bang(VALUE self, VALUE arg1, VALUE arg2);
	_exportRGSSLinker VALUE rb_str_delete_bang(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_squeeze_bang(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_str_each_line(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_ary_aref(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_ary_fetch(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_ary_index(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_ary_rindex(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_ary_aset(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_ary_insert(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_ary_each_index(VALUE self);
	_exportRGSSLinker VALUE rb_ary_reverse_each(VALUE self);
	_exportRGSSLinker VALUE rb_ary_length(VALUE self);
	_exportRGSSLinker VALUE rb_ary_empty_p(VALUE self);
	_exportRGSSLinker VALUE rb_ary_reverse_bang(VALUE self);
	_exportRGSSLinker VALUE rb_ary_reverse_m(VALUE self);
	_exportRGSSLinker VALUE rb_ary_transpose(VALUE self);
	_exportRGSSLinker VALUE rb_ary_replace(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_ary_fill(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_ary_times(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_ary_equal(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_ary_to_s(VALUE self);
	_exportRGSSLinker VALUE rb_ary_inspect(VALUE self);
	_exportRGSSLinker VALUE rb_ary_eql(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_ary_at(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_ary_first(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_ary_last(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_ary_concat(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_ary_push_m(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_ary_unshift(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_ary_each(VALUE self);
	_exportRGSSLinker VALUE rb_ary_join_m(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_ary_sort(VALUE self);
	_exportRGSSLinker VALUE rb_ary_sort_bang(VALUE self);
	_exportRGSSLinker VALUE rb_ary_collect(VALUE self);
	_exportRGSSLinker VALUE rb_ary_collect_bang(VALUE self);
	_exportRGSSLinker VALUE rb_ary_delete(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_ary_delete_at_m(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_ary_reject(VALUE self);
	_exportRGSSLinker VALUE rb_ary_reject_bang(VALUE self);
	_exportRGSSLinker VALUE rb_ary_clear(VALUE self);
	_exportRGSSLinker VALUE rb_ary_includes(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_ary_compact(VALUE self);
	_exportRGSSLinker VALUE rb_ary_compact_bang(VALUE self);
	_exportRGSSLinker VALUE rb_hash_equal(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_hash_aref(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_hash_aset(VALUE self, VALUE arg1, VALUE arg2);
	_exportRGSSLinker VALUE rb_hash_default(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_hash_set_default(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_hash_index(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_hash_indexes(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_hash_size(VALUE self);
	_exportRGSSLinker VALUE rb_hash_empty_p(VALUE self);
	_exportRGSSLinker VALUE rb_hash_each(VALUE self);
	_exportRGSSLinker VALUE rb_hash_sort(VALUE self);
	_exportRGSSLinker VALUE rb_hash_keys(VALUE self);
	_exportRGSSLinker VALUE rb_hash_values(VALUE self);
	_exportRGSSLinker VALUE rb_hash_shift(VALUE self);
	_exportRGSSLinker VALUE rb_hash_delete(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_hash_select(VALUE self);
	_exportRGSSLinker VALUE rb_hash_reject(VALUE self);
	_exportRGSSLinker VALUE rb_hash_reject_bang(VALUE self);
	_exportRGSSLinker VALUE rb_hash_clear(VALUE self);
	_exportRGSSLinker VALUE rb_hash_invert(VALUE self);
	_exportRGSSLinker VALUE rb_hash_has_key(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_hash_has_value(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_io_reopen(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_io_print(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_io_putc(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_io_puts(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_io_printf(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_io_syswrite(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_io_sysread(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_io_fileno(VALUE self);
	_exportRGSSLinker VALUE rb_io_to_io(VALUE self);
	_exportRGSSLinker VALUE rb_io_fsync(VALUE self);
	_exportRGSSLinker VALUE rb_io_sync(VALUE self);
	_exportRGSSLinker VALUE rb_io_set_sync(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_io_lineno(VALUE self);
	_exportRGSSLinker VALUE rb_io_set_lineno(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_io_readlines(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_io_read(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_io_write_m(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_io_tell(VALUE self);
	_exportRGSSLinker VALUE rb_io_pos(VALUE self);
	_exportRGSSLinker VALUE rb_io_set_pos(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_io_eof(VALUE self);
	_exportRGSSLinker VALUE rb_io_close_m(VALUE self);
	_exportRGSSLinker VALUE rb_io_closed(VALUE self);
	_exportRGSSLinker VALUE rb_io_binmode_m(VALUE self);
	_exportRGSSLinker VALUE zlib_deflate(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE zlib_inflate(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_file_s_directory(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_file_s_exist(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_file_s_readable(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_file_s_writable(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_file_s_file(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_file_s_size(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_file_s_size2(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_file_s_owned(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_file_s_grpowned(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_file_s_pipe(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_file_s_atime(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_file_s_mtime(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_file_s_ctime(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_file_s_utime(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_file_s_chmod(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_file_s_chown(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_file_s_lchmod(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_file_s_lchown(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_file_s_delete(VALUE self, VALUE array_of_arg);
	_exportRGSSLinker VALUE rb_file_s_rename(VALUE self, VALUE arg1, VALUE arg2);
	_exportRGSSLinker VALUE rb_file_s_expand_path(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_file_s_basename(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_file_s_dirname(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_file_s_extname(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_dir_s_chdir(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_dir_s_getwd(VALUE self);
	_exportRGSSLinker VALUE rb_dir_s_chroot(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_dir_s_mkdir(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_dir_s_rmdir(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_dir_s_glob(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rb_dir_s_aref(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_initialize(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_dispose(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_disposed(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_viewport(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_flash(VALUE self, VALUE arg1, VALUE arg2);
	_exportRGSSLinker VALUE rgss_sprite_update(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_bitmap(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_bitmap_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_sprite_src_rect(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_src_rect_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_sprite_visible(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_visible_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_sprite_x(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_x_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_sprite_y(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_y_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_sprite_z(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_z_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_sprite_ox(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_ox_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_sprite_oy(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_oy_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_sprite_zoom_x(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_zoom_x_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_sprite_zoom_y(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_zoom_y_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_sprite_angle(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_angle_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_sprite_mirror(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_mirror_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_sprite_bush_depth(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_bush_depth_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_sprite_opacity(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_opacity_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_sprite_bend_type(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_bend_type_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_sprite_color(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_color_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_sprite_tone(VALUE self);
	_exportRGSSLinker VALUE rgss_sprite_tone_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_plane_initialize(int argc,VALUE* argv,VALUE self);
	_exportRGSSLinker VALUE rgss_plane_dispose(VALUE self);
	_exportRGSSLinker VALUE rgss_plane_disposed(VALUE self);
	_exportRGSSLinker VALUE rgss_plane_viewport(VALUE self);
	_exportRGSSLinker VALUE rgss_plane_bitmap(VALUE self);
	_exportRGSSLinker VALUE rgss_plane_bitmap_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_plane_visible(VALUE self);
	_exportRGSSLinker VALUE rgss_plane_visible_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_plane_z(VALUE self);
	_exportRGSSLinker VALUE rgss_plane_z_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_plane_ox(VALUE self);
	_exportRGSSLinker VALUE rgss_plane_ox_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_plane_oy(VALUE self);
	_exportRGSSLinker VALUE rgss_plane_oy_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_plane_zoom_x(VALUE self);
	_exportRGSSLinker VALUE rgss_plane_zoom_x_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_plane_zoom_y(VALUE self);
	_exportRGSSLinker VALUE rgss_plane_zoom_y_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_plane_opacity(VALUE self);
	_exportRGSSLinker VALUE rgss_plane_opacity_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_plane_bend_type(VALUE self);
	_exportRGSSLinker VALUE rgss_plane_bend_type_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_plane_color(VALUE self);
	_exportRGSSLinker VALUE rgss_plane_color_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rgss_plane_tone(VALUE self);
	_exportRGSSLinker VALUE rgss_plane_tone_set(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_float_add(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_float_sub(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_float_mul(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_float_div(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_float_mod(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_float_divmod(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_float_pow(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_float_equ(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_float_cmp(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_float_sup(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_float_sup_e(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_float_inf(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_float_inf_e(VALUE self, VALUE arg1);
	_exportRGSSLinker VALUE rb_float_abs(VALUE self);
	_exportRGSSLinker VALUE rb_float_to_i(VALUE self);
}

//---
//IDs interne des objets du RGSS
//---
enum RGSSLinkerInternalObjectLinks {
	_id_rb_mKernel,
	_id_rb_cObject,
	_id_rb_cModule,
	_id_rb_cClass,
	_id_rb_cNilClass,
	_id_rb_cSymbol,
	_id_rb_cTrueClass,
	_id_rb_cData,
	_id_rb_cFalseClass,
	_id_rb_cArray,
	_id_rb_cString,
	_id_rb_cFloat,
	_id_rb_cInteger,
	_id_rb_cNumeric,
	_id_rb_eStandardError,
	_id_rb_eTypeError,
	_id_rb_eArgError,
	_id_rb_eIndexError,
	_id_rb_cFile,
	_id_rb_cDir,
  
	_id_rgss_cSprite,
	_id_rgss_cBitmap,
	_id_rgss_cViewport,
	_id_rgss_cRect,
	_id_rgss_cTone,
	_id_rgss_cColor,
	_id_rgss_cFont,
	_id_rgss_mAudio,
	_id_rgss_mGraphics,
	_id_rgss_mInput,
	_id_rgss_cPlane,

	_id_rgsslinker_last_link
};

//---
// Définition des structures et valeurs utiles de Ruby
//---

#define T_NONE   0x00

#define T_NIL    0x01
#define T_OBJECT 0x02
#define T_CLASS  0x03
#define T_ICLASS 0x04
#define T_MODULE 0x05
#define T_FLOAT  0x06
#define T_STRING 0x07
#define T_REGEXP 0x08
#define T_ARRAY  0x09
#define T_FIXNUM 0x0a
#define T_HASH   0x0b
#define T_STRUCT 0x0c
#define T_BIGNUM 0x0d
#define T_FILE   0x0e

#define T_TRUE   0x20
#define T_FALSE  0x21
#define T_DATA   0x22
#define T_MATCH  0x23
#define T_SYMBOL 0x24

#define T_BLKTAG 0x3b
#define T_UNDEF  0x3c
#define T_VARMAP 0x3d
#define T_SCOPE  0x3e
#define T_NODE   0x3f

#define T_MASK   0x3f
//---
//Partie intéressante de st.h
//---

typedef unsigned long st_data_t;
typedef struct st_table_entry st_table_entry;
struct st_table_entry {
    unsigned int hash;
    st_data_t key;
    st_data_t record;
    st_table_entry *next;
};

typedef struct st_table st_table;

struct st_hash_type {
    int (*compare)();
    int (*hash)();
};

struct st_table {
    struct st_hash_type *type;
    int num_bins;
    int num_entries;
    struct st_table_entry **bins;
};

//---
//Structures du ruby
//---
struct RBasic {
    unsigned long flags;
    VALUE klass;
};

struct RObject {
    struct RBasic basic;
    struct st_table *iv_tbl;
};

struct RClass {
    struct RBasic basic;
    struct st_table *iv_tbl;
    struct st_table *m_tbl;
    VALUE super;
};

struct RFloat {
    struct RBasic basic;
    double value;
};

struct RString {
    struct RBasic basic;
    long len;
    char *ptr;
    union {
	long capa;
	VALUE shared;
    } aux;
};

struct RArray {
    struct RBasic basic;
    long len;
    union {
	long capa;
	VALUE shared;
    } aux;
    VALUE *ptr;
};

struct RFile {
    struct RBasic basic;
    struct rb_io_t *fptr;
};

struct RData {
    struct RBasic basic;
    void (*dmark);
    void (*dfree);
    void *data;
};

struct RBignum {
    struct RBasic basic;
    char sign;
    long len;
    void *digits;
};

struct RGSSCOLOR {
    struct RBasic basic;
    void (*dmark)(void*);
    void (*dfree)(void*);
    double *data;
};
 
struct RGSSBMINFO{
    DWORD unk1;
    DWORD unk2;
    BITMAPINFOHEADER *infoheader;
    LPBYTE firstRow;
    LPBYTE lastRow;
};
 
struct BITMAPSTRUCT {
    DWORD unk1;
    DWORD unk2;
    RGSSBMINFO *bminfo;
};
 
struct RGSSBITMAP {
    struct RBasic basic;
    void (*dmark)(void*);
    void (*dfree)(void*);
    BITMAPSTRUCT *bm;
};


#define R_CAST(st)   (struct st*)
#define RBASIC(obj)  (R_CAST(RBasic)(obj))
#define ROBJECT(obj) (R_CAST(RObject)(obj))
#define RCLASS(obj)  (R_CAST(RClass)(obj))
#define RMODULE(obj) RCLASS(obj)
#define RFLOAT(obj)  (R_CAST(RFloat)(obj))
#define RSTRING(obj) (R_CAST(RString)(obj))
#define RARRAY(obj)  (R_CAST(RArray)(obj))
#define RDATA(obj)   (R_CAST(RData)(obj))
#define RBIGNUM(obj) (R_CAST(RBignum)(obj))
#define RFILE(obj)   (R_CAST(RFile)(obj))
#define RBITMAP(obj)   (R_CAST(RGSSBITMAP)(obj))

#define RGSSConst(obj) (*(int*)rgss_ptr(obj))
#define LONG2FIX(value) ((value)<<1)|1
#define FIX2LONG(value) ((value)>>1)

#define RSTRING_LEN(str) \
	RSTRING(str)->len
#define RSTRING_PTR(str) \
	RSTRING(str)->ptr