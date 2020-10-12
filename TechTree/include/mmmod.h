#pragma once
#include <windef.h> // for HINSTANCE

typedef void* mmm_hook;

typedef struct mmm_api {
  // Don't touch this
  void* _mmm_bookkeeping_;
  // Insert an instruction at `orig_address` that JMPs to the given
  // `hook_address`.
  mmm_hook (*hook_jmp)(size_t orig_address, size_t hook_address);
  // Insert an instruction at `orig_address` that CALLs the given
  // `hook_address`.
  mmm_hook (*hook_call)(size_t orig_address, size_t hook_address);
  // Replace the vtable entry at `orig_address` by a pointer to `hook_address`.
  mmm_hook (*hook_vtbl)(size_t orig_address, size_t hook_address);
  // Overwrite some bytes starting at `orig_address`.
  mmm_hook (*patch_bytes)(size_t orig_address, const void* buffer,
                          size_t buf_size);
  // Remove a previously installed hook.
  void (*revert_hook)(mmm_hook hook);
  // Check if the mod named `mod_name` is loaded; case sensitive.
  char (*is_mod_loaded)(const char* mod_name);
} mmm_api;

typedef struct mmm_meta {
  const char* version;
  const char* game_base_dir;
  const char* mod_base_dir;
  const char* mod_short_name;
} mmm_meta;

typedef struct mmm_mod_info {
  HINSTANCE instance;
  mmm_meta* meta;
  const char* name;
  const char* version;
  mmm_api* api;
} mmm_mod_info;
