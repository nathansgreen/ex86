OUT = 'build'

def options(opt):
    opt.load('compiler_c')

def configure(conf):
    conf.load('compiler_c')
    conf.env.append_value('CFLAGS', '-DREGISTER_SIZE=64')
    conf.env.append_value('CFLAGS', '-Wall')
    conf.env.append_value('CFLAGS', '-Werror')
    conf.env.append_value('CFLAGS', '-pedantic')
    conf.env.append_value('CFLAGS', '-std=c99')
    
def build(bld):
    bld.recurse('ex86')
    bld.recurse('iex86')
