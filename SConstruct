
env = Environment(CC = 'gcc', \
				  CCFLAGS = '-Wall -Werror -s -O3', \
				  LIBS = Split('m GL glut openal vorbisfile'))

launcher = 'launcher/fge.c'
env.Program(target = 'fge', \
			source = Glob('src/*/*.c') + [launcher],\
			CPPPATH = [str(f)+'/extern/' for f in Glob('src/*')])

