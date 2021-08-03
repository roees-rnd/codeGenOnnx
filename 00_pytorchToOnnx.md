### Saving module as pickle:
locate network moule (has a base model torch.nn.Module)
```python
import pickle
with open('model31.pkl', 'wb') as fid:
    pickle.dump(self.actor, fid)  # only one that was relevant
    pickle.dump(self.actor.forward, fid)
    pickle.dump(state, fid)

```


### Converting torch pickeled module to onnx:
```python
import torch.nn.init as init
import torch.onnx
from part1 import policies
from policies import *

with open('../model31.pkl','rb') as fid:
    actor = pickle.load(fid)
    actor_forward = pickle.load(fid)
    state = pickle.load(fid)

torch.onnx.export(actor,
    state,
    "model31.onnx",
    export_params=True,
    opset_version=10,
    do_constant_folding=True,
    input_names = ['input'],
    output_names = ['output'],
    dynamic_axes={'input' : {0 : 'batch_size'},
    'output' : {0 : 'batch_size'}})

```