# PD-KNN

The repository contains a Pure Data  implementation of the K Nearest Neighbors (KNN) machine learning algorithm. The external can be compiled and built using the `MAKE` file.

A sample Pure Data patch `gyrosc.pd` is included that uses the `KNN` external to learn inputs from the GyrOSC mobile application.

**** 

## PD Externals

Pure Data externals are written using the `C` programming language. When the `KNN` library is first loaded into Pure Data, the `KNN_setup` function is called. The function initializes the class prototype. When `KNN`  is first loaded into a patch, the `KNN_new` function is called. The function uses the previously intialized class prototype to instantiate an object in memory.

The `add` and `test` methods are triggered whenever an `add` or `test` message is sent to the object, respectively.

The external requires two input arguments when loaded, `k` and `size`. The size is the dimension of the input.

****

## Example

The `gyrosc.pd` is an example of a patch that utilizes the `KNN` external to learn on inputs from the GyrOSC mobile application. Download the GyrOSC mobile application and set the target IP Address to your local host. The author of this project has found it necessary for both the mobile phone and the machine running `gyrosc.pd` to be in the same network. Set the Port to 9999, which is the port used by the `gyrosc.pd` patch. In the settings page of the GyrOSC mobile application, toggle on Gyroscope.

Once the `gyrosc.pd` patch is open, click on `port 9999` to start receiving input from. Check the toggle labeled "block gyrOSC input" to allow input stream. On the right hand side of the interface, check the toggle labelled "begin adding/testing" to allow input stream into the `KNN` external. Note that the `KNN` external has been intialized with `k` set to 5 and `size` set to `3`.

Place the mobile phone in different position and toggle the input stream after setting the `CLASS_ID` to label the input stream. After having recorded different data points, you can begin testing by clicking on the `test` message. The `KNN` external will output the corresponding `CLASS_ID` of the phone orientation.

**** 

## KNN Algorithm

K-Nearest Neighbor is a machine learning algorithm that is used to classify data. 

**How does it work?**

1. Euclidian distance from the test point to each point in the dataset is calculated.
2. Points are then sorted according to their relative distance to the test point.
3. First k neighbors in the sorted neighbor set are selected
4. A prediction regarding the classification of the test point is made by selecting the class that occurs most frequently within the set of k nearest neighbors.

**Euclidian distance formula**

<img src="https://latex.codecogs.com/gif.latex?\sqrt&space;{\sum_{i=1}^{n}&space;{(x_i&space;-&space;y_i)^2}}" title="\sqrt {\sum_{i=1}^{n} {(x_i - y_i)^2}}" />

