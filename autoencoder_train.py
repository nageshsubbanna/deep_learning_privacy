from keras.models import load_model
import nii
import numpy as np
import mrcfile as mrc
import os

from keras import backend as K
K.clear_session()

with h5py.File('object.nii', 'r') as f:
    train_data = f['train_mat'][...]
    val_data = f['val_mat'][...]
    test_data = f['test_mat'][...]

print(train_data.shape)
print(val_data.shape)
print(test_data.shape)

