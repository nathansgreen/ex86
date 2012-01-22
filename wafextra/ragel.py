from waflib import Task
from waflib.TaskGen import extension

class ragel(Task.Task):
    color   = 'BLUE'
    run_str = '${RAGEL} -o ${TGT[0].name} -C ${SRC[0].abspath()}'
    ext_out = ['.c'] # just to make sure

@extension('.rl')
def ragel(self, node):
    out = node.change_ext('.c')
    tsk = self.create_task('ragel', node, [out])
    tsk.cwd = node.parent.get_bld().abspath()
    self.source.append(out)

def configure(conf):
    conf.find_program('ragel', var='RAGEL', mandatory=True)
