# BCI-Mandala

## Aim:

To develop an EEG driven intervention tool that uses neurofeedback system to help increase attention levels in
children.

## Setup:

1. A mandala was printed on a 4 X 4(ft) sunboard, onto which 206 LEDs were mounted across 6 layers of the mandala.
2. Neurosky mindwave mobile 2 was used for the EEG data.
3. The data from Neurosky was sent to the ATmega- 328 microcontroller via a HC-05 Bluetooth module.
4. 26 shift registers were used to connect 206 LED bulbs in 6 concentric layers.

## Design

For each layer of the mandala a certain threshold of the attention value is set. As the attention levels of the
participant increases subsequently the levels of the Mandala light up. The number of lit layers in the mandala
gives a feedback to the participant

<img width="663" alt="image" src="https://user-images.githubusercontent.com/77855667/154084530-f8746dbc-b6c8-4487-b397-ec05aee10ac3.png">


Images: 

<img width="773" alt="image" src="https://user-images.githubusercontent.com/77855667/154084706-34622d9b-3d51-4770-a756-135d1736cff2.png">
