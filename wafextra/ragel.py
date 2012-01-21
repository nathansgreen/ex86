from waflib import Task
from waflib.TaskGen import extension

class ragel(Task.Task):
    color   = 'BLUE'
    run_str = '${RAGEL} ${SRC[0].abspath()} -o ${TGT[0].name}'
    ext_out = ['.c'] # just to make sure

@extension('.rl')
def ragel(self, node):
    out = node.change_ext('.c')
    self.source.append(out)
    tsk = self.create_task('ragel')
    tsk.set_inputs(node)
    tsk.set_outputs(out)

def configure(conf):
    conf.find_program('ragel', var='RAGEL', mandatory=True)
