
env = Environment(CC = 'gcc', \
				  CCFLAGS = '-Wall -Werror -s -Ofast', \
				  LIBS = Split('m z GL GLU SDL SDL_mixer'))

launcher = 'launcher/fge.c'
env.Program(target = 'build/fge', \
			source = Glob('src/*/*.c') + [launcher], \
			CPPPATH = [str(f)+'/extern/' for f in Glob('src/*')])

env.Program(target = 'build/svg2fvz', \
			source = ['util/svg2fvz/svg2fvz.c'], \
			LIBS = Split('z'))
