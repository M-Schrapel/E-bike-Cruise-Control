# E-Bike Cruise Control

This repository provides insights into our research on e-bike Cruise Control.

## Contents

- **Cruise Control Implementation**: A basic tutorial for modding eBikes using an Arduino and a MOSFET was added for starting your own implementations at your own risk. 

- **Dataset**: The anonymized dataset of cyclists traveling at unknown speeds can be used to compare your results with future research.

## Technology

Cruise Control (CC), known from cars and trucks, limits automatically your travelled speed. We are doing research on CC applications for e-bikes and have built a prototype that can be implemented on e-bikes from many different manufacturers. Once you reach your desired speed, the motor disengages what makes it hard to further accelerate. If you feel your e-bike is too fast, this is an easy way to reduce your perceived risk.

We tested our technology with different cyclists. Here is an average pattern recorded on a 300m straight road that exemplifies how the technology limits speeds. Different motor modes (Eco, Turbo) were tested and compared to cycling without electric support (None).

![](https://raw.githubusercontent.com/M-Schrapel/E-bike-Cruise-Control/main/Cruise%20Control%20Implementation/Images/route_cycling_pattern_comb.jpg)

We also tested CC at different speeds. Here you find an average cycling patterns from 16 to 22 km/h:

![](https://raw.githubusercontent.com/M-Schrapel/E-bike-Cruise-Control/main/Cruise%20Control%20Implementation/Images/route_cycling_pattern_all.jpg)

CC can effectively reduce your speed and potentially reduce risks of accidents at higher speeds. Please refer to our Implementation folder if you want to modify your own e-bike at your risk.

## Dataset

If you are interested in starting you own research with CC for e-bikes, we provide a dataset containing measured speeds at different motor modes (Eco,Turbo), speeds normalized by the target speed, perceived speeds in relation to the motor modes and target speeds and involved workloads when using CC. Please refer to the subfolder Dataset for more details.
