import sys
from waflib.Build import BuildContext
from waflib import Utils, Logs

def exec_command(self, cmd, **kw):
    subprocess = Utils.subprocess
    kw['shell'] = isinstance(cmd, str)
    Logs.debug('runner: %r' % cmd)
    Logs.debug('runner_env: kw=%s' % kw)
    try:
        kw['stdout'] = kw['stderr'] = subprocess.PIPE
        p = subprocess.Popen(cmd, **kw)
        (out, err) = p.communicate()
        if out:
            sys.stdout.write(out.decode(sys.stdout.encoding or 'iso8859-1'))
        if err:
            sys.stdout.write(err.decode(sys.stdout.encoding or 'iso8859-1'))
        return p.returncode
    except OSError:
        return -1

BuildContext.exec_command = exec_command

OUT = 'build'

def options(opt):
    opt.load('compiler_c flex bison')

def configure(conf):
    conf.load('compiler_c flex bison')

    conf.env.append_value('CFLAGS', '-DNDEBUG')
    conf.env.append_value('CFLAGS', '-DREGISTER_SIZE=16')
    conf.env.append_value('CFLAGS', '-DISA_8086')
    conf.env.append_value('CFLAGS', '-DSYNTAX_INTEL')
    conf.env.append_value('CFLAGS', '-Wall')
    conf.env.append_value('CFLAGS', '-Werror')
    conf.env.append_value('CFLAGS', '-Wfatal-errors')
    conf.env.append_value('CFLAGS', '-pedantic')
    conf.env.append_value('CFLAGS', '-std=c99')
    
def build(bld):
    bld.recurse('ex86')
    bld.recurse('iex86-intel')
