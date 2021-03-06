#!python
import os

# Reads variables from an optional file.
customs = ['../custom.py']
opts = Variables(customs, ARGUMENTS)

# Gets the standart flags CC, CCX, etc.
env = DefaultEnvironment()

# Define our parameters
opts.Add(EnumVariable('target', "Compilation target", 'release', ['d', 'debug', 'r', 'release']))
opts.Add(EnumVariable('platform', "Compilation platform", 'windows', ['windows', 'x11', 'linux', 'osx']))
opts.AddVariables(
    PathVariable('target_path', 'The path where the lib is installed.', 'demo/addons/godot_3dtv/bin/'),
    PathVariable('target_name', 'The library name.', 'libgodot_3dtv', PathVariable.PathAccept),
)
opts.Add(BoolVariable('use_llvm', "Use the LLVM / Clang compiler", 'no'))

# Other needed paths
godot_headers_path = "godot_headers/"

# only support 64 at this time..
bits = 64

# Updates the environment with the option variables.
opts.Update(env)

# Check some environment settings
if env['use_llvm']:
    env['CXX'] = 'clang++'

# Setup everything for our platform
if env['platform'] == 'windows':
    env['target_path'] += 'win64/'
    if not env['use_llvm']:
        # This makes sure to keep the session environment variables on windows,
        # that way you can run scons in a vs 2017 prompt and it will find all the required tools
        env.Append(ENV = os.environ)

        env.Append(CCFLAGS = ['-DWIN32', '-D_WIN32', '-D_WINDOWS', '-W3', '-GR', '-D_CRT_SECURE_NO_WARNINGS'])
        if env['target'] in ('debug', 'd'):
            env.Append(CCFLAGS = ['-EHsc', '-D_DEBUG', '-MDd'])
        else:
            env.Append(CCFLAGS = ['-O2', '-EHsc', '-DNDEBUG', '-MD'])
    # untested
    else:
        if env['target'] in ('debug', 'd'):
            env.Append(CCFLAGS = ['-fPIC', '-g3','-Og', '-std=c++17'])
        else:
            env.Append(CCFLAGS = ['-fPIC', '-g','-O3', '-std=c++17'])

# untested
elif env['platform'] == 'osx':
    env['target_path'] += 'osx/'
    if env['target'] in ('debug', 'd'):
        env.Append(CCFLAGS = ['-g','-O2', '-arch', 'x86_64'])
        env.Append(LINKFLAGS = ['-arch', 'x86_64'])
    else:
        env.Append(CCFLAGS = ['-g','-O3', '-arch', 'x86_64'])
        env.Append(LINKFLAGS = ['-arch', 'x86_64'])

elif env['platform'] in ('x11', 'linux'):
    env['target_path'] += 'x11/'
    if env['target'] in ('debug', 'd'):
        env.Append(CCFLAGS = ['-fPIC', '-g3','-Og', '-std=c++17'])
    else:
        env.Append(CCFLAGS = ['-fPIC', '-g','-O3', '-std=c++17'])

env.Append(CPPPATH=['.', 'src/', godot_headers_path])

sources = Glob('src/*.c')
sources += Glob('src/*.cpp')
sources += Glob('src/*/*.c')
sources += Glob('src/*/*.cpp')

library = env.SharedLibrary(target=env['target_path'] + env['target_name'], source=sources)

Default(library)

# Generates help for the -h scons option.
Help(opts.GenerateHelpText(env))
