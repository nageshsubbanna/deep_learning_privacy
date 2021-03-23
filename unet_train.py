from __future__ import absolute_import, division, print_function, unicode_literals
import tensorflow as tf
'''
tf.config.optimizer.set_jit(True)
gpus = tf.config.experimental.list_physical_devices('GPU')
if gpus:
  # Restrict TensorFlow to only use the first GPU
  try:
    tf.config.experimental.set_visible_devices(gpus[0], 'GPU')
  except RuntimeError as e:
    # Visible devices must be set at program startup
    print(e)
'''

from tensorflow.keras.optimizers import Adam
from unet_config import*
import os
import datetime
from Unet3D import Unet3D
import numpy as np
import random

def dice_coe(y_true,y_pred, loss_type='jaccard', smooth=1.):

    y_true_f = tf.reshape(y_true,[-1])
    y_pred_f = tf.reshape(y_pred,[-1])

    intersection = tf.reduce_sum(y_true_f * y_pred_f)

    if loss_type == 'jaccard':
        union = tf.reduce_sum(tf.square(y_pred_f)) + tf.reduce_sum(tf.square(y_true_f))

    return (2. * intersection + smooth) / (union + smooth)


    if (NUM_OF_GPU==1):

        if RESUME_TRAINING==1:
            inputs = tf.keras.Input(shape=INPUT_PATCH_SIZE, name='CT')
            Model_3D=Unet3D(inputs,num_classes=NUMBER_OF_CLASSES)
            Model_3D.load_weights(RESUME_TRAIING_MODEL)
            initial_epoch_of_training=TRAINING_INITIAL_EPOCH
            Model_3D.compile(optimizer=OPTIMIZER, loss=[dice_loss], metrics=['accuracy',dice_coe])
            Model_3D.summary()
        else:
            initial_epoch_of_training=0
            inputs = tf.keras.Input(shape=INPUT_PATCH_SIZE, name='CT')
            Model_3D=Unet3D(inputs,num_classes=NUMBER_OF_CLASSES)
            Model_3D.compile(optimizer=OPTIMIZER, loss=[dice_loss], metrics=['accuracy',dice_coe])
            Model_3D.summary()

        Model_3D.fit(traing_data,
                   steps_per_epoch=TRAINING_STEP_PER_EPOCH,
                   epochs=TRAING_EPOCH,
                   initial_epoch=initial_epoch_of_training,
                   validation_data=Val_batched_dataset,
                   validation_steps=VALIDATION_STEP,
                   callbacks=[tensorboard_callback,csv_logger,Model_callback])

if __name__ == '__main__':
   Training()
