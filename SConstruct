import os

lib_name = "GDExample"

sources = Glob("code/src/*.cpp")

output_dir = "godot/bin"

env = Environment()
env.SharedLibrary(target=os.path.join(output_dir, lib_name), source=sources)