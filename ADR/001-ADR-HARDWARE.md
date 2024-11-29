---
# Configuration of the Controller Hardware in SEA:ME context, to control the Racer "Waveshare" 
parent: Decisions
nav_order: 001
title: Architecture Decision Record

## status: proposed
## date: 2024-11-29
## decision-makers: 
   - Nuno Taboada
   - Heitor Maciel
   - Ivo Marques
   - Antonio Ferreira

## consulted: 
  - Felipe Prezado (fp@seame.pt)
  - Pedro Batista (pb@seame.pt)
  - Paulo Silva (ps@seame.pt)
## informed: 
  - Felipe Prezado (fp@seame.pt)
  - Pedro Batista (pb@seame.pt)
  - Paulo Silva (ps@seame.pt)
---

## Context and Problem Statement

Multiple disciplines in automotive control are the driving force for this ADR. The result of this decision addresses the hardware solution to implement an automotive controller that will provide embedded simple solution, interfacing to sensors, advanced drive system and image processing, algorithms, AI and ML
Considering this implementation will be also driven by the pursuit of knowledge and innovation by the decision-makers, it seems fair that the most elevated factor should be knowledge acquisition.

## Decision Drivers

* the features and settings challenges of multiple hardware platforms
* integration of different types of control hardware, from CPU, GPU and MicroController universe of hardware
* implementation of performance issues when implementing in AI and ML
* simple straight forward way off implementing a one controller solution

## Considered Options

* option 1 : JetSon Nano Okdo (JSNano) with CAN HAT : JSNano/CAN
* option 2 : Raspberry Pi 4B with CAN HAT : RPi/CAN
* option 3 : Arduino/CAN + RPi/CAN
* option 4 : Arduino/CAN + JSNano/CAN
* option 5 : Arduino/CAN (sensors) + RPi/IP + JSNano/CAN/IP 

## Decision Outcome

Chosen option:
 ### option 5 : Sensors <-> [i2C,SPI,, Custom] Arduino [CAN]  <-> [CAN] JSNano [IP] <->  [IP] RPi

Because it will provide all technical means to achieve purposes:
- learn multiple platforms
- learn multiple protocols integration
- learn multiple code platforms 
- full implementation

#### Consequences

##### Benefits
* The learning journey most likely will fill the knowledge goals
* The requirements will be easier to implement

##### Drawbacks
 * bulkier car
 * complexity and fail pruner
 * tighter schedule

### Confirmation

At the end of the first product, "DES_Instrument _Cluster", the decision shall be confirmed as  VALID or INVALID
with report of of the pros and cons faced during the first product development.

## Pros and Cons of the Options

Alternative option if not confirmed the first decision:
###  option 4 : Arduino/CAN + JSNano/CAN

Because it will provide all technical means to achieve purposes:
- learn multiple platforms
- learn multiple protocols integration
- learn multiple code platforms 
- full implementation

#### Consequences

##### Benefits
 * minimal control units solution car
 * complexity simpler
 * easier to comply schedule
 
##### Drawbacks
* The learning journey most likely will end up with some  knowledge gaps compare to the goals
* The requirements will be handle harder and rely on software + OS power

