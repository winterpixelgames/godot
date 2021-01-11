# The libraries and defines added in this file are the *requirements* that are
# needed to build on the selected platform. Do not add debug/release/optional
# compilation flags here.

################################################################################
# Commands to always run
################################################################################
_target_osx_logo = custom_target(
    'osx_logo',
    output: ['logo.gen.h'],
    input: ['logo.png'],
    command: [SCRIPT_PLATFORM_LOGO, '@INPUT@', '@OUTPUT@', 'osx'],
    build_by_default: true
)
SOURCES += [_target_osx_logo]


################################################################################
# Host Machine Specifics
################################################################################
if PLATFORM == 'osx'
   
   # add the godot linuxbsd main to main sources
   MAIN_SOURCES += files('godot_main_osx.mm')

   # the src files for the linux *platform*
   _macos_srcs = files([
	   'context_gl_osx.mm',
       'crash_handler_osx.mm',
       'dir_access_osx.mm',
       'display_server_osx.mm',
       'joypad_osx.cpp',
       'os_osx.mm',
       'vulkan_context_osx.mm',
   ])

   # get all of our dependencies
   #_cpp = meson.get_compiler('objcpp')
   _macos_deps = [
	   dependency('appleframeworks', modules : ['Foundation', 'Cocoa', 'Carbon', 'AudioUnit', 'CoreAudio', 'CoreMIDI', 'IOKit', 'ForceFeedback', 'CoreVideo', 'AVFoundation', 'CoreMedia']),
	   dependency('threads', method: 'auto'),
   ]

   OSX_ARGS = [
	   '-DOSX_ENABLED',
	   '-DUNIX_ENABLED', 
	   '-DAPPLE_STYLE_KEYS',
	   '-DCOREAUDIO_ENABLED',
	   '-DCOREMIDI_ENABLED',
       '-DVULKAN_ENABLED',
   ]

   CPP_ARGS += OSX_ARGS
   OBJCPP_ARGS += OSX_ARGS

   
   LINK_ARGS += ['-g3', '-Xlinker', '-no_deduplicate', '-framework', 'Metal', '-framework', 'QuartzCore', '-framework', 'IOSurface']

   DEPENDENCIES += _macos_deps
   SOURCES += _macos_srcs
   
endif