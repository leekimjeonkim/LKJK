from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import os
import urllib

import numpy as np
import tensorflow as tf

# 데이터셋 초기화, num은 로컬이 아닌 cloud가 나중에 입력되야함
SONG_TRAINING = num + ".CSV"
SONG_TRAINING_URL = "/assets/pattern/"

SONG_TEST = num + ".CSV"
SONG_TEST_URL = "/assets/pattern/"

def main():

  if not os.path.exists(SONG_TRAINING):
    raw = urllib.urlopen(SONG_TRAINING_URL).read()
    with open(SONG_TRAINING, "w") as f:
      f.write(raw)

  if not os.path.exists(SONG_TEST):
    raw = urllib.urlopen(SONG_TEST_URL).read()
    with open(SONG_TEST, "w") as f:
      f.write(raw)

  # 테스트 셋은 향후 오박 부분이 입력되어야함.
  training_set = tf.contrib.learn.datasets.base.load_csv_with_header(
      filename=SONG_TRAINING,
      target_dtype=np.int,
      features_dtype=np.float32)
  test_set = tf.contrib.learn.datasets.base.load_csv_with_header(
      filename=SONG_TEST,
      target_dtype=np.int,
      features_dtype=np.float32)

  # H, S, K 3차원으로 이루어짐
  feature_columns = [tf.contrib.layers.real_valued_column("", dimension=3)]

  # 패턴 12개에 대해서 12 -> 24 -> 12 순으로 분류.
  classifier = tf.contrib.learn.DNNClassifier(feature_columns=feature_columns,
                                              hidden_units=[12, 24, 12],
                                              n_classes=3,
                                              model_dir="/tmp/song_model")
  # 인풋값만 정리해줌
  def get_train_inputs():
    x = tf.constant(training_set.data)
    y = tf.constant(training_set.target)

    return x, y

  # 분류값은 랜덤으로 돌리는게 더 나음
  classifier.fit(input_fn=get_train_inputs, steps=2000)

  # Define the test inputs
  def get_test_inputs():
    x = tf.constant(test_set.data)
    y = tf.constant(test_set.target)

    return x, y

  # accuracy 측정. 500번이상 해야 의미가 있음.
  accuracy_score = classifier.evaluate(input_fn=get_test_inputs,
                                       steps=1)["accuracy"]

  print("\n정확도: {0:f}\n".format(accuracy_score))

  # 예시 샘플 넣어서 테스트.
  def new_samples():
    return np.array(
      [[6.4, 3.2, 4.5],
       [5.8, 3.1, 5.0]], dtype=np.float32)

  predictions = list(classifier.predict(input_fn=new_samples))

  print(
      "샘플 테스트:    {}\n"
      .format(predictions))

if __name__ == "__main__":
    main()