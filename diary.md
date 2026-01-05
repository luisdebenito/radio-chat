## 05/12/2025

AFAIK internet works over TCP/IP. I want to know if it is possible to create an infra similar to the one internet has, but with radio, so a custom radio protocol with transmiters and receivers that transfer data. This has probably been done a million times, but why not trying ourselves ah?

We are going to use C++, so plese go ahead and:

```sudo apt install clang```

Time to leave if you are using mac/windows. (says, empowered while writing this into codium, accessing the world wide web through qutebrowser, in his debian + xcfe machine)


**********

To start with this project, we are going to define what are we going to need, the basics, and then, once that is working (hopefully sooner than later), we can invest some time in studying how to improve it.

These are the steps we need for our Radio Protocol, that we are going to call TRRP (Transmitter-Receiver-Radio-Protocol)

1. Set up the hardware for the transmitter.
    - Computer - Lenovo V110-15IKB with Debian 13
    - SDR Transmitter - Which one? TBD

2. Software for the transmitter.
    - Already said that it is going to be C++
    - We need an SDR framework (GNU Radio (?))

3. Workflow of the data
    1. Package the data e.g: [ID][Date][Payload][CRC]
    2. Modulation: Convert the data to a waveform
    3. Transmit the data: feed the SDR with our output

4. Hardware for the receiver:
    - Probably a raspberry pi that tunes to our frequency

5. Software for the receiver:
    - Demodulation: Convert the waveform to data
    - Check integrity using the CRC
    - Read the Payload
    - Show to the end user


I need to check the legality of radio frequencies usage in Spain, cause I know there is some limitation but I am feeling too lazy to dig into them atm



## 06/12/2025

Tomorrow is my brithday, I am turning 30. Happy to reach the 30s like this, tbh. Thank you to everyone that made me as happy as I am =).
Plan for today is to create the headers of each class as imagine them in my head following the workflow described yesterday:

<u>IdGenerator</u>: class in charged of creating a unique ID, I haven't thought about what format will it have. Probably smth like uuid

<u>CRCGenerator</u>: this class is the one computing the payload sent to get a CRC from it, and securing integrity between the transmitter and the receiver.

<u>Message</u>: the message itself, which contains a generated id, the date it was sent and the payload (raw, without any encription for now, TBImplemented in the future)

<u>Package</u>: Obviously there will be some messages big enough that won't be able to be sent in just one "package", or we will need one for one, so this is a package of the original message so the receiver can create them from each of the pieces.

<u>PackageBuilder</u>: Here is where the original message is segmented in N packages so they can be sent through the SDR.

<u>WaveformEncoder</u>: I am really ignorant here, I guess we will need to encode the message so it can be sent in a format the SDR understands, I still need to investigate how.

<u>TransmissionManager</u>: The orchestrator, creates the message, fragmentates it, processes it and sends to the SDRTransmitter

<u>SDRTransmitter</u>: I guess I need to study how tf do we communicate with the SDR

## 10/12/2025

Soooo, let's keep on coding. So far, until we reach the point of creating the waveform and creating the SDR transmitter interface, everything is basically maping the str to a Message to a list of Packages. Easy pc lemon squeezy.

*******

We already have the packages being built, now I need to understand how to create the Waveform for each package.

****
I have decided to create different directories for the common source, the one belonging to transmitting the signal and the one in charge of receiving them.

****
AFAI have read, the most reliable way to create the waveform from the serialized string of the package is using BPSK, we can maybe change it in a future. I can also create the decoder and the creation of the Message out of a list of packages. So goood to continue.


## 11/12/2025

I am going to focus on the transmission for now. I have realiced we'll probably need a queue so we can stack all the waveforms that the device needs to send. I don't know if I will wait for an ACK message back, or just give it an expiration date, and send my messages for like a day to then expire them. 

I am thinking that queue instead of saving it to the RAM memory, should be stored in a bucket or smth. Still to decide. Cause maybe there'll be huge amount of info there, or maybe not. Everything is unknown.


## 03/01/2026

Happy new year. I have explained the whole idea to a couple engineering friends and it doesn't look bad at all. It actually looks promising.
I still need to understand how to encode the signals so the decoder knows where to start decoding among all the noise present in the atnosphere.

I also need to understand if radio antenas placed in top of mountains are there to magnify all radio waves that it detects (?)


## 04/01/2026

I have talked to Javi, my closest telecom engineer friend and has strongly recommended me to use LoRa. Not LoraWan. the difference is that LoraWan ultimately converts the packages into IP ones using the gateway. We want decentralized, P2P, which is more fun and anarchic.

For that, we will change the idea of using an SDR for a LoRa USB Modem. 

Also, I don't need a WaveFormEncoder and anything, just the package themselves. So it makes thing way easier.

Cool, so now we have a loRaSender that consumes the queue and "prints" the serialized package that it'd send, I guess I need to buy a LoRa USB modem.

## 05/01/2026

Until I get the LoRa USB Modem and everything, I think I will do a small class called Chat to collect all the messages sent and received (built from packages). Then at some point I'll use this chat to show it in the screen. Also, I am thinking of creating a json file with the chat history. Would I use a db like sqlite? I could, but sounds overkill atm.

I will use X11 directly, I needed to install de libX11-dev package to properly work with it. It looks ok so far, I have gotten to the point of opening an empty window.