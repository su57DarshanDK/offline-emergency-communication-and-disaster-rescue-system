# offline-emergency-communication-and-disaster-rescue-system
# GHOSTLINK X 🚨

## AI-Powered Silent Disaster Rescue & Offline Emergency Communication System

> **"When voices fail, intelligent signals save lives."**

GHOSTLINK X is an **offline emergency communication and disaster rescue system** designed to help trapped survivors communicate with rescue teams when conventional communication infrastructure such as mobile networks, Wi-Fi, or the Internet is unavailable.

The system uses **Morse-code-based tapping**, an **accelerometer for vibration detection**, and **ESP8266 wireless communication** to transmit emergency signals from a victim node to a rescue control node.

A **Raspberry Pi 5** acts as the rescue control center, processing emergency signals, displaying alerts, activating alarms, and providing a foundation for intelligent rescue monitoring.

---

# 📌 Project Overview

During disasters such as:

* Earthquakes
* Building collapses
* Mining accidents
* Industrial accidents
* Landslides
* Military emergencies
* Remote-area emergencies

victims may become trapped and lose access to phones, cellular networks, Wi-Fi, or the Internet.

GHOSTLINK X provides an alternative communication method.

A trapped survivor can:

1. Press a push button to enter Morse code.
2. Tap on a surface to create vibration signals.
3. The accelerometer detects the vibration.
4. Arduino UNO processes the input.
5. Morse code is decoded into an emergency message.
6. ESP8266 transmits the message wirelessly using an offline communication protocol.
7. The rescue node receives the signal.
8. Raspberry Pi 5 processes the emergency information.
9. LCD, LEDs, and buzzer alert the rescue team.
10. The event can be displayed and logged through a rescue dashboard.

---

# 🧠 Core Concept

```text
       TRAPPED SURVIVOR
              │
       Morse / Tapping
              │
              ▼
      ┌─────────────────┐
      │   ACCELEROMETER  │
      │  Vibration Input │
      └────────┬────────┘
               │
               ▼
        ┌──────────────┐
        │  ARDUINO UNO │
        │ Signal Logic │
        └──────┬───────┘
               │
               ▼
        ┌──────────────┐
        │ ESP8266 #1   │
        │ Transmitter  │
        └──────┬───────┘
               │
        OFFLINE WIRELESS
               │
               ▼
        ┌──────────────┐
        │ ESP8266 #2   │
        │  Receiver    │
        └──────┬───────┘
               │
               ▼
       ┌────────────────┐
       │  RASPBERRY PI 5│
       │ Rescue Center  │
       └───────┬────────┘
               │
        ┌──────┼───────┐
        ▼      ▼       ▼
      LCD    BUZZER    LED
        │      │       │
        └──────┴───────┘
           RESCUE ALERT
```

---

# 🛰️ Two-Node Architecture

## Node 1 — Victim Node

The victim node is placed near or under the simulated disaster debris.

### Components

| Component            | Purpose                     |
| -------------------- | --------------------------- |
| Arduino UNO          | Main controller             |
| ESP8266 #1           | Wireless transmitter        |
| Accelerometer        | Detects vibration/tapping   |
| Push Button          | Morse-code input            |
| OLED Display         | Displays victim-side status |
| Active Buzzer Module | Local alert                 |
| LEDs                 | Status indication           |

### Main Responsibilities

* Detect Morse input
* Detect physical vibration
* Process tapping patterns
* Decode Morse messages
* Display status
* Transmit emergency information

---

# 🚑 Node 2 — Rescue Control Node

Node 2 represents the rescue team's control station.

### Components

| Component             | Purpose                   |
| --------------------- | ------------------------- |
| Raspberry Pi 5        | Rescue control computer   |
| ESP8266 #2            | Wireless receiver         |
| RG1602A / RG1G02A LCD | Emergency message display |
| Active Buzzer Module  | Rescue alarm              |
| Red LED               | Emergency indication      |
| Green LED             | System status             |

### Main Responsibilities

* Receive emergency signals
* Process incoming data
* Display emergency messages
* Activate alarms
* Indicate system status
* Run the rescue dashboard
* Store/log emergency events

---

# 📡 Offline Communication

GHOSTLINK X is designed to operate **without Internet connectivity**.

The two ESP8266 modules communicate directly using an offline wireless communication method such as **ESP-NOW**.

### No requirement for:

* ❌ Internet
* ❌ SIM card
* ❌ Mobile tower
* ❌ Bluetooth
* ❌ Cloud server
* ❌ Wi-Fi router

The ESP8266 radios communicate directly between the nodes.

> **Important:** ESP8266/ESP-NOW is suitable for a prototype and short-to-medium-range demonstration. For true kilometer-scale disaster communication, the system can later be upgraded with LoRa or another long-range radio technology.

---

# 🔤 Morse Communication

The survivor can transmit emergency information using Morse code.

Example:

```text
... --- ...
```

represents:

```text
SOS
```

Another example:

```text
.... . .-.. .--.
```

represents:

```text
HELP
```

The system measures the timing between taps to distinguish:

* Dot `.`
* Dash `-`
* Character gap
* Word/message gap

---

# 📳 Accelerometer-Based Detection

The accelerometer acts as the project's **vibration detection mechanism**.

A trapped person can tap:

```text
TAP → TAP → TAP
```

The accelerometer detects changes in acceleration and produces sensor readings.

Arduino analyzes the readings to determine whether the detected activity crosses a configured vibration threshold.

### Possible detection states

```text
No significant movement
        ↓
Monitoring

Vibration detected
        ↓
Possible activity

Repeated vibration pattern
        ↓
Possible survivor signal

Morse pattern detected
        ↓
Emergency message
```

This provides an additional communication method beyond a simple push button.

---

# 🔔 Emergency Alert System

When a valid emergency signal reaches Node 2:

### LCD

```text
SOS RECEIVED
SURVIVOR ALERT
```

### Red LED

```text
EMERGENCY
```

### Active Buzzer

The buzzer activates to alert the rescue team.

### Green LED

Indicates that the rescue system is active and operational.

---

# 🖥️ Raspberry Pi 5 Rescue Center

The Raspberry Pi 5 acts as the central intelligence and monitoring unit.

Possible functions include:

* Emergency signal processing
* Alert prioritization
* Event logging
* Rescue dashboard
* Sensor data monitoring
* Communication status
* Future AI-based signal analysis

Example dashboard:

```text
================================
       GHOSTLINK X
     RESCUE COMMAND
================================

SYSTEM STATUS : ONLINE

NODE 1        : CONNECTED
SIGNAL        : RECEIVED

MESSAGE       : SOS
ALERT LEVEL   : HIGH

VIBRATION     : DETECTED
SURVIVOR      : POSSIBLE

TIME          : 15:42:18

================================
```

---

# 🔄 Complete Working Flow

```text
1. Survivor is trapped
          ↓
2. Survivor taps or enters Morse code
          ↓
3. Accelerometer detects vibration
          ↓
4. Arduino processes the signal
          ↓
5. Morse pattern is decoded
          ↓
6. OLED confirms the emergency
          ↓
7. ESP8266 #1 transmits the data
          ↓
8. ESP8266 #2 receives the data
          ↓
9. Raspberry Pi 5 processes the alert
          ↓
10. LCD displays the emergency
          ↓
11. Red LED activates
          ↓
12. Active buzzer sounds
          ↓
13. Rescue dashboard updates
```

---

# 🧪 Demonstration Scenario

For the project demonstration, create two areas.

## Area 1 — Disaster / Survivor Zone

Create simulated rubble using:

* Cardboard
* Thermocol
* Paper
* Small blocks

Place Node 1 underneath or beside the simulated debris.

Label it:

> **TRAPPED SURVIVOR NODE**

The user taps the debris or uses the Morse button.

---

## Area 2 — Rescue Command Center

Place:

* Raspberry Pi 5
* LCD
* ESP8266 receiver
* LEDs
* Active buzzer
* Monitor

Label it:

> **RESCUE CONTROL CENTER**

When the survivor sends SOS:

```text
Victim Node
     ↓
SOS
     ↓
Wireless Transmission
     ↓
Rescue Node
     ↓
Raspberry Pi 5
     ↓
LCD + Buzzer + LED
```

---

# 🧩 Hardware

## Node 1

* Arduino UNO × 1
* ESP8266 NodeMCU × 1
* Accelerometer × 1
* Push Buttons × 1–3
* OLED Display × 1
* Active Buzzer Module × 1
* LEDs × 2
* Resistors
* Breadboard
* Jumper wires
* Battery/Power Bank

## Node 2

* Raspberry Pi 5 × 1
* ESP8266 NodeMCU × 1
* RG1602A / RG1G02A 16×2 LCD × 1
* Active Buzzer Module × 1
* LEDs × 2
* Resistors
* Jumper wires
* Raspberry Pi power supply
* Monitor/HDMI display

---

# 💻 Software

### Arduino

* Arduino IDE
* C/C++

### Raspberry Pi

* Raspberry Pi OS
* Python 3
* GPIO libraries
* Flask
* Serial/network communication libraries

### Communication

* ESP-NOW
* Wireless peer-to-peer communication

---

# 🌍 Applications

GHOSTLINK X can be adapted for:

### Earthquake Rescue

Detect tapping from people trapped under collapsed structures.

### Mining

Provide emergency communication in underground environments.

### Building Collapse

Allow trapped victims to transmit silent distress signals.

### Military

Provide silent emergency communication in remote environments.

### Industrial Safety

Provide emergency worker signaling in hazardous areas.

### Remote Areas

Provide emergency communication where cellular infrastructure is unavailable.

### Disaster Management

Create decentralized emergency communication networks.

---

# ⭐ Key Features

* ✅ Offline emergency communication
* ✅ Morse-code communication
* ✅ Vibration-based survivor detection
* ✅ ESP8266 wireless communication
* ✅ Two-node architecture
* ✅ Raspberry Pi 5 rescue center
* ✅ LCD emergency display
* ✅ OLED victim display
* ✅ Active buzzer alerts
* ✅ LED status indication
* ✅ Real-time rescue monitoring
* ✅ Expandable architecture

---

# 🚀 Future Enhancements

## 1. LoRa Long-Range Communication

Replace or supplement ESP8266 communication with LoRa to significantly extend communication range.

---

## 2. Multi-Node Rescue Network

Add additional wireless relay nodes:

```text
Victim Node
     ↓
Relay Node 1
     ↓
Relay Node 2
     ↓
Rescue Center
```

This can extend communication coverage across larger disaster areas.

---

## 3. GPS Location

Add GPS to transmit approximate survivor/node coordinates.

---

## 4. AI Survivor Detection

Use Raspberry Pi to analyze:

* vibration patterns
* tapping frequency
* repeated signals
* environmental activity

and estimate whether a signal is likely to be intentional human activity.

---

## 5. Thermal Camera

A thermal camera can help rescue teams search for human presence in difficult environments.

---

## 6. Drone-Based Relay

A drone could carry a wireless relay node over a disaster area to extend communication coverage.

---

# 🔐 Important Design Principle

GHOSTLINK X is designed around one important principle:

> **Communication should not completely depend on infrastructure that may itself be destroyed during a disaster.**

Instead, the system creates a local, decentralized communication path between survivors and rescuers.

---

# 📊 Advantages

| Feature                 | GHOSTLINK X |
| ----------------------- | ----------- |
| Internet required       | No          |
| SIM required            | No          |
| Cellular tower required | No          |
| Bluetooth required      | No          |
| Silent communication    | Yes         |
| Morse communication     | Yes         |
| Vibration detection     | Yes         |
| Wireless communication  | Yes         |
| Rescue alarm            | Yes         |
| Raspberry Pi monitoring | Yes         |
| Expandable              | Yes         |

---

# 🎯 Project Objective

The main objective of GHOSTLINK X is to develop a **low-cost, portable, offline emergency communication system** that allows trapped survivors to transmit distress signals through Morse code and vibration-based interaction, while providing rescue teams with a centralized system for receiving, processing, and responding to those alerts.

---

# 🏆 Why GHOSTLINK X?

Traditional communication systems can become unavailable during disasters.

GHOSTLINK X provides another communication layer:

```text
VOICE ❌
MOBILE NETWORK ❌
INTERNET ❌

        ↓

MORSE + VIBRATION
        ↓
OFFLINE WIRELESS
        ↓
RESCUE CONTROL CENTER
        ↓
HELP 🚨
```

The project combines:

**Embedded Systems + Wireless Communication + Human Safety + Disaster Management + Intelligent Monitoring**

into a single rescue platform.

---

# 📜 License

This project is developed as an educational and prototype disaster-rescue technology project.

It should be further tested, validated, and certified before being used in real emergency or life-critical environments.

---

# 👨‍💻 Project

**GHOSTLINK X**

### AI-Powered Silent Disaster Rescue & Offline Emergency Communication System

> **When voices fail, intelligent signals save lives.**
