

env = Environment(CXX='clang++',CPPPATH="include",SCONS_CXX_STANDARD="c++17")
src = Glob("src/*.cpp")
src.append(Glob("src/imgui/*.cpp"))
env.Program('bin/GraphVis',src,LIBS=["SDL2"])
