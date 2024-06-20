import argparse
import os
from tqdm import tqdm
import numpy
import pandas
from sklearn.neighbors import KNeighborsClassifier

parser = argparse.ArgumentParser(description='Experiment runner for shapeon')
parser.add_argument('path', help='Path to UCR archieve')
args = parser.parse_args()
dirs = [f.path for f in os.scandir(args.path) if f.is_dir()]
dirs[:] = [x for x in dirs if "Missing" not in x]              # Not a dataset
dirs[:] = [x for x in dirs if "Gesture" not in x]              # Contains NAN
dirs[:] = [x for x in dirs if "Wiimote" not in x]              # Contains NAN
dirs[:] = [x for x in dirs if "Dodger" not in x]               # Contains NAN
dirs[:] = [x for x in dirs if "PLAID" not in x]                # Contains NAN
dirs[:] = [x for x in dirs if "MelbournePedestrian" not in x]  # Contains NAN

for path in (bar := tqdm(dirs)):
    name = os.path.basename(path)
    bar.set_description('{0:32}'.format(name))
    path_learn = os.path.join(path, name + '_TRAIN.tsv')
    path_test = os.path.join(path, name + '_TEST.tsv')
    data_learn = pandas.read_csv(path_learn, delimiter='\t').to_numpy()
    data_test = pandas.read_csv(path_test, delimiter='\t').to_numpy()
    labels_learn = data_learn[:, 0].astype(int)
    labels_test = data_test[:, 0].astype(int)
    series_learn = numpy.delete(data_learn, 0, axis=1)
    series_test = numpy.delete(data_test, 0, axis=1)
    knn = KNeighborsClassifier(n_neighbors=5)
    knn.fit(series_learn, labels_learn)
    tqdm.write(f'{name}: {knn.score(series_test, labels_test)}')
