env = Environment(CC = "clang", CXX = "clang++", CXXFLAGS = "-Wall -g -O0")

libs = ['pthread', 'boost_regex']
libs_path = []

for sf in Glob('src/*.cpp'):
    env.Program(target = sf.name.split('/')[-1][0:-4], 
                source = [sf], 
                CPPPATH = ['src'], 
                LIBS = libs, 
                LIBPATH = libs_path)

for sf in Glob('ptr/*.cpp'):
    env.Program(target = sf.name.split('/')[-1][0:-4], 
                source = [sf], 
                CPPPATH = ['src'], 
                LIBS = libs, 
                LIBPATH = libs_path)