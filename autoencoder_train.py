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

train_num = train_data.shape[0]
val_num = val_data.shape[0]
test_num = test_data.shape[0]
box_size = train_data.shape[1]

train_data = train_data.reshape([-1, box_size, box_size, box_size, 1])
val_data = val_data.reshape([-1, box_size, box_size, box_size, 1])
test_data = test_data.reshape([-1, box_size, box_size, box_size, 1])

print(train_data.shape)
print(val_data.shape)
print(test_data.shape)

autoencoder = load_model('autoencoder.nii')
decoded_imgs = autoencoder.predict(test_data, batch_size=100)
decoded_imgs = decoded_imgs.reshape(test_num, box_size, box_size, box_size)
print("decoded imgs shape is:")
print(decoded_imgs.shape)

import matplotlib
# Force matplotlib to not use any Xwindows backend.
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

# write back to nii file
nii_file = nii.File("reconstruction.hdf5", "w")
nii_file.create_dataset("recon_mat", decoded_imgs.shape, np.int8)
for i in range(len(decoded_imgs)):
    nii_file["recon_mat"][i] = decoded_imgs[i]

nii_file.close()
print('Reconstruction NII file successfully created.')
