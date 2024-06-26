import argparse
import os
from tqdm import tqdm
import subprocess
from sklearn.neighbors import KNeighborsClassifier
import pandas
import numpy


def eval(path_train, path_test):
    data_train = pandas.read_csv(path_train, sep='\\s+').to_numpy()
    data_test = pandas.read_csv(path_test, sep='\\s+').to_numpy()
    labels_learn = data_train[:, 0].astype(int)
    labels_test = data_test[:, 0].astype(int)
    series_learn = numpy.delete(data_train, 0, axis=1)
    series_test = numpy.delete(data_test, 0, axis=1)
    knn = KNeighborsClassifier(n_neighbors=3)
    knn.fit(series_learn, labels_learn)
    return knn.score(series_test, labels_test)


EXTRACT_PATH = "./extract"
CONVERT_PATH = "./convert"

parser = argparse.ArgumentParser(description='Experiment runner for shapeon')
parser.add_argument(
    'shots', help='How many training examples should be used', type=int)
parser.add_argument('path', help='Path to UCR archieve')
args = parser.parse_args()
shot_count = args.shots

print(f"Shots: {shot_count}")

dirs = [f.path for f in os.scandir(args.path) if f.is_dir()]
dirs[:] = [x for x in dirs if "Missing" not in x]              # Not a dataset
dirs[:] = [x for x in dirs if "Gesture" not in x]              # Contains NAN
dirs[:] = [x for x in dirs if "Wiimote" not in x]              # Contains NAN
dirs[:] = [x for x in dirs if "Dodger" not in x]               # Contains NAN
dirs[:] = [x for x in dirs if "PLAID" not in x]                # Contains NAN
dirs[:] = [x for x in dirs if "MelbournePedestrian" not in x]  # Contains NAN
dirs[:] = [x for x in dirs if "Pig" not in x]  # Too many classes
dirs[:] = [x for x in dirs if "Phoneme" not in x]  # Too many classes
dirs[:] = [x for x in dirs if "Thorax" not in x]  # Too many classes
dirs[:] = [x for x in dirs if "ShapesAll" not in x]  # Too many classes

print(f"Data sets: {len(dirs)}")

for path in (bar := tqdm(dirs)):
    name = os.path.basename(path)
    bar.set_description('{0:32}'.format(name))

    path_learn = os.path.join(path, name + '_TRAIN.tsv')
    path_test = os.path.join(path, name + '_TEST.tsv')

    # Create shotified training file
    classes = set([])
    with open(path_learn) as in_file:
        for line in in_file:
            classes.add(line.partition('\t')[0])
        classes = dict.fromkeys(classes, 0)
    lines = []
    with open(path_learn) as in_file:
        for line in in_file:
            c = line.partition('\t')[0]
            if classes[c] < shot_count:
                classes[c] = classes[c] + 1
                lines.append(line)

    path_shots = "/tmp/utrain.tsv"
    with open(path_shots, "w") as out_file:
        for line in lines:
            out_file.write(line)

    # Extract features
    subprocess.run([EXTRACT_PATH, "/tmp/features.tsv",
                   path_shots], capture_output=True)

    # Convert train and test
    path_processed_train = "/tmp/train.tsv"
    path_processed_test = "/tmp/test.tsv"
    subprocess.run([CONVERT_PATH, path_processed_train, "/tmp/features.tsv",
                    path_shots], capture_output=True)
    subprocess.run([CONVERT_PATH, path_processed_test, "/tmp/features.tsv",
                    path_test], capture_output=True)

    # Eval unprocessed
    score_unprocessed = eval(path_shots, path_test)
    score_processed = eval(path_processed_train, path_processed_test)

    # Print result
    print(f"Before: {score_unprocessed} - After: {score_processed}")
