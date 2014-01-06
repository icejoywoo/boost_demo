import os

env = Environment(CC = "clang", CXX = "clang++", CXXFLAGS = "-Wall -g -O0")

libs = ['pthread', 'boost_regex', 'boost_signals']
libs_path = []

def simple_compile(dir):
    for sf in Glob(os.path.join(dir, '*.cpp')):
        env.Program(target = sf.name.split('/')[-1][0:-4], 
                    source = [sf], 
                    CPPPATH = [dir], 
                    LIBS = libs, 
                    LIBPATH = libs_path)


simple_compile('src')
simple_compile('ptr')
simple_compile('function')
simple_compile('signal')