import sys

sys.path.append('wafextra')

import sync_exec

OUT = 'build'

def options(opt):
    opt.load('compiler_c ragel')

def configure(conf):
    conf.load('compiler_c ragel')

    conf.env['CFLAGS'] += [ '-DNDEBUG', '-DREGISTER_SIZE=16', '-DISA_8086',
                            '-Wall', '-Werror', '-Wfatal-errors', '-pedantic',
                            '-std=c99']
    conf.env['RAGELFLAGS'] += [ '-C', '-G2' ]
    
def build(bld):
    bld.recurse('ex86')
    bld.recurse('iex86-intel')
